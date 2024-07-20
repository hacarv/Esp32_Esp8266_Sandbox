#include <Arduino.h>
#include "utils.h"

void setupUtils() {
  Serial.begin(115200);
}

void sendWebSocketMessage(String message) {
  Serial.println(message);
  
}
