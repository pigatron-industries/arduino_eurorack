#ifndef RotaryEncoderButton_h
#define RotaryEncoderButton_h

#include "RotaryEncoder.h"
#include "../io/digitalinputs/PushButton.h"

class RotaryEncoderButton {

public:

    enum EncoderEvent {
        EVENT_NONE,
        EVENT_CLOCKWISE,
        EVENT_ANTICLOCKWISE,
        EVENT_SHORT_PRESS,
        EVENT_LONG_HOLD,
        EVENT_HELD_CLOCKWISE,
        EVENT_HELD_ANTICLOCKWISE
    };

    RotaryEncoderButton(uint8_t encoderPin1, uint8_t encoderPin2, uint8_t buttonPin) : 
        encoder(encoderPin1, encoderPin2), 
        encoderButtonPin(NativeDevice::instance, buttonPin), 
        encoderButton(encoderButtonPin) {}

    RotaryEncoder& getEncoder() { return encoder; }
    PushButton<>& getEncoderButton() { return encoderButton; }

    EncoderEvent getEncoderEvent();

private:
    RotaryEncoder encoder;
    DigitalInputPin<> encoderButtonPin;
    PushButton<> encoderButton;
    
};

#endif
