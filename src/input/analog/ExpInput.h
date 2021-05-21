#ifndef ExpInput_h
#define ExpInput_h

#include <inttypes.h>
#include "AbstractInput.h"

template<class T>
class ExpInput : public AbstractInput<T> {
    public:
        ExpInput(T input) : AbstractInput<T>(input) {
        }

        ExpInput(T input, float midValue) : AbstractInput<T>(input) {
            this->midValue = midValue;
        }

        float getValue() { 
            expValue = midValue*powf(2, AbstractInput<T>::getSmoothedVoltage());
            return expValue;
        }
        
        void setMidValue(float midValue) { this->midValue = midValue; }

    private:
        float midValue = 523.25; //C5
        float expValue;
};

#endif