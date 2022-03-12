#ifndef WaveInterpolator_h
#define WaveInterpolator_h

#include "../base/WaveShape.h"
#include "../../util/TypeSelector.h"

namespace eurorack {

    class Interpolator : public WaveShape {
        public:
            Interpolator(int size) { lastIndex = size-1; }
            void setInterpolation(float interpolation);
            virtual float get(float phase);
            virtual float polyblep(float phase, float phaseIncrement);
            virtual void setFrequency(float frequency);
        protected:
            float interpolation;
            float interpolationFraction;
            size_t interpolationIndex1;
            size_t interpolationIndex2;
            size_t lastIndex;

            virtual float get(int index, float phase) = 0;
            virtual float polyblep(int index, float phase, float phaseIncrement) = 0;
            virtual void setFrequency(int index, float frequency) = 0;
    };

    inline void Interpolator::setInterpolation(float interpolation) {
        this->interpolation = interpolation;
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

    inline float Interpolator::get(float phase) {
        if(interpolationIndex1 == interpolationIndex2) {
            return get(interpolationIndex1, phase);
        } else {
            float a = get(interpolationIndex1, phase);
            float b = get(interpolationIndex2, phase);
            return a + (b - a) * interpolationFraction;
        }
    }

    inline float Interpolator::polyblep(float phase, float phaseIncrement) {
        if(interpolationIndex1 == interpolationIndex2) {
            return polyblep(interpolationIndex1, phase, phaseIncrement);
        } else {
            float a = polyblep(interpolationIndex1, phase, phaseIncrement);
            float b = polyblep(interpolationIndex2, phase, phaseIncrement);
            return a + (b - a) * interpolationFraction;
        }
    }

    inline void Interpolator::setFrequency(float frequency) {
        if(interpolationIndex1 == interpolationIndex2) {
            setFrequency(interpolationIndex1, frequency);
        } else {
            setFrequency(interpolationIndex1, frequency);
            setFrequency(interpolationIndex2, frequency);
        }
    }



    template<class... Ts>
    class WaveInterpolator : public Interpolator, private TypeSelector<WaveShape, Ts...> {
        public:
            WaveInterpolator() : Interpolator(sizeof...(Ts)) {}
            WaveInterpolator(Ts&&... args) : Interpolator(sizeof...(Ts)), TypeSelector<WaveShape, Ts...>(args...) {}
            using Interpolator::get;
            using Interpolator::polyblep;
            using Interpolator::setFrequency;
            using TypeSelector<WaveShape, Ts...>::operator[];

        protected:
            float get(int index, float phase) { return (*this)[index]->get(phase); }
            float polyblep(int index, float phase, float phaseIncrement) { return (*this)[index]->polyblep(phase, phaseIncrement); }
            void setFrequency(int index, float frequency) { (*this)[index]->setFrequency(frequency); }
    };



    template<class T, int N>
    class WaveArrayInterpolator : public Interpolator, private ArraySelector<T, N> {
        public:
            WaveArrayInterpolator() : Interpolator(N) {}
            void select(float interpolation);
            using Interpolator::get;
            using Interpolator::polyblep;
            using Interpolator::setFrequency;
            using ArraySelector<T, N>::operator[];

        protected:
            float get(int index, float phase) { return (*this)[index].get(phase); }
            float polyblep(int index, float phase, float phaseIncrement) { return (*this)[index].polyblep(phase, phaseIncrement); }
            void setFrequency(int index, float frequency) { (*this)[index].setFrequency(frequency); }
    };

}

#endif