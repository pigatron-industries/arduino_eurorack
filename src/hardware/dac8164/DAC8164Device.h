#ifndef DAC8164Device_h
#define DAC8164Device_h

#include <eurorack.h>
#include "DAC8164.h"

#define DAC8164_PINCOUNT 4

#define DAC8164_PINDEF(PIN) AnalogOutputPin<DAC8164Device>(*this, PIN, 14, 5, -5)


class DAC8164Device : public DAC8164, public Device, public DigitalOutputDevice, public AnalogOutputDevice {
    public:
        DAC8164Device(uint8_t enablePin=-1, uint8_t syncPin=-1, uint8_t ldacPin=-1) : 
            DAC8164(enablePin, syncPin, ldacPin) {
        }

        inline void digitalWrite(uint8_t pin, bool value);
        inline void analogWrite(uint8_t pin, uint16_t value);
        inline void send();

        AnalogOutputPin<DAC8164Device> pins[DAC8164_PINCOUNT] = {
            DAC8164_PINDEF(0), DAC8164_PINDEF(1), DAC8164_PINDEF(2), DAC8164_PINDEF(3)
        };
};

void DAC8164Device::digitalWrite(uint8_t pin, bool value) {
    writeChannel(pin, 0x3FFF);
}

void DAC8164Device::analogWrite(uint8_t pin, uint16_t value) {
    writeChannel(pin, value);
}

void DAC8164Device::send() {
    for(int i = 0; i < DAC8164_PINCOUNT; i++) {
        AnalogOutputPin<DAC8164Device>& pin = pins[i];
        if(pin.getPinType() == PinType::ANALOG_OUTPUT) {
            analogWrite(pin.getPin(), pin.getBinaryValue());
        } else if(pin.getPinType() == PinType::DIGITAL_OUTPUT) {
            digitalWrite(pin.getPin(), pin.getDigitalValue());
        }
    }
}

#endif
