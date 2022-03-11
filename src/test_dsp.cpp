#ifdef TEST_COMPILE
    #include "eurorack.h"
    #include "eurorack_dsp.h"

    using namespace eurorack;

    Sine sine;
    Pulse pulse;

    WaveSelector<Sine> waveSelector;
    WaveInterpolator<Sine, Pulse> waveInterpolator;
    WaveInterpolator<Sine&, Pulse&> waveInterpolatorRef =  WaveInterpolator<Sine&, Pulse&>(sine, pulse);

    void testWaveShapes() {
    }


#endif
