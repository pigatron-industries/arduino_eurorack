#ifndef PushButton_h
#define PushButton_h

#include "GateInput.h"

template<class T = DigitalInputPin>
class PushButton {

    public:
        PushButton(T input) : input(input) {
            debouncer.begin(input.getValue());
        }
        bool update() { return debouncer.update(input.getValue()); }
        bool released() { return debouncer.rose(); }
        bool pressed() { return debouncer.fell(); }
        bool held() { return !debouncer.read(); }
        unsigned long duration() { return debouncer.duration(); }
        unsigned long previousDuration() { return debouncer.previousDuration(); }

    protected:
        T input;
        Debouncer debouncer;

};

#endif
