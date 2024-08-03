#include "StepperMotor.h"

StepperMotor::StepperMotor() : DeviceBaseClass() {}

void StepperMotor::begin(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin, const char *deviceKey)
{
    _stepPin = stepPin;
    init(stepPin, deviceKey);
    setGPIO(stepPin, dirPin, enablePin);
    _steps = 0;
    _stepper->setPinsInverted(false,false,true); 
    onStop();
}

void StepperMotor::moveSteps(int steps)
{
    _steps = steps;
    _stepper->enableOutputs();
    _stepper->setMaxSpeed(500);
    _stepper->setAcceleration(250);
    _stepper->move(steps);
    Serial.print("Steps: ");
    Serial.println(steps);
}

void StepperMotor::loop()
{
    if (_stepper->distanceToGo() == 0)
    {
        onStop();
    }
    else
    {
        _stepper->run();
    }
}

bool StepperMotor::isConnected()
{
    return _stepPin != 0;
}

int StepperMotor::read()
{
    return _stepper->currentPosition();
}

void StepperMotor::readAndNotify()
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

void StepperMotor::getValue()
{
    int value = read();
    _lastValue = value;
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_VALUE_KEY;
    doc[VALUE_KEY] = _lastValue;
    sendMessage(doc);
}

void StepperMotor::getGPIO()
{
}

void StepperMotor::setGPIO(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin)
{
    _stepper = new AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);

    pinMode(enablePin,OUTPUT);

    _stepper->setEnablePin(enablePin);
}

void StepperMotor::setValue(const JsonDocument &doc)
{
    moveSteps(doc[VALUE_KEY]);
}

void StepperMotor::onStop()
{
    _stepper->stop();
    _stepper->disableOutputs();
}

void StepperMotor::onCancel()
{
    onStop();
     JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = MESSAGE_KEY;
    doc[VALUE_KEY] = "Motor Stop!";
    sendMessage(doc);
}

void StepperMotor::checkConnection()
{
    if (!isConnected())
    {
        const char *message = "{\"" ERROR_KEY "\":\"Stepper motor not connected\"}";
        Serial.println(message);
    }
}
