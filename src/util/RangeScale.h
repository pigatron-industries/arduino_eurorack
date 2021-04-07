#ifndef RangeScale_h
#define RangeScale_h

class RangeScale {
    public:
        RangeScale(float fromMin, float fromMax, float toMin, float toMax) {
            this->fromMin = fromMin;
            this->fromMax = fromMax;
            this->toMin = toMin;
            this->toMax = toMax;
            calcFactor();
        }

        int convert(float fromValue) {
            if(fromValue < fromMin) {
                fromValue = fromMin;
            } else if (fromValue > fromMax) {
                fromValue = fromMax;
            }
            return ((fromValue - fromMin) * factor) + toMin;
        }

        void setToRange(float toMin, float toMax) { 
            this->toMin = toMin; 
            this->toMax - toMax;
            calcFactor();
        }

        float getFromMin() { return fromMin; }
        float getFromMax() { return fromMax; }
        float getToMin() { return toMin; }
        float getToMax() { return toMax; }

    private:
        float fromMin, fromMax, toMin, toMax;
        float fromRange, toRange, factor;

        void calcFactor() {
            fromRange = fromMax - fromMin;
            toRange = toMax - toMin;
            factor = toRange / fromRange;
        }
};

#endif