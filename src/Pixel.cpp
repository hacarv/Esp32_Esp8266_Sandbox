#include "Pixel.h"

Pixel::Pixel() : DeviceBaseClass() {}

void Pixel::begin(uint8_t pin, uint16_t pixels)
{
    _pin = pin;
    _pixels = pixels;
    _strip = Adafruit_NeoPixel(pixels, pin, NEO_GRB + NEO_KHZ800);
    _strip.begin();
    _strip.clear(); // Initialize all pixels to 'off'
    _strip.show();
    checkConnection();
}

void Pixel::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    for (size_t i = 0; i < _pixels; i++)
    {
        setPixelColor(i, r, g, b);
    }
}

void Pixel::setPixelColor(uint8_t pixel, uint8_t r, uint8_t g, uint8_t b)
{
    _strip.setPixelColor(pixel, _strip.Color(r, g, b));
    _strip.show();
}

bool Pixel::isConnected()
{
    return _pin != 0; 
}

void Pixel::checkConnection()
{
    if (!isConnected())
    {
        const char *message = "{\"" ERROR_KEY "\":\"PIXEL not connected\"}";
        Serial.println(message);
    }
}
