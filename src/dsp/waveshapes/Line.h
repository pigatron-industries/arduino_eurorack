#ifndef Line_h
#define Line_h

#include "../base/WaveShape.h"
#include "math.h"

namespace eurorack {

    class Line : public WaveShape {
        public:
            Line() { setLength(1); }
            virtual void setLength(float length);
            void setStartValue(float startValue);
            void setEndValue(float endValue);
            void setStartEndValue(float startValue, float endValue);
            virtual float get(float phase);

        protected:
            float startValue;
            float endValue;
            float lengthRecip;

            float gradient;

            void calculateGradient();
    };

    inline void Line::setLength(float length) {
        WaveShape::setLength(length);
        lengthRecip = 1 / length;
        calculateGradient();
    }

    inline void Line::setStartValue(float startValue) {
        this->startValue = startValue;
        calculateGradient();
    }

    inline void Line::setEndValue(float endValue) {
        this->endValue = endValue;
        calculateGradient();
    }

    inline void Line::setStartEndValue(float startValue, float endValue) {
        this->startValue = startValue;
        this->endValue = endValue;
        calculateGradient();
    }

    inline float Line::get(float phase) {
        if(isinf(gradient)) {
            return endValue;
        } else {
            return startValue + phase * gradient;
        }
    }

    inline void Line::calculateGradient() {
        gradient = (endValue - startValue) * lengthRecip;
    }

}

#endif