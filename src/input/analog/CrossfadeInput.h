#ifndef CrossfadeInput_h
#define CrossfadeInput_h

#include <inttypes.h>
#include "LinearInput.h"

template<class T>
class CrossfadeInput : public LinearInput<T> {
    public:
        CrossfadeInput(T input, float _realMin, float _realMax) : 
            LinearInput<T>(input, _realMin, _realMax, 0, 1) {
        }

        inline bool update() {
            if(this->update()) {
                dryLevel = (sinf(this->getValue()*M_PI - M_PI*0.5) + 1)*0.5;
                wetLevel = (sinf((1-this->getValue())*M_PI - M_PI*0.5) + 1)*0.5;
            }
            return this->isChanged();
        }

        inline float getDryLevel() { return dryLevel; }
        inline float getWetLevel() { return wetLevel; }

    private:
        float dryLevel;
        float wetLevel;

};

#endif