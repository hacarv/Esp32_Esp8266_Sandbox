#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <ContinuousStepper.h>

class StepperMotor {
public:
    void begin(int stepPin, int dirPin, int enablePin);
    void moveSteps(int steps);
    void update();
        void checkConnection();
    bool isConnected();
private:
    ContinuousStepper<StepperDriver> _stepper;
    int _steps;
};

#endif


