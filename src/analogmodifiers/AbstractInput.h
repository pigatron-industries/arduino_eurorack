#ifndef AbstractInput_h
#define AbstractInput_h

#include <inttypes.h>
#include "Arduino.h"
#include "../hardware/AnalogInputPin.h"
#include "../util/util.h"
#include "../util/RangeScale.h"

#define SMOOTHING_FAST 0.0005
#define SMOOTHING_SLOW 0.1

template<class T = AnalogInputPin>
class AbstractInput {
    public:
        AbstractInput(T input) : 
            input(input) {
                smoothingWeight = SMOOTHING_SLOW;
        }

        AbstractInput(T input, float smoothingWeight) : 
            input(input) {
                this->smoothingWeight = smoothingWeight;
        }

        void setSmoothingWeight(float smoothingWeight) {
            this->smoothingWeight = smoothingWeight;
        }

        bool update() { return readVoltage(); }
        bool isChanged() { return changed; }
        float getVoltage() { return targetVoltage; }
        uint32_t getRawValue() { return value; }

        float getSmoothedVoltage() { 
            smoothedVoltage = smooth(targetVoltage, smoothedVoltage, smoothingWeight);
            return smoothedVoltage;
        }

    protected:
        T input;
        float smoothingWeight;

        uint32_t value;
        float targetVoltage;
        float smoothedVoltage;

        bool changed;

        bool readVoltage() {
            float prevVoltage = smoothedVoltage;
            float newVoltage = input.readVoltage();
            float diff = fabsf(newVoltage-prevVoltage);
            if(diff > 0.02) {
                changed = true;
                targetVoltage = newVoltage;
            } else {
                changed = false;
            }
            return changed;
        }
};

#endif