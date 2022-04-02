#ifndef ExpInput_h
#define ExpInput_h

#include "AbstractAnalogInput.h"

template<class T = AnalogInputPin<NativeDevice>>
class ExpInput : public AbstractAnalogInput<T> {
    public:
        static constexpr float MID_VALUE_C5 = 523.25;

        ExpInput(T& input) : AbstractAnalogInput<T>(input) {
        }

        ExpInput(T& input, float midValue) : AbstractAnalogInput<T>(input) {
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