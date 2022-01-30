#ifndef WaveSelector_h
#define WaveSelector_h

#include "../../util/ObjectSelector.h"

template<class... Ts>
class WaveSelector : public WaveShape, public ObjectSelector<WaveShape, Ts...> {
    public:
        virtual float get(float phase) { 
            return ObjectSelector<WaveShape, Ts...>::selected->get(phase);
        }
};

#endif