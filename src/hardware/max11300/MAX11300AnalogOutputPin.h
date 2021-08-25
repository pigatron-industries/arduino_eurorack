#ifndef MAX11300AnalogOutputPin_h
#define MAX11300AnalogOutputPin_h

#include "../native/AnalogOutputPin.h"
#include "MAX11300.h"

class MAX11300AnalogOutputPin : public AnalogOutputPin {
    public:
        MAX11300AnalogOutputPin(MAX11300& max11300, uint8_t pin): 
            AnalogOutputPin(pin, 12, -5, 5),
            max11300(max11300) { 
                this->pin = pin; 
        }

        void init() {
            max11300.setPinModeAnalogOut(pin, DACNegative5to5);
        }

        void write(int value) { max11300.writeAnalogPin(pin, value); }
        void writeVoltage(float voltage) { max11300.writeAnalogPin(pin, voltageScale.convertReverse(voltage)); }

    protected:
        MAX11300& max11300;
};

#endif