#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>

class LED {
public:
    void begin();
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void update();
    void checkConnection();
    bool isConnected();

private:
    Adafruit_NeoPixel _strip;
};

#endif
