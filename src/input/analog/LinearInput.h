#ifndef LinearInput_h
#define LinearInput_h

#include <inttypes.h>
#include "AbstractInput.h"
#include "../../util/RangeScale.h"

class LinearInput : public AbstractInput {
    public:
        LinearInput(uint8_t _pin, float _realMin, float _realMax, float _virtualMin, float _virtualMax) : 
            AbstractInput(_pin),
            scale(_realMin, _realMax, _virtualMin, _virtualMax) {
        }

        void setRange(float _virtualMin, float _virtualMax) {
            scale.setToRange(_virtualMin, _virtualMax);
        }

        inline float getValue() {
            float voltage = getSmoothedVoltage();
            return scale.convert(voltage);
        }

    private:
        float virtualValue;

        RangeScale scale;
};

#endif