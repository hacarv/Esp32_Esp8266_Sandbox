#include "ServoMotor.h"

ServoMotor::ServoMotor() : DeviceBaseClass() {}

void ServoMotor::begin(uint8_t pin, const char *deviceKey)
{
    init(pin,deviceKey);
    servo.attach(pin);
    servo.write(90);
    checkConnection();
}

void ServoMotor::checkConnection()
{
    if (!isConnected())
    {
        checkConnectionMessage();
    }
}

bool ServoMotor::isConnected()
{
    return _pin != 0;
}

int ServoMotor::read()
{
    return servo.read();
}

void ServoMotor::readAndNotify()
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

void ServoMotor::getValue()
{
    int value = read();
    _lastValue = value;
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_VALUE_KEY;
    doc[VALUE_KEY] = value;
    sendMessage(doc);
}

void ServoMotor::setGPIO(uint8_t pin)
{
      servo.attach(pin);
    DeviceBaseClass::setGPIO(pin);
}

void ServoMotor::setValue(const JsonDocument &doc)
{
    _lastValue = doc[VALUE_KEY];

    if (_lastValue >=1 && _lastValue <= 180)
    {
       servo.write(_lastValue);
    }

    getValue();
}


