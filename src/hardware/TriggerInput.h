#ifndef TriggerInput_h
#define TriggerInput_h

#include <inttypes.h>

#define MAX_INTERRUPT_TRIGGERS 10

class TriggerInput {

public:
    TriggerInput(uint8_t pin, bool inverted = true, bool useInterrupt = true);
    uint8_t getPin() { return pin; }
    bool getValue() { return value; } 
    bool rose() { return inverted ? didFallInternal() : didRiseInternal(); }
    bool fell() { return inverted ? didRiseInternal() : didFallInternal(); }
    bool update(); // need to call update if pin doesn't use interrupt

private:
    uint8_t pin;
    bool value;
    bool inverted;
    bool useInterrupt;
    bool interruptFired;

    bool didRise;
    bool didFall;

    static TriggerInput* interruptInputs[MAX_INTERRUPT_TRIGGERS];
    static uint8_t interruptInputCount;
    static void interrupt();

    void setValue(bool value) { 
        this->value = value;
        this->didRise = didRise || value;
        this->didFall = didFall || !value;
    }

    bool didRiseInternal() {
        bool returnValue = didRise;
        didRise = false;
        return returnValue;
    }

    bool didFallInternal() {
        bool returnValue = didFall;
        didFall = false;
        return returnValue;
    }
};

#endif
