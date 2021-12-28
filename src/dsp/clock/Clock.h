#ifndef Clock_h
#define Clock_h

#include "Clock.h"

class Clock {
    public:
        void init(float sampleRate) {
            this->sampleRate = sampleRate;
            sampleRateRecip = 1/sampleRate;
        }

        void setFrequency(float frequency) {
            this->frequency = frequency;
            phaseInc = frequency * sampleRateRecip;
        }

        void reset() {
            phase = 0;
        }

        bool process() {
            phase += phaseInc;
            if(phase > 1.0f) {
                phase -= 1.0f;
                return true;
            } else if (phase < 0.0f) {
                phase += 1.0f;
                return true;
            }
            return false;
        }

    private:
        float sampleRate, sampleRateRecip;
        float frequency;
        float phaseInc;
        float phase = 0;
        
};

#endif
