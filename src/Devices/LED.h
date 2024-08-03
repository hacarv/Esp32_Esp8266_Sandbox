#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "DeviceBaseClass.h"
#include "config.h"

class LED : public DeviceBaseClass
{
public:
    LED();

    /// 
    void begin(uint8_t pin, const char *deviceKey);
    void checkConnection();
    bool isConnected();
    int read();
    void readAndNotify();

    /// Base Class functions
    void setValue(const JsonDocument &doc) override;
    void getValue() override;

private:
    
};

#endif