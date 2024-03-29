#ifndef WaveOscillator_h
#define WaveOscillator_h

#include "BaseOscillator.h"
#include "../base/WaveShape.h"

namespace eurorack {

    // increments through a waveshape over time
    template<class T = WaveShape>
    class WaveOscillator : public BaseOscillator {
        public:
            WaveOscillator() {}
            WaveOscillator(T waveShape): waveShape(waveShape) {}
            void init(float sampleRate, bool repeat = true);
            void setFrequency(float frequency);
            void setAmplitude(float amplitude);
            void setPeriod(float period);
            void setPhase(float phase);
            void setPolyblep(bool polyblepEnabled) { this->polyblepEnabled = polyblepEnabled; }
            T& getShape() { return waveShape; }
            virtual float process();

        protected:
            T waveShape;

            float sampleRate;
            float sampleTime;

            float amplitude = 0.8;
            float increment;
            float phase;
            bool repeat;
            bool playing;
            bool polyblepEnabled;

            void incrementPhase();
    };

    template<class T>
    void WaveOscillator<T>::init(float sampleRate, bool repeat) {
        this->sampleRate = sampleRate;
        this->sampleTime = 1.0f/sampleRate;
        this->increment = sampleTime;
        this->repeat = repeat;
        phase = 0;
        playing = repeat;
    }

    template<class T>
    void WaveOscillator<T>::setFrequency(float frequency) {
        increment = sampleTime * frequency;
        waveShape.setFrequency(frequency);
    }

    template<class T>
    void WaveOscillator<T>::setAmplitude(float amplitude) {
        this->amplitude = amplitude;
    }

    template<class T>
    void WaveOscillator<T>::setPeriod(float period) {
        increment = sampleTime / period;
    }

    template<class T>
    void WaveOscillator<T>::setPhase(float phase) {
        this->phase = phase;
    }

    template<class T>
    float WaveOscillator<T>::process() {
        if(!playing) {
            return 0;
        }

        float value = waveShape.get(phase);
        if(polyblepEnabled) {
            value += waveShape.polyblep(phase, increment);
        }
        
        incrementPhase();
        return value * amplitude;
    }

    template<class T>
    void WaveOscillator<T>::incrementPhase() {
        phase += increment;
        if(phase > waveShape.getLength()) {
            if(repeat) {
                phase -= waveShape.getLength();
            } else {
                playing = false;
                phase = 0;
            }
        } else if(phase < 0) {
            phase += waveShape.getLength();
        }
    }

}

#endif