#ifndef Triangle_h
#define Triangle_h

#include "../base/WaveShape.h"
#include "../../util/mathutil.h"
#include "math.h"

namespace eurorack {

    class Triangle : public WaveShape {
        public:
            Triangle() {}
            virtual float get(float phase);
            virtual float polyblep(float phase, float phaseIncrement);
    };

    inline float Triangle::get(float phase) {
        float t = -1 + (2*phase);
        return 2 * (fabsf(t) - 0.5);
    }

    inline float Triangle::polyblep(float phase, float phaseIncrement) {
        float pb = 0;
        pb += polyblepTransient(phase, phaseIncrement);
        pb -= polyblepTransient(fastmod1f(phase + 0.5f), phaseIncrement);
        return pb;
    }

}

#endif