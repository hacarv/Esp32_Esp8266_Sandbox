#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#if defined(ESP32)
#include <ESP32Servo.h>
#elif defined(ESP8266)
#include <Servo.h>
#endif
#include <ArduinoJson.h>
#include "config.h"
#include "DeviceBaseClass.h"

class ServoMotor : public DeviceBaseClass
{
public:
    ServoMotor();
    void begin(uint8_t pin);
    void setPosition(uint8_t position);
    void getPosition();
    void checkConnection();
    bool isConnected();

private:
    Servo _servo;
    uint8_t _pin;
    uint8_t _position;
};

#endif
