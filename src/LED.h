#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "DeviceBaseClass.h"
#include "config.h"

class LED: public DeviceBaseClass 
{
public:
    LED();
    void begin(uint8_t pin);
    void setValue(uint8_t value);
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