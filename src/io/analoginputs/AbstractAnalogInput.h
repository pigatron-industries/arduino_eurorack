#ifndef AbstractAnalogInput_h
#define AbstractAnalogInput_h

#include <inttypes.h>
#include <Arduino.h>
#include "../../hardware/device/DevicePin.h"
#include "../../hardware/native/NativeDevice.h"
#include "../../util/util.h"
#include "../../util/RangeScale.h"
#include "../../dsp/filter/AnalogInputFilter.h"

#define STABILISE_THRESHOLD 0.00

template<class T = AnalogInputPin<NativeDevice>>
class AbstractAnalogInput {
    public:
        AbstractAnalogInput(T& input) : 
            input(input) {
            input.setPinType(PinType::ANALOG_INPUT);
        }

        bool update() { return readVoltage(); }
        bool isChanged() { return changed; }
        float getVoltage() { return measuredVoltage; }
        uint32_t getRawValue() { return value; }

        float getStableVoltage() {
            return stableVoltage;
        }

    protected:
        T& input;

        uint32_t value;
        float measuredVoltage; // actual voltage as measured
        float smoothedVoltage; // after smoothing (averaging) function
        float stableVoltage;   // after hysteresis function

        AnalogInputFilter inputFilter = AnalogInputFilter();

        bool changed;

        bool readVoltage() {
            measuredVoltage = input.analogRead();
            smoothedVoltage = inputFilter.process(measuredVoltage);

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