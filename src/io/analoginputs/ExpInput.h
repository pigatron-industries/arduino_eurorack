#ifndef ExpInput_h
#define ExpInput_h

#include "AbstractInput.h"

template<class T = NativeDevice>
class ExpInput : public AbstractInput<T> {
    public:
        ExpInput(AnalogInputPin<T>& input) : AbstractInput<T>(input) {
        }

        ExpInput(AnalogInputPin<T>& input, float midValue) : AbstractInput<T>(input) {
            this->midValue = midValue;
        }

        float getValue() { 
            expValue = midValue*powf(2, this->getStableVoltage());
            return expValue;
        }
        
        void setMidValue(float midValue) { this->midValue = midValue; }

    private:
        float midValue = 523.25; //C5
        float expValue;
};

#endif