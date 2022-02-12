#include "WaveTableFactory.h"
#include <math.h>

using namespace eurorack;

float WaveTableFactory::SAMPLERATE = 48000;

bool WaveTableFactory::addSine(BaseWaveTable* wavetable, float amplitude, int mult, float phaseShift) {
    float nyquist = SAMPLERATE * 0.5;
    size_t bufferSize = wavetable->getSampleSize();
    SampleBuffer& tempBuffer = wavetable->getTempBuffer();
    bool added = false;

    // create sine in temp buffer
    float phaseIncrement = (1 / float(bufferSize)) * M_PI*2 * mult;
    float phase = phaseShift;
    for(size_t i = 0; i < bufferSize; i++) {
        tempBuffer[i] = sinf(phase) * amplitude;
        phase += phaseIncrement;
    }

    // copy temp buffer to each table if it's max frequency is less than nyquist
    for(size_t tableIndex = 0; tableIndex < wavetable->getTableSize(); tableIndex++) {
        float maxFrequency = wavetable->getTableFrequency(tableIndex) * mult;
        if(maxFrequency <= nyquist) {
            added = true;
            wavetable->copyTempBufferToTable(tableIndex);
        }
    }

    return added;
}

void WaveTableFactory::addHarmonics(BaseWaveTable* wavetable, RollOffFunction* rolloff, float amplitude, int mult) {
    int harmonic = 1;
    bool added = true;
    while(added) {
        float harmonicAmplitude = rolloff->rolloff(harmonic) * amplitude;
        if(harmonicAmplitude > 0) {
            int harmonicMult = harmonic * mult;
            added = addSine(wavetable, harmonicAmplitude, harmonicMult);
        }
        harmonic++;
    }
}

void WaveTableFactory::addSquare(BaseWaveTable* wavetable, float amplitude, int mult) {
    SquareRollOffFunction rolloff = SquareRollOffFunction();
    addHarmonics(wavetable, &rolloff, amplitude, mult);
}

void WaveTableFactory::addTriangle(BaseWaveTable* wavetable, float amplitude, int mult) {
    TriangleRollOffFunction rolloff = TriangleRollOffFunction();
    addHarmonics(wavetable, &rolloff, amplitude, mult);
}

void WaveTableFactory::addRamp(BaseWaveTable* wavetable, float amplitude, int mult) {
    RampRollOffFunction rolloff = RampRollOffFunction();
    addHarmonics(wavetable, &rolloff, amplitude, mult);
}

void WaveTableFactory::addPulse(BaseWaveTable* wavetable, float amplitude, int mult) {
    PulseRollOffFunction rolloff = PulseRollOffFunction();
    addHarmonics(wavetable, &rolloff, amplitude, mult);
}

void WaveTableFactory::addImpulse(BaseWaveTable* wavetable, float amplitude, int mult) {
    float amp = amplitude * -0.18;
    addSine(wavetable, amp *  1.0, mult * 1,  0);
    addSine(wavetable, amp * -0.9, mult * 2,  M_PI*0.5);
    addSine(wavetable, amp * -0.8, mult * 3,  0);
    addSine(wavetable, amp *  0.7, mult * 4,  M_PI*0.5);
    addSine(wavetable, amp *  0.6, mult * 5,  0);
    addSine(wavetable, amp * -0.5, mult * 6,  M_PI*0.5);
    addSine(wavetable, amp * -0.4, mult * 7,  0);
    addSine(wavetable, amp *  0.3, mult * 8,  M_PI*0.5);
    addSine(wavetable, amp *  0.2, mult * 9,  0);
    addSine(wavetable, amp * -0.1, mult * 10, M_PI*0.5);
}

void WaveTableFactory::addViolin(BaseWaveTable* wavetable, float amplitude, int mult) {
    float amp = amplitude * 0.490;
    addSine(wavetable, amp * 0.995, mult * 1,  0);
    addSine(wavetable, amp * 0.940, mult * 2,  M_PI*0.5);
    addSine(wavetable, amp * 0.425, mult * 3,  0);
    addSine(wavetable, amp * 0.480, mult * 4,  M_PI*0.5);
    addSine(wavetable, amp * 0.365, mult * 6,  M_PI*0.5);
    addSine(wavetable, amp * 0.040, mult * 7,  0);
    addSine(wavetable, amp * 0.085, mult * 8,  M_PI*0.5);
    addSine(wavetable, amp * 0.090, mult * 10, M_PI*0.5);
}
