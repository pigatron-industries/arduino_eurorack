#ifndef WaveSelector_h
#define WaveSelector_h

#include "../../util/TypeSelector.h"

namespace eurorack {

    template<class... Ts>
    class WaveSelector : public WaveShape, public TypeSelector<WaveShape, Ts...> {
        public:
            WaveSelector() {}
            WaveSelector(Ts&&... args) : TypeSelector<WaveShape, Ts...>(args...) {}
            virtual float get(float phase);
            virtual float polyblep(float phase, float phaseIncrement);
            virtual void setFrequency(float frequency);
    };

    template<class... Ts>
    inline float WaveSelector<Ts...>::get(float phase) {
        return TypeSelector<WaveShape, Ts...>::getSelected()->get(phase);
    }

    template<class... Ts>
    inline float WaveSelector<Ts...>::polyblep(float phase, float phaseIncrement) {
        return TypeSelector<WaveShape, Ts...>::getSelected()->polyblep(phase, phaseIncrement);
    }

    template<class... Ts>
    inline void WaveSelector<Ts...>::setFrequency(float frequency) {
        TypeSelector<WaveShape, Ts...>::getSelected()->setFrequency(frequency);
    }

}

#endif