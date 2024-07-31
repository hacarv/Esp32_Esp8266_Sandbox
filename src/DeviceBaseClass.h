#ifndef DEVICEBASECLASS_H
#define DEVICEBASECLASS_H

#include <Arduino.h>

class DeviceBaseClass {
protected:
    void (*sendMessageFunct)(char* messageData);
    unsigned long _interval;  // Interval in milliseconds
    unsigned long _lastReadTime;  // Last time a read was performed

public:
    DeviceBaseClass();
    
    void setSendMessageFunction(void (*sendMsgFunc)(char* messageData));
    void setInterval(unsigned long interval);
    bool isIntervalExpired();
    void sendMessage(char *messageData);
    // virtual void begin();
    // virtual void update();
};

#endif
