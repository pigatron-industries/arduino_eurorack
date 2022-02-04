#ifndef WaveShape_h
#define WaveShape_h

#include "Function.h"

namespace eurorack {

    // Curve that represents a single cycle of a waveform
    class WaveShape : public Function {
        public:
            WaveShape() {}
            virtual void setLength(float length);
            float getLength() { return length; }
            virtual float polyblep(float phase, float phaseIncrement) { return 0; }
        protected:
            float length = 1;
            float polyblepTransient(float phase, float phaseIncrement);
    };

    inline void WaveShape::setLength(float length) { 
        this->length = length; 
    }

    inline float polyblepTransient(float phase, float phaseIncrement) { 
        if(phase < phaseIncrement) {
            phase /= phaseIncrement;
            return phase + phase - phase * phase - 1.0;
        }
        else if(phase > 1.0f - phaseIncrement) {
            phase = (phase - 1.0) / phaseIncrement;
            return phase * phase + phase + phase + 1.0;
        }
        else {
            return 0.0f;
        }
    }

}

#endif