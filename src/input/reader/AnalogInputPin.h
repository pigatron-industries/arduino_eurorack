#ifndef AnalogInputPin_h
#define AnalogInputPin_h

#include <inttypes.h>
#include <Arduino.h>

class AnalogInputPin {
    public:
        AnalogInputPin(uint8_t pin) { this->pin = pin; }

    protected:
        uint8_t pin;
};

#endif