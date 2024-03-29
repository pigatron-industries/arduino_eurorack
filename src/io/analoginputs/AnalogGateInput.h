#ifndef AnalogGateInput_h
#define AnalogGateInput_h

#include "LinearInput.h"

template<class T = AnalogInputPin<NativeDevice>>
class AnalogGateInput : public AbstractAnalogInput<T> {
    public:
        AnalogGateInput(T& input, float triggerVoltage = 2) : 
            AbstractAnalogInput<T>(input)  {
                this->triggerVoltage = triggerVoltage;
        }

        inline bool update() {
            if(AbstractAnalogInput<T>::update()) {
                gate = this->getStableVoltage() > triggerVoltage;
                if(debounce.update(gate)) {
                    triggeredOn = debounce.rose();
                    triggeredOff = debounce.fell();
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
        Debounce debounce;
};

#endif