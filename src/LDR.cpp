#include "LDR.h"

LDR::LDR() : DeviceBaseClass() {}

void LDR::begin(uint8_t pin)
{
    _pin = pin;
    _lastValue = -1;
    pinMode(_pin, INPUT);
    checkConnection();
}

int LDR::read()
{
    return analogRead(_pin);
}

void LDR::readAndNotify()
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

void LDR::getData()
{
    int value = read();
    _lastValue = value;
    JsonDocument doc;
     doc["device"] = LDR_KEY;
    doc["value"] = value;
    char messageBuffer[JSON_DOC_SIZE];
    serializeJson(doc, messageBuffer);
    sendMessage(messageBuffer);
}

bool LDR::isConnected()
{
    return analogRead(_pin) != -1;
}

void LDR::checkConnection()
{
    if (!isConnected())
    {
        const char *message = "{\"" ERROR_KEY "\":\"LDR not connected\"}";
        // notifyClients(message);
        Serial.println(message);
    }
}



