#ifndef AnalogGateInput_h
#define AnalogGateInput_h

#include "LinearInput.h"

template<class T = NativeDevice>
class AnalogGateInput : public LinearInput<T> {
    public:
        AnalogGateInput(AnalogInputPin<T>& input, float triggerVoltage = 3) : 
            LinearInput<T>(input, -5, 5, -5, 5)  {
                this->triggerVoltage = triggerVoltage;
                this->smoothingWeight = 1;
        }

        inline bool update() {
            bool prevGate = gate;
            if(LinearInput<T>::update()) {
                gate = this->getValue() > triggerVoltage;
                triggeredOn = !prevGate && gate;
                return true;
            }
            return false;
        }

        inline bool isTriggeredOn() {
            return triggeredOn;
        }

        inline bool isGateOn() {
            return gate;
        }

    private:
        float triggerVoltage;
        bool gate;
        bool triggeredOn;
};

#endif