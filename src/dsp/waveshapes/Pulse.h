#ifndef Pulse_h
#define Pulse_h

#include "../base/WaveShape.h"
#include "math.h"

namespace eurorack {

    class Pulse : public WaveShape {
        public:
            Pulse() {}
            void setWidth(float width) { this->width = width; }
            virtual float get(float phase);
        protected:
            float width = 0.5;
    };

    inline float Pulse::get(float phase) {
        return phase < width ? 1 : -1;
    }

}

#endif