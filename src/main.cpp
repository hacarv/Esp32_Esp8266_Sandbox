#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#endif
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <ContinuousStepper.h>
#include "config.h"
#include "LDR.h"
#include "LED.h"
#include "ServoMotor.h"
#include "Potentiometer.h"
#include "StepperMotor.h"
#include "WebSocketHandler.h"
#include "WiFiManager.h"

// WebSocket server
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Global instances for devices
LDR ldr;
LED led;
ServoMotor servoMotor;
Potentiometer potentiometer;
StepperMotor stepperMotor;
WiFiManager wifiManager;

void setup()
{
  Serial.begin(115200);

  // Setup devices with respective pins and intervals
  ldr.begin(LDR_PIN, 10); // Example interval: 10ms
  led.begin();
  servoMotor.begin(SERVO_PIN);
  potentiometer.begin(POTENTIOMETER_PIN, 10); // Example interval: 10ms
  stepperMotor.begin(STEPPER_PIN_STEP, STEPPER_PIN_DIR, STEPPER_PIN_ENABLE);

  // Inicializar WebSocket
  initWebSocket();
  wifiManager.begin();
  server.addHandler(&ws);
  server.begin();
}

void loop()
{
  unsigned long currentMillis = millis();

  ldr.update(currentMillis);
  potentiometer.update(currentMillis);
  led.update();
  servoMotor.update();
  stepperMotor.update();
  handleWebSocket();
}
