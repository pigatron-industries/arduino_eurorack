#ifndef EnvelopePlayer_h
#define EnvelopePlayer_h

#include "Envelope.h"
#include "../oscillator/WaveOscillator.h"

template<class T = WaveShape>
class EnvelopePlayer : public WaveOscillator<T> {
    public:
        EnvelopePlayer() {}
        EnvelopePlayer(T waveShape): WaveOscillator<T>(waveShape) {}
        void init(float sampleRate, bool repeat = false);
        void setGate(bool value);
        virtual float process();
        
    private:
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
        WaveOscillator<T>::phase = 0;
        WaveOscillator<T>::playing = true;
    } else {
        // TODO this causes envelope to jump to sustain point if it hasn't reached it yet
        WaveOscillator<T>::phase = WaveOscillator<T>::waveShape.getSustainPhase();
        WaveOscillator<T>::playing = true;
    }
}

template<class T>
float EnvelopePlayer<T>::process() {
    if(gate && !WaveOscillator<T>::playing) {
        return 1;
    }
    
    float value = WaveOscillator<T>::waveShape.get(WaveOscillator<T>::phase);

    if(WaveOscillator<T>::playing) {
        WaveOscillator<T>::incrementPhase();
        if(gate && WaveOscillator<T>::phase > WaveOscillator<T>::waveShape.getSustainPhase()) {
            WaveOscillator<T>::playing = false;
            WaveOscillator<T>::phase = WaveOscillator<T>::waveShape.getSustainPhase();
        } else if(!gate && WaveOscillator<T>::phase > WaveOscillator<T>::waveShape.getLength()) {
            WaveOscillator<T>::playing = false;
        }
    }

    return value;
}

#endif