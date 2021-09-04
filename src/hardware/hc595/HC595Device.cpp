#include "HC595Device.h"

#define CLOCKINTERVAL 1 //us

HC595Device::HC595Device(const uint8_t clockPin, const uint8_t latchPin, const uint8_t dataPin) {
    this->dataPin = dataPin;
    this->latchPin = latchPin;
    this->clockPin = clockPin;
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, LOW);
    digitalWrite(dataPin, LOW);
    Device::setDeferredOutput(true);
}

void HC595Device::digitalWrite(uint8_t pin, bool value) {
    pins[pin].digitalWrite(value);
    send();
}

void HC595Device::send() {
    digitalWrite(latchPin, LOW);
    digitalWrite(clockPin, LOW);

    for(int8_t i=HC595_PINCOUNT; i>=0; i--) {
        digitalWrite(dataPin, pins[i].getDigitalValue());
        delayMicroseconds(CLOCKINTERVAL);
        digitalWrite(clockPin, HIGH);
        delayMicroseconds(CLOCKINTERVAL);
        digitalWrite(clockPin, LOW);
    }

    digitalWrite(dataPin, LOW);
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, HIGH);
    delayMicroseconds(CLOCKINTERVAL);
    digitalWrite(latchPin, LOW);
}