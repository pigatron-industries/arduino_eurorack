#ifndef WaveInterpolator2D_h
#define WaveInterpolator2D_h

#include "WaveInterpolator.h"

namespace eurorack {

    template<class T, int X, int Y>
    class WaveInterpolator2D : public WaveArrayInterpolator<WaveArrayInterpolator<T, Y>, X> {
        public:

            void setInterpolationX(float x) {
                this->setInterpolation(x);
            }

            void setInterpolationY(float y) {
                for(int i = 0; i < X; i++) {
                    (*this)[i].setInterpolation(y);
                }
            }
    };

}

#endif