#include "EurorackConfig.h"
#include <Arduino.h>

void Eurorack::init() {
    analogReadResolution(12);
    Serial.begin(SERIAL_BAUD);
}
