#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#if defined(ESP32)
#include <AsyncTCP.h>
#else
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "config.h"

#include "DeviceManager.h"
#include "WiFiManager.h"

extern DeviceManager deviceManager;
extern WiFiManager wifiManager;

class WebSocketHandler
{
public:
    WebSocketHandler();
    void begin(AsyncWebServer *server);
    void Loop();
    void sendMessage(char *message);
    void setReceivedMessageFunction(void (*receivedMsgFunc)(const JsonDocument &));
    void (*receivedMessageFunct)(const JsonDocument &);

private:
    void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
    AsyncWebSocket ws;
};

#endif // WEBSOCKETHANDLER_H
