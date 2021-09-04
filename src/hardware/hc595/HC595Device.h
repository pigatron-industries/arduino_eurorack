#ifndef HC595Device_h
#define HC595Device_h

#include "../device/DevicePin.h"

#define HC595_PINCOUNT 8

class HC595Device: public Device, public DigitalOutputDevice {
    public:
        HC595Device(const uint8_t clockPin, const uint8_t latchPin, const uint8_t dataPin);
        void digitalWrite(uint8_t pin, bool value);
        void send();

        DigitalOutputPin<HC595Device> pins[HC595_PINCOUNT] = { 
            DigitalOutputPin<HC595Device>(*this, 0),
            DigitalOutputPin<HC595Device>(*this, 1),
            DigitalOutputPin<HC595Device>(*this, 2),
            DigitalOutputPin<HC595Device>(*this, 3),
            DigitalOutputPin<HC595Device>(*this, 4),
            DigitalOutputPin<HC595Device>(*this, 5),
            DigitalOutputPin<HC595Device>(*this, 6),
            DigitalOutputPin<HC595Device>(*this, 7)
        };

    private:
        uint8_t dataPin;
        uint8_t latchPin;
        uint8_t clockPin;
};

#endif
