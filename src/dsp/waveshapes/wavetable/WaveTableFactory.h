#ifndef WaveTableGenerator_h
#define WaveTableGenerator_h

#include "RollOffFunction.h"
#include <eurorack_dsp.h>

namespace eurorack {

    class WaveTableFactory {
        public:
            static bool addSine(BaseWaveTable* wavetable, float amplitude = 0.5, int mult = 1, float phaseShift = 0);
            static void addHarmonics(BaseWaveTable* wavetable, RollOffFunction* rolloff, float amplitude = 0.5, int mult = 1);
            static void addSquare(BaseWaveTable* wavetable, float amplitude = 0.5, int mult = 1);
            static void addTriangle(BaseWaveTable* wavetable, float amplitude = 0.5, int mult = 1);
            static void addRamp(BaseWaveTable* wavetable, float amplitude = 0.5, int mult = 1);
            static void addPulse(BaseWaveTable* wavetable, float amplitude = 0.5, int mult = 1);
            static void addImpulse(BaseWaveTable* wavetable, float amplitude = 0.5, int mult = 1);
            static void addViolin(BaseWaveTable* wavetable, float amplitude = 0.5, int mult = 1);

            static float SAMPLERATE;
    };

}

#endif
