#ifndef MAX11300Device_h
#define MAX11300Device_h

#include "../device/DevicePin.h"
#include "MAX11300.h"

#define MAX11300_PINCOUNT 20

class MAX11300Device: public MAX11300, public Device, public DigitalOutputDevice, public DigitalInputDevice, public AnalogOutputDevice, public AnalogInputDevice {
    public:
        MAX11300Device(SPIClass* spi, uint8_t convertPin, uint8_t selectPin);
        void setPinType(uint8_t pin, PinType pinType);
        void digitalWrite(uint8_t pin, bool value);
        bool digitalRead(uint8_t pin);
        void analogWrite(uint8_t pin, uint16_t value);
        uint16_t analogRead(uint8_t pin);
        void send();

        AnalogInputOutputPin<MAX11300Device> pins[MAX11300_PINCOUNT] = { 
            AnalogInputOutputPin<MAX11300Device>(*this, 0, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 1, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 2, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 3, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 4, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 5, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 6, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 7, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 8, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 9, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 10, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 11, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 12, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 13, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 14, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 15, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 16, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 17, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 18, 12, -5, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 19, 12, -5, 5)
        };
};

#endif
