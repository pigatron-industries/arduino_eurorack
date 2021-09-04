#ifndef GateInput_h
#define GateInput_h

#include "../../hardware/device/DevicePin.h"
#include "../../hardware/native/NativeDevice.h"
#include "../../util/Debounce.h"

template<class T = NativeDevice>
class GateInput {

    public:
        GateInput(DigitalInputPin<T> input) : input(input) {
            debounce.begin(input.digitalRead());
        }

        bool update() { return debounce.update(input.digitalRead()); }
        bool rose() { return debounce.fell(); }
        bool fell() { return debounce.rose(); }
        unsigned long duration() { return debounce.duration(); }
        unsigned long previousDuration() { return debounce.previousDuration(); }

    protected:
        DigitalInputPin<T> input;
        Debounce debounce;

};

#endif
