#ifndef Envelope_h
#define Envelope_h

#include "../base/WaveShape.h"

namespace eurorack {

    template<class T = WaveShape>
    class Envelope : public T {
        public:
            Envelope() {}
            void setSustainPhase(float sustainPhase) { this->sustainPhase = sustainPhase; }
            float getSustainPhase() { return sustainPhase; }
            float getAttackPhase(float value);
            float getDecayPhase(float value);
        
        private:
            float sustainPhase;
    };

    template<class T>
    float Envelope<T>::getAttackPhase(float targetValue) {
        float phaseIncrement = 0.01;
        float phase = 0;
        float value = this->get(phase);

        while(value < targetValue && phase < this->getSustainPhase()) {
            value = this->get(phase);
            phase += phaseIncrement;
        }

        return phase;
    }

    template<class T>
    float Envelope<T>::getDecayPhase(float targetValue) {
        float phaseIncrement = 0.01;
        float phase = sustainPhase;
        float value = this->get(phase);

        while(value > targetValue && phase < this->getLength()) {
            value = this->get(phase);
            phase += phaseIncrement;
        }

        return phase;
    }

}

#endif