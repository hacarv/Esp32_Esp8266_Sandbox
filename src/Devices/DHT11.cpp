#include "DHT11.h"

DHT::DHT() : DeviceBaseClass() {}

void DHT::begin(uint8_t pin, const char *deviceKey)
{
    init(pin, deviceKey);
    dht = new DHT_Async(pin, DHT_TYPE_11);
    checkConnection();
}

void DHT::checkConnection()
{
    if (!isConnected())
    {
        checkConnectionMessage();
    }
}

bool DHT::isConnected()
{
    return _pin != 0;
}

int DHT::read()
{
    return dht->measure(&temperature, &humidity);
}

void DHT::readAndNotify()
{
    if (isIntervalExpired() && isReadAndNotifyEnabled())
    {
        if (read() == 1)
        {
            if (temperature != lastTemperature || humidity != lastHumidity)
            {
                getValue();
            }
        }
    }
}

void DHT::getValue()
{
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_VALUE_KEY;
    doc[VALUE_KEY]["Humidity"] = humidity;
    doc[VALUE_KEY]["Temperature"] = temperature;
    sendMessage(doc);
}
void DHT::getGPIO()
{
    JsonDocument doc;
    doc[MESSAGE_TYPE_KEY] = SET_GPIO_KEY;
    doc[VALUE_KEY] = _pin;
    sendMessage(doc);
}

void DHT::setGPIO(uint8_t pin)
{
    dht = new DHT_Async(pin, DHT_TYPE_11);
    DeviceBaseClass::setGPIO(pin);
}
