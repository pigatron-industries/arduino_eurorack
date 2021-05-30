#ifndef AnalogPin_h
#define AnalogPin_h

#include <inttypes.h>
#include <Arduino.h>
#include "../util/RangeScale.h"

class AnalogPin {
    public:
        // Default low and high voltage inverted on purpose due to inverting op-amp
        AnalogPin(uint8_t pin, uint8_t bits = 12, float lowVoltage = 5, float highVoltage = -5) :
                voltageScale(0, pow(2, bits)-1, lowVoltage, highVoltage) { 
            this->pin = pin;
        }
        int read() { return analogRead(pin); }
        float readVoltage() { return convertToVoltage(read()); }

    protected:
        uint8_t pin;
        RangeScale voltageScale; 

        float convertToVoltage(int value) {  
            return voltageScale.convert(value);
        }
};

#endif