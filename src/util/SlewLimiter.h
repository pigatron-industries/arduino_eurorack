#ifndef SlewLimiter_h
#define SlewLimiter_h

#include "util.h"

class SlewLimiter {
    public:
        SlewLimiter(float speed = 0.01) { this->speed = speed; }
        void setTargetValue(float targetValue) { this->targetValue = targetValue; }
        void setSpeed(float speed) { this->speed = speed; }
        float getValue() { return value; }
        float update() {
            value = smooth(targetValue, value, speed);
            return value;
        }

    private:
        float targetValue;
        float speed = 0.01;

        float value;

};

#endif