#include "IS32FL3738Device.h"

#define IS32_I2C_SPEED 3400000

// Global Registers
#define IS32_REG_GLOBAL_PAGE 0xFD
#define IS32_REG_GLOBAL_UNLOCK 0xFE

// Page 3 registers
#define IS32_REG_GLOBAL_CONFIG 0x00
#define IS32_REG_GLOBAL_CURRENT_CONTROL 0x01

// Page 0 Registers
#define IS32_REG_LED_ON_OFF_START 0x00


// IS32_REG_GLOBAL_CONFIG flags
#define IS32_REG_GLOBAL_CONFIG_SSD_RUN 0x01

// IS32_REG_GLOBAL_UNLOCK values
#define IS32_REG_GLOBAL_UNLOCK_PAGE_UNLOCK 0xC5 //Unlock page selection


IS32FL3738Device::IS32FL3738Device(TwoWire& wire, uint8_t sdbPin, uint8_t address) : 
    wire(wire), address(address) {
        this->sdbPin = sdbPin;
}

void IS32FL3738Device::init() {
    wire.begin();
    wire.setClock(IS32_I2C_SPEED);

    selectPage(3);
    writeRegister(IS32_REG_GLOBAL_CONFIG, IS32_REG_GLOBAL_CONFIG_SSD_RUN);
    writeRegister(IS32_REG_GLOBAL_CURRENT_CONTROL, 0xFF);
    setOnOffRegisters();

    pinMode(sdbPin, OUTPUT);
    ::digitalWrite(sdbPin, true);
}

void IS32FL3738Device::digitalWrite(uint8_t pin, bool value) {
    analogWrite(pin, value ? 0xFF : 0x00);
}

void IS32FL3738Device::analogWrite(uint8_t pin, uint16_t value) {
    uint8_t sw = pin/8;
    uint8_t cs = pin%8;
    uint8_t reg = sw*0x20 + cs*0x02;
    selectPage(1);
    writeRegister(reg, value & 0xFF);
}

void IS32FL3738Device::setOnOffRegisters() {
    selectPage(0);
    for(int sw = 0; sw < 6; sw++) {
        for(int cs = 0; cs < 2; cs++) {
            uint8_t reg = sw*4 + cs;
            uint8_t data = 0;
            data |= pins[sw*8+cs*4].isEnabled() ? 0b00000011 : 0x00;
            data |= pins[sw*8+cs*4+1].isEnabled() ? 0b00001100 : 0x00;
            data |= pins[sw*8+cs*4+2].isEnabled() ? 0b00110000 : 0x00;
            data |= pins[sw*8+cs*4+3].isEnabled() ? 0b11000000 : 0x00;
            writeRegister(reg, data);
            writeRegister(reg+0x02, data);
        }
    }
}

void IS32FL3738Device::selectPage(uint8_t page) {
    writeRegister(IS32_REG_GLOBAL_UNLOCK, IS32_REG_GLOBAL_UNLOCK_PAGE_UNLOCK);
    writeRegister(IS32_REG_GLOBAL_PAGE, page);
}

void IS32FL3738Device::writeRegister(uint8_t reg, uint8_t data) {
    wire.beginTransmission(address);
    wire.write(reg);
    wire.write(data);
    wire.endTransmission();
}