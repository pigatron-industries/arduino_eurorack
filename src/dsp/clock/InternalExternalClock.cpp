#include "InternalExternalClock.h"
#include <math.h>

#define WAIT_TIME_MIN 0.2


void InternalExternalClock::setFrequencyMultiplierDivider(MultiplierDivider type, int value) {
    frequencyMultiplierDividerType = type;
    frequencyMultiplierDivider = value;
}

void InternalExternalClock::externalTick() {
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

bool InternalExternalClock::process() {
    switch(state) {
        case CLK_EXTERNAL_WAITING:
            externalTimeCounter += sampleTime;
        case CLK_INTERNAL:
            return processInternal();
        case CLK_EXTERNAL:
            return processExternal();
    }
    return false;
}

bool InternalExternalClock::processInternal() {
    return Clock::process();
}

bool InternalExternalClock::processExternal() {
    bool internalTick = Clock::process();
    externalTimeCounter += sampleTime;
    if(externalTicked) {
        externalTicked = false;
        return true;
    } else {
        if(externalTimeCounter > externalWaitTime) {
            state = CLK_INTERNAL;
        }
        return false;
    }
}