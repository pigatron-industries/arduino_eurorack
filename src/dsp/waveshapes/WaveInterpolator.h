#ifndef WaveInterpolator_h
#define WaveInterpolator_h

#include "WaveSelector.h"

namespace eurorack {

    template<class... Ts>
    class WaveInterpolator : public WaveSelector<Ts...> {
        public:
            WaveInterpolator() {}
            WaveInterpolator(Ts&&... args) : WaveSelector<Ts...>(args...) {}
            virtual float get(float phase);
            virtual float polyblep(float phase, float phaseIncrement);
            virtual void setFrequency(float frequency);
            void select(float interpolation);

        protected:
            float interpolation;
            float interpolationFraction;
            size_t interpolationIndex1;
            size_t interpolationIndex2;
    };

    template<class... Ts>
    inline float WaveInterpolator<Ts...>::get(float phase) {
        if(interpolationIndex1 == interpolationIndex2) {
            return WaveSelector<Ts...>::objectPtrs[interpolationIndex1]->get(phase);
        } else {
            float a = WaveSelector<Ts...>::objectPtrs[interpolationIndex1]->get(phase);
            float b = WaveSelector<Ts...>::objectPtrs[interpolationIndex2]->get(phase);
            return a + (b - a) * interpolationFraction;
        }
    }

    template<class... Ts>
    inline float WaveInterpolator<Ts...>::polyblep(float phase, float phaseIncrement) {
        if(interpolationIndex1 == interpolationIndex2) {
            return WaveSelector<Ts...>::objectPtrs[interpolationIndex1]->polyblep(phase, phaseIncrement);
        } else {
            float a = WaveSelector<Ts...>::objectPtrs[interpolationIndex1]->polyblep(phase, phaseIncrement);
            float b = WaveSelector<Ts...>::objectPtrs[interpolationIndex2]->polyblep(phase, phaseIncrement);
            return a + (b - a) * interpolationFraction;
        }
    }

    template<class... Ts>
    inline void WaveInterpolator<Ts...>::setFrequency(float frequency) {
        if(interpolationIndex1 == interpolationIndex2) {
            return WaveSelector<Ts...>::objectPtrs[interpolationIndex1]->setFrequency(frequency);
        } else {
            WaveSelector<Ts...>::objectPtrs[interpolationIndex1]->setFrequency(frequency);
            WaveSelector<Ts...>::objectPtrs[interpolationIndex2]->setFrequency(frequency);
        }
    }

    template<class... Ts>
    inline void WaveInterpolator<Ts...>::select(float interpolation) {
        this->interpolation = interpolation;
        int lastIndex = WaveSelector<Ts...>::size - 1;
        if(interpolation >= lastIndex) {
            interpolationIndex1 = lastIndex;
            interpolationIndex2 = lastIndex;
            interpolationFraction = 0;
        } else if (interpolation <= 0) {
            interpolationIndex1 = 0;
            interpolationIndex2 = 0;
            interpolationFraction = 0;
        } else {
            interpolationIndex1 = static_cast<int>(interpolation);
            interpolationIndex2 = interpolationIndex1 + 1;
            interpolationFraction = interpolation - static_cast<float>(interpolationIndex1);
        }
    }

}

#endif