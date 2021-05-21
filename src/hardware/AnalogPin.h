#ifndef AnalogPin_h
#define AnalogPin_h

#include <inttypes.h>
#include <Arduino.h>
#include "../util/RangeScale.h"

class AnalogPin {
    public:
        AnalogPin(uint8_t pin) { this->pin = pin; }
        int read() { return analogRead(pin); }
        float readVoltage() { return convertToVoltage(read()); }

    protected:
        uint8_t pin;
        RangeScale voltageScale = RangeScale(0, 4095, 5, -5); 

        float convertToVoltage(int value) {  
            return voltageScale.convert(value);
        }
};

#endif