#ifndef MAX11300Pin_h
#define MAX11300Pin_h

#include "../native/AnalogInputPin.h"
#include "MAX11300.h"

class MAX11300Pin : public AnalogInputPin {
    public:
        MAX11300Pin(MAX11300& max11300, uint8_t pin): 
            AnalogInputPin(pin, 12, -5, 5),
            max11300(max11300) { 
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