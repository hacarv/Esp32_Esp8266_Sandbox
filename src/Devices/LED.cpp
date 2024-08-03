#include "LED.h"

LED::LED() : DeviceBaseClass() {}

void LED::begin(uint8_t pin, const char *deviceKey)
{
    init(pin,deviceKey);
    checkConnection();
}

void LED::checkConnection()
{
    if (!isConnected())
    {
        checkConnectionMessage();
    }
}

bool LED::isConnected()
{
    return _pin != 0;
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
            getValue();
        }
    }
}

void LED::getValue()
{
    int value = read();
    _lastValue = value;
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_VALUE_KEY;
    doc[VALUE_KEY] = value;
    sendMessage(doc);
}

void LED::setValue(const JsonDocument &doc)
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

