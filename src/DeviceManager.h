#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <ArduinoJson.h>
#include "config.h"
#include "Devices/LDR.h"
#include "Devices/LED.h"
#include "Devices/Pixel.h"
#include "Devices/Potentiometer.h"
#include "Devices/ServoMotor.h"
#include "Devices/StepperMotor.h"

class DeviceManager
{
protected:
    void (*sendMessageFunct)(char *messageData);

public:
    void begin();
    void readAndNotifyDevices();
    void handleWebSocketMessage(const JsonDocument &doc);
    DeviceBaseClass* getDevice(const char *deviceKey);
    void handleDeviceMessage(const JsonDocument &doc);
    void setSendMessageFunction(void (*sendMsgFunc)(char *messageData));
    void handleDeviceAction(DeviceBaseClass *device, const char *messageType, const JsonDocument &doc);

private:
    LDR ldr;
    LED led;
    Pixel pixel;
    Potentiometer potentiometer;
    ServoMotor servoMotor;
    StepperMotor stepperMotor;
};

#endif // DEVICEMANAGER_H
