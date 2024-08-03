#include "DeviceManager.h"

void DeviceManager::begin()
{
    // Setup devices with respective pins and intervals
    led.begin(LED_PIN, LED_KEY);
    ldr.begin(LDR_PIN, LDR_KEY);
    potentiometer.begin(POTENTIOMETER_PIN, POTENTIOMETER_KEY);
    relay.begin(RELAY_PIN, RELAY_KEY);
    pixel.begin(PIXEL_PIN, 4);
    servoMotor.begin(SERVO_PIN,SERVO_KEY);    
    stepperMotor.begin(STEPPER_PIN_STEP, STEPPER_PIN_DIR, STEPPER_PIN_ENABLE);

    led.setSendMessageFunction(sendMessageFunct);
    ldr.setSendMessageFunction(sendMessageFunct);
    potentiometer.setSendMessageFunction(sendMessageFunct);
    relay.setSendMessageFunction(sendMessageFunct);
    servoMotor.setSendMessageFunction(sendMessageFunct);
}

DeviceBaseClass *DeviceManager::getDevice(const char *deviceKey)
{
    if (strcmp(deviceKey, LED_KEY) == 0)
    {
        return &led;
    }
    else if (strcmp(deviceKey, LDR_KEY) == 0)
    {
        return &ldr;
    }
    else if (strcmp(deviceKey, POTENTIOMETER_KEY) == 0)
    {
        return &potentiometer;
    }
    else if (strcmp(deviceKey, RELAY_KEY) == 0)
    {
        return &relay;
    }
     else if (strcmp(deviceKey, SERVO_KEY) == 0)
    {
        return &servoMotor;
    }

    return nullptr;
}

void DeviceManager::readAndNotifyDevices()
{
    ldr.readAndNotify();

    potentiometer.readAndNotify();

    servoMotor.readAndNotify();
}

void DeviceManager::handleWebSocketMessage(const JsonDocument &doc)
{
    if (doc.containsKey(DEVICE_KEY))
    {
        handleDeviceMessage(doc);
    }
}

void DeviceManager::handleDeviceMessage(const JsonDocument &doc)
{
    if (!doc.containsKey(MESSAGE_TYPE_KEY))
        return;

    const char *deviceKey = doc[DEVICE_KEY];
    const char *messageType = doc[MESSAGE_TYPE_KEY];
    DeviceBaseClass *device;

    device = getDevice(deviceKey);

    //prevent function call if device is null
    if (device != nullptr)
    {
        handleDeviceAction(device, messageType, doc);
    }
}

// Function to handle device actions
void DeviceManager::handleDeviceAction(DeviceBaseClass *device, const char *messageType, const JsonDocument &doc)
{
    if (strcmp(messageType, GET_VALUE_KEY) == 0)
    {
        device->getValue();
    }
    else if (strcmp(messageType, SET_INTERVAL_KEY) == 0)
    {
        device->setInterval(doc[VALUE_KEY]);
    }
    else if (strcmp(messageType, SET_VALUE_KEY) == 0)
    {
        device->setValue(doc);
    }
    else if (strcmp(messageType, SET_GPIO_KEY) == 0)
    {
        device->setGPIO(doc[VALUE_KEY]);
        device->getGPIO();
    }
    else if (strcmp(messageType, GET_GPIO_KEY) == 0)
    {
        device->getGPIO();
    }
     else if (strcmp(messageType, SET_READ_NOTIFY_KEY) == 0)
    {
        device->setReadAndNotify(doc[VALUE_KEY]);
    }
}

void DeviceManager::setSendMessageFunction(void (*sendMsgFunc)(char *messageData))
{
    sendMessageFunct = sendMsgFunc;
}
