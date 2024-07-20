#include "LED.h"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "config.h"
#include "WebSocketHandler.h"

void LED::begin() {
    _strip = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);
    _strip.begin();
    _strip.show(); // Initialize all pixels to 'off'
    checkConnection();
}

void LED::setColor(uint8_t r, uint8_t g, uint8_t b) {
    _strip.setPixelColor(0, _strip.Color(r, g, b));
    _strip.show();
}

void LED::update() {
    // No periodic update required for LED
}

bool LED::isConnected() {
    return true; // Dummy check, replace with actual connection check if needed
}

void LED::checkConnection() {
    if (!isConnected()) {
        String message = "{\"" ERROR_KEY "\":\"LED not connected\"}";
        notifyClients(message);
        Serial.println(message);
    }
}

