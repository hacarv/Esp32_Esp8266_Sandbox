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
    void begin(uint8_t pin, uint16_t pixels);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setPixelColor(uint8_t pixel, uint8_t r, uint8_t g, uint8_t b);
    void checkConnection();
    bool isConnected();

private:
    Adafruit_NeoPixel _strip;
    uint8_t _pin = 0;
    uint16_t _pixels;
};

#endif
