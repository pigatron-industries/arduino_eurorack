#ifndef WaveInterpolator3D_h
#define WaveInterpolator3D_h

#include "WaveInterpolator.h"

namespace eurorack {

    template<class T, int X, int Y, int Z>
    class WaveInterpolator3D : public WaveArrayInterpolator<WaveArrayInterpolator<WaveArrayInterpolator<T, Z>, Y>, X> {
        public:

            void setInterpolationX(float x) {
                this->setInterpolation(x);
            }

            void setInterpolationY(float y) {
                for(int i = 0; i < X; i++) {
                    (*this)[i].setInterpolation(y);
                }
            }

            void setInterpolationZ(float z) {
                for(int i = 0; i < X; i++) {
                    for(int j = 0; j < Y; j++) {
                        (*this)[i][j].setInterpolation(z);
                    }
                }
            }
    };

}

#endif