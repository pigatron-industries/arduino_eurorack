#ifndef GateInput_h
#define GateInput_h

#include "../../hardware/device/DevicePin.h"
#include "../../hardware/native/NativeDevice.h"
#include "../../util/Debounce.h"

template<class T = NativeDevice>
class GateInput {

    public:
        GateInput(DigitalInputPin<T>& input) : input(input) {
            input.setPinType(PinType::DIGITAL_INPUT_PULLUP);
            debounce.begin(input.digitalRead());
        }

        bool getValue() { return inverted ? !debounce.read() : debounce.read(); }
        bool update() { return debounce.update(input.digitalRead()); }
        bool rose() { return inverted ? debounce.fell() : debounce.rose(); }
        bool fell() { return inverted ? debounce.rose() : debounce.fell(); }
        unsigned long duration() { return debounce.duration(); }
        unsigned long previousDuration() { return debounce.previousDuration(); }

    protected:
        DigitalInputPin<T>& input;
        Debounce debounce;

};

#endif
