#ifndef Device_h
#define Device_h

#include <inttypes.h>

enum PinType {
    ANALOG_OUTPUT, 
    ANALOG_INPUT,
    DIGITAL_OUTPUT,
    DIGITAL_INPUT,
    DIGITAL_INPUT_PULLUP
};

class Device {
    public:
        bool isDeferredOutput() { return deferredOutput; }
        void setDeferredOutput(bool deferredOutput) { this->deferredOutput = deferredOutput; }
        bool isDeferredInput() { return deferredInput; }
        void setDeferredInput(bool deferredInput) { this->deferredInput = deferredInput; }
    protected:
        bool deferredOutput = false;
        bool deferredInput = false;
};

class DigitalOutputDevice {
    public:
        virtual void digitalWrite(uint8_t pin, bool value) = 0;
};

class DigitalInputDevice {
    public:
        virtual bool digitalRead(uint8_t pin) = 0;
};

class AnalogOutputDevice {
    public:
        virtual void analogWrite(uint8_t pin, uint16_t value) = 0;
};

class AnalogInputDevice {
    public:
        virtual uint16_t analogRead(uint8_t pin) = 0;
};

#endif