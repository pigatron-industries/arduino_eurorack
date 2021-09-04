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
            AnalogInputOutputPin<MAX11300Device>(*this, 0),
            AnalogInputOutputPin<MAX11300Device>(*this, 1),
            AnalogInputOutputPin<MAX11300Device>(*this, 2),
            AnalogInputOutputPin<MAX11300Device>(*this, 3),
            AnalogInputOutputPin<MAX11300Device>(*this, 4),
            AnalogInputOutputPin<MAX11300Device>(*this, 5),
            AnalogInputOutputPin<MAX11300Device>(*this, 6),
            AnalogInputOutputPin<MAX11300Device>(*this, 7),
            AnalogInputOutputPin<MAX11300Device>(*this, 8),
            AnalogInputOutputPin<MAX11300Device>(*this, 9),
            AnalogInputOutputPin<MAX11300Device>(*this, 10),
            AnalogInputOutputPin<MAX11300Device>(*this, 11),
            AnalogInputOutputPin<MAX11300Device>(*this, 12),
            AnalogInputOutputPin<MAX11300Device>(*this, 13),
            AnalogInputOutputPin<MAX11300Device>(*this, 14),
            AnalogInputOutputPin<MAX11300Device>(*this, 15),
            AnalogInputOutputPin<MAX11300Device>(*this, 16),
            AnalogInputOutputPin<MAX11300Device>(*this, 17),
            AnalogInputOutputPin<MAX11300Device>(*this, 18),
            AnalogInputOutputPin<MAX11300Device>(*this, 19)
        };
};

#endif
