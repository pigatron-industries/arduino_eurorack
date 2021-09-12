#ifndef NativeDevice_h
#define NativeDevice_h

#include "../device/DevicePin.h"

#define NATIVE NativeDevice::instance
#define AnalogInput(PIN) AnalogInputPin<> PIN = AnalogInputPin<>(NativeDevice::instance, ::PIN);
#define AnalogOutput(PIN) AnalogOutputPin<> PIN = AnalogOutputPin<>(NativeDevice::instance, ::PIN);
#define DigitalInput(PIN) DigitalInputPin<> D ## PIN = DigitalInputPin<>(NativeDevice::instance, PIN);
#define DigitalOutput(PIN) DigitalOutputPin<> D ## PIN = DigitalOutputPin<>(NativeDevice::instance, PIN);

class NativeDevice: public Device, public DigitalOutputDevice, public DigitalInputDevice, public AnalogOutputDevice, public AnalogInputDevice {
    public:
        static NativeDevice instance;
        NativeDevice();
        void setPinType(uint8_t pin, PinType pinType);
        void digitalWrite(uint8_t pin, bool value);
        bool digitalRead(uint8_t pin);
        void analogWrite(uint8_t pin, uint16_t value);
        uint16_t analogRead(uint8_t pin);
};

#endif
