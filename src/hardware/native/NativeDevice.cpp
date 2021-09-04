#include "NativeDevice.h"

NativeDevice::NativeDevice() {
}

void NativeDevice::setPinType(uint8_t pin, PinType pinType) {
    switch(pinType) {
        case PinType::ANALOG_OUTPUT:
            pinMode(pin, OUTPUT);
            break;
        case PinType::ANALOG_INPUT:
            pinMode(pin, INPUT);
            break;
        case PinType::DIGITAL_OUTPUT:
            pinMode(pin, OUTPUT);
            break;
        case PinType::DIGITAL_INPUT:
            pinMode(pin, INPUT);
            break;
        case PinType::DIGITAL_INPUT_PULLUP:
            pinMode(pin, INPUT_PULLUP);
            break;
    }
}

void NativeDevice::digitalWrite(uint8_t pin, bool value) {
    ::digitalWrite(pin, value);
}

bool NativeDevice::digitalRead(uint8_t pin) {
    return ::digitalRead(pin);
}

void NativeDevice::analogWrite(uint8_t pin, uint16_t value) {
    ::analogWrite(pin, value);
}

uint16_t NativeDevice::analogRead(uint8_t pin) {
    return ::analogRead(pin);
}
