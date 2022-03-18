#ifndef LinearInput_h
#define LinearInput_h

#include <inttypes.h>
#include "AbstractInput.h"
#include "../../util/RangeScale.h"

template<class T = NativeDevice>
class EnumInput : public LinearInput<T> {
    public:
        EnumInput() : 
            LinearInput(AnalogInputPin<T>& input, float _realMin, float _realMax, float _virtualMin, float _virtualMax) {
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