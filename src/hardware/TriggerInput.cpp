#include "TriggerInput.h"

#include <Arduino.h>

uint8_t TriggerInput::interruptInputCount = 0;
TriggerInput* TriggerInput::interruptInputs[MAX_INTERRUPT_TRIGGERS];

TriggerInput::TriggerInput(uint8_t pin, bool inverted, bool useInterrupt) {
    this->pin = pin;
    this->inverted = inverted;
    this->useInterrupt = useInterrupt;
    pinMode(pin, INPUT_PULLUP);
    value = digitalRead(pin);
    if(useInterrupt) {
        interruptInputs[interruptInputCount] = this;
        interruptInputCount++;
        attachInterrupt(digitalPinToInterrupt(pin), interrupt, CHANGE);
    }
}

void TriggerInput::interrupt() {
    for(uint8_t i = 0; i < interruptInputCount; i++) {
        TriggerInput* input = interruptInputs[i];
        bool value = digitalRead(input->getPin());
        if(value != input->getValue()) {    
            input->setValue(value);
            input->interruptFired = true;
        }
    }
}

bool TriggerInput::update() {
    bool updatedValue = digitalRead(pin);
    if(updatedValue != value || interruptFired) {
        setValue(updatedValue);
        interruptFired = false;
        return true;
    }
    return false;
}