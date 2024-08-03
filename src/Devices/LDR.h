#ifndef LDR_H
#define LDR_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "DeviceBaseClass.h"
#include "config.h"

class LDR: public DeviceBaseClass 
{
public:
    LDR();
    /// 
    void begin(uint8_t pin, const char *deviceKey);
    void checkConnection();
    bool isConnected();
    int read();
    void readAndNotify();

    /// Base Class functions
    //void setValue(const JsonDocument &doc) override;
    void getValue() override;
    void getGPIO() override;
    void setGPIO(uint8_t pin) override;

private:

};

#endif
