#ifndef MCP23S17OutputPin_h
#define MCP23S17OutputPin_h

#include <inttypes.h>
#include <gpio_MCP23S17.h>
#include "../native/DigitalOutputPin.h"

class MCP23S17OutputPin : public DigitalOutputPin {
    public:
        MCP23S17OutputPin(gpio_MCP23S17& mcp23s17, uint8_t pin) :
            DigitalOutputPin(pin), 
            mcp23s17(mcp23s17) { 
        }

        void init() {
            mcp23s17.gpioPinMode(pin, OUTPUT);
        }
        
        void setValue(bool value) {
            mcp23s17.gpioDigitalWriteFast(pin, true);
            //gpio.gpioPortUpdate();
        }

    protected:
        gpio_MCP23S17& mcp23s17;
};

#endif