#ifndef DigitalInputPin_h
#define DigitalInputPin_h

#include <inttypes.h>
#include <Arduino.h>

class DigitalInputPin {
    public:
        DigitalInputPin(uint8_t pin) { 
            this->pin = pin;
            pinMode(pin, INPUT);
        }
        
        bool getValue() {
            return digitalRead(pin);
        }

    protected:
        uint8_t pin;
};

#endif