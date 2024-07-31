#include "WiFiManager.h"

#if defined(ESP32)
Preferences preferences;
#endif


void WiFiManager::begin()
{
#if defined(ESP32)
    preferences.begin("wifi-config", false);
#else
    EEPROM.begin(EEPROM_SIZE);
#endif
    loadConfiguration();
    WiFi.mode(WIFI_AP_STA);
    setupAP();
    if (strlen(wifi_data._ssid) > 0)
    {
        connectToNetwork(wifi_data._ssid, wifi_data._password);
    }
}

void WiFiManager::setupAP()
{
    Serial.print("SoftAP: ");
    Serial.println(wifi_data._apSsid);

    WiFi.softAP(wifi_data._apSsid, wifi_data._apPassword);
    IPAddress localIP;
    localIP.fromString(wifi_data._apIp);
    WiFi.softAPConfig(localIP, localIP, IPAddress(255, 255, 255, 0));
    Serial.print("Access Point started: ");
    Serial.print(wifi_data._apSsid);
    Serial.print(" IP: ");
    Serial.println(wifi_data._apIp);
}

void WiFiManager::handleMessage(const JsonDocument &doc)
{
    if (doc.containsKey("setAP"))
    {
        strlcpy(wifi_data._apSsid, doc["setAP"]["ssid"], sizeof(wifi_data._apSsid));
        strlcpy(wifi_data._apPassword, doc["setAP"]["password"], sizeof(wifi_data._apPassword));
        strlcpy(wifi_data._apIp, doc["setAP"]["ip"], sizeof(wifi_data._apIp));
        setupAP();
        saveConfiguration();
    }
    else if (doc.containsKey("connectWiFi"))
    {
        strlcpy(wifi_data._ssid, doc["connectWiFi"]["ssid"], sizeof(wifi_data._ssid));
        strlcpy(wifi_data._password, doc["connectWiFi"]["password"], sizeof(wifi_data._password));
        connectToNetwork(wifi_data._ssid, wifi_data._password);
        saveConfiguration();
    }
    else if (doc.containsKey("scanNetworks"))
    {
        // scanNetworks();
    }
}

void WiFiManager::scanNetworks(const char *buffer)
{
    int n = WiFi.scanNetworks();
    JsonDocument scanDoc;
    JsonArray networks = scanDoc.to<JsonArray>();

    for (int i = 0; i < n; ++i)
    {
        JsonObject network;
        network["ssid"] = WiFi.SSID(i);
        network["rssi"] = WiFi.RSSI(i);
        networks.add(network);
    }

    // serializeJson(scanDoc, buffer);
}

void WiFiManager::connectToNetwork(const char *ssid, const char *password)
{
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    int retry_count = 0;
    while (WiFi.status() != WL_CONNECTED && retry_count < 20)
    {
        delay(500);
        Serial.print(".");
        retry_count++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.print("Connected to WiFi: ");
        Serial.println(ssid);
        Serial.print(" IP: ");
        Serial.println(WiFi.localIP());
        JsonDocument statusDoc;
        statusDoc["status"] = "connected";
        char jsonString[JSON_DOC_SIZE];
        // serializeJson(statusDoc, jsonString);
        // notifyClients(jsonString.c_str());
    }
    else
    {
        Serial.print("Failed to connect to WiFi: ");
        Serial.println(ssid);
        JsonDocument statusDoc;
        statusDoc["status"] = "connection_failed";
        char jsonString[JSON_DOC_SIZE];
        // serializeJson(statusDoc, jsonString);
        // notifyClients(jsonString.c_str());
    }
}

void WiFiManager::saveConfiguration()
{
#if defined(ESP32)
    preferences.putString("ssid", wifi_data._ssid);
    preferences.putString("password", wifi_data._password);
    preferences.putString("apSsid", wifi_data._apSsid);
    preferences.putString("apPassword", wifi_data._apPassword);
    preferences.putString("apIp", wifi_data._apIp);
#else
    EEPROM.put(0, wifi_data);
    // EEPROM.put(32, _password);
    // EEPROM.put(64, _apSsid);
    // EEPROM.put(96, _apPassword);
    // EEPROM.put(128, _apIp);
    EEPROM.commit();
#endif
}

void WiFiManager::loadConfiguration()
{

#if defined(ESP32)

    strlcpy(wifi_data._ssid, preferences.getString("ssid", DEFAULT_SSID).c_str(), sizeof(wifi_data._ssid));
    strlcpy(wifi_data._password, preferences.getString("password", DEFAULT_PASSWORD).c_str(), sizeof(wifi_data._password));
    strlcpy(wifi_data._apSsid, preferences.getString("apSsid", DEFAULT_AP_SSID).c_str(), sizeof(wifi_data._apSsid));
    strlcpy(wifi_data._apPassword, preferences.getString("apPassword", DEFAULT_AP_PASSWORD).c_str(), sizeof(wifi_data._apPassword));
    strlcpy(wifi_data._apIp, preferences.getString("apIp", DEFAULT_AP_IP).c_str(), sizeof(wifi_data._apIp));
#else
    EEPROM.get(0, wifi_data);
    // EEPROM.get(32, _password);
    // EEPROM.get(64, _apSsid);
    // EEPROM.get(96, _apPassword);
    // EEPROM.get(128, _apIp);
    if (strcmp(wifi_data._ssid, ""))
    {
        strcpy(wifi_data._ssid, DEFAULT_SSID);
        strcpy(wifi_data._password, DEFAULT_PASSWORD);
        strcpy(wifi_data._apPassword, DEFAULT_AP_PASSWORD);
        strcpy(wifi_data._apSsid, DEFAULT_AP_SSID);
        strcpy(wifi_data._apIp, DEFAULT_AP_IP);
    }
#endif
}
