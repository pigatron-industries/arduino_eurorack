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

void Clock::externalTick() {
    switch(state) {
        case INTERNAL:
            state = EXTERNAL_WAITING;
            break;
        case EXTERNAL_WAITING:
            state = EXTERNAL;
        case EXTERNAL:
            externalTime = externalTimeCounter;
            externalWaitTime = externalTime*2;
            externalTicked = true;
    }
    externalTimeCounter = 0;
}
