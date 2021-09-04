#ifndef DevicePin_h
#define DevicePin_h

#include "Device.h"
#include "../../util/RangeScale.h"
#include <inttypes.h>

template<class T>
class DevicePin {
    public:
        DevicePin(T& device, uint8_t pin) : device(device), pin(pin) {}

    protected:
        T& device;
        int pin;
        bool enabled = true;
};


template<class T>
class DigitalOutputPin: public DevicePin<T> {
    public:
        DigitalOutputPin(T& device, uint8_t pin) : DevicePin<T>(device, pin) {}

        void digitalWrite(bool value) {
            digitalValue = value;
            if(!DevicePin<T>::device.isDeferredOutput()) {
                DevicePin<T>::device.digitalWrite(DevicePin<T>::pin, value);
            }
        }

        bool getDigitalValue() {
            return digitalValue;
        }

    protected:
        bool digitalValue;
};


template<class T>
class DigitalInputPin: public DevicePin<T> {
    public:
        DigitalInputPin(T& device, uint8_t pin) : DevicePin<T>(device, pin) {}

        bool digitalRead() {
            return DevicePin<T>::device.digitalRead(DevicePin<T>::pin);
        }

        bool getDigitalValue() {
            return digitalValue;
        }

    protected:
        bool digitalValue;
};


template<class T>
class AnalogOutputPin: public DigitalOutputPin<T> {
    public:
        AnalogOutputPin(T& device, uint8_t pin, uint8_t bits = 12, float lowVoltage = 5, float highVoltage = -5) : 
            DigitalOutputPin<T>(device, pin), 
            voltageScale(0, pow(2, bits)-1, lowVoltage, highVoltage) {
        }

        void analogWrite(float value) {
            // TODO convert float to int
            analogValue = value;
            if(!DevicePin<T>::device.isDeferredOutput()) {
                DevicePin<T>::device.analogWrite(DevicePin<T>::pin, voltageScale.convertReverse(value));
            }
        }

        float getAnalogValue() {
            return analogValue;
        }

        uint16_t getBinaryValue() {
            return voltageScale.convertReverse(analogValue);
        }

    protected:
        PinType pinType;
        float analogValue;
        RangeScale voltageScale;
};


template<class T>
class AnalogInputPin: public DigitalInputPin<T> {
    public:
        AnalogInputPin(T& device, uint8_t pin, uint8_t bits = 12, float lowVoltage = 5, float highVoltage = -5) : 
            DigitalInputPin<T>(device, pin),
            voltageScale(0, pow(2, bits)-1, lowVoltage, highVoltage) {}

        float analogRead() {
            return voltageScale.convert(DevicePin<T>::device.analogRead(DevicePin<T>::pin));
        }

        float getAnalogValue() {
            return analogValue;
        }

    protected:
        PinType pinType;
        bool analogValue;
        RangeScale voltageScale;
};


template<class T>
class DigitalInputOutputPin: public DigitalInputPin<T>, public DigitalOutputPin<T> {
    public:
        DigitalInputOutputPin(T& device, uint8_t pin) : DigitalInputPin<T>(device, pin), DigitalOutputPin<T>(device, pin) {}
};


template<class T>
class AnalogInputOutputPin: public AnalogInputPin<T>, public AnalogOutputPin<T> {
    public:
        AnalogInputOutputPin(T& device, uint8_t pin) : AnalogInputPin<T>(device, pin), AnalogOutputPin<T>(device, pin) {}
};

#endif