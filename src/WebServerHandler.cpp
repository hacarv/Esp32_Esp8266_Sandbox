#include "WebServerHandler.h"

WebServerHandler::WebServerHandler() : server(80) {}

void WebServerHandler::begin()
{
    Serial.println(F("Init WebServerHandler"));
    server.begin();
    Serial.println(F("WebServerHandler Initialized"));
}

void WebServerHandler::handleWebRequests()
{
    // This method can be used to add additional request handlers
}
