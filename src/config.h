#ifndef CONFIG_H
#define CONFIG_H

#define DEFAULT_SSID "HCT"
#define DEFAULT_PASSWORD "Hc172920"
#define DEFAULT_AP_SSID "ESP-AP"
#define DEFAULT_AP_PASSWORD "12345678"
#define DEFAULT_AP_IP "192.168.4.1"

#if defined(ESP32)
#define LED_PIN 32
#define LDR_PIN 34
#define PIXEL_PIN 18
#define SERVO_PIN 5
#define POTENTIOMETER_PIN 35
#define STEPPER_PIN_STEP 19
#define STEPPER_PIN_DIR 21
#define STEPPER_PIN_ENABLE 22

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
#define LDR_KEY "ldr"
#define LED_KEY "led"
#define PIXEL_KEY "pixel"
#define SERVO_KEY "servo"
#define POTENTIOMETER_KEY "potentiometer"
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

// JSON Document size
#define JSON_DOC_SIZE 200

#endif // CONFIG_H
