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
        
        private:
            float sustainPhase;
    };

}

#endif