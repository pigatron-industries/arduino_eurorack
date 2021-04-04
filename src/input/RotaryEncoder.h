#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include <Arduino.h>

// Enable this to emit codes twice per step.
//#define HALF_STEP

// Enable weak pullups
#define ENABLE_PULLUPS

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Anti-clockwise step.
#define DIR_CCW 0x20

class RotaryEncoder {

public:
    RotaryEncoder(uint8_t pin1, uint8_t pin2);

    static void interruptCallback();

    bool update() {
        movement = position;
        position = 0; 
        return movement != 0;
    }

    long getMovement() {
        return movement;
    }

private:
    static RotaryEncoder* encoderPtr;

    long position = 0;
    long movement = 0;

    unsigned char state;
    unsigned char pin1;
    unsigned char pin2;

    unsigned char process();
};

#endif
