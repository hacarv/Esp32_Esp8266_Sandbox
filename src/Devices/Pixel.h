#ifndef PIXEL_H
#define PIXEL_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "DeviceBaseClass.h"
#include "config.h"
#include <Adafruit_NeoPixel.h>

class Pixel : public DeviceBaseClass
{

public:
    Pixel();
    void begin(uint8_t pin, uint16_t pixels, const char *deviceKey);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setPixelColor(uint8_t pixel, uint8_t r, uint8_t g, uint8_t b);
    void setBrightness(uint8_t value) override;
    void checkConnection();
    bool isConnected();

    /// Base Class functions
    void setGPIO(uint8_t pin) override;
    void setValue(const JsonDocument &doc) override;

private:
    Adafruit_NeoPixel _strip;
    uint16_t _pixels;
};

#endif
