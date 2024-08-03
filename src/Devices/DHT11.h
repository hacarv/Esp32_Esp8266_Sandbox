#ifndef DHT11_H
#define DHT11_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "DeviceBaseClass.h"
#include "DHT_Async.h"
#include "config.h"

class DHT : public DeviceBaseClass
{
public:
    DHT();
    ///
    void begin(uint8_t pin, const char *deviceKey);
    void checkConnection();
    bool isConnected();
    int read();
    void readAndNotify();

    /// Base Class functions
    // void setValue(const JsonDocument &doc) override;
    void getValue() override;
    void getGPIO() override;
    void setGPIO(uint8_t pin) override;

private:
    DHT_Async *dht;

    float temperature = 0;

    float humidity = 0;

    float lastTemperature = 0;

    float lastHumidity = 0;
};

#endif