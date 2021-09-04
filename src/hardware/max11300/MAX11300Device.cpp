#include "MAX11300Device.h"

MAX11300Device::MAX11300Device(SPIClass* spi, uint8_t convertPin, uint8_t selectPin) : 
    MAX11300(spi, convertPin, selectPin) {
}

void MAX11300Device::setPinType(uint8_t pin, PinType pinType) {
    switch(pinType) {
        case PinType::ANALOG_OUTPUT:
            setPinModeAnalogOut(pin, DACNegative5to5);
            break;
        case PinType::ANALOG_INPUT:
            setPinModeAnalogIn(pin, ADCNegative5to5);
            break;
        case PinType::DIGITAL_OUTPUT:
            break;
        case PinType::DIGITAL_INPUT:
            break;
    }
}

void MAX11300Device::digitalWrite(uint8_t pin, bool value) {
    writeDigitalPin(pin, value);
}

bool MAX11300Device::digitalRead(uint8_t pin) {
    return readDigitalPin(pin);
}

void MAX11300Device::analogWrite(uint8_t pin, uint16_t value) {
    writeAnalogPin(pin, value);
}

uint16_t MAX11300Device::analogRead(uint8_t pin) {
    return readAnalogPin(pin);
}

void MAX11300Device::send() {
    for(int i = 0; i < MAX11300_PINCOUNT; i++) {
        //TODO
        // if(digitalValues[i].enabled) {
        //     writeDigitalPin(i, digitalValues[i].value);
        // }
    }
}