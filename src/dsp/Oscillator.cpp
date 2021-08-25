#include <math.h>
#include "Oscillator.h"

using namespace pigatron;

void pigatron::Oscillator::init(float sample_rate)
{
    sr_        = sample_rate;
    sr_recip_  = 1.0f / sample_rate;
    freq_      = 100.0f;
    amp_       = 0.5f;
    phase_     = 0.0f;
    phase_inc_ = calcPhaseInc(freq_);
    waveform_  = WAVE_SIN;
}