#ifndef TriggerInput_h
#define TriggerInput_h

#include <inttypes.h>

#define MAX_INTERRUPT_TRIGGERS 10

class TriggerInput {

public:
    TriggerInput(uint8_t pin, bool inverted = true, bool useInterrupt = true);
    uint8_t getPin() { return pin; }
    bool getValue() { return value; } 
    bool didRise() { return inverted ? didFallInternal() : didRiseInternal(); }
    bool didFall() { return inverted ? didRiseInternal() : didFallInternal(); }
    bool update(); // need to call update if pin doesn't use interrupt

private:
    uint8_t pin;
    bool value;
    bool inverted;
    bool useInterrupt;
    bool interruptFired;

    bool rose;
    bool fell;

    static TriggerInput* interruptInputs[MAX_INTERRUPT_TRIGGERS];
    static uint8_t interruptInputCount;
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
