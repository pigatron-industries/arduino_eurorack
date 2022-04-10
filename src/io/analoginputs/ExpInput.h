#ifndef ExpInput_h
#define ExpInput_h

#include "AbstractAnalogInput.h"

template<class T = AnalogInputPin<NativeDevice>>
class ExpInput : public AbstractAnalogInput<T> {
    public:
        static constexpr float MID_VALUE_C5 = 523.25;

        ExpInput(T& input, float midValue = MID_VALUE_C5, float base = 2) : AbstractAnalogInput<T>(input), base(base) {
            this->midValue = midValue;
        }

        float getValue() { 
            expValue = midValue*powf(base, this->getStableVoltage());
            return expValue;
        }
        
        void setMidValue(float midValue) { this->midValue = midValue; }

    private:
        const float base;
        float midValue;
        float expValue;
};

#endif