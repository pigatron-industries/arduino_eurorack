#ifndef PushButton_h
#define PushButton_h

#include "../../hardware/device/DevicePin.h"
#include "../../hardware/native/NativeDevice.h"
#include "../../util/Debounce.h"

template<class T = NativeDevice>
class PushButton {

    public:
        PushButton(DigitalInputPin<T>& input) : input(input) { 
            input.setPinType(PinType::DIGITAL_INPUT_PULLUP);
        }
        bool update() { return debounce.update(input.digitalRead()); }
        bool released() { return debounce.rose(); }
        bool pressed() { return debounce.fell(); }
        bool held() { return !debounce.read(); }
        unsigned long duration() { return debounce.duration(); }
        unsigned long previousDuration() { return debounce.previousDuration(); }

        bool heldFor(int duration) {
            if (!held()) {
                latch = false;
                return false;
            }
            if (held() && debounce.duration() >= duration && !latch) {
                latch = true;
                return true;
            }
            return false;
        }

        void waitForPressAndRelease() {
            while(!held()) { update(); }
            while(held()) { update(); }
        }

    protected:
        DigitalInputPin<T>& input;
        Debounce debounce;
        bool latch = false;

};

#endif
