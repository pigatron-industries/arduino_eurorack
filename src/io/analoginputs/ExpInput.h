#ifndef ExpInput_h
#define ExpInput_h

#include "AbstractInput.h"

template<class T = AnalogInputPin<NativeDevice>>
class ExpInput : public AbstractInput<T> {
    public:
        static constexpr float MID_VALUE_C5 = 523.25;

        ExpInput(T& input) : AbstractInput<T>(input) {
        }

        ExpInput(T& input, float midValue) : AbstractInput<T>(input) {
            this->midValue = midValue;
        }

        float getValue() { 
            expValue = midValue*powf(2, this->getStableVoltage());
            return expValue;
        }
        
        void setMidValue(float midValue) { this->midValue = midValue; }

    private:
        float midValue = MID_VALUE_C5;
        float expValue;
};

#endif