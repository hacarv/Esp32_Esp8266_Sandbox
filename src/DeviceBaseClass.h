#ifndef DEVICEBASECLASS_H
#define DEVICEBASECLASS_H

#include <Arduino.h>
#include <ArduinoJson.h>

#if defined(ESP32)
#include <Preferences.h>
extern Preferences devicePreferences;
#endif

class DeviceBaseClass
{
protected:
    void (*sendMessageFunct)(char *messageData);
    uint8_t _pin = 0;
    int _lastValue;
    int _interval;     // Interval in milliseconds
    unsigned long _lastReadTime; // Last time a read was performed
    const char *deviceKey;
    bool readAndNotifyEnabled = true; // Default to enabled

public:
    DeviceBaseClass();

    void init(uint8_t pin, const char * _deviceKey);
    void checkConnectionMessage();
    void sendGPIOMessage(uint8_t pin);
    void sendIntervalMessage(int pin);
    void setSendMessageFunction(void (*sendMsgFunc)(char *messageData));
    void setInterval(int interval);
    void getInterval();
    bool isIntervalExpired();
    void sendMessage(char *messageData);
    void sendMessage(JsonDocument &doc);
    virtual void getValue();
    virtual void setValue(const JsonDocument &doc);
    virtual void getGPIO();
    virtual void setGPIO(uint8_t pin);

    // Enable or disable readAndNotify function
    void setReadAndNotify(bool state);
    void getReadAndNotify();
    bool isReadAndNotifyEnabled();
    const char *getCustomKey(const char *key);


    virtual void saveNotifyIntervalToStorage(int interval);
    virtual int loadNotifyIntervalFromStorage(int interval);
    virtual uint8_t loadGPIOFromStorage(uint8_t pin);
    virtual void saveGPIOToStorage(uint8_t pin);
    virtual void setBrightness(uint8_t value);
    virtual void onCancel();


    // virtual void begin();
    // virtual void update();
};

#endif
