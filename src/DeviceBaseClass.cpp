#include "DeviceBaseClass.h"

DeviceBaseClass::DeviceBaseClass(): sendMessageFunct(nullptr), _interval(1000), _lastReadTime(0) {} // Default value of 1000 ms

void DeviceBaseClass::setSendMessageFunction(void (*sendMsgFunc)(char *messageData))
{
    sendMessageFunct = sendMsgFunc;
}

void DeviceBaseClass::setInterval(unsigned long interval)
{
    _interval = interval;
    Serial.println(_interval);
}

bool DeviceBaseClass::isIntervalExpired()
{
    unsigned long currentTime = millis();

    if (_interval != -1 && currentTime - _lastReadTime >= _interval)
    {
        _lastReadTime = currentTime;
        return true;
    }

    return false;
}

void DeviceBaseClass::sendMessage(char* messageData)
{
     if (sendMessageFunct != nullptr) {
            sendMessageFunct(messageData);
        } else {
            Serial.println("sendMessage function is not set!");
        }
}

// virtual void DeviceBaseClass::begin() {
//     Serial.println("Initializing device...");
// }

// virtual void DeviceBaseClass::update() {
//     Serial.println("Updating device...");
// }
