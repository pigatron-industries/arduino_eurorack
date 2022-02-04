#ifndef WaveSelector_h
#define WaveSelector_h

#include "../../util/TypeSelector.h"

namespace eurorack {

    template<class... Ts>
    class WaveSelector : public WaveShape, public TypeSelector<WaveShape, Ts...> {
        public:
            virtual float get(float phase) { 
                return TypeSelector<WaveShape, Ts...>::selected->get(phase);
            }
    };

}

#endif