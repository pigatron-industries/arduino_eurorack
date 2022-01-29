#ifndef WaveShape_h
#define WaveShape_h

#include "Function.h"

// Curve that represents a single cycle of a waveform
class WaveShape : public Function {
    public:
        WaveShape() {}
        virtual void setLength(float length);
        float getLength() { return length; }

    protected:
        float length = 1;
};

inline void WaveShape::setLength(float length) { 
    this->length = length; 
}

#endif