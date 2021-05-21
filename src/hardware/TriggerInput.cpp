#include "TriggerInput.h"

#include <Arduino.h>

uint8_t TriggerInput::inputCount = 0;
TriggerInput* TriggerInput::inputs[10];

TriggerInput::TriggerInput(uint8_t pin, bool inverted) {
    this->pin = pin;
    this->inverted = inverted;
    pinMode(pin, INPUT_PULLUP);
    value = digitalRead(pin);
    inputs[inputCount] = this;
    inputCount++;
    attachInterrupt(digitalPinToInterrupt(pin), interrupt, CHANGE);
}

void TriggerInput::interrupt() {
    for(uint8_t i = 0; i < inputCount; i++) {
        TriggerInput* input = inputs[i];
        bool value = digitalRead(input->getPin());
        if(value != input->getValue()) {    
            input->setValue(value);
        }
    }
}
