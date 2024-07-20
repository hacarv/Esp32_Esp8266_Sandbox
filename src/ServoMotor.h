#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Servo.h>

class ServoMotor {
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

