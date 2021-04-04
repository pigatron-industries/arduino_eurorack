#ifndef GateInput_h
#define GateInput_h

#include <inttypes.h>
#include "LinearInput.h"


class GateInput : public LinearInput {
    public:
        GateInput(uint8_t _pin, float triggerVoltage = 3) : 
            LinearInput(_pin, -5, 5, -5, 5)  {
                this->triggerVoltage = triggerVoltage;
                smoothingWeight = 1;
        }

        inline bool update() {
            bool prevOpen = open;
            if(LinearInput::update()) {
                open = getValue() > triggerVoltage;
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