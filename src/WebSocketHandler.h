#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <ArduinoJson.h>
#include <AsyncWebSocket.h>
#include <ArduinoJson.h>
#include "LED.h"
#include "LDR.h"
#include "ServoMotor.h"
#include "StepperMotor.h"
#include "config.h"
#include "WiFiManager.h"

extern AsyncWebSocket ws;

extern LED led;
extern LDR ldr;
extern ServoMotor servoMotor;
extern StepperMotor stepperMotor;
extern WiFiManager wifiManager;

void initWebSocket();
void handleWebSocket();
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);

void notifyClients(String message);

#endif // WEBSOCKETHANDLER_H


