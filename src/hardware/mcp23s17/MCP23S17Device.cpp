#include "MCP23S17Device.h"

void MCP23S17Device::init() {
    for(int i = 0; i < MCP23S17_PINCOUNT; i++) {
        gpioPinMode(pins[i].getPin(), pins[i].getPinType() == PinType::DIGITAL_OUTPUT);
        if(pins[i].getInterruptEnabled()) {
            
        }
    }
}
