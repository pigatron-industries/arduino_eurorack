#include "Clock.h"

void Clock::init(float sampleRate) {
    this->sampleRate = sampleRate;
    sampleTime = 1/sampleRate;
}

void Clock::setFrequency(float frequency) {
    this->frequency = frequency;
    phaseInc = frequency * sampleTime;
}

void Clock::reset() {
    phase = 0;
}

inline bool Clock::process() {
    phase += phaseInc;
    if(phase > phaseMax) {
        phase -= phaseMax;
        return true;
    } else if (phase < 0.0f) {
        phase += phaseMax;
        return true;
    }
    return false;
}
