#include "LDR.h"

LDR::LDR() : DeviceBaseClass() {}

void LDR::begin(uint8_t pin, const char *deviceKey)
{
    init(pin, deviceKey);
    checkConnection();
}

void LDR::checkConnection()
{
    if (!isConnected())
    {
        checkConnectionMessage();
    }
}

bool LDR::isConnected()
{
    return _pin != 0;
}

int LDR::read()
{
    return analogRead(_pin);
}

void LDR::readAndNotify()
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

void LDR::getValue()
{
    int value = read();
    _lastValue = value;
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_VALUE_KEY;
    doc[VALUE_KEY] = value;
    sendMessage(doc);
}
void LDR::getGPIO()
{
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_GPIO_KEY;
    doc[VALUE_KEY] = _pin;
    sendMessage(doc);
}

void LDR::setGPIO(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    setGPIOMessage(_pin);
}
