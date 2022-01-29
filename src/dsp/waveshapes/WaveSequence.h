#ifndef WaveSequence_h
#define WaveSequence_h

#include "../base/WaveShape.h"
#include "math.h"

template<int N, class T = WaveShape>
class WaveSequence : public WaveShape {
    public:
        WaveSequence();
        T& segment(int i);
        void setSegmentLength(int i, float length);
        virtual float get(float phase);

    protected:
        T segments[N];

        void calculateTotalLength();
};

template<int N, class T>
WaveSequence<N, T>::WaveSequence() {
    for(int i = 0; i< N; i++) {
        segment(i).setLength(1.0f/N);
    }
}

template<int N, class T>
inline T& WaveSequence<N, T>::segment(int i) {
    return segments[i];
}

template<int N, class T>
inline void WaveSequence<N, T>::setSegmentLength(int i, float length) {
    segments[i].setLength(length);
    calculateTotalLength();
}

template<int N, class T>
inline void WaveSequence<N, T>::calculateTotalLength() {
    float totalLength = 0;
    for(T& segment : segments) {
        totalLength += segment.getLength();
    }
    setLength(totalLength);
}

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