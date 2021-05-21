#ifndef AnalogGateInput_h
#define AnalogGateInput_h

#include <inttypes.h>
#include "LinearInput.h"

template<class T>
class AnalogGateInput : public LinearInput<T> {
    public:
        AnalogGateInput(T input, float triggerVoltage = 3) : 
            LinearInput<T>(input, -5, 5, -5, 5)  {
                this->triggerVoltage = triggerVoltage;
                smoothingWeight = 1;
        }

        inline bool update() {
            bool prevOpen = open;
            if(LinearInput<T>::update()) {
                open = LinearInput<T>::getValue() > triggerVoltage;
                triggered = !prevOpen && open;
                return true;
            }
            return false;
        }

        inline bool isTriggered() {
            return triggered;
        }

        inline bool isOpen() {
            return open;
        }

    private:
        float triggerVoltage;
        bool triggered;
        bool open;
};

#endif