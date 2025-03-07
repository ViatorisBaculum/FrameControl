#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <esp_now.h>
#include <ui/ui.h>
#include <ui/actions.h>
#include <ui/vars.h>
#include <WiFi.h>
#include <uitools.h>

// const confs
constexpr uint8_t RECEIVER_MACS[][6] = {
    {0x1C, 0x69, 0x20, 0xCE, 0x68, 0x50}, // Receiver 1
    {0xF0, 0xF5, 0xBD, 0x02, 0xEE, 0xB8}, // Receiver 2
    {0xF0, 0xF5, 0xBD, 0x02, 0xEE, 0xB8}  // Receiver 3
};
constexpr size_t NUM_RECEIVERS = sizeof(RECEIVER_MACS) / sizeof(RECEIVER_MACS[0]);
constexpr uint32_t SEND_INTERVAL = 500;
constexpr uint32_t INACTIVITY_TIMEOUT = 600000;
constexpr uint8_t BACKLIGHT_ACTIVE = 50;
constexpr uint8_t BACKLIGHT_INACTIVE = 0;

// message struct
#pragma pack(push, 1)
struct MessageData
{
  char command[32];
  int value;
  float measurement;
  bool status;
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
lv_disp_t *display;
auto lv_last_tick = millis();

// Function definitions
void messageReceived(const uint8_t *mac, const uint8_t *data, int len);
void updateBacklight();
void sendMessage(Receiver &receiver);
void initESPNow();
void updateBacklight();
void action_switch_led(lv_event_t *e);

void initESPNow()
{
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("ESP-NOW Initialisierung fehlgeschlagen");
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
    receivers[i].sentData.value = 0;
    receivers[i].sentData.measurement = 0.0f;
    receivers[i].sentData.status = false;

    if (esp_now_add_peer(&receivers[i].peerInfo) != ESP_OK)
    {
      Serial.printf("Peer %d hinzufügen fehlgeschlagen\n", i);
    }
  }

  // start esp with deactivated leds
  set_var_state_led1(receivers[0].sentData.status);
  set_var_state_led2(receivers[1].sentData.status);
  set_var_state_led3(receivers[2].sentData.status);

  esp_now_register_recv_cb(messageReceived);
  Serial.println("ESP-NOW initialisiert");
}

void IRAM_ATTR messageReceived(const uint8_t *mac, const uint8_t *data, int len)
{
  for (auto &receiver : receivers)
  {
    if (memcmp(mac, receiver.mac, 6) == 0)
    {
      if (len == sizeof(MessageData))
      {
        memcpy(&receiver.receivedData, data, len);
        Serial.printf("Daten von %02X:%02X:%02X:%02X:%02X:%02X: %s, %d, %.2f, %s\n",
                      mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
                      receiver.receivedData.command,
                      receiver.receivedData.value,
                      receiver.receivedData.measurement,
                      receiver.receivedData.status ? "true" : "false");
      }
      break;
    }
  }
}

void sendMessage(Receiver &receiver)
{
  esp_err_t result = esp_now_send(receiver.mac,
                                  reinterpret_cast<uint8_t *>(&receiver.sentData),
                                  sizeof(MessageData));

  if (result != ESP_OK)
  {
    Serial.printf("Fehler beim Senden an %02X:%02X:%02X:%02X:%02X:%02X\n",
                  receiver.mac[0], receiver.mac[1], receiver.mac[2],
                  receiver.mac[3], receiver.mac[4], receiver.mac[5]);
  }
}

void action_switch_led(lv_event_t *e)
{
  int userData = (int)lv_event_get_user_data(e);
  receivers[userData].sentData.status = !receivers[userData].sentData.status;
  Serial.println("LED " + String(userData) + ": Is: " + receivers[userData].sentData.status);

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
}

void updateBacklight()
{
  const bool isActive = (lv_disp_get_inactive_time(display) < INACTIVITY_TIMEOUT);
  smartdisplay_lcd_set_backlight(isActive ? BACKLIGHT_ACTIVE : BACKLIGHT_INACTIVE);
}

void updateBatteryPercentage()
{
  set_var_battery_percentage1(receivers[0].receivedData.measurement);
  set_var_battery_percentage2(receivers[1].receivedData.measurement);
  set_var_battery_percentage3(receivers[2].receivedData.measurement);
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

  initESPNow();
  ui_init();

  Serial.println("System bereit");
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
  if (now - lastLedUpdate >= 500)
  {
    static uint8_t ledState = 0;
    smartdisplay_led_set_rgb(ledState & 0x01, ledState & 0x02, ledState & 0x04);
    ledState = (ledState + 1) % 8;
    lastLedUpdate = now;
  }
#endif
}