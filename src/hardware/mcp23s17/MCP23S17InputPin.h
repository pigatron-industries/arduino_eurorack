#ifndef MCP23S17InputPin_h
#define MCP23S17InputPin_h

#include <inttypes.h>
#include <gpio_MCP23S17.h>
#include "../native/DigitalInputPin.h"

class MCP23S17InputPin : public DigitalInputPin {
    public:
        MCP23S17InputPin(gpio_MCP23S17& mcp23s17, uint8_t pin) :
            DigitalInputPin(pin),
            mcp23s17(mcp23s17) { 
        }

        void init() {
            mcp23s17.gpioPinMode(pin, INPUT);
        }
        
        bool getValue() {
            return mcp23s17.gpioDigitalReadFast(pin);
        }

    protected:
        gpio_MCP23S17& mcp23s17;
};

#endif