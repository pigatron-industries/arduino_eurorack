#ifndef AbstractInput_h
#define AbstractInput_h

#include <inttypes.h>
#include "Arduino.h"
#include "../../hardware/device/DevicePin.h"
#include "../../hardware/native/NativeDevice.h"
#include "../../util/util.h"
#include "../../util/RangeScale.h"

#define SMOOTHING_WEIGHT 0.03
#define STABILISE_THRESHOLD 0.005

template<class T = NativeDevice>
class AbstractInput {
    public:
        AbstractInput(AnalogInputPin<T>& input) : 
            input(input) {
        }

        bool update() { return readVoltage(); }
        bool isChanged() { return changed; }
        float getVoltage() { return measuredVoltage; }
        uint32_t getRawValue() { return value; }

        float getStableVoltage() {
            return stableVoltage;
        }

    protected:
        AnalogInputPin<T>& input;
        float smoothingWeight = SMOOTHING_WEIGHT;

        uint32_t value;
        float measuredVoltage;
        float smoothedVoltage;
        float stableVoltage;

        bool changed;

        bool readVoltage() {
            measuredVoltage = input.analogRead();
            smoothedVoltage = smooth(measuredVoltage, smoothedVoltage, smoothingWeight);
            float diff = fabsf(smoothedVoltage-stableVoltage);
            if(diff > STABILISE_THRESHOLD) {
                changed = true;
                stableVoltage = smoothedVoltage;
            } else {
                changed = false;
            }
            return changed;
        }
};

#endif