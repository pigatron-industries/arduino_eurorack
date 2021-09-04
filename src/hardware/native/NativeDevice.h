#ifndef NativeDevice_h
#define NativeDevice_h

#include "../device/DevicePin.h"

class NativeDevice: public Device, public DigitalOutputDevice, public DigitalInputDevice, public AnalogOutputDevice, public AnalogInputDevice {
    public:
        NativeDevice();
        void setPinType(uint8_t pin, PinType pinType);
        void digitalWrite(uint8_t pin, bool value);
        bool digitalRead(uint8_t pin);
        void analogWrite(uint8_t pin, uint16_t value);
        uint16_t analogRead(uint8_t pin);
};

#endif
