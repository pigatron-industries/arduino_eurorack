#ifndef EnumInput_h
#define EnumInput_h

#include <inttypes.h>
#include "AbstractInput.h"
#include "../../util/RangeScale.h"

template<class T = NativeDevice>
class EnumInput : public LinearInput<T> {
    public:
        EnumInput(AnalogInputPin<T>& input, float _realMin, float _realMax, int maxIntValue) : 
            LinearInput<T>(input, _realMin, _realMax, 0.1, maxIntValue+0.9) {
        }

        inline bool update() {
            bool changed = LinearInput<T>::update();
            if(changed) {
                int prevIntValue = intValue;
                intValue = int(getValue());
                if(prevIntValue != intValue) {
                    return true;
                }
            }
            return false;
        }

        inline int getIntValue() {
            return intValue;
        }

    private:
        int intValue;
};

#endif