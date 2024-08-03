#include "Relay.h"

Relay::Relay() : DeviceBaseClass() {}

void Relay::begin(uint8_t pin, const char *deviceKey)
{
    init(pin,deviceKey);
    pinMode(_pin, OUTPUT);
    checkConnection();
}

void Relay::checkConnection()
{
    if (!isConnected())
    {
        checkConnectionMessage();
    }
}

bool Relay::isConnected()
{
    return _pin != 0;
}

int Relay::read()
{
    return _lastValue;
}

void Relay::readAndNotify()
{
    if (isIntervalExpired())
    {
        int value = read();

        if (value != _lastValue)
        {
            getValue();
        }
    }
}

void Relay::getValue()
{
    int value = read();
    _lastValue = value;
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_VALUE_KEY;
    doc[VALUE_KEY] = value;
    sendMessage(doc);
}

void Relay::setValue(const JsonDocument &doc)
{
    _lastValue = doc[VALUE_KEY];

    if (_lastValue == 1)
    {
        digitalWrite(_pin, HIGH);
    }
    else
    {
        digitalWrite(_pin, LOW);
    }

    getValue();
}

