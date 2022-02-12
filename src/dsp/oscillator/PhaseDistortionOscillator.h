#ifndef PhaseDistortionOscillator_h
#define PhaseDistortionOscillator_h

#include "WaveOscillator.h"

namespace eurorack {

    template<class T = WaveShape, class F = Function>
    class PhaseDistortionOscillator : public WaveOscillator<T> {
        public:
            PhaseDistortionOscillator() {}
            PhaseDistortionOscillator(T waveShape) : WaveOscillator<T>(waveShape) {}
            PhaseDistortionOscillator(T waveShape, F distortionFunction) : WaveOscillator<T>(waveShape), distortionFunction(distortionFunction) {}
            virtual float process();

        protected:
            F distortionFunction;
    };

    template<class T, class F>
    float PhaseDistortionOscillator<T, F>::process() {
        if(!WaveOscillator<T>::playing) {
            return 0;
        }

        float distortedPhase = distortionFunction.get(WaveOscillator<T>::phase); // + phaseOffset;
        //TODO mod distortedPhase so value is between 0 and 1
        float value = WaveOscillator<T>::waveShape.get(distortedPhase);
        if(WaveOscillator<T>::polyblepEnabled) {
            value += WaveOscillator<T>::waveShape.polyblep(WaveOscillator<T>::phase, WaveOscillator<T>::increment);
        }
        WaveOscillator<T>::incrementPhase();
        return value * WaveOscillator<T>::amplitude;
    }

}

#endif