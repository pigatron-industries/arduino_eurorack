#ifndef GateInput_h
#define GateInput_h

#include <Bounce2.h>

class GateInput {

public:
    GateInput(uint8_t pin) {
        debouncer.attach(pin, INPUT);
    }

    bool update() { return debouncer.update(); }
    bool rose() { return debouncer.fell(); }
    bool fell() { return debouncer.rose(); }
    unsigned long duration() { return debouncer.duration(); }
    unsigned long previousDuration() { return debouncer.previousDuration(); }

private:
    Bounce debouncer;

};

#endif
