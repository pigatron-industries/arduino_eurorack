#ifndef Line_h
#define Line_h

#include "../base/WaveShape.h"
#include "math.h"

class Line : public WaveShape {
    public:
        Line() {}
        void setStartValue(float startValue);
        void setEndValue(float endValue);
        virtual float get(float phase);

    protected:
        float startValue;
        float endValue;

        float gradient;

        void calculateGradient();
};

inline void Line::setStartValue(float startValue) {
    this->startValue = startValue;
    calculateGradient();
}

inline void Line::setEndValue(float endValue) {
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
    gradient = (endValue - startValue) / length;
}

#endif