#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <ArduinoJson.h>
#include "config.h"
#include "DeviceBaseClass.h"
#include <ContinuousStepper.h>

class StepperMotor : public DeviceBaseClass
{
public:
    StepperMotor();
    void begin(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin);
    void moveSteps(int steps);
    void getPosition();
    void loop();
    void checkConnection();
    bool isConnected();

private:
    ContinuousStepper<StepperDriver> _stepper;
    int _steps;
    uint8_t _stepPin = 0;
};

#endif
