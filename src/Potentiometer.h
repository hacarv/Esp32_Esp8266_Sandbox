#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "DeviceBaseClass.h"
#include "config.h"

class Potentiometer : public DeviceBaseClass
{
public:
    Potentiometer();
    void begin(uint8_t pin);
    void checkConnection();
    void getData();
    bool isConnected();
    int read();
    void readAndNotify();

private:
    uint8_t _pin = 0;
    int _lastValue;
};

#endif
