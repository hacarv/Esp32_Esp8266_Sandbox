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
    /// 
    void begin(uint8_t pin, const char *deviceKey);
    void checkConnection();
    bool isConnected();
    int read();
    void readAndNotify();

    /// Base Class functions
    void getValue() override;
    void getGPIO() override;
    void setGPIO(uint8_t pin) override;

private:

};

#endif
