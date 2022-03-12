#ifdef TEST_COMPILE
    #include "eurorack.h"
    #include "eurorack_dsp.h"

    using namespace eurorack;

    Sine sine;
    Pulse pulse;
    WaveTable<10, 128> waveTable;

    WaveSelector<Sine> waveSelector;

    void testWaveSelector() {
        waveSelector.select(0);
    }


    WaveInterpolator<Sine, Pulse> waveInterpolator;
    WaveInterpolator<Sine&, Pulse&> waveInterpolatorRef =  WaveInterpolator<Sine&, Pulse&>(sine, pulse);
    WaveArrayInterpolator<WaveTable<10, 128>, 5> waveArrayInterpolator;

    void testWaveInterpolator() {
        waveInterpolator.setInterpolation(0);
        waveInterpolator.get(0.5);
        waveInterpolatorRef.setInterpolation(0);
        waveInterpolatorRef.get(0.5);
        waveArrayInterpolator.setInterpolation(0);
        waveArrayInterpolator.get(0.5);
    }

#endif
