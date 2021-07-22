#ifndef GateInput_h
#define GateInput_h

#include "../../hardware/native/DigitalInputPin.h"
#include "../../util/Debouncer.h"

template<class T = DigitalInputPin>
class GateInput {

    public:
        GateInput(T input) : input(input) {
            debouncer.begin(input.getValue());
        }

        bool update() { return debouncer.update(input.getValue()); }
        bool rose() { return debouncer.fell(); }
        bool fell() { return debouncer.rose(); }
        unsigned long duration() { return debouncer.duration(); }
        unsigned long previousDuration() { return debouncer.previousDuration(); }

    protected:
        T input;
        Debouncer debouncer;

};

#endif
