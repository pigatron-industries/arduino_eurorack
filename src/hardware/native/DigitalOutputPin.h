#ifndef DigitalOutputPin_h
#define DigitalOutputPin_h

#include <inttypes.h>
#include <Arduino.h>

class DigitalOutputPin {
    public:
        DigitalOutputPin(uint8_t pin) { 
            this->pin = pin;
            pinMode(pin, OUTPUT);
        }
        
        void setValue(bool value) {
            digitalWrite(pin, value);
        }

    protected:
        uint8_t pin;
};

#endif