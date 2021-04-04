#ifndef PushButton_h
#define PushButton_h

#include <Bounce2.h>

class PushButton {

public:
    PushButton(uint8_t pin) {
        debouncer.attach(pin, INPUT_PULLUP);
        digitalWrite(pin, HIGH);
    }

    bool update() { return debouncer.update(); }
    bool released() { return debouncer.rose(); }
    bool pressed() { return debouncer.fell(); }
    bool held() { return !debouncer.read(); }
    unsigned long duration() { return debouncer.duration(); }
    unsigned long previousDuration() { return debouncer.previousDuration(); }

private:
    Bounce debouncer;

};

#endif
