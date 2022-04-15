#include "Clock.h"
#include <math.h>

#define WAIT_TIME_MIN 0.2

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
        case CLK_INTERNAL:
            state = CLK_EXTERNAL_WAITING;
            break;
        case CLK_EXTERNAL_WAITING:
            state = CLK_EXTERNAL;
        case CLK_EXTERNAL:
            externalTime = externalTimeCounter;
            frequency = 1/externalTime;
            externalWaitTime = fmaxf(externalTime*2, WAIT_TIME_MIN);
            externalTicked = true;
    }
    externalTimeCounter = 0;
}
