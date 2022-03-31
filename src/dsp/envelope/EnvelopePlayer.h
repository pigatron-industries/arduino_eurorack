#ifndef EnvelopePlayer_h
#define EnvelopePlayer_h

#include <Arduino.h>
#include "Envelope.h"
#include "../oscillator/WaveOscillator.h"

namespace eurorack {

    template<class T = Envelope<WaveShape>>
    class EnvelopePlayer : public WaveOscillator<T> {
        public:
            EnvelopePlayer() {}
            EnvelopePlayer(T waveShape): WaveOscillator<T>(waveShape) {}
            void init(float sampleRate, bool repeat = false);
            void setGate(bool value);
            virtual float process();
            
        private:
            enum State { OFF, ATTACK, SUSTAIN, DECAY };
            State state = State::OFF;
            bool gate;
    };

    template<class T>
    void EnvelopePlayer<T>::init(float sampleRate, bool repeat) {
        WaveOscillator<T>::init(sampleRate, repeat);
        WaveOscillator<T>::increment = WaveOscillator<T>::sampleTime;
    }

    template<class T>
    void EnvelopePlayer<T>::setGate(bool value) {
        if(value == gate) {
            return;
        }
        gate = value;
        if(gate) {
            state = State::ATTACK;
            WaveOscillator<T>::phase = 0;
            WaveOscillator<T>::playing = true;
        } else {
            state = State::DECAY;
            // TODO this causes envelope to jump to sustain point if it hasn't reached it yet
            WaveOscillator<T>::phase = WaveOscillator<T>::waveShape.getSustainPhase();
            WaveOscillator<T>::playing = true;
        }
    }

    template<class T>
    float EnvelopePlayer<T>::process() {
        if(state == State::SUSTAIN) {
            WaveOscillator<T>::phase = WaveOscillator<T>::waveShape.getSustainPhase();
        }

        float value = WaveOscillator<T>::waveShape.get(WaveOscillator<T>::phase);

        if(WaveOscillator<T>::playing) {
            WaveOscillator<T>::incrementPhase();
            if(gate && WaveOscillator<T>::phase >= WaveOscillator<T>::waveShape.getSustainPhase()) {
                state = State::SUSTAIN;
                WaveOscillator<T>::playing = false;
            } else if(!gate && WaveOscillator<T>::phase > WaveOscillator<T>::waveShape.getLength()) {
                state = State::OFF;
                WaveOscillator<T>::playing = false;
            }
        }

        return value;
    }

}

#endif