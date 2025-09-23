#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <esp_now.h>
#include <ui/ui.h>
#include <ui/actions.h>
#include <ui/vars.h>
#include <WiFi.h>
#include <uitools.h>
#include <Preferences.h>
#include <esp_wifi.h>
#include <esp_system.h>
#include <esp_mac.h>
#include <driver/gpio.h>

// const confs
constexpr uint8_t RECEIVER_MACS[][6] = {
    {0xF0, 0xF5, 0xBD, 0x2C, 0x03, 0x84}, // Receiver 0
    {0x1C, 0x69, 0x20, 0xCE, 0x68, 0x50}, // Receiver 1 - deprecated
    {0xF0, 0xF5, 0xBD, 0x2C, 0x08, 0xF4}  // Receiver 2
};
constexpr size_t NUM_RECEIVERS = sizeof(RECEIVER_MACS) / sizeof(RECEIVER_MACS[0]);
constexpr uint32_t SEND_INTERVAL = 100;
constexpr uint32_t LED_UPDATE_INTERVAL = 500;
constexpr uint32_t INACTIVITY_TIMEOUT = 600000;
constexpr uint32_t PIR_INACTIVITY_MS = 2000;
constexpr uint8_t BACKLIGHT_ACTIVE = 1.0f;
constexpr uint8_t BACKLIGHT_INACTIVE = 0;
constexpr uint8_t MASTER_CHANNEL = 1;
constexpr gpio_num_t pirPin = GPIO_NUM_22;

// Message protocol: header + fixed payloads
#pragma pack(push, 1)
enum MsgType : uint8_t
{
  MSG_CMD = 1,
  MSG_TELEMETRY = 2,
  MSG_ACK = 3
};

struct MsgHdr
{
  uint8_t magic;   // 0xA5
  uint8_t version; // 0x01
  uint8_t type;    // MsgType
  uint8_t channel; // 0..N-1
  uint16_t len;    // payload length
  uint16_t seq;    // sequence id
  uint16_t crc;    // CRC16-CCITT over header(with crc=0) + payload
};

struct CmdPayload
{
  uint16_t brightness; // 0..100
  uint8_t state;       // 0/1
  uint8_t reqTelem;    // 0/1 request telemetry
};

struct TelemetryPayload
{
  uint16_t appliedBrightness; // 0..100 actually set
  uint8_t appliedState;       // 0/1 actually set
  uint16_t halfVoltageMv;     // half of battery voltage in mV (e.g., 1890)
  uint32_t operatingHours;    // total operating hours
  uint32_t lastChargedDate;   // device-defined
};
#pragma pack(pop)

// receiver struct
struct Receiver
{
  uint8_t mac[6];
  esp_now_peer_info_t peerInfo;
  // desired (master)
  uint16_t desiredBrightness;
  bool desiredState;
  // last telemetry
  TelemetryPayload telemetry;
  // set when new telemetry arrives (handled in loop task)
  volatile bool telemetryDirty;
  uint32_t lastSend;
};

// global variables
Receiver receivers[NUM_RECEIVERS];
auto lv_last_tick = millis();
Preferences preferences;

// Function definitions
void messageReceived(const esp_now_recv_info *info, const uint8_t *data, int len);
void updateBacklight();
void sendMessage(Receiver &receiver);
void sendAck(Receiver &receiver, uint8_t channel, uint16_t seq);
void initESPNow();
void action_switch_led(lv_event_t *e);
void updateBatteryPercentage();
float calculateBatteryPercentage(float voltage);
void setLEDState();
bool getLEDState(char preset);
void printMasterMac();

void initESPNow()
{
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("ESP-NOW initialisation failed");
    return;
  }

  // (optional aber hilfreich in EU)
  wifi_country_t c = {.cc = "EU", .schan = 1, .nchan = 13, .policy = WIFI_COUNTRY_POLICY_MANUAL};
  esp_wifi_set_country(&c);

  // Kanal hart setzen
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(MASTER_CHANNEL, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);

  // WICHTIG: peerInfo.channel = MASTER_CHANNEL (NICHT 0!)
  for (size_t i = 0; i < NUM_RECEIVERS; i++)
  {
    memcpy(receivers[i].mac, RECEIVER_MACS[i], 6);
    memcpy(receivers[i].peerInfo.peer_addr, receivers[i].mac, 6);
    receivers[i].peerInfo.channel = MASTER_CHANNEL; // <- statt 0
    receivers[i].peerInfo.encrypt = false;

    // Initialize desired brightness from UI vars per channel
    switch (i)
    {
    case 0:
      receivers[i].desiredBrightness = (int)get_var_brightness_led1();
      break;
    case 1:
      receivers[i].desiredBrightness = (int)get_var_brightness_led2();
      break;
    case 2:
      receivers[i].desiredBrightness = (int)get_var_brightness_led3();
      break;
    default:
      // receivers[i].desiredBrightness = 0;
      break;
    }
    receivers[i].desiredState = getLEDState('1' + i);
    receivers[i].telemetry = {};

    if (esp_now_add_peer(&receivers[i].peerInfo) != ESP_OK)
    {
      Serial.printf("Adding Peer %d failed\n", i);
    }
  }

  set_var_state_led1(receivers[0].desiredState);
  set_var_state_led2(receivers[1].desiredState);
  set_var_state_led3(receivers[2].desiredState);

  esp_now_register_recv_cb(messageReceived);
  Serial.println("ESP-NOW initialised");
  printMasterMac();
}

// CRC16-CCITT (0x1021) helper
static uint16_t crc16_ccitt(const uint8_t *buf, size_t len)
{
  uint16_t crc = 0xFFFF;
  for (size_t i = 0; i < len; ++i)
  {
    crc ^= (uint16_t)buf[i] << 8;
    for (int b = 0; b < 8; ++b)
    {
      if (crc & 0x8000)
        crc = (crc << 1) ^ 0x1021;
      else
        crc <<= 1;
    }
  }
  return crc;
}

void printMasterMac()
{
  uint8_t mac[6];
  esp_read_mac(mac, ESP_MAC_WIFI_STA);
  Serial.printf("Master STA MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void sendAck(Receiver &receiver, uint8_t channel, uint16_t seq)
{
  // Echo the telemetry sequence so the slave can confirm the handshake before sleeping.
  MsgHdr ack{};
  ack.magic = 0xA5;
  ack.version = 0x01;
  ack.type = MSG_ACK;
  ack.channel = channel;
  ack.len = 0;
  ack.seq = seq;
  ack.crc = 0;

  uint16_t crc = crc16_ccitt(reinterpret_cast<const uint8_t *>(&ack), sizeof(MsgHdr));
  ack.crc = crc;

  esp_err_t result = esp_now_send(receiver.mac, reinterpret_cast<const uint8_t *>(&ack), sizeof(MsgHdr));
  if (result != ESP_OK)
  {
    Serial.printf("Error sending ACK to %02X:%02X:%02X:%02X:%02X:%02X\n",
                  receiver.mac[0], receiver.mac[1], receiver.mac[2],
                  receiver.mac[3], receiver.mac[4], receiver.mac[5]);
  }
}

// Callback function for received ESP-NOW messages
void IRAM_ATTR messageReceived(const esp_now_recv_info *info, const uint8_t *data, int len)
{
  const uint8_t *mac = info ? info->src_addr : nullptr;
  for (auto &receiver : receivers)
  {
    if (mac && memcmp(mac, receiver.mac, 6) == 0)
    {
      // Parse message header + payload
      if (len >= (int)sizeof(MsgHdr))
      {
        const MsgHdr *hdr = reinterpret_cast<const MsgHdr *>(data);
        if (hdr->magic == 0xA5 && hdr->version == 0x01 && hdr->len + sizeof(MsgHdr) == (uint16_t)len)
        {
          // Verify CRC
          MsgHdr tmp = *hdr;
          tmp.crc = 0;
          uint16_t crc = crc16_ccitt(reinterpret_cast<const uint8_t *>(&tmp), sizeof(MsgHdr));
          uint16_t tail = crc16_ccitt(reinterpret_cast<const uint8_t *>(data) + sizeof(MsgHdr), hdr->len);
          crc ^= tail;
          if (crc == hdr->crc)
          {
            const uint8_t *payload = reinterpret_cast<const uint8_t *>(data) + sizeof(MsgHdr);
            if (hdr->type == MSG_ACK)
            {
              Serial.printf("ACK %02X:%02X:%02X:%02X:%02X:%02X ch%u seq%u\n",
                            mac ? mac[0] : 0, mac ? mac[1] : 0, mac ? mac[2] : 0, mac ? mac[3] : 0, mac ? mac[4] : 0, mac ? mac[5] : 0,
                            hdr->channel, hdr->seq);
            }
            else if (hdr->type == MSG_TELEMETRY && hdr->len == sizeof(TelemetryPayload))
            {
              memcpy(&receiver.telemetry, payload, sizeof(TelemetryPayload));
              // Mark for UI update in loop task (avoid calling LVGL from WiFi/ESPNOW context)
              receiver.telemetryDirty = true;
              sendAck(receiver, hdr->channel, hdr->seq);
              Serial.printf("TELEM %02X:%02X:%02X:%02X:%02X:%02X ch%u seq%u: bright=%u, state=%u, halfV=%u, hours=%u, date=%u\n",
                            mac ? mac[0] : 0, mac ? mac[1] : 0, mac ? mac[2] : 0, mac ? mac[3] : 0, mac ? mac[4] : 0, mac ? mac[5] : 0,
                            hdr->channel, hdr->seq,
                            (unsigned)receiver.telemetry.appliedBrightness,
                            (unsigned)receiver.telemetry.appliedState,
                            (unsigned)receiver.telemetry.halfVoltageMv,
                            (unsigned)receiver.telemetry.operatingHours,
                            (unsigned)receiver.telemetry.lastChargedDate);
            }
          }
        }
      }
      break;
    }
  }
}

void sendMessage(Receiver &receiver)
{
  // Update desired from UI variables before sending (map receiver to channel)
  size_t idx = NUM_RECEIVERS; // invalid by default
  for (size_t i = 0; i < NUM_RECEIVERS; ++i)
  {
    if (&receivers[i] == &receiver)
    {
      idx = i;
      break;
    }
  }
  if (idx < 3)
  {
    switch (idx)
    {
    case 0:
      receiver.desiredBrightness = (int)get_var_brightness_led1();
      receiver.desiredState = get_var_state_led1();
      break;
    case 1:
      receiver.desiredBrightness = (int)get_var_brightness_led2();
      receiver.desiredState = get_var_state_led2();
      break;
    case 2:
      receiver.desiredBrightness = (int)get_var_brightness_led3();
      receiver.desiredState = get_var_state_led3();
      break;
    }

    // Persist brightness to NVS only if changed to survive reboots
    static uint32_t lastSavedBrightness[3] = {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu};
    if (lastSavedBrightness[idx] != receiver.desiredBrightness)
    {
      preferences.begin("framecontrol", false);
      char key[16];
      snprintf(key, sizeof(key), "brightness_led%u", (unsigned)(idx + 1));
      preferences.putUInt(key, receiver.desiredBrightness);
      preferences.end();
      lastSavedBrightness[idx] = receiver.desiredBrightness;
    }
  }
  // Build command packet
  CmdPayload cmd{};
  cmd.brightness = (uint16_t)receiver.desiredBrightness;
  cmd.state = receiver.desiredState ? 1 : 0;
  cmd.reqTelem = 1;

  MsgHdr hdr{};
  hdr.magic = 0xA5;
  hdr.version = 0x01;
  hdr.type = MSG_CMD;
  hdr.channel = (uint8_t)idx;
  hdr.len = sizeof(CmdPayload);
  // Randomize the handshake sequence to avoid any shared state on the master.
  uint16_t seq = static_cast<uint16_t>(esp_random() & 0xFFFF);
  if (seq == 0)
  {
    seq = 1;
  }
  hdr.seq = seq;
  hdr.crc = 0;

  uint8_t buffer[sizeof(MsgHdr) + sizeof(CmdPayload)];
  memcpy(buffer, &hdr, sizeof(MsgHdr));
  memcpy(buffer + sizeof(MsgHdr), &cmd, sizeof(CmdPayload));
  uint16_t crc = crc16_ccitt(buffer, sizeof(MsgHdr));
  crc ^= crc16_ccitt(buffer + sizeof(MsgHdr), sizeof(CmdPayload));
  reinterpret_cast<MsgHdr *>(buffer)->crc = crc;

  esp_err_t result = esp_now_send(receiver.mac, buffer, sizeof(buffer));

  if (result != ESP_OK)
  {
    Serial.printf("Error sending to %02X:%02X:%02X:%02X:%02X:%02X\n",
                  receiver.mac[0], receiver.mac[1], receiver.mac[2],
                  receiver.mac[3], receiver.mac[4], receiver.mac[5]);
  }
}

// action_switch_led moved to uitools.c for clarity

void updateBacklight()
{
  lv_disp_t *disp = lv_disp_get_default();
  const bool isActive = (lv_disp_get_inactive_time(disp) < INACTIVITY_TIMEOUT);
  smartdisplay_lcd_set_backlight(isActive ? BACKLIGHT_ACTIVE : BACKLIGHT_INACTIVE);
}

// Calculates 18650 Li-Ion battery percentage from half-voltage reading (mV)
float calculateBatteryPercentage(float halfVoltageMv)
{
  // Slave reports half voltage in mV (e.g., 1890 => 3.780V)
  float mv = halfVoltageMv * 2.0f;

  // Clamp to reasonable bounds
  if (mv <= 3300.0f)
    return 0.0f;
  if (mv >= 4200.0f)
    return 100.0f;

  // Piecewise-linear approximation of 18650 OCV curve
  const float pts_mv[] = {3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200};
  const float pts_pc[] = {0, 10, 20, 30, 45, 60, 72, 84, 92, 100};

  for (int i = 0; i < 9; ++i)
  {
    if (mv <= pts_mv[i + 1])
    {
      float t = (mv - pts_mv[i]) / (pts_mv[i + 1] - pts_mv[i]);
      return pts_pc[i] + t * (pts_pc[i + 1] - pts_pc[i]);
    }
  }
  return 0.0f; // fallback
}

void updateBatteryPercentage()
{
  for (size_t i = 0; i < NUM_RECEIVERS; ++i)
  {
    bool desiredState = false;
    float desiredBrightness = 0.0f;
    switch (i)
    {
    case 0:
      desiredState = get_var_state_led1();
      desiredBrightness = get_var_brightness_led1();
      break;
    case 1:
      desiredState = get_var_state_led2();
      desiredBrightness = get_var_brightness_led2();
      break;
    case 2:
      desiredState = get_var_state_led3();
      desiredBrightness = get_var_brightness_led3();
      break;
    default:
      break;
    }

    if (desiredBrightness <= 0.0f)
    {
      desiredState = false;
      switch (i)
      {
      case 0:
        set_var_state_led1(false);
        break;
      case 1:
        set_var_state_led2(false);
        break;
      case 2:
        set_var_state_led3(false);
        break;
      default:
        break;
      }
    }

    const TelemetryPayload &tele = receivers[i].telemetry;
    bool pending = (tele.appliedState != (desiredState ? 1 : 0)) ||
                   (tele.appliedBrightness != static_cast<uint16_t>(desiredBrightness + 0.5f));

    float batteryPct = calculateBatteryPercentage(static_cast<float>(tele.halfVoltageMv));
    uitools_update_channel_feedback(static_cast<int>(i),
                                    batteryPct,
                                    static_cast<float>(tele.appliedBrightness),
                                    pending);
  }

  uitools_tick_pending();
}

void setLEDState()
{
  preferences.begin("framecontrol", false);
  preferences.putBool("state_led1", get_var_state_led1());
  preferences.putBool("state_led2", get_var_state_led2());
  preferences.putBool("state_led3", get_var_state_led3());
  preferences.end();
}

bool getLEDState(char preset)
{
  preferences.begin("framecontrol", false);
  char key[15];
  sprintf(key, "state_led%c", preset);
  bool value = preferences.getBool(key, false);
  preferences.end();
  return value;
}

extern "C" void setLEDState_c(void)
{
  setLEDState();
}

void setup()
{
#ifdef ARDUINO_USB_CDC_ON_BOOT
  delay(5000);
#endif

  Serial.begin(115200);

  smartdisplay_init();
  {
    lv_disp_t *disp = lv_disp_get_default();
    lv_disp_set_rotation(disp, LV_DISPLAY_ROTATION_90);
  }

  // Restore last saved brightness levels before initializing ESP-NOW
  preferences.begin("framecontrol", true);
  uint32_t b1 = preferences.getUInt("brightness_led1", 50);
  uint32_t b2 = preferences.getUInt("brightness_led2", 50);
  uint32_t b3 = preferences.getUInt("brightness_led3", 50);
  preferences.end();
  set_var_brightness_led1((float)b1);
  set_var_brightness_led2((float)b2);
  set_var_brightness_led3((float)b3);

  initESPNow();
  ui_init();
  uitools_install_tick_screen_hook();
  uitools_style_main_tabview();

  pinMode(pirPin, INPUT);

  Serial.println("System ready");
}

static inline bool readPirSensor()
{
  bool motion = digitalRead(pirPin) != 0;
  bool useSensor = get_var_use_pir_sensor();
  if (!useSensor)
    return true; // always "motion" if PIR sensor is disabled

  return motion;
}

static inline bool getDesiredStateVar(size_t idx)
{
  switch (idx)
  {
  case 0:
    return get_var_state_led1();
  case 1:
    return get_var_state_led2();
  case 2:
    return get_var_state_led3();
  default:
    return false;
  }
}

static inline void setDesiredStateVar(size_t idx, bool state)
{
  switch (idx)
  {
  case 0:
    set_var_state_led1(state);
    break;
  case 1:
    set_var_state_led2(state);
    break;
  case 2:
    set_var_state_led3(state);
    break;
  default:
    break;
  }

  if (idx < NUM_RECEIVERS)
  {
    receivers[idx].desiredState = state;
  }
}

void loop()
{
  const uint32_t now = millis();
  const bool motion = readPirSensor();

  static bool sensorInitialised = false;
  static bool lastSensorState = false;
  static uint32_t lastMotionMs = 0;
  static bool overrideActive = false;
  static bool savedStates[NUM_RECEIVERS];

  if (!sensorInitialised)
  {
    lastSensorState = motion;
    lastMotionMs = now;
    sensorInitialised = true;
  }

  if (motion != lastSensorState)
  {
    Serial.printf("PIR sensor: %s\n", motion ? "motion" : "idle");
    lastSensorState = motion;
  }

  if (motion)
  {
    lastMotionMs = now;
    if (overrideActive)
    {
      for (size_t i = 0; i < NUM_RECEIVERS; ++i)
      {
        setDesiredStateVar(i, savedStates[i]);
      }
      Serial.println("PIR sensor: motion -> LEDs restored");
      overrideActive = false;
    }
  }
  else
  {
    if (!overrideActive && (now - lastMotionMs) >= PIR_INACTIVITY_MS)
    {
      for (size_t i = 0; i < NUM_RECEIVERS; ++i)
      {
        bool currentState = getDesiredStateVar(i);
        savedStates[i] = currentState;
        setDesiredStateVar(i, false);
      }
      Serial.println("PIR sensor: inactivity -> LEDs off");
      overrideActive = true;
    }
    else if (overrideActive)
    {
      for (size_t i = 0; i < NUM_RECEIVERS; ++i)
      {
        if (getDesiredStateVar(i))
        {
          setDesiredStateVar(i, false);
        }
      }
    }
  }

  // send messages at regular intervals
  for (auto &receiver : receivers)
  {
    if (now - receiver.lastSend >= SEND_INTERVAL)
    {
      sendMessage(receiver);
      updateBatteryPercentage();
      receiver.lastSend = now;
    }
  }

  // Apply telemetry-driven UI updates in the main loop context
  for (size_t i = 0; i < NUM_RECEIVERS; ++i)
  {
    if (receivers[i].telemetryDirty)
    {
      switch (i)
      {
      case 0:
        set_var_led_on_time1(receivers[i].telemetry.operatingHours);
        set_var_last_charged1(receivers[i].telemetry.lastChargedDate);
        break;
      case 1:
        set_var_led_on_time2(receivers[i].telemetry.operatingHours);
        set_var_last_charged2(receivers[i].telemetry.lastChargedDate);
        break;
      case 2:
        set_var_led_on_time3(receivers[i].telemetry.operatingHours);
        set_var_last_charged3(receivers[i].telemetry.lastChargedDate);
        break;
      }
      receivers[i].telemetryDirty = false;
    }
  }

  updateBacklight();

  // LVGL Wartung
  lv_timer_handler();
  lv_tick_inc(millis() - lv_last_tick);
  lv_last_tick = now;

  ui_tick();

#ifdef BOARD_HAS_RGB_LED
  static uint32_t lastLedUpdate = 0;
  if (now - lastLedUpdate >= LED_UPDATE_INTERVAL)
  {
    static uint8_t ledState = 0;
    smartdisplay_led_set_rgb(ledState & 0x01, ledState & 0x02, ledState & 0x04);
    ledState = (ledState + 1) % 8;
    lastLedUpdate = now;
  }
#endif
}
