#ifndef MAX11300Pin_h
#define MAX11300Pin_h

#include "../AnalogPin.h"
#include "MAX11300.h"

class MAX11300Pin : public AnalogPin {
    public:
        MAX11300Pin(MAX11300& max11300, uint8_t pin): 
            max11300(max11300), 
            AnalogPin(pin) { 
                this->pin = pin; 
        }

        int read() { return max11300.readAnalogPin(pin); }
        float readVoltage() { return convertToVoltage(read()); }

        void write(int value) { max11300.writeAnalogPin(pin, value); }
        void writeVoltage(float voltage) { max11300.writeAnalogPin(pin, voltageScale.convertReverse(voltage)); }

    protected:
        MAX11300& max11300;
};

#endif