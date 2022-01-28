#ifndef Triangle_h
#define Triangle_h

#include "../base/WaveShape.h"
#include "math.h"

class Triangle : public WaveShape {
    public:
        Triangle() {}
        virtual float get(float phase);
};

inline float Triangle::get(float phase) {
    float t = -1 + (2*phase);
    return 2 * (fabsf(t) - 0.5);
}

#endif