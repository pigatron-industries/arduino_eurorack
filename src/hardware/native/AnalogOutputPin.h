#ifndef AnalogOutputPin_h
#define AnalogOutputPin_h

#include <inttypes.h>
#include <Arduino.h>
#include "../../util/RangeScale.h"

class AnalogOutputPin {
    public:
        // Default low and high voltage inverted on purpose due to inverting op-amp
        AnalogOutputPin(uint8_t pin, uint8_t bits = 12, float lowVoltage = 5, float highVoltage = -5) :
                voltageScale(lowVoltage, highVoltage, 0, pow(2, bits)-1) { 
            this->pin = pin;
        }
        void write(int value) { analogWrite(pin, value); }
        void writeVoltage(float voltage) { analogWrite(pin, voltageScale.convert(voltage)); }

    protected:
        uint8_t pin;
        RangeScale voltageScale; 

        float convertToVoltage(int value) {  
            return voltageScale.convert(value);
        }
};

#endif