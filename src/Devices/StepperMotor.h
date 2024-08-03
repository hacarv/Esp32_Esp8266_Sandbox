#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <ArduinoJson.h>
#include "config.h"
#include "DeviceBaseClass.h"
#include <AccelStepper.h>

class StepperMotor : public DeviceBaseClass
{
public:
    StepperMotor();
    void begin(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin,const char *deviceKey);
    void moveSteps(int steps);
    void loop();
    void checkConnection();
    bool isConnected();

    int read();

    void readAndNotify();

    void getValue() override;
    void getGPIO() override;
    void setGPIO(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin);
    void setValue(const JsonDocument &doc) override;

    void onStop();
    void onCancel() override;

private:
    AccelStepper *_stepper;
    int _steps;
    uint8_t _stepPin = 0;
};

#endif
