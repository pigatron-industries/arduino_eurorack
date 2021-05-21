#ifndef RangeScale_h
#define RangeScale_h

#include <Arduino.h>

class RangeScale {
    public:
        RangeScale(float fromMin, float fromMax, float toMin, float toMax) {
            this->fromMin = fromMin;
            this->fromMax = fromMax;
            this->toMin = toMin;
            this->toMax = toMax;
            calcFactor();
        }

        float convert(float fromValue) {
            if(fromValue < fromMin) {
                fromValue = fromMin;
            } else if (fromValue > fromMax) {
                fromValue = fromMax;
            }
            return ((fromValue - fromMin) * factor) + toMin;
        }

        float convertReverse(float toValue) {
            if(toValue < toMin) {
                toValue = toMin;
            } else if (toValue > toMax) {
                toValue = toMax;
            }
            return ((toValue - toMin) * reverseFactor) + fromMin;  
        }

        void setToRange(float toMin, float toMax) { 
            this->toMin = toMin; 
            this->toMax = toMax;
            calcFactor();
        }

        float getFromMin() { return fromMin; }
        float getFromMax() { return fromMax; }
        float getToMin() { return toMin; }
        float getToMax() { return toMax; }

    private:
        float fromMin, fromMax, toMin, toMax;
        float fromRange, toRange, factor, reverseFactor;

        void calcFactor() {
            fromRange = fromMax - fromMin;
            toRange = toMax - toMin;
            factor = toRange / fromRange;
            reverseFactor = fromRange / toRange;
        }
};

#endif