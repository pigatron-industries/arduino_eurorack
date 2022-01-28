#ifndef WaveSequence_h
#define WaveSequence_h

#include "../base/WaveShape.h"
#include "math.h"

template<int N, class T = WaveShape>
class WaveSequence : public WaveShape {
    public:
        WaveShapeSequence() {}
        virtual float get(float phase);

    protected:
        T segments[N];
};

template<int N, class T>
inline float WaveSequence<N, T>::get(float phase) {
    float segmentStart = 0;
    float segmentEnd = 0;
    for(T& segment : segments) {
        segmentEnd += segment.getLength();
        if(phase < segmentEnd) {
            return segment.get(phase - segmentStart);
        }
        segmentStart = segmentEnd;
    }
    return 0;
}

#endif