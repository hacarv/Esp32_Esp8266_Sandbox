#include "StepperMotor.h"


StepperMotor::StepperMotor():DeviceBaseClass(){}

void StepperMotor::begin(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin) {
    _stepPin = stepPin;
    _stepper.begin(stepPin, dirPin);
    _stepper.setEnablePin(enablePin);
    _steps = 0;
}

void StepperMotor::moveSteps(int steps) {
    _steps = steps;
    _stepper.spin(200);
}

void StepperMotor::getPosition()
{
    
}

void StepperMotor::loop() {
    _stepper.loop();
}

bool StepperMotor::isConnected() {
    return _stepPin != 0;
}


void StepperMotor::checkConnection() {
    if (!isConnected()) {
         const char * message = "{\"" ERROR_KEY "\":\"Stepper motor not connected\"}";
        Serial.println(message);
    }
}


