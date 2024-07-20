#include "ServoMotor.h"
#include <Arduino.h>
#include "config.h"
#include "WebSocketHandler.h"

void ServoMotor::begin(int pin) {
    _pin = pin;
    _servo.attach(_pin);
    _position = 90; // Default position
    _servo.write(_position);
    checkConnection();
}

void ServoMotor::setPosition(int position) {
    _position = position;
    _servo.write(_position);
}

void ServoMotor::update() {
    // No periodic update required for ServoMotor
}

bool ServoMotor::isConnected() {
    return _servo.attached();
}

void ServoMotor::checkConnection() {
    if (!isConnected()) {
        String message = "{\"" ERROR_KEY "\":\"Servo motor not connected\"}";
        notifyClients(message);
        Serial.println(message);
    }
}
