#ifndef NativeDevice_h
#define NativeDevice_h

#include "../device/DevicePin.h"

#define NATIVE NativeDevice::instance
#define GET_MACRO(_1, _2, NAME,...) NAME
#define GET_MACRO3(_1, _2, _3, NAME,...) NAME

#define AnalogInput1(PIN) AnalogInputPin<> PIN = AnalogInputPin<>(NativeDevice::instance, ::PIN);
#define AnalogInput2(NAME, PIN) AnalogInputPin<> NAME = AnalogInputPin<>(NativeDevice::instance, ::PIN);
#define AnalogInput(...) GET_MACRO(__VA_ARGS__, AnalogInput2, AnalogInput1)(__VA_ARGS__)

#define AnalogOutput1(PIN) AnalogOutputPin<> PIN = AnalogOutputPin<>(NativeDevice::instance, ::PIN);
#define AnalogOutput2(NAME, PIN) AnalogOutputPin<> NAME = AnalogOutputPin<>(NativeDevice::instance, ::PIN);
#define AnalogOutput(...) GET_MACRO(__VA_ARGS__, AnalogOutput2, AnalogOutput1)(__VA_ARGS__)

#define DigitalInput1(PIN) DigitalInputPin<> D ## PIN = DigitalInputPin<>(NativeDevice::instance, PIN);
#define DigitalInput2(NAME, PIN) DigitalInputPin<> NAME = DigitalInputPin<>(NativeDevice::instance, PIN);
#define DigitalInput3(NAME, PIN, INVERT) DigitalInputPin<> NAME = DigitalInputPin<>(NativeDevice::instance, PIN, INVERT);
#define DigitalInput(...) GET_MACRO3(__VA_ARGS__, DigitalInput3, DigitalInput2, DigitalInput1)(__VA_ARGS__)

#define DigitalOutput1(PIN) DigitalOutputPin<> D ## PIN = DigitalOutputPin<>(NativeDevice::instance, PIN);
#define DigitalOutput2(NAME, PIN) DigitalOutputPin<> NAME = DigitalOutputPin<>(NativeDevice::instance, PIN);
#define DigitalOutput(...) GET_MACRO(__VA_ARGS__, DigitalOutput2, DigitalOutput1)(__VA_ARGS__)

class NativeDevice: public Device, public DigitalOutputDevice, public DigitalInputDevice, public AnalogOutputDevice, public AnalogInputDevice {
    public:
        static NativeDevice instance;
        NativeDevice();
        void init();
        void setPinType(uint8_t pin, PinType pinType);
        void digitalWrite(uint8_t pin, bool value);
        bool digitalRead(uint8_t pin);
        void analogWrite(uint8_t pin, uint16_t value);
        uint16_t analogRead(uint8_t pin);
};

#endif
