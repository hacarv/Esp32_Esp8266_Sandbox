#include "DeviceBaseClass.h"
#include "config.h"

DeviceBaseClass::DeviceBaseClass() : sendMessageFunct(nullptr), _interval(loadNotifyIntervalFromStorage(1000)), _pin(0), _lastReadTime(0)
{
}

void DeviceBaseClass::init(uint8_t pin, const char *deviceKey)
{
#if defined(ESP32)
    pin = loadGPIOFromStorage(pin);
#endif
    setGPIO(pin);
}

void DeviceBaseClass::checkConnectionMessage()
{
    Serial.printf("%s: GPIO not defined yet", deviceKey);
    Serial.println();
}

void DeviceBaseClass::setGPIOMessage(uint8_t pin)
{
    Serial.printf("%s - GPIO set: %d", deviceKey, pin);
    Serial.println();
}

void DeviceBaseClass::setSendMessageFunction(void (*sendMsgFunc)(char *messageData))
{
    sendMessageFunct = sendMsgFunc;
}

void DeviceBaseClass::setInterval(unsigned long interval)
{
    _interval = interval;
#if defined(ESP32)
    saveNotifyIntervalToStorage(_interval);
#endif
    Serial.println(_interval);
    getInterval();
}

void DeviceBaseClass::getInterval()
{
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_INTERVAL_KEY;
    doc[VALUE_KEY] = _interval;
    sendMessage(doc);
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

void DeviceBaseClass::sendMessage(char *messageData)
{
    if (sendMessageFunct != nullptr)
    {
        sendMessageFunct(messageData);
    }
    else
    {
        Serial.println("sendMessage function is not set!");
    }
}

void DeviceBaseClass::sendMessage(JsonDocument &doc)
{
    doc[DEVICE_KEY] = deviceKey;
    char messageBuffer[JSON_DOC_SIZE];
    serializeJson(doc, messageBuffer);
    sendMessage(messageBuffer);
}

void DeviceBaseClass::setReadAndNotify(bool state)
{
    readAndNotifyEnabled = state;
}

void DeviceBaseClass::getReadAndNotify()
{
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_READ_NOTIFY_KEY;
    doc[VALUE_KEY] = isReadAndNotifyEnabled();
    sendMessage(doc);
}

bool DeviceBaseClass::isReadAndNotifyEnabled()
{
    return readAndNotifyEnabled;
}

void DeviceBaseClass::getValue()
{
    Serial.println(deviceKey);
    Serial.println(F("getValue The function has not  implemented!"));
}

void DeviceBaseClass::setValue(const JsonDocument &doc)
{
    Serial.println(deviceKey);
    Serial.println(F("setValue The function has not  implemented!"));
}

void DeviceBaseClass::getGPIO()
{
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_GPIO_KEY;
    doc[VALUE_KEY] = _pin;
    sendMessage(doc);
}

void DeviceBaseClass::setGPIO(uint8_t pin)
{
    _pin = pin;
#if defined(ESP32)
    saveGPIOToStorage(_pin);
#endif
    pinMode(_pin, OUTPUT);
    setGPIOMessage(_pin);
}

const char *DeviceBaseClass::getCustomKey(const char *key)
{
    // Calcular el tamaño del buffer necesario
    size_t totalLength = strlen(deviceKey) + strlen(key) + 1; // +1 para el terminador nulo

    // Asignar memoria para el buffer
    char *result = new char[totalLength];

    // Copiar y concatenar las cadenas
    strcpy(result, deviceKey);
    strcat(result, key);

    return result;
}


uint8_t DeviceBaseClass::loadGPIOFromStorage(uint8_t pin)
{
#if defined(ESP32)
    devicePreferences.begin(deviceKey, true);
    uint8_t value = devicePreferences.getUChar(getCustomKey("gpio"), pin);
    devicePreferences.end();
    return value;
#else
    return pin;
#endif
}

void DeviceBaseClass::saveGPIOToStorage(uint8_t pin)
{
#if defined(ESP32)
    devicePreferences.begin(deviceKey, false);
    devicePreferences.putUChar(getCustomKey("gpio"), pin);
    devicePreferences.end();
#else
    //
#endif
}

int DeviceBaseClass::loadNotifyIntervalFromStorage(int interval)
{
#if defined(ESP32)
    devicePreferences.begin(deviceKey, true);
    uint8_t value = devicePreferences.getUChar(getCustomKey("interval"), interval);
    devicePreferences.end();
    return value;
#else
    return interval;
#endif
}

void DeviceBaseClass::saveNotifyIntervalToStorage(int interval)
{
#if defined(ESP32)
    devicePreferences.begin(deviceKey, false);
    devicePreferences.putInt(getCustomKey("interval"), interval);
    devicePreferences.end();
#else
    //
#endif
}

// virtual void DeviceBaseClass::begin() {
//     Serial.println("Initializing device...");
// }

// virtual void DeviceBaseClass::update() {
//     Serial.println("Updating device...");
// }
