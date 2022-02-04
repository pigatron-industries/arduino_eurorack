#ifndef Sine_h
#define Sine_h

#include "../base/WaveShape.h"
#include "math.h"

namespace eurorack {

    class Sine : public WaveShape {
        public:
            Sine() {}
            virtual float get(float phase);
    };

    inline float Sine::get(float phase) {
        return sinf(phase * M_PI * 2.0f);
    }

}

#endif