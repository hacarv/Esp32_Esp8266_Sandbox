#include "LED.h"

LED::LED() : DeviceBaseClass() {}

void LED::begin(uint8_t pin)
{
    _pin = pin;
    _lastValue = -1;
    pinMode(_pin, OUTPUT);
    Serial.printf("LED - Begin: %d",_pin);
    checkConnection();
}

void LED::setValue(uint8_t value)
{
    if (value == 1)
    {
        digitalWrite(_pin, HIGH);
         Serial.println("H");
    }
    else
    {
        digitalWrite(_pin, LOW);
        Serial.println("L");
    }

    Serial.println(_pin);
    Serial.println(value);
    getData();
}

int LED::read()
{
    return digitalRead(_pin);
}

void LED::readAndNotify()
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

void LED::getData()
{
    int value = read();
    _lastValue = value;
    JsonDocument doc;
    doc["device"] = LED_KEY;
    doc["value"] = value;
    char messageBuffer[JSON_DOC_SIZE];
    serializeJson(doc, messageBuffer);
    sendMessage(messageBuffer);
}

bool LED::isConnected()
{
    return analogRead(_pin) != -1;
}

void LED::checkConnection()
{
    if (!isConnected())
    {
        const char *message = "{\"" ERROR_KEY "\":\"LED not connected\"}";

        Serial.println(message);
    }
}
