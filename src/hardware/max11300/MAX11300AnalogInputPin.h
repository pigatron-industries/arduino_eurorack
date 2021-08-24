#ifndef MAX11300Pin_h
#define MAX11300Pin_h

#include "../native/AnalogInputPin.h"
#include "MAX11300.h"

class MAX11300AnalogInputPin : public AnalogInputPin {
    public:
        MAX11300AnalogInputPin(MAX11300& max11300, uint8_t pin): 
            AnalogInputPin(pin, 12, -5, 5),
            max11300(max11300) { 
                this->pin = pin; 
        }

        void init() {
            max11300.setPinModeAnalogIn(pin, ADCNegative5to5);
        }

        int read() { return max11300.readAnalogPin(pin); }
        float readVoltage() { return convertToVoltage(read()); }

    protected:
        MAX11300& max11300;
};

#endif