#include <Arduino.h>
#include "DeviceManager.h"
#include "WiFiManager.h"
#include "WebServerHandler.h"
#include "WebSocketHandler.h"
#include "config.h"

DeviceManager deviceManager;
WiFiManager wifiManager;
WebServerHandler webServerHandler;
WebSocketHandler webSocketHandler;

#if defined(ESP32)
Preferences devicePreferences;
#endif

// Example of a function that could be used as a member function pointer
void sendMessageHandler(char *messageData)
{
  webSocketHandler.sendMessage(messageData);
}

void receivedMessageHandler(const JsonDocument &doc)
{
  if (doc.containsKey(SET_AP_KEY) || doc.containsKey(CONNECT_WIFI_KEY) || doc.containsKey(SCAN_NETWORKS_KEY))
  {
    wifiManager.handleMessage(doc);
  }
  else
  {
    deviceManager.handleWebSocketMessage(doc);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println(".....");
  Serial.println("Init Device");

  wifiManager.begin();
  webSocketHandler.setReceivedMessageFunction(receivedMessageHandler);
  webSocketHandler.begin(&webServerHandler.server);
  webServerHandler.begin();
  deviceManager.setSendMessageFunction(sendMessageHandler);
  deviceManager.begin();
}

void loop()
{
  unsigned long currentTime = millis();

  deviceManager.readAndNotifyDevices();

  webSocketHandler.Loop();
}
