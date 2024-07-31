#include "DeviceManager.h"

void DeviceManager::begin()
{
    // Setup devices with respective pins and intervals
    led.begin(LED_PIN);
    ldr.begin(LDR_PIN);
    pixel.begin(PIXEL_PIN, 4);
    servoMotor.begin(SERVO_PIN);
    potentiometer.begin(POTENTIOMETER_PIN);
    stepperMotor.begin(STEPPER_PIN_STEP, STEPPER_PIN_DIR, STEPPER_PIN_ENABLE);

    led.setSendMessageFunction(sendMessageFunct);
    ldr.setSendMessageFunction(sendMessageFunct);
    potentiometer.setSendMessageFunction(sendMessageFunct);
}

void DeviceManager::readAndNotifyDevices()
{
    led.readAndNotify();

    ldr.readAndNotify();

    potentiometer.readAndNotify();
}

void DeviceManager::handleWebSocketMessage(const JsonDocument &doc)
{
    if (doc.containsKey(DEVICE_KEY))
    {
        handleDeviceRequest(doc);
    }
}

void DeviceManager::handleDeviceRequest(const JsonDocument &doc)
{
    const char *device = doc[DEVICE_KEY];

     if (strcmp(device, LED_KEY) == 0)
    {
        if (doc.containsKey(GET_VALUE_KEY) && strcmp(doc[GET_VALUE_KEY], "value") == 0)
        {
           led.getData();
        }
        if (doc.containsKey(SET_INTERVAL_KEY))
        {
            led.setInterval(doc[SET_INTERVAL_KEY]);
        }
        if (doc.containsKey(SET_VALUE_KEY))
        {
            led.setValue(doc[SET_VALUE_KEY]);
        }
        if (doc.containsKey("set_pin"))
        {
            led.begin(doc["set_pin"]);
        }
    }
    if (strcmp(device, LDR_KEY) == 0)
    {
        if (doc.containsKey(GET_VALUE_KEY) && strcmp(doc[GET_VALUE_KEY], "value") == 0)
        {
            ldr.getData();
        }
        if (doc.containsKey(SET_INTERVAL_KEY))
        {
            ldr.setInterval(doc[SET_INTERVAL_KEY]);
        }
    }
    else if (strcmp(device, POTENTIOMETER_KEY) == 0)
    {
        if (doc.containsKey(GET_VALUE_KEY) && strcmp(doc[GET_VALUE_KEY], "value") == 0)
        {
            potentiometer.getData();
        }
        if (doc.containsKey(SET_INTERVAL_KEY))
        {
            potentiometer.setInterval(doc[SET_INTERVAL_KEY]);
        }
    }
    else if (strcmp(device, PIXEL_KEY) == 0)
    {
        if (doc.containsKey(SET_VALUE_KEY))
        {
            pixel.setColor(doc[SET_VALUE_KEY]["r"], doc[SET_VALUE_KEY]["g"], doc[SET_VALUE_KEY]["b"]);
        }
    }
    else if (strcmp(device, SERVO_KEY) == 0)
    {
        if (doc.containsKey(SET_VALUE_KEY))
        {
            servoMotor.setPosition(doc[SET_VALUE_KEY]);
        }
    }
    else if (strcmp(device, STEPPER_KEY) == 0)
    {
        if (doc.containsKey(SET_VALUE_KEY))
        {
            stepperMotor.moveSteps(doc[SET_VALUE_KEY]);
        }
    }
}
void DeviceManager::setSendMessageFunction(void (*sendMsgFunc)(char *messageData))
{
    sendMessageFunct = sendMsgFunc;
}
