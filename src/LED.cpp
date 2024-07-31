#include "LED.h"

LED::LED() : DeviceBaseClass() {}

void LED::begin(uint8_t pin)
{
    _pin = pin;
    _lastValue = 0;
    pinMode(_pin, OUTPUT);
    Serial.printf("LED - Begin: %d",_pin);
    Serial.println();
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
    return _lastValue;
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
      return _pin != 0;
}

void LED::checkConnection()
{
    if (!isConnected())
    {
        const char *message = "{\"" ERROR_KEY "\":\"LED not connected\"}";

        Serial.println(message);
    }
}
