#ifndef BaseOscillator_h
#define BaseOscillator_h

namespace eurorack {

    class BaseOscillator
    {
        public:
            virtual void setFrequency(const float f) = 0;
            virtual float process() = 0;
    };

}

#endif