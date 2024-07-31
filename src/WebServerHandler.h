#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <ESPAsyncWebServer.h>
#include "config.h"

class WebServerHandler {
public:
    WebServerHandler();
    void begin();
    void handleWebRequests();

    AsyncWebServer server;
private:
    
};

#endif // WEBSERVERHANDLER_H
