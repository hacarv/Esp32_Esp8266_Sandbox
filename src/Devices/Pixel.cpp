#include "Pixel.h"

Pixel::Pixel() : DeviceBaseClass() {}

void Pixel::begin(uint8_t pin, uint16_t pixels, const char *deviceKey)
{
    init(pin, deviceKey);
    _pixels = pixels;
    _strip = Adafruit_NeoPixel(pixels, pin, NEO_GRB + NEO_KHZ800);
    _strip.begin();
    _strip.clear(); // Initialize all pixels to 'off'
    _strip.show();
    checkConnection();
}

void Pixel::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    Serial.print("R");
    Serial.print(r);
    for(int i=0; i<_strip.numPixels(); i++) 
    {
        setPixelColor(i, r, g, b);
    }
}

void Pixel::setPixelColor(uint8_t pixel, uint8_t r, uint8_t g, uint8_t b)
{
    _strip.setPixelColor(pixel, _strip.Color(r, g, b));
    _strip.show();
      delay(50); 
}

void Pixel::setBrightness(uint8_t value)
{
    _strip.setBrightness(value);
    _strip.show();
    delay(10); 
}

bool Pixel::isConnected()
{
    return _pin != 0;
}

void Pixel::setGPIO(uint8_t pin)
{
    _strip = Adafruit_NeoPixel(_pixels, pin, NEO_GRB + NEO_KHZ800);
    _strip.begin();
    _strip.clear(); // Initialize all pixels to 'off'
    _strip.show();
    DeviceBaseClass::setGPIO(pin);
}

void Pixel::setValue(const JsonDocument &doc)
{
    setColor(doc[VALUE_KEY]["R"], doc[VALUE_KEY]["G"], doc[VALUE_KEY]["B"]);
}

void Pixel::checkConnection()
{
    if (!isConnected())
    {
        const char *message = "{\"" ERROR_KEY "\":\"PIXEL not connected\"}";
        Serial.println(message);
    }
}
