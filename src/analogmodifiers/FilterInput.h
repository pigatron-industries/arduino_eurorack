#ifndef FilterInput_h
#define FilterInput_h

#include <inttypes.h>
#include "AbstractInput.h"

template<class T = AnalogPin>
class FilterInput : public AbstractInput<T> {
    public:
        FilterInput(T input) : AbstractInput<T>(input) {
        }

        FilterInput(T input, float zeroFrequency) : AbstractInput<T>(input) {
            this->zeroFrequency = zeroFrequency;
        }

        inline bool update() {
            if(this->readVoltage()) {
                if(this->getVoltage() > 0.5) {
                    frequency = zeroFrequency*powf(2, (this->getVoltage()*2)-6);
                    highPass = true;
                    lowPass = false;
                } else if (this->getVoltage() < -0.5) {
                    frequency = zeroFrequency*powf(2, (this->getVoltage()*2)+7);
                    lowPass = true;
                    highPass = false;
                } else {
                    lowPass = false;
                    highPass = false;
                }
            }
            return this->isChanged();
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