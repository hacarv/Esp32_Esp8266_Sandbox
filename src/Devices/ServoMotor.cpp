#include "ServoMotor.h"

ServoMotor::ServoMotor(): DeviceBaseClass(){}

void ServoMotor::begin(uint8_t pin) {
    _pin = pin;
    _servo.attach(_pin);
    _position = 90; // Default position
    _servo.write(_position);
    checkConnection();
}

void ServoMotor::setPosition(uint8_t position) {
    _position = position;
    _servo.write(_position);
}

void ServoMotor::getPosition()
{
     JsonDocument doc;
    doc[SERVO_KEY] = _servo.read();
    char messageBuffer[JSON_DOC_SIZE];
    serializeJson(doc, messageBuffer);
    sendMessage(messageBuffer);
}

bool ServoMotor::isConnected() {
    return _servo.attached();
}

void ServoMotor::checkConnection() {
    if (!isConnected()) {
        const char* message = "{\"" ERROR_KEY "\":\"Servo motor not connected\"}";
        Serial.println(message);
    }
}
