#ifndef MCP23S17Device_h
#define MCP23S17Device_h

#include <gpio_MCP23S17.h>
#include "../device/DevicePin.h"

#define MCP23S17_PINCOUNT 16

class MCP23S17Device: public gpio_MCP23S17, public Device, public DigitalOutputDevice, public DigitalInputDevice {
    public:
        MCP23S17Device(const uint8_t csPin,const uint8_t haenAddress);
        void setPinType(uint8_t pin, PinType pinType);
        void digitalWrite(uint8_t pin, bool value);
        bool digitalRead(uint8_t pin);

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

#endif
