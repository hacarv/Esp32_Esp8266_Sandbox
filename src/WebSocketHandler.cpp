#include "WebSocketHandler.h"
#include <ArduinoJson.h>
#include "LED.h"
#include "ServoMotor.h"
#include "StepperMotor.h"
#include "config.h"

extern LED led;
extern ServoMotor servoMotor;
extern StepperMotor stepperMotor;

AsyncWebSocket *wsServer;

void notifyClients(const String& message) {
    wsServer->textAll(message);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    String message = (char *)data;
    StaticJsonDocument<JSON_DOC_SIZE> doc; // Using the predefined size
    DeserializationError error = deserializeJson(doc, message);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
    
    if (doc.containsKey(LED_KEY)) {
      led.setColor(doc[LED_KEY]["r"], doc[LED_KEY]["g"], doc[LED_KEY]["b"]);
    }
    if (doc.containsKey(SERVO_KEY)) {
      servoMotor.setPosition(doc[SERVO_KEY]);
    }
    if (doc.containsKey(STEPPER_KEY)) {
      stepperMotor.moveSteps(doc[STEPPER_KEY]);
    }
  }
}

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  wsServer = server;
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

