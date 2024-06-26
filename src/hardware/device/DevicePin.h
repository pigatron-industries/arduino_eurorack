#ifndef DevicePin_h
#define DevicePin_h

#include <inttypes.h>
#include "Device.h"
#include "../../util/RangeScale.h"
#include "../../eeprom/Config.h"

class NativeDevice;

template<class T = NativeDevice>
class DevicePin {
    public:
        DevicePin(T& device, uint8_t pin) : device(device), pin(pin) {}

        void setPinType(PinType pinType) {
            this->enabled = true;
            this->pinType = pinType;
            if(!device.isDeferredInit()) {
                device.setPinType(pin, pinType);
            }
        }

        PinType getPinType() { return pinType; }
        uint8_t getPin() { return pin; };
        void enable(bool enabled) { this->enabled = enabled; }
        bool isEnabled() { return enabled; }
        T& getDevice() { return device; }

    protected:
        T& device;
        uint8_t pin;
        PinType pinType;
        bool enabled = false;
};

class AbstractDigitalPin {
    public:
        bool getDigitalValue() { return digitalValue; }
        void setDigitalValue(bool digitalValue) { this->digitalValue = digitalValue; }

    protected:
        bool digitalValue;
};

class AnalogPinCalibrationData {
    public:
        uint8_t check = 0;
        float min = 0;
        float max = 0;
};

class AbstractAnalogPin {
    public:
        AbstractAnalogPin(uint8_t bits = 12, float lowVoltage = 5, float highVoltage = -5) :
            voltageScale(0, pow(2, bits)-1, lowVoltage, highVoltage),
            calibratedScale(0, pow(2, bits)-1, lowVoltage, highVoltage) {}

        float getAnalogValue() { return analogValue; }
        void setAnalogValue(float analogValue) { this->analogValue = analogValue; }
        uint16_t getBinaryValue() { return calibratedScale.convertReverse(analogValue); }
        void setBinaryRange(uint16_t min, uint16_t max) { calibratedScale.setInputRange(min, max); }
        void setAnalogRange(float min, float max) { calibratedScale.setOutputRange(min, max); }
        RangeScale& getScale() { return voltageScale; }
        RangeScale& getCalibratedScale() { return calibratedScale; }

        void loadCalibration() {
            Config::config.load(calibration);
            if(calibration.data.check == 0) {
                calibratedScale.setOutputRange(calibration.data.min, calibration.data.max);
            }
        }

        void saveCalibration() {
            calibration.data.check = 0;
            calibration.data.min = calibratedScale.getToMin();
            calibration.data.max = calibratedScale.getToMax();
            Config::config.save(calibration);
        }

    protected:
        float analogValue;
        RangeScale voltageScale;
        RangeScale calibratedScale;
        ConfigField<AnalogPinCalibrationData> calibration;
};


class AbstractDigitalOutputPin: virtual public AbstractDigitalPin {
    public:
        virtual void digitalWrite(bool value) = 0;
};


template<class T = NativeDevice>
class DigitalOutputPin: virtual public DevicePin<T>, virtual public AbstractDigitalOutputPin {
    public:
        DigitalOutputPin(T& device, uint8_t pin) : DevicePin<T>(device, pin) {
            DevicePin<T>::setPinType(PinType::DIGITAL_OUTPUT);
        }

        void digitalWrite(bool value) {
            digitalValue = value;
            if(!DevicePin<T>::device.isDeferredOutput()) {
                DevicePin<T>::device.digitalWrite(DevicePin<T>::pin, value);
            }
        }
};


class AbstractDigitalInputPin: virtual public AbstractDigitalPin {
    public:
        virtual bool digitalRead() = 0;
};


template<class T = NativeDevice>
class DigitalInputPin: virtual public DevicePin<T>, virtual public AbstractDigitalInputPin {
    public:
        DigitalInputPin(T& device, uint8_t pin, bool pullup = false) : DevicePin<T>(device, pin) {
            if(pullup) {
                DevicePin<T>::setPinType(PinType::DIGITAL_INPUT_PULLUP);
            } else {
                DevicePin<T>::setPinType(PinType::DIGITAL_INPUT);
            }
        }

        bool digitalRead() {
            if(!DevicePin<T>::device.isDeferredInput()) {
                digitalValue = DevicePin<T>::device.digitalRead(DevicePin<T>::pin);
            }
            return digitalValue;
        }

        void enableInterrupt(bool enabled) { this->interruptEnabled = enabled; }
        bool getInterruptEnabled() { return interruptEnabled; }

    protected:
        bool interruptEnabled;
};


class AbstractAnalogOutputPin: virtual public AbstractAnalogPin {
    public:
        virtual void binaryWrite(uint16_t value) = 0;
        virtual void analogWrite(float value) = 0;
};


template<class T = NativeDevice>
class AnalogOutputPin: public DigitalOutputPin<T>, virtual public AbstractAnalogOutputPin {
    public:
        AnalogOutputPin(T& device, uint8_t pin, uint8_t bits = 12, float lowVoltage = 5, float highVoltage = -5) : 
            DevicePin<T>(device, pin),
            AbstractAnalogPin(bits, lowVoltage, highVoltage),
            DigitalOutputPin<T>(device, pin) {
                DevicePin<T>::setPinType(PinType::ANALOG_OUTPUT);
        }

        void binaryWrite(uint16_t value) {
            analogValue = calibratedScale.convert(value);
            if(!DevicePin<T>::device.isDeferredOutput()) {
                DevicePin<T>::device.analogWrite(DevicePin<T>::pin, value);
            }
        }

        void analogWrite(float value) {
            // TODO convert float to int
            analogValue = value;
            if(!DevicePin<T>::device.isDeferredOutput()) {
                DevicePin<T>::device.analogWrite(DevicePin<T>::pin, calibratedScale.convertReverse(analogValue));
            }
        }
};


class AbstractAnalogInputPin: virtual public AbstractAnalogPin {
    public:
        virtual float analogRead() = 0;
        virtual uint16_t binaryRead() = 0;
};


template<class T = NativeDevice>
class AnalogInputPin: public DigitalInputPin<T>, virtual public AbstractAnalogInputPin {
    public:
        AnalogInputPin(T& device, uint8_t pin, uint8_t bits = 12, float lowVoltage = 5, float highVoltage = -5) : 
            DevicePin<T>(device, pin),
            AbstractAnalogPin(bits, lowVoltage, highVoltage),
            DigitalInputPin<T>(device, pin) {
                DevicePin<T>::setPinType(PinType::ANALOG_INPUT);
        }

        float analogRead() {
            if(!DevicePin<T>::device.isDeferredInput()) {
                uint16_t binaryValue = DevicePin<T>::device.analogRead(DevicePin<T>::pin);
                analogValue = calibratedScale.convert(binaryValue);
            }
            return analogValue;
        }

        uint16_t binaryRead() {
            return DevicePin<T>::device.analogRead(DevicePin<T>::pin);
        }
};


template<class T = NativeDevice>
class DigitalInputOutputPin: public DigitalInputPin<T>, public DigitalOutputPin<T> {
    public:
        DigitalInputOutputPin(T& device, uint8_t pin) : 
            DevicePin<T>(device, pin),
            DigitalInputPin<T>(device, pin), 
            DigitalOutputPin<T>(device, pin) {}
};


template<class T = NativeDevice>
class AnalogInputOutputPin: public AnalogInputPin<T>, public AnalogOutputPin<T> {
    public:
        AnalogInputOutputPin(T& device, uint8_t pin, uint8_t bits = 12, float lowVoltage = 5, float highVoltage = -5) : 
            DevicePin<T>(device, pin),
            AbstractAnalogPin(bits, lowVoltage, highVoltage),
            AnalogInputPin<T>(device, pin, bits, lowVoltage, highVoltage), 
            AnalogOutputPin<T>(device, pin, bits, lowVoltage, highVoltage) {}
};

#endif