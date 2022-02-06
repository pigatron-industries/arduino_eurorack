#ifndef RollOffFunction_h
#define RollOffFunction_h

#include <math.h>

class RollOffFunction {
    public:
        virtual float rolloff(int harmonic) = 0;
};

class SquareRollOffFunction : public RollOffFunction {
    public:
        virtual float rolloff(int harmonic) {
            if(harmonic % 2 == 0) {
                return 0;
            } else {
                return 1.0 / float(harmonic);
            }
        }
};

class TriangleRollOffFunction : public RollOffFunction {
    public:
        virtual float rolloff(int harmonic) {
            if(harmonic % 2 == 0) {
                return 0;
            } else {
                float amp = 1.0 / float(harmonic*harmonic);
                if(harmonic % 4 == 1) {
                    return amp;
                } else {
                    return amp * -1;
                }
            }
        }
};

class RampRollOffFunction : public RollOffFunction {
    public:
        virtual float rolloff(int harmonic) {
            return 1.0 / float(harmonic);
        }
};

class PulseRollOffFunction : public RollOffFunction {
    public:
        virtual float rolloff(int harmonic) {
            return sinf(float(harmonic)) / float(harmonic);
        }
};

#endif