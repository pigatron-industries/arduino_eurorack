#ifndef PushButton_h
#define PushButton_h

#include "../../util/Debounce.h"

template<class T = DigitalInputPin>
class PushButton {

    public:
        PushButton(T input) : input(input) {}
        void init() { debounce.begin(input.getValue()); }
        bool update() { return debounce.update(input.getValue()); }
        bool released() { return debounce.rose(); }
        bool pressed() { return debounce.fell(); }
        bool held() { return !debounce.read(); }
        unsigned long duration() { return debounce.duration(); }
        unsigned long previousDuration() { return debounce.previousDuration(); }

        void waitForPressAndRelease() {
            while(!held()) { update(); }
            while(held()) { update(); }
        }

    protected:
        T input;
        Debounce debounce;

};

#endif
