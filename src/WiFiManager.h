#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <ArduinoJson.h>

class WiFiManager {
public:
    void begin();
    void handleMessage(const JsonDocument& doc);
    void scanNetworks();
    void connectToNetwork(const char* ssid, const char* password);
    void saveConfiguration();
    void loadConfiguration();
    void setupAP();
    
private:
    String _ssid;
    String _password;
    String _apSsid;
    String _apPassword;
    String _apIp;
};

#endif // WIFIMANAGER_H
