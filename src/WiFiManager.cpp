#include "WiFiManager.h"
#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#include <Preferences.h>
Preferences preferences;
#else
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#define EEPROM_SIZE 512
#endif
#include "WebSocketHandler.h"
#include "config.h"

#if !defined(ESP32)
#include <EEPROM.h>
#endif

void WiFiManager::begin() {

#if defined(ESP32)
    preferences.begin("wifi-config", false);
#else
    EEPROM.begin(EEPROM_SIZE);
#endif
    loadConfiguration();
    WiFi.mode(WIFI_AP_STA);
    setupAP();
    
    if (!_ssid.isEmpty()) {
        connectToNetwork(_ssid.c_str(), _password.c_str());
    }
}

void WiFiManager::setupAP() {
    WiFi.softAP(_apSsid.c_str(), _apPassword.c_str());
    IPAddress localIP;
    localIP.fromString(_apIp.c_str());
    WiFi.softAPConfig(localIP, localIP, IPAddress(255, 255, 255, 0));
    Serial.println("Access Point started: " + _apSsid + " IP: " + _apIp);
}

void WiFiManager::handleMessage(const JsonDocument& doc) {
    if (doc.containsKey("setAP")) {
        _apSsid = doc["setAP"]["ssid"].as<String>();
        _apPassword = doc["setAP"]["password"].as<String>();
        _apIp = doc["setAP"]["ip"].as<String>();
        setupAP();
        saveConfiguration();
    } else if (doc.containsKey("connectWiFi")) {
        _ssid = doc["connectWiFi"]["ssid"].as<String>();
        _password = doc["connectWiFi"]["password"].as<String>();
        connectToNetwork(_ssid.c_str(), _password.c_str());
        saveConfiguration();
    } else if (doc.containsKey("scanNetworks")) {
        scanNetworks();
    }
}

void WiFiManager::scanNetworks() {
    int n = WiFi.scanNetworks();
    JsonDocument scanDoc;
    JsonArray networks = scanDoc.to<JsonArray>();

    for (int i = 0; i < n; ++i) {
        JsonObject network;
        network["ssid"] = WiFi.SSID(i);
        network["rssi"] = WiFi.RSSI(i);
        networks.add(network);
    }

    String jsonString;
    serializeJson(scanDoc, jsonString);
    notifyClients(jsonString);
}

void WiFiManager::connectToNetwork(const char* ssid, const char* password) {

     Serial.println("Connecting to WiFi: " + String(ssid));
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi: " + String(ssid));
    notifyClients("{\"status\":\"connected\"}");
}

void WiFiManager::saveConfiguration() {
#if defined(ESP32)
    preferences.putString("ssid", _ssid);
    preferences.putString("password", _password);
    preferences.putString("apSsid", _apSsid);
    preferences.putString("apPassword", _apPassword);
    preferences.putString("apIp", _apIp);
#else
    EEPROM.put(0, _ssid);
    EEPROM.put(100, _password);
    EEPROM.put(200, _apSsid);
    EEPROM.put(300, _apPassword);
    EEPROM.put(400, _apIp);
    EEPROM.commit();
#endif
}

void WiFiManager::loadConfiguration() {
#if defined(ESP32)
    _ssid = preferences.getString("ssid", DEFAULT_SSID);
    _password = preferences.getString("password", DEFAULT_PASSWORD);
    _apSsid = preferences.getString("apSsid", DEFAULT_AP_SSID);
    _apPassword = preferences.getString("apPassword", DEFAULT_AP_PASSWORD);
    _apIp = preferences.getString("apIp", DEFAULT_AP_IP);
    Serial.println("Access Point SSID: " + _apSsid + " IP: " + _apIp);
#else
    EEPROM.get(0,_ssid);
    if (_ssid.isEmpty()) {
        _ssid = DEFAULT_SSID;
    }
    EEPROM.get(100,_password);
    if (_password.isEmpty()) {
        _password = DEFAULT_PASSWORD;
    }
    EEPROM.get(200,_apSsid);
    if (_apSsid.isEmpty()) {
        _apSsid = DEFAULT_AP_SSID;
    }
    EEPROM.get(300,_apPassword);
    if (_apPassword.isEmpty()) {
        _apPassword = DEFAULT_AP_PASSWORD;
    }
    EEPROM.get(400,_apIp);
    if (_apIp.isEmpty()) {
        _apIp = DEFAULT_AP_IP;
    }
#endif
}
