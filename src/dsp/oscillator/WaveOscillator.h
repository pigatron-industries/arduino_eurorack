#ifndef WaveOscillator_h
#define WaveOscillator_h

#include "../base/WaveShape.h"

// increments through a waveshape over time
template<class T = WaveShape>
class WaveOscillator {
    public:
        WaveOscillator() {}
        WaveOscillator(T waveShape): waveShape(waveShape) {}
        void init(float sampleRate, bool repeat = true);
        void setFrequency(float frequency);
        void setPeriod(float period);
        void setPhase(float phase);
        T& getShape() { return waveShape; }
        virtual float process();

    private:
        T waveShape;

        float sampleRate;
        float sampleTime;

        float increment;
        float phase;
        bool repeat;
        bool playing;

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
    float value = waveShape.get(phase);
    if(playing) {
        incrementPhase();
    }
    return value;
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
    }
}

#endif