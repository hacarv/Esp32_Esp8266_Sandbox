#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#if defined(ESP32)
#include <ESP32Servo.h>
#elif defined(ESP8266)
#include <Servo.h>
#endif

class ServoMotor
{
public:
    void begin(int pin);
    void setPosition(int position);
    void update();
    void checkConnection();
    bool isConnected();

private:
    Servo _servo;
    int _pin;
    int _position;
};

#endif
