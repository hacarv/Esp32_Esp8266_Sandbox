#include "StepperMotor.h"
#include <Arduino.h>
#include "config.h"
#include "WebSocketHandler.h"

void StepperMotor::begin(int stepPin, int dirPin, int enablePin) {
    _stepper.begin(stepPin, dirPin);
    _stepper.setEnablePin(enablePin);
    _steps = 0;
}

void StepperMotor::moveSteps(int steps) {
    _steps = steps;
    _stepper.spin(200);
}

void StepperMotor::update() {
    _stepper.loop();
}

bool StepperMotor::isConnected() {
    return true;//_stepper.isPowered();
}


void StepperMotor::checkConnection() {
    if (!isConnected()) {
        String message = "{\"" ERROR_KEY "\":\"Stepper motor not connected\"}";
        notifyClients(message);
        Serial.println(message);
    }
}


