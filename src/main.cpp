#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <esp_now.h>
#include <ui/ui.h>
#include <ui/actions.h>
#include <ui/vars.h>
#include <WiFi.h>
#include <uitools.h>
#include <Preferences.h>

// const confs
constexpr uint8_t RECEIVER_MACS[][6] = {
    {0xF0, 0xF5, 0xBD, 0x02, 0xEE, 0xB8}, // Receiver 0
    {0x1C, 0x69, 0x20, 0xCE, 0x68, 0x50}, // Receiver 1
    {0xF0, 0xF5, 0xBD, 0x2C, 0x08, 0xF4}, // Receiver 4
    {0x40, 0x4C, 0xCA, 0x5D, 0xF1, 0x30}, // Receiver 2
    {0xF0, 0xF5, 0xBD, 0x01, 0x96, 0xE0}  // Receiver 3
};
constexpr size_t NUM_RECEIVERS = sizeof(RECEIVER_MACS) / sizeof(RECEIVER_MACS[0]);
constexpr uint32_t SEND_INTERVAL = 100;
constexpr uint32_t LED_UPDATE_INTERVAL = 500;
constexpr uint32_t INACTIVITY_TIMEOUT = 600000;
constexpr uint8_t BACKLIGHT_ACTIVE = 50;
constexpr uint8_t BACKLIGHT_INACTIVE = 0;

// message struct
#pragma pack(push, 1)
struct MessageData
{
  char command[32];
  uint32_t brightness;
  float measurement;
  bool status;
  uint32_t operatingHours;
  uint32_t lastChargedDate;
};
#pragma pack(pop)

// receiver struct
struct Receiver
{
  uint8_t mac[6];
  esp_now_peer_info_t peerInfo;
  MessageData sentData;
  MessageData receivedData;
  uint32_t lastSend;
};

// global variables
Receiver receivers[NUM_RECEIVERS];
lv_disp_t *display; // Define display here
auto lv_last_tick = millis();
Preferences preferences;
uint8_t batteryPercentage = 0;

// Function definitions
void messageReceived(const uint8_t *mac, const uint8_t *data, int len);
void updateBacklight();
void sendMessage(Receiver &receiver);
void initESPNow();
void action_switch_led(lv_event_t *e);
void updateBatteryPercentage();
float calculateBatteryPercentage(float voltage);
void setLEDState();
bool getLEDState(char preset);

void initESPNow()
{
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("ESP-NOW initialisation failed");
    return;
  }

  for (size_t i = 0; i < NUM_RECEIVERS; i++)
  {
    memcpy(receivers[i].mac, RECEIVER_MACS[i], 6);

    // Peer-Info konfigurieren
    memcpy(receivers[i].peerInfo.peer_addr, receivers[i].mac, 6);
    receivers[i].peerInfo.channel = 0;
    receivers[i].peerInfo.encrypt = false;

    // SentData initialisieren
    snprintf(receivers[i].sentData.command, sizeof(receivers[i].sentData.command), "Hello Slave!");
    // Initialize brightness from UI vars per channel
    switch (i)
    {
    case 0:
      receivers[i].sentData.brightness = (int)get_var_brightness_led1();
      break;
    case 1:
      receivers[i].sentData.brightness = (int)get_var_brightness_led2();
      break;
    case 2:
      receivers[i].sentData.brightness = (int)get_var_brightness_led3();
      break;
    default:
      // receivers[i].sentData.brightness = 0;
      break;
    }
    receivers[i].sentData.measurement = 0.0f;
    receivers[i].sentData.status = getLEDState('1' + i);
    receivers[i].sentData.operatingHours = 0;
    receivers[i].sentData.lastChargedDate = 0;

    if (esp_now_add_peer(&receivers[i].peerInfo) != ESP_OK)
    {
      Serial.printf("Adding Peer %d failed\n", i);
    }
  }

  set_var_state_led1(receivers[0].sentData.status);
  set_var_state_led2(receivers[1].sentData.status);
  set_var_state_led3(receivers[2].sentData.status);

  esp_now_register_recv_cb(messageReceived);
  Serial.println("ESP-NOW initialised");
}

// Callback-Funktion für empfangene Nachrichten
void IRAM_ATTR messageReceived(const uint8_t *mac, const uint8_t *data, int len)
{
  for (auto &receiver : receivers)
  {
    if (memcmp(mac, receiver.mac, 6) == 0)
    {
      if (len == sizeof(MessageData))
      {
        memcpy(&receiver.receivedData, data, len);
        // Ensure proper parsing: enforce string termination and log all fields
        receiver.receivedData.command[sizeof(receiver.receivedData.command) - 1] = '\0';
        Serial.printf("Data from %02X:%02X:%02X:%02X:%02X:%02X: %s, brightness: %u, voltage: %.2f, hours: %u, date: %u, state: %s\n",
                      mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
                      receiver.receivedData.command,
                      static_cast<unsigned>(receiver.receivedData.brightness),
                      receiver.receivedData.measurement,
                      static_cast<unsigned>(receiver.receivedData.operatingHours),
                      static_cast<unsigned>(receiver.receivedData.lastChargedDate),
                      receiver.receivedData.status ? "true" : "false");
      }
      Serial.println(receiver.receivedData.measurement);
      break;
    }
  }
}

void sendMessage(Receiver &receiver)
{
  // Update brightness from UI variables before sending (map receiver to channel)
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
      receiver.sentData.brightness = (int)get_var_brightness_led1();
      break;
    case 1:
      receiver.sentData.brightness = (int)get_var_brightness_led2();
      break;
    case 2:
      receiver.sentData.brightness = (int)get_var_brightness_led3();
      break;
    }

    // Persist brightness to NVS only if changed to survive reboots
    static uint32_t lastSavedBrightness[3] = {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu};
    if (lastSavedBrightness[idx] != receiver.sentData.brightness)
    {
      preferences.begin("framecontrol", false);
      char key[16];
      snprintf(key, sizeof(key), "brightness_led%u", (unsigned)(idx + 1));
      preferences.putUInt(key, receiver.sentData.brightness);
      preferences.end();
      lastSavedBrightness[idx] = receiver.sentData.brightness;
    }
  }
  esp_err_t result = esp_now_send(receiver.mac,
                                  reinterpret_cast<uint8_t *>(&receiver.sentData),
                                  sizeof(MessageData));

  if (result != ESP_OK)
  {
    Serial.printf("Error sending to %02X:%02X:%02X:%02X:%02X:%02X\n",
                  receiver.mac[0], receiver.mac[1], receiver.mac[2],
                  receiver.mac[3], receiver.mac[4], receiver.mac[5]);
  }
}

void action_switch_led(lv_event_t *e)
{
  int userData = (int)lv_event_get_user_data(e);
  receivers[userData].sentData.status = !receivers[userData].sentData.status;

  switch (userData)
  {
  case 0:
    set_var_state_led1(receivers[userData].sentData.status);
    break;
  case 1:
    set_var_state_led2(receivers[userData].sentData.status);
    break;
  case 2:
    set_var_state_led3(receivers[userData].sentData.status);
    break;
  default:
    break;
  }
  setLEDState();
}

void updateBacklight()
{
  const bool isActive = (lv_disp_get_inactive_time(display) < INACTIVITY_TIMEOUT);
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
  const float pts_pc[] = {   0,   10,   20,   30,   45,   60,   72,   84,   92,  100};

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
  bool incrementBatteryPercentage = false;

  if (receivers[0].receivedData.status == receivers[0].sentData.status)
  {
    set_var_battery_percentage1(calculateBatteryPercentage(receivers[0].receivedData.measurement));
  }
  else
  {
    set_var_battery_percentage1(batteryPercentage);
    incrementBatteryPercentage = true;
  }

  if (receivers[1].receivedData.status == receivers[1].sentData.status)
  {
    set_var_battery_percentage2(calculateBatteryPercentage(receivers[1].receivedData.measurement));
  }
  else
  {
    set_var_battery_percentage2(batteryPercentage);
    incrementBatteryPercentage = true;
  }

  if (receivers[2].receivedData.status == receivers[2].sentData.status)
  {
    set_var_battery_percentage3(calculateBatteryPercentage(receivers[2].receivedData.measurement));
  }
  else
  {
    set_var_battery_percentage3(batteryPercentage);
    incrementBatteryPercentage = true;
  }

  if (incrementBatteryPercentage)
  {
    batteryPercentage = batteryPercentage > 100 ? 0 : (batteryPercentage + 1);
  }
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

void setup()
{
#ifdef ARDUINO_USB_CDC_ON_BOOT
  delay(5000);
#endif

  Serial.begin(115200);

  smartdisplay_init();
  display = lv_disp_get_default();
  lv_disp_set_rotation(display, LV_DISPLAY_ROTATION_90);

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

  Serial.println("System ready");
}

void loop()
{
  const uint32_t now = millis();

  // Sende an alle Empfänger im Intervall
  for (auto &receiver : receivers)
  {
    if (now - receiver.lastSend >= SEND_INTERVAL)
    {
      sendMessage(receiver);
      updateBatteryPercentage();
      receiver.lastSend = now;
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
