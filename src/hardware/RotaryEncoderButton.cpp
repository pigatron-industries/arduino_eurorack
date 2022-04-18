#include "RotaryEncoderButton.h"

RotaryEncoderButton::EncoderEvent RotaryEncoderButton::getEncoderEvent() {
    encoderButton.update();
    encoder.update();
    long movement = encoder.getMovement();

    if(encoderButton.held()) {
        if(movement > 0) {
            rotatedWhilePressed = true;
            return EncoderEvent::EVENT_HELD_CLOCKWISE;
        }
        if(movement < 0) {
            rotatedWhilePressed = true;
            return EncoderEvent::EVENT_HELD_ANTICLOCKWISE;
        }
        if(!rotatedWhilePressed && encoderButton.duration() >= 3000) {
            return EncoderEvent::EVENT_LONG_HOLD;
        }
    }
    if(movement > 0) {
        return EncoderEvent::EVENT_CLOCKWISE;
    }
    if(movement < 0) {
        return EncoderEvent::EVENT_ANTICLOCKWISE;
    }
    if(encoderButton.released()) {
        rotatedWhilePressed = false;
        if(encoderButton.previousDuration() < 1000) {
            return EncoderEvent::EVENT_SHORT_PRESS;
        }
    }
    if(encoderButton.pressed()) {
        return EncoderEvent::EVENT_PRESSED;
    }
    return EncoderEvent::EVENT_NONE;
}
