#ifndef SmoothStepFunction_h
#define SmoothStepFunction_h

#include "../waveshapes/WaveSequence.h"
#include "../waveshapes/Line.h"

namespace eurorack {

    //https://www.desmos.com/calculator/a09w9zntai
    class SmoothStepFunction : public WaveShape {
        public:
            SmoothStepFunction(float midGradient = 0, float midPoint = 0.5) { this->midGradient = midGradient; this->midPoint = midPoint; calcCoefficients(); }
            void setMidPoint(float midPoint) { this->midPoint = midPoint; calcCoefficients(); } 
            void setMidGradient(float midGradient) {  this->midGradient = midGradient; calcCoefficients(); }
            void setParams(float midPoint, float midGradient) { this->midPoint = midPoint; this->midGradient = midGradient; calcCoefficients(); }
            virtual float get(float phase);

        private:
            float midPoint = 0.5; // 0 - 1
            float midGradient = 0; // -1 - 1
            float c, d, e;

            void calcCoefficients();
    };

    inline void SmoothStepFunction::calcCoefficients() {
        c = (2.0/(1-midGradient))-1;
        d = 1.0/powf(midPoint, c-1);
        e = 1.0/powf(1-midPoint, c-1);
    }

    inline float SmoothStepFunction::get(float x) {
        if(x < 0) {
            return 0;
        } else if (x > 1) {
            return 1;
        } else if (x < midPoint) {
            return powf(x, c) * d;
        } else {
            return 1 - (powf(1-x, c) * e);
        }
    }

}

#endif