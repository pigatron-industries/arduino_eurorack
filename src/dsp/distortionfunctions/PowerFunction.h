#ifndef PowerFunction_h
#define PowerFunction_h

#include <math.h>

namespace eurorack {

    // https://www.desmos.com/calculator/g8anfrfrxa
    class PowerFunction {
        public:
            PowerFunction(float gradient = 0.5) { this->gradient = gradient; calcCoefficients(); }
            void setGradient(float gradient) {  this->gradient = gradient; calcCoefficients(); }
            float get(float phase);

        private:
            float gradient; // -1 - 1
            float c;

            void calcCoefficients();
    };


    inline void PowerFunction::calcCoefficients() {
        c = (2.0/(1-gradient))-1;
    }

    inline float PowerFunction::get(float x) {
            if(x < 0) {
                return 0;
            } else if (x > 1) {
                return 1;
            } else {
                return 1 - powf(1-x, c);
            }
    }

}

#endif