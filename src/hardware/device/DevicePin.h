#ifndef DevicePin_h
#define DevicePin_h

#include "Device.h"
#include "../../util/RangeScale.h"
#include <inttypes.h>


template<class T>
class DevicePin {
    public:
        DevicePin(T& device, uint8_t pin) : device(device), pin(pin) {}

        void setPinType(PinType pinType) {
            this->pinType = pinType;
            DevicePin<T>::device.setPinType(DevicePin<T>::pin, pinType);
        }

    protected:
        T& device;
        int pin;
        PinType pinType;
        bool enabled = true;
};


template<class T>
class DigitalOutputPin: virtual public DevicePin<T> {
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
class DigitalInputPin: virtual public DevicePin<T> {
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


class AbstractAnalogPin {
    public:
        AbstractAnalogPin(uint8_t bits = 12, float lowVoltage = 5, float highVoltage = -5) :
            voltageScale(0, pow(2, bits)-1, lowVoltage, highVoltage) {}

        float getAnalogValue() {
            return analogValue;
        }

        uint16_t getBinaryValue() {
            return voltageScale.convertReverse(analogValue);
        }

        void setInputRange(uint16_t min, uint16_t max) {
            
        }

    protected:
        float analogValue;
        RangeScale voltageScale;
};


template<class T>
class AnalogOutputPin: public DigitalOutputPin<T>, virtual public AbstractAnalogPin {
    public:
        AnalogOutputPin(T& device, uint8_t pin, uint8_t bits = 12, float lowVoltage = 5, float highVoltage = -5) : 
            DevicePin<T>(device, pin),
            AbstractAnalogPin(bits, lowVoltage, highVoltage),
            DigitalOutputPin<T>(device, pin) {}

        void analogWrite(float value) {
            // TODO convert float to int
            analogValue = value;
            if(!DevicePin<T>::device.isDeferredOutput()) {
                DevicePin<T>::device.analogWrite(DevicePin<T>::pin, voltageScale.convertReverse(analogValue));
            }
        }
};


template<class T>
class AnalogInputPin: public DigitalInputPin<T>, virtual public AbstractAnalogPin {
    public:
        AnalogInputPin(T& device, uint8_t pin, uint8_t bits = 12, float lowVoltage = 5, float highVoltage = -5) : 
            DevicePin<T>(device, pin),
            AbstractAnalogPin(bits, lowVoltage, highVoltage),
            DigitalInputPin<T>(device, pin) {}

        float analogRead() {
            return voltageScale.convert(DevicePin<T>::device.analogRead(DevicePin<T>::pin));
        }

        uint16_t binaryRead() {
            return DevicePin<T>::device.analogRead(DevicePin<T>::pin);
        }
};


template<class T>
class DigitalInputOutputPin: public DigitalInputPin<T>, public DigitalOutputPin<T> {
    public:
        DigitalInputOutputPin(T& device, uint8_t pin) : 
            DevicePin<T>(device, pin),
            DigitalInputPin<T>(device, pin), 
            DigitalOutputPin<T>(device, pin) {}
};


template<class T>
class AnalogInputOutputPin: public AnalogInputPin<T>, public AnalogOutputPin<T> {
    public:
        AnalogInputOutputPin(T& device, uint8_t pin, uint8_t bits = 12, float lowVoltage = 5, float highVoltage = -5) : 
            DevicePin<T>(device, pin),
            AbstractAnalogPin(bits, lowVoltage, highVoltage),
            AnalogInputPin<T>(device, pin, bits, lowVoltage, highVoltage), 
            AnalogOutputPin<T>(device, pin, bits, lowVoltage, highVoltage) {}
};

#endif