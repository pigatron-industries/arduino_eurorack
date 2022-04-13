#include "NativeDevice.h"

#define SERIAL_BAUD 115200

NativeDevice NativeDevice::instance;

NativeDevice::NativeDevice() {
    setDeferredInit(false);
}

void NativeDevice::init() {
    analogReadResolution(12);
    Serial.begin(SERIAL_BAUD);
    #if defined(TEENSYDUINO)
        for(uint32_t i = 0; i < (sizeof(adc.adc)/sizeof(adc.adc[0])); i++ ) {
            adc.adc[i]->setAveraging(4);
            adc.adc[i]->setSamplingSpeed(ADC_SAMPLING_SPEED::HIGH_SPEED);
            adc.adc[i]->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED);
        }
    #endif
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
    #if defined(TEENSYDUINO)
        return adc.analogRead(pin);
    #else
        return ::analogRead(pin);
    #endif
}
