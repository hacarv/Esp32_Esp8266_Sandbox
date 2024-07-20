#ifndef CONFIG_H
#define CONFIG_H

#if defined(ESP32)
  #define SSID "your_SSID"
  #define PASSWORD "your_PASSWORD"

  #define AP_SSID "ESP32_AP"
  #define AP_PASSWORD "your_AP_PASSWORD"

  #define LDR_PIN 34
  #define LED_PIN 18
  #define SERVO_PIN 5
  #define POTENTIOMETER_PIN 35
  #define STEPPER_PIN1 19
  #define STEPPER_PIN2 21
  #define STEPPER_PIN3 22
  #define STEPPER_PIN4 23

#elif defined(ESP8266)
  #define SSID "your_SSID"
  #define PASSWORD "your_PASSWORD"

  #define AP_SSID "ESP8266_AP"
  #define AP_PASSWORD "your_AP_PASSWORD"

  #define LDR_PIN A0
  #define LED_PIN D1
  #define SERVO_PIN D2
  #define POTENTIOMETER_PIN A0
  #define STEPPER_PIN1 D5
  #define STEPPER_PIN2 D6
  #define STEPPER_PIN3 D7
  #define STEPPER_PIN4 D8

#endif

// JSON Keys
#define LDR_KEY "ldr"
#define LED_KEY "led"
#define SERVO_KEY "servo"
#define POTENTIOMETER_KEY "potentiometer"
#define STEPPER_KEY "stepper"
#define ERROR_KEY "error"

// JSON Document size
#define JSON_DOC_SIZE 200

#endif // CONFIG_H
