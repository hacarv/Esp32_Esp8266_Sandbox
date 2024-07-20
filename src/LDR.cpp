#include "LDR.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "WebSocketHandler.h"
#include "config.h"

void LDR::begin(int pin, int interval) {
    _pin = pin;
    _lastValue = -1;
    _lastReadTime = 0;
    _interval = interval;
    pinMode(_pin, INPUT);
    checkConnection();
}

int LDR::read() {
    return analogRead(_pin);
}

void LDR::readAndNotify() {
    int value = read();
    if (value != _lastValue) {
        _lastValue = value;
        StaticJsonDocument<JSON_DOC_SIZE> doc;
        doc[LDR_KEY] = value;
        String jsonString;
        serializeJson(doc, jsonString);
        notifyClients(jsonString);
    }
}

bool LDR::isConnected() {
    return analogRead(_pin) != -1;
}

void LDR::checkConnection() {
    if (!isConnected()) {
        String message = "{\"" ERROR_KEY "\":\"LDR not connected\"}";
        notifyClients(message);
        Serial.println(message);
    }
}

void LDR::update(unsigned long currentTime) {
    if (_interval != -1 && currentTime - _lastReadTime >= _interval) {
        readAndNotify();
        _lastReadTime = currentTime;
    }
}
