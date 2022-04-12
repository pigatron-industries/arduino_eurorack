#ifndef AnalogInputFilter_h
#define AnalogInputFilter_h

#include "../distortionfunctions/PowerFunction.h"

using namespace eurorack;

class AnalogInputFilter {
    public:
        AnalogInputFilter(float threshold = 1.0, float gradient = 0.75) : smoothnessFunction(gradient) { setThreshold(threshold); }
        void setThreshold(float threshold) { this->threshold = threshold; thresholdRecip = 1.0/threshold; }
        void setGradient(float gradient) { smoothnessFunction.setGradient(gradient); }
        float process(float value);

    private:
        PowerFunction smoothnessFunction;
        float threshold;
        float thresholdRecip;

        float prevValue = 0;
        float filteredValue = 0;
};


inline float AnalogInputFilter::process(float value) {
    float diff = fabsf(value-prevValue);
    if(diff < threshold) {
        float smoothing = smoothnessFunction.get(diff*thresholdRecip);
        filteredValue = (value*smoothing) + filteredValue*(1-smoothing);
    } else {
        filteredValue = value;
    }
    prevValue = value;
    return filteredValue;    
}

#endif