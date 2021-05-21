#ifndef FilterInput_h
#define FilterInput_h

#include <inttypes.h>
#include "AbstractInput.h"

template<class T>
class FilterInput : public AbstractInput<T> {
    public:
        FilterInput(T input) : AbstractInput(input) {
        }

        FilterInput(T input, float zeroFrequency) : AbstractInput(input) {
            this->zeroFrequency = zeroFrequency;
        }

        inline bool update() {
            if(readVoltage()) {
                if(getVoltage() > 0.5) {
                    frequency = zeroFrequency*powf(2, (getVoltage()*2)-6);
                    highPass = true;
                    lowPass = false;
                } else if (getVoltage() < -0.5) {
                    frequency = zeroFrequency*powf(2, (getVoltage()*2)+7);
                    lowPass = true;
                    highPass = false;
                } else {
                    lowPass = false;
                    highPass = false;
                }
            }
            return isChanged();
        }

        inline float getFrequency() {
            return frequency;
        }

        inline void setZeroFrequency(float _zeroFrequency) {
            zeroFrequency = _zeroFrequency;
        }

        inline bool getLowPass() { return lowPass; }
        inline bool getHighPass() { return highPass; }

    private:
        float zeroFrequency = 523.25; //C5
        float frequency;
        bool lowPass;
        bool highPass;
};

#endif