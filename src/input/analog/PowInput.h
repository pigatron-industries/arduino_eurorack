#ifndef PowInput_h
#define PowInput_h

#include <inttypes.h>
#include "LinearInput.h"

class PowInput : public LinearInput {
    public:
        PowInput(uint8_t pin, float power, float realMin, float realMax) : LinearInput(pin, realMin, realMax, 0, 1) {
            this->power = power;
        }

        float getValue() { 
            powValue = powf(LinearInput::getValue(), power);
            return powValue;
        }

    private:
        float power;
        float powValue;
};

#endif