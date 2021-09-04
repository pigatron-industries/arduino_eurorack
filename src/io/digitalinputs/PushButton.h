#ifndef PushButton_h
#define PushButton_h

#include "../../hardware/device/DevicePin.h"
#include "../../hardware/native/NativeDevice.h"
#include "../../util/Debounce.h"

template<class T = NativeDevice>
class PushButton {

    public:
        PushButton(DigitalInputPin<T> input) : input(input) {}
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
        DigitalInputPin<T> input;
        Debounce debounce;

};

#endif
