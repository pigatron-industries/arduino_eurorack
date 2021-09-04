#include "MCP23S17Device.h"

MCP23S17Device::MCP23S17Device(const uint8_t csPin, const uint8_t haenAdresss) : gpio_MCP23S17(csPin, haenAdresss) {
}

void MCP23S17Device::setPinType(uint8_t pin, PinType pinType) {
    gpioPinMode(pin, pinType == PinType::DIGITAL_OUTPUT);
}

void MCP23S17Device::digitalWrite(uint8_t pin, bool value) {
    gpioDigitalWriteFast(pin, value);
}

bool MCP23S17Device::digitalRead(uint8_t pin) {
    return gpioDigitalRead(pin);
}
