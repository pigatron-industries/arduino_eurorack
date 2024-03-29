#ifndef PowInput_h
#define PowInput_h

#include <inttypes.h>
#include "LinearInput.h"

template<class T = AnalogInputPin<NativeDevice>>
class PowInput : public LinearInput<T> {
    public:
        PowInput(T& input, float power, float realMin, float realMax) : LinearInput<T>(input, realMin, realMax, 0, 1) {
            this->power = power;
        }

        float getValue() { 
            powValue = powf(this->getValue(), power);
            return powValue;
        }

    private:
        float power;
        float powValue;
};

#endif