#include "StepperMotor.h"
#include <Arduino.h>
#include "config.h"
#include "WebSocketHandler.h"

void StepperMotor::begin(int pin1, int pin2, int pin3, int pin4) {
    _pin1 = pin1;
    _pin2 = pin2;
    _pin3 = pin3;
    _pin4 = pin4;
    _stepper.attach(pin1, pin2, pin3, pin4);
    checkConnection();
}

void StepperMotor::moveSteps(int steps) {
    _stepper.step(steps);
}

void StepperMotor::update() {
    // No periodic update required for StepperMotor
}

bool StepperMotor::isConnected() {
    // Dummy check, replace with actual connection check if needed
    return digitalRead(_pin1) != -1;
}

void StepperMotor::checkConnection() {
    if (!isConnected()) {
        String message = "{\"" ERROR_KEY "\":\"Stepper motor not connected\"}";
        notifyClients(message);
        Serial.println(message);
    }
}


