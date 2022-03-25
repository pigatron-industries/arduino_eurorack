#ifndef AnalogInputSumPin_h
#define AnalogInputSumPin_h

#include <inttypes.h>
#include "../../hardware/device/DevicePin.h"

template<class T = NativeDevice>
class AnalogInputSumPin : public AnalogInputPin<T> {
    public:
        AnalogInputSumPin(AnalogInputPin<T>& pin1, AnalogInputPin<T>& pin2) : 
            DevicePin<T>(pin1.getDevice(), -1),
            AnalogInputPin<T>(pin1.getDevice(), -1),
            pin1(pin1), pin2(pin2)
        {}

        float analogRead() {
            return pin1.analogRead() + pin2.analogRead();
        }

    private:
        AnalogInputPin<T>& pin1;
        AnalogInputPin<T>& pin2;

};

#endif