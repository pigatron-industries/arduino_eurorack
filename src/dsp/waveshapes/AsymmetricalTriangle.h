#ifndef AsymmetricalTriangle_h
#define AsymmetricalTriangle_h

#include "WaveSequence.h"
#include "Line.h"

class AsymmetricalTriangle : public WaveSequence<2, Line> {
    public:
        AsymmetricalTriangle();
        void setPeakPosition(float peakPosition);
};

inline AsymmetricalTriangle::AsymmetricalTriangle() {
    segment(0).setStartValue(-1);
    segment(0).setEndValue(1);
    segment(1).setStartValue(1);
    segment(1).setEndValue(-1);
}

inline void AsymmetricalTriangle::setPeakPosition(float peakPosition) {
    segment(0).setLength(peakPosition);
    segment(1).setLength(1.0f-peakPosition);
}


#endif