#include "DelayLine.h"


void DelayLine::setDelay(size_t delay) {
    this->delay = delay;
    delayFrac = 0.0f;
    this->delayInt = delay < bufferSize ? delay : bufferSize - 1;
}

void DelayLine::setDelay(float delay) {
    this->delay = delay;
    int32_t int_delay = static_cast<int32_t>(delay);
    delayFrac = delay - static_cast<float>(int_delay);
    delayInt = static_cast<size_t>(int_delay) < bufferSize ? int_delay : bufferSize - 1;
}
