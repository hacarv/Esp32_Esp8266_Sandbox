#ifndef CONFIG_H
#define CONFIG_H

#define DEFAULT_SSID ""
#define DEFAULT_PASSWORD "12345678"
#define DEFAULT_AP_SSID "ESP-AP"
#define DEFAULT_AP_PASSWORD ""
#define DEFAULT_AP_IP "192.168.4.1"

#if defined(ESP32)
#define BUTTON_PIN 34
#define DHT_PIN 33
#define LED_PIN 2
#define LDR_PIN 39
#define PIXEL_PIN 17
#define POTENTIOMETER_PIN 36
#define RELAY_PIN 16
#define SERVO_PIN 4
#define STEPPER_PIN_STEP 25
#define STEPPER_PIN_DIR 26
#define STEPPER_PIN_ENABLE 27

#elif defined(ESP8266)
#define LDR_PIN A0
#define LED_PIN D1
#define SERVO_PIN D2
#define POTENTIOMETER_PIN A0
#define STEPPER_PIN_STEP D5
#define STEPPER_PIN_DIR D6
#define STEPPER_PIN_ENABLE D7

#endif

// JSON Keys
#define BUTTON_KEY "button"
#define DHT_KEY "dht"
#define LED_KEY "led"
#define LDR_KEY "ldr"
#define PIXEL_KEY "pixel"
#define POTENTIOMETER_KEY "pot"
#define RELAY_KEY "relay"
#define SERVO_KEY "servo"
#define STEPPER_KEY "stepper"

#define ERROR_KEY "error"
#define SET_AP_KEY "setAP"
#define CONNECT_WIFI_KEY "connectWiFi"
#define SCAN_NETWORKS_KEY "scanNetworks"
#define GET_VALUE_KEY "get_value"
#define SET_VALUE_KEY "set_value"
#define SET_GPIO_KEY "set_gpio"
#define GET_GPIO_KEY "get_gpio"
#define SET_INTERVAL_KEY "set_interval"
#define DEVICE_KEY "Device"
#define MESSAGE_TYPE_KEY "Type"
#define VALUE_KEY "Value"
#define MESSAGE_KEY "message"
#define SET_READ_NOTIFY_KEY "set_readAndNotify"
#define SET_BRIGHTNESS_KEY "set_brightness"
#define SET_CANCEL_KEY "set_cancel"

// JSON Document size
#define JSON_DOC_SIZE 200

#endif // CONFIG_H
