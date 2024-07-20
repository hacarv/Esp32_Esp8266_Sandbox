#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <ContinuousStepper.h>

class StepperMotor {
public:
    void begin(int pin1, int pin2, int pin3, int pin4);
    void moveSteps(int steps);
    void update();
    void checkConnection();
    bool isConnected();

private:
    ContinuousStepper _stepper;
    int _pin1, _pin2, _pin3, _pin4;
};

#endif


