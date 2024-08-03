#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#if defined(ESP32)
#include <WiFi.h>
#include <Preferences.h>
extern Preferences devicePreferences; 
#else
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#define EEPROM_SIZE 512
#endif
#include "config.h"

class WiFiManager
{
    struct wifi_config
    {
        char _ssid[32] = "1";
        char _password[32] = "1";
        char _apSsid[32] = "1";
        char _apPassword[32] = "1";
        char _apIp[16];
    } wifi_data;

public:
    void begin();
    void handleMessage(const JsonDocument &doc);
    void scanNetworks();
    void connectToNetwork(const char *ssid, const char *password);
    void saveConfiguration();
    void loadConfiguration();
    void setupAP();

private:
    

    //wifi_config wifi_data;
};

#endif // WIFIMANAGER_H
