#include "Potentiometer.h"

Potentiometer::Potentiometer() : DeviceBaseClass() {}

void Potentiometer::begin(uint8_t pin)
{
    _pin = pin;
    _lastValue = -1;
    pinMode(_pin, INPUT);
    checkConnection();
}

int Potentiometer::read()
{
    return analogRead(_pin);
}

void Potentiometer::getData()
{
    int value = read();
    _lastValue = value;
    JsonDocument doc;
    doc["device"] = POTENTIOMETER_KEY;
    doc["value"] = value;
    char messageBuffer[JSON_DOC_SIZE];
    serializeJson(doc, messageBuffer);
    sendMessage(messageBuffer);
}

void Potentiometer::readAndNotify()
{
    if (isIntervalExpired())
    {
        int value = read();

        if (value != _lastValue)
        {
            getData();
        }
    }
}

bool Potentiometer::isConnected()
{
    return _pin != 0;
}

void Potentiometer::checkConnection()
{
    if (!isConnected())
    {
        const char *message = "{\"" ERROR_KEY "\":\"Potentiometer not connected\"}";
        Serial.println(message);
    }
}
