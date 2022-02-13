#ifndef TwoLineFunction_h
#define TwoLineFunction_h

#include "../waveshapes/WaveSequence.h"
#include "../waveshapes/Line.h"

namespace eurorack {

    class TwoLineFunction : public WaveSequence<2, Line> {
        public:
            TwoLineFunction();
            void setMidPoint(float x, float y);
    };

    inline TwoLineFunction::TwoLineFunction() {
        segment(0).setStartValue(0);
        segment(0).setLength(0.5);
        segment(0).setEndValue(0.5);
        segment(1).setStartValue(0.5);
        segment(1).setLength(0.5);
        segment(1).setEndValue(1);
    }

    inline void TwoLineFunction::setMidPoint(float x, float y) {
        segment(0).setStartValue(0);
        segment(0).setEndValue(x);
        segment(0).setLength(y);
        segment(1).setStartValue(x);
        segment(1).setEndValue(1);
        segment(1).setLength(1.0-y);
    }

}

#endif