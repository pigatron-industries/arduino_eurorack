#ifndef RangeScale_h
#define RangeScale_h

class RangeScale {
    public:
        RangeScale(int fromMin, int fromMax, int toMin, int toMax) {
            this->fromMin = fromMin;
            this->fromMax = fromMax;
            this->toMin = toMin;
            this->toMax = toMax;
            fromRange = fromMax - fromMin;
            toRange = toMax - toMin;
            factor = toRange / fromRange;
        }

        int convert(int fromValue) {
            return ((fromValue - fromMin) * factor) + toMin;
        }

    private:
        int fromMin, fromMax, toMin, toMax;
        int fromRange, toRange, factor;

};

#endif