#ifndef LinearInput_h
#define LinearInput_h

#include <inttypes.h>
#include "AbstractInput.h"
#include "../../util/RangeScale.h"

template<class T = AnalogInputPin>
class LinearInput : public AbstractInput<T> {
    public:
        LinearInput(T input, float _realMin, float _realMax, float _virtualMin, float _virtualMax) : 
            AbstractInput<T>(input),
            scale(_realMin, _realMax, _virtualMin, _virtualMax) {
        }

        void setRange(float _virtualMin, float _virtualMax) {
            scale.setToRange(_virtualMin, _virtualMax);
        }

        inline float getValue() {
            float voltage = this->getStableVoltage();
            return scale.convert(voltage);
        }

    private:
        float virtualValue;

        RangeScale scale;
};

#endif