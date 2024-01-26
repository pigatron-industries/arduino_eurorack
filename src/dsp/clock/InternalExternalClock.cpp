#include "InternalExternalClock.h"
#include <math.h>

#define WAIT_TIME_MIN 0.2


void InternalExternalClock::setFrequencyMultiplierDivider(MultiplierDivider type, int value) {
    frequencyMultiplierDividerType = type;
    frequencyMultiplierDivider = value;
    clockDivider.setDivisor(value);
}

void InternalExternalClock::externalTick() {
    externalTicked = true;
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
    }
    externalTimeCounter = 0;
}

bool InternalExternalClock::process() {
    bool tick = false;
    switch(state) {
        case CLK_EXTERNAL_WAITING:
            externalTimeCounter += sampleTime;
            tick = externalTicked;
            if(externalTicked) {
                externalTicked = false;
            }
            processInternal();
            break;
        case CLK_INTERNAL:
            tick = processInternal();
            break;
        case CLK_EXTERNAL:
            tick = processExternal();
    }

    if (frequencyMultiplierDividerType == CLK_DIVIDER && tick == true) {
        return clockDivider.tick();
    }

    return tick;
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
        // Switch back to internal after no external tick for time
        if(externalTimeCounter > externalWaitTime) {
            state = CLK_INTERNAL;
        }
        return false;
    }
}