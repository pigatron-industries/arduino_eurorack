#ifndef AnalogGateInput_h
#define AnalogGateInput_h

#include "LinearInput.h"

template<class T = AnalogInputPin<NativeDevice>>
class AnalogGateInput : public AbstractAnalogInput<T> {
    public:
        AnalogGateInput(T& input, float triggerVoltage = 2) : 
            AbstractAnalogInput<T>(input)  {
                this->triggerVoltage = triggerVoltage;
                this->smoothingWeight = 1;
        }

        inline bool update() {
            bool prevGate = gate;
            if(AbstractAnalogInput<T>::update()) {
                gate = this->getStableVoltage() > triggerVoltage;
                triggeredOn = !prevGate && gate;
                triggeredOff = prevGate && !gate;
                if(prevGate != gate) {
                    return true;
                }
            }
            return false;
        }

        inline bool isTriggeredOn() {
            return triggeredOn;
        }

        inline bool isTriggeredOff() {
            return triggeredOff;
        }

        inline bool isGateOn() {
            return gate;
        }

    private:
        float triggerVoltage;
        bool gate;
        bool triggeredOn;
        bool triggeredOff;
};

#endif