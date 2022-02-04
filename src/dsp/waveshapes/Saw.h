#ifndef Saw_h
#define Saw_h

#include "../base/WaveShape.h"
#include "math.h"

namespace eurorack {

    class Saw : public WaveShape {
        public:
            Saw() {}
            virtual float get(float phase);
    };

    inline float Saw::get(float phase) {
        return -1 * (((phase * 2)) - 1);
    }

}

#endif