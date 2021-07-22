#include "Debouncer.h"

#include <Arduino.h>

Debouncer::Debouncer():
    previousMillis(0),
    intervalMillis(10),
    state(0) {
}

void Debouncer::setInterval(uint16_t intervalMillis) {
    this->intervalMillis = intervalMillis;
}

void Debouncer::begin(bool value) {
	state = 0;
    if (value) {
        setStateFlag(DEBOUNCED_STATE | UNSTABLE_STATE);
    }

    #ifdef BOUNCE_LOCK_OUT
        previousMillis = 0;
    #else
        previousMillis = millis();
    #endif
}

bool Debouncer::update(bool value)
{
    unsetStateFlag(CHANGED_STATE);
    #ifdef BOUNCE_LOCK_OUT
    
        // Ignore everything if we are locked out
        if (millis() - previousMillis >= intervalMillis) {
            if (value != getStateFlag(DEBOUNCED_STATE) ) {
                previousMillis = millis();
                changeState();
            }
        }
    
    #elif defined BOUNCE_WITH_PROMPT_DETECTION

        if (value != getStateFlag(DEBOUNCED_STATE)) {
        // We have seen a change from the current button state.
            if (millis() - previousMillis >= intervalMillis) {
            // We have passed the time threshold, so a new change of state is allowed.
            // set the STATE_CHANGED flag and the new DEBOUNCED_STATE.
            // This will be prompt as long as there has been greater than interval_misllis ms since last change of input.
            // Otherwise debounced state will not change again until bouncing is stable for the timeout period.
                changeState();
            }
        }

        // If the readState is different from previous readState, reset the debounce timer - as input is still unstable
        // and we want to prevent new button state changes until the previous one has remained stable for the timeout.
        if (value != getStateFlag(UNSTABLE_STATE)) {
        // Update Unstable Bit to macth readState
            toggleStateFlag(UNSTABLE_STATE);
            previousMillis = millis();
        }
        
    #else

        // If the reading is different from last reading, reset the debounce counter
        if (value != getStateFlag(UNSTABLE_STATE)) {
            previousMillis = millis();
            toggleStateFlag(UNSTABLE_STATE);
        } else
            if ( millis() - previousMillis >= intervalMillis ) {
                // We have passed the threshold time, so the input is now stable
                // If it is different from last state, set the STATE_CHANGED flag
                if (value != getStateFlag(DEBOUNCED_STATE) ) {
                    previousMillis = millis();
                    changeState();
                }
            }
        
    #endif

    return changed(); 
}

unsigned long Debouncer::previousDuration() const {
	return durationOfPreviousState;
}

unsigned long Debouncer::duration() const {
	return (millis() - stateChangeLastTime);
}

inline void Debouncer::changeState() {
	toggleStateFlag(DEBOUNCED_STATE);
	setStateFlag(CHANGED_STATE) ;
	durationOfPreviousState = millis() - stateChangeLastTime;
	stateChangeLastTime = millis();
}

bool Debouncer::read() const{
    return getStateFlag(DEBOUNCED_STATE);
}

bool Debouncer::rose() const {
    return getStateFlag(DEBOUNCED_STATE) && getStateFlag(CHANGED_STATE);
}

bool Debouncer::fell() const {
    return !getStateFlag(DEBOUNCED_STATE) && getStateFlag(CHANGED_STATE);
}
