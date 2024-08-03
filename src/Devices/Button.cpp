#include "Button.h"

Button::Button() : DeviceBaseClass() {}

void Button::begin(uint8_t pin, const char *deviceKey)
{
    init(pin, deviceKey);
    pinMode(_pin, INPUT);
    checkConnection();
}

void Button::checkConnection()
{
    if (!isConnected())
    {
        checkConnectionMessage();
    }
}

bool Button::isConnected()
{
    return _pin != 0;
}

int Button::read()
{
    return digitalRead(_pin);
}

void Button::readAndNotify()
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

void Button::getValue()
{
    int value = read();
    _lastValue = value;
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_VALUE_KEY;
    doc[VALUE_KEY] = value;
    sendMessage(doc);
}
void Button::getGPIO()
{
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_GPIO_KEY;
    doc[VALUE_KEY] = _pin;
    sendMessage(doc);
}

void Button::setGPIO(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    sendGPIOMessage(_pin);
}
