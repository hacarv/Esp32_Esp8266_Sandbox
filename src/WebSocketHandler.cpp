#include "WebSocketHandler.h"

WebSocketHandler::WebSocketHandler() : ws("/ws") {}

void WebSocketHandler::begin(AsyncWebServer *server)
{
  Serial.println(F("Init WebSocketHandler"));
  ws.onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
             { this->onEvent(server, client, type, arg, data, len); });
  server->addHandler(&ws);
  Serial.println(F("WebSocketHandler Initialized"));
}

void WebSocketHandler::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                               void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
  case WS_EVT_CONNECT:
    Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    break;
  case WS_EVT_DISCONNECT:
    Serial.printf("WebSocket client #%u disconnected\n", client->id());
    break;
  case WS_EVT_DATA:
    handleWebSocketMessage(arg, data, len);
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}

void WebSocketHandler::handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
  {
    data[len] = 0;
    JsonDocument doc;
    deserializeJson(doc, (char *)data);
    Serial.print("MSG: ");
    Serial.println((char *)data);
    
    receivedMessageFunct(doc);
  }
}

void WebSocketHandler::sendMessage(char *message)
{
  ws.textAll(message);
  Serial.println(message);
}

void WebSocketHandler::setReceivedMessageFunction(void (*receivedMsgFunc)(const JsonDocument &))
{
  receivedMessageFunct = receivedMsgFunc;
}

void WebSocketHandler::Loop()
{
  // Manejar eventos del WebSocket
  ws.cleanupClients();
}
