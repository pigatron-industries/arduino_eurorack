#include "MultiplexGateOutput.h"

#include <Arduino.h>

MultiplexGateOutput::MultiplexGateOutput(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin, uint8_t size) {
    this->dataPin = dataPin;
    this->latchPin = latchPin;
    this->clockPin = clockPin;
    this->size = size;
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, LOW);
    digitalWrite(dataPin, LOW);
    for(uint8_t i=0; i < size; i++) {
        data[i] = LOW;
    }
    sendData();
}

void MultiplexGateOutput::setValue(uint8_t index, bool value) {
    data[index] = value;
}

void MultiplexGateOutput::setTrigger(uint8_t index) {
    setValue(index, HIGH);
    triggerTimer[index].start(TRIGGER_TIME);
}

void MultiplexGateOutput::update() {
    for(uint8_t i=0; i < size; i++) {
        if(triggerTimer[i].hasJustStopped()) {
            setValue(i, LOW);
        }
    }
}

void MultiplexGateOutput::sendData() {
    //start sequence
    digitalWrite(latchPin, LOW);
    digitalWrite(clockPin, LOW);

    for(int8_t i=size-1; i>=0; i--) {
        digitalWrite(dataPin, data[i]);
        delayMicroseconds(CLOCKINTERVAL);
        digitalWrite(clockPin, HIGH);
        delayMicroseconds(CLOCKINTERVAL);
        digitalWrite(clockPin, LOW);
    }

    //set latch
    digitalWrite(dataPin, LOW);
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, HIGH);
    delayMicroseconds(CLOCKINTERVAL);
    digitalWrite(latchPin, LOW);
}
