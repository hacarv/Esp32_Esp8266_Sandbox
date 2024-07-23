#include "WebSocketHandler.h"


void initWebSocket() {
    ws.onEvent([](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
        handleWebSocketMessage(arg, data, len);
    });
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if(info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        data[len] = 0;
        JsonDocument doc;
        deserializeJson(doc, (char*)data);

        if (doc.containsKey(SET_AP_KEY) || doc.containsKey(CONNECT_WIFI_KEY) || doc.containsKey(SCAN_NETWORKS_KEY)) {
            wifiManager.handleMessage(doc);
        } else {
            if (doc.containsKey(LDR_KEY)) {
                ldr.readAndNotify();
            }
            if (doc.containsKey(LED_KEY)) {
                led.setColor(doc[LED_KEY]["r"], doc[LED_KEY]["g"], doc[LED_KEY]["b"]);
            }
            if (doc.containsKey(SERVO_KEY)) {
                servoMotor.setPosition(doc[SERVO_KEY]);
            }
            if (doc.containsKey(STEPPER_KEY)) {
                stepperMotor.moveSteps(doc[STEPPER_KEY]);
            }
        }
    }
}

void notifyClients(String message) {
    ws.textAll(message);
}

void handleWebSocket() {
    // Manejar eventos del WebSocket
    ws.cleanupClients();
}
