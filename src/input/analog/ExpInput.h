#ifndef ExpInput_h
#define ExpInput_h

#include <inttypes.h>
#include "AbstractInput.h"

template<class T>
class ExpInput : public AbstractInput<T> {
    public:
        ExpInput(T input) : AbstractInput(input) {
        }

        ExpInput(uint8_t _pin, float midValue) : AbstractInput(_pin) {
            this->midValue = midValue;
        }

        float getValue() { 
            expValue = midValue*powf(2, getSmoothedVoltage());
            return expValue;
        }
        
        void setMidValue(float midValue) { this->midValue = midValue; }

    private:
        float midValue = 523.25; //C5
        float expValue;
};

#endif