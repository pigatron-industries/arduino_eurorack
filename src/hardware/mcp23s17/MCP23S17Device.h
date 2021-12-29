#ifndef MCP23S17Device_h
#define MCP23S17Device_h

#include <gpio_MCP23S17.h>
#include "../device/DevicePin.h"

#define MCP23S17_PINCOUNT 16

class MCP23S17Device: public gpio_MCP23S17, public Device, public DigitalOutputDevice, public DigitalInputDevice {
    public:
        MCP23S17Device(const uint8_t csPin,const uint8_t haenAddress) : gpio_MCP23S17(csPin, haenAddress) {
            begin();
        };
        inline void setPinType(uint8_t pin, PinType pinType);
        inline void digitalWrite(uint8_t pin, bool value);
        inline bool digitalRead(uint8_t pin);

        DigitalInputOutputPin<MCP23S17Device> pins[MCP23S17_PINCOUNT] = { 
            DigitalInputOutputPin<MCP23S17Device>(*this, 0),
            DigitalInputOutputPin<MCP23S17Device>(*this, 1),
            DigitalInputOutputPin<MCP23S17Device>(*this, 2),
            DigitalInputOutputPin<MCP23S17Device>(*this, 3),
            DigitalInputOutputPin<MCP23S17Device>(*this, 4),
            DigitalInputOutputPin<MCP23S17Device>(*this, 5),
            DigitalInputOutputPin<MCP23S17Device>(*this, 6),
            DigitalInputOutputPin<MCP23S17Device>(*this, 7),
            DigitalInputOutputPin<MCP23S17Device>(*this, 8),
            DigitalInputOutputPin<MCP23S17Device>(*this, 9),
            DigitalInputOutputPin<MCP23S17Device>(*this, 10),
            DigitalInputOutputPin<MCP23S17Device>(*this, 11),
            DigitalInputOutputPin<MCP23S17Device>(*this, 12),
            DigitalInputOutputPin<MCP23S17Device>(*this, 13),
            DigitalInputOutputPin<MCP23S17Device>(*this, 14),
            DigitalInputOutputPin<MCP23S17Device>(*this, 15)
        };
};

void MCP23S17Device::setPinType(uint8_t pin, PinType pinType) {
    gpioPinMode(pin, pinType == PinType::DIGITAL_OUTPUT);
}

void MCP23S17Device::digitalWrite(uint8_t pin, bool value) {
    gpioDigitalWriteFast(pin, value);
}

bool MCP23S17Device::digitalRead(uint8_t pin) {
    return gpioDigitalRead(pin);
}

#endif
