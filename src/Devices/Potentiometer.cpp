#include "Potentiometer.h"

Potentiometer::Potentiometer() : DeviceBaseClass() {}

void Potentiometer::begin(uint8_t pin, const char *deviceKey)
{
    init(pin, deviceKey);
    pinMode(_pin, INPUT);
    checkConnection();
}

void Potentiometer::checkConnection()
{
    if (!isConnected())
    {
        checkConnectionMessage();
    }
}

bool Potentiometer::isConnected()
{
    return _pin != 0;
}

int Potentiometer::read()
{
    return analogRead(_pin);
}

void Potentiometer::readAndNotify()
{
    if (isIntervalExpired() && isReadAndNotifyEnabled())
    {
        int value = read();

        if (value != _lastValue)
        {
            getValue();
        }
    }
}

void Potentiometer::getValue()
{
    int value = read();
    _lastValue = value;
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_VALUE_KEY;
    doc[VALUE_KEY] = value;
    sendMessage(doc);
}

void Potentiometer::getGPIO()
{
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_GPIO_KEY;
    doc[VALUE_KEY] = _pin;
    sendMessage(doc);
}

void Potentiometer::setGPIO(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    sendGPIOMessage(_pin);
}

