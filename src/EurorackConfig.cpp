#include "EurorackConfig.h"
#include <Arduino.h>

#define SERIAL_BAUD 115200

void Eurorack::init() {
    analogReadResolution(12);
    Serial.begin(SERIAL_BAUD);
}
