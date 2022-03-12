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
    WaveInterpolator2D<WaveTable<10, 128>, 5, 3> waveInterpolator2D;
    WaveInterpolator3D<WaveTable<10, 128>, 5, 3, 2> waveInterpolator3D;

    void testWaveInterpolator() {
        waveInterpolator.setInterpolation(0);
        waveInterpolator.get(0.5);
        waveInterpolatorRef.setInterpolation(0);
        waveInterpolatorRef.get(0.5);
        waveArrayInterpolator.setInterpolation(0);
        waveArrayInterpolator.get(0.5);
        waveInterpolator2D.setInterpolationX(0);
        waveInterpolator2D.setInterpolationY(0);
        waveInterpolator2D.get(0.5);
        waveInterpolator3D.setInterpolationX(0);
        waveInterpolator3D.setInterpolationY(0);
        waveInterpolator3D.setInterpolationZ(0);
        waveInterpolator3D.get(0.5);
    }

#endif
