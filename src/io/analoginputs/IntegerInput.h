#ifndef IntegerInput_h
#define IntegerInput_h

#include <inttypes.h>
#include <eurorack.h>
#include <math.h>

template<class T = AnalogInputPin<NativeDevice>>
class IntegerInput : public LinearInput<T> {
    public:
        IntegerInput(T& input, float _realMin, float _realMax, int minValue, int maxValue) : 
            LinearInput<T>(input, _realMin, _realMax, float(minValue)-0.49, float(maxValue)+0.49) {
                this->minValue = minValue;
                this->maxValue = maxValue;
        }

        void setRange(int min, int max) {
            LinearInput<T>::setRange(float(min)-0.49, float(max)+0.49);
        }

        inline bool update() {
            bool changed = LinearInput<T>::update();
            if(changed) {
                int prevIntValue = intValue;
                intValue = int(roundf(this->getValue()));
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
        int minValue;
        int maxValue;
        int intValue;
};

#endif