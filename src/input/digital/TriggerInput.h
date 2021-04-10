#ifndef TriggerInput_h
#define TriggerInput_h

#include <inttypes.h>

class TriggerInput {

public:
    TriggerInput(uint8_t pin, bool inverted = true);
    uint8_t getPin() { return pin; }
    bool getValue() { return value; } 
    bool didRise() { return inverted ? didFallInternal() : didRiseInternal(); }
    bool didFall() { return inverted ? didRiseInternal() : didFallInternal(); }

private:
    uint8_t pin;
    bool value;
    bool inverted;

    bool rose;
    bool fell;

    static TriggerInput* inputs[10];
    static uint8_t inputCount;
    static void interrupt();

    void setValue(bool value) { 
        this->value = value;
        this->rose = rose || value;
        this->fell = fell || !value;
    }

    bool didRiseInternal() {
        bool returnValue = rose;
        rose = false;
        return returnValue;
    }

    bool didFallInternal() {
        bool returnValue = fell;
        fell = false;
        return returnValue;
    }
};

#endif
