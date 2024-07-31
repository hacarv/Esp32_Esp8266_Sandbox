#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <ArduinoJson.h>
#include "config.h"
#include "LDR.h"
#include "LED.h"
#include "Pixel.h"
#include "Potentiometer.h"
#include "ServoMotor.h"
#include "StepperMotor.h"

class DeviceManager
{
protected:
    void (*sendMessageFunct)(char *messageData);

public:
    void begin();
    void readAndNotifyDevices();
    void handleWebSocketMessage(const JsonDocument &doc);
    void handleDeviceRequest(const JsonDocument &doc);
    void setSendMessageFunction(void (*sendMsgFunc)(char *messageData));

private:
    LDR ldr;
    LED led;
    Pixel pixel;
    Potentiometer potentiometer;
    ServoMotor servoMotor;
    StepperMotor stepperMotor;
};

#endif // DEVICEMANAGER_H
