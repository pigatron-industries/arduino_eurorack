#ifndef GateInput_h
#define GateInput_h

#include "../../hardware/native/DigitalInputPin.h"
#include "../../util/Debounce.h"

template<class T = DigitalInputPin>
class GateInput {

    public:
        GateInput(T input) : input(input) {
            debounce.begin(input.getValue());
        }

        bool update() { return debounce.update(input.getValue()); }
        bool rose() { return debounce.fell(); }
        bool fell() { return debounce.rose(); }
        unsigned long duration() { return debounce.duration(); }
        unsigned long previousDuration() { return debounce.previousDuration(); }

    protected:
        T input;
        Debounce debounce;

};

#endif
