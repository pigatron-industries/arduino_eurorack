#ifndef WaveList_h
#define WaveList_h

#include "../base/WaveShape.h"

template<int N>
class WaveList : public WaveShape {
    public:
        WaveList(WaveShape* waveShapes[N]);
        void select(int n) { waveShape = waveShapes[n]; }
        virtual float get(float phase) { return waveShape->get(phase); }
    protected:
        WaveShape* waveShape;
        WaveShape** waveShapes;

};

template<int N>
inline WaveList<N>::WaveList(WaveShape* waveShapes[N]) { 
    this->waveShapes = waveShapes;
    this->waveShape = waveShapes[0];
}

#endif