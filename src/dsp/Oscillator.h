#ifndef Oscillator_h
#define Oscillator_h
#include <stdint.h>
#include "util/util.h"

constexpr float TWO_PI_F     = (float)M_PI*2;
constexpr float TWO_PI_RECIP = 1.0f / float(M_PI*2);

namespace pigatron
{
/** Synthesis of several waveforms, including polyBLEP bandlimited waveforms.
*/
class Oscillator
{
  public:
    Oscillator() {}
    ~Oscillator() {}

    /** Choices for output waveforms, POLYBLEP are appropriately labeled. Others are naive forms.
    */
    enum
    {
        WAVE_SIN,
        WAVE_TRI,
        WAVE_SAW,
        WAVE_RAMP,
        WAVE_SQUARE,
        WAVE_POLYBLEP_TRI,
        WAVE_POLYBLEP_SAW,
        WAVE_POLYBLEP_SQUARE,
        WAVE_LAST,
    };

    /** Initializes the Oscillator
        \param sample_rate - sample rate of the audio engine being run, and the frequency that the Process function will be called.
        Defaults:
        - freq_ = 100 Hz
        - amp_ = 0.5
        - waveform_ = sine wave.
    */
    void init(float sample_rate);

    /** Changes the frequency of the Oscillator, and recalculates phase increment.
    */
    inline void setFrequency(const float f){
        freq_      = f;
        phase_inc_ = calcPhaseInc(f);
    }

    /** Sets the amplitude of the waveform.
    */
    inline void setAmp(const float a) { amp_ = a; }

    /** Sets the waveform to be synthesized by the Process() function.
    */
    inline void setWaveform(const uint8_t wf) {
        waveform_ = wf < WAVE_LAST ? wf : WAVE_SIN;
    }

    /** Processes the waveform to be generated, returning one sample. This should be called once per sample period.
    */
    float process();

    /** Adds a value 0.0-1.0 (mapped to 0.0-TWO_PI) to the current phase. Useful for PM and "FM" synthesis.
    */
    void phaseAdd(float _phase) { phase_ += _phase; }

    /** Resets the phase to the input argument. If no argument is present, it will reset phase to 0.0;
    */
    void setPhase(float _phase = 0.0f) { phase_ = _phase; }

    void setAllowHighFrequency(bool allowHighFrequency) { this->allowHighFrequency = allowHighFrequency; }

  private:
    float   calcPhaseInc(float f);
    uint8_t waveform_;
    float   amp_, freq_;
    float   sr_, sr_recip_, phase_, phase_inc_;
    float   last_out_, last_freq_;
    bool allowHighFrequency;
};


static inline float polyblep(float phase_inc, float t)
{
    float dt = phase_inc;
    if(t < dt)
    {
        t /= dt;
        return t + t - t * t - 1.0f;
    }
    else if(t > 1.0f - dt)
    {
        t = (t - 1.0f) / dt;
        return t * t + t + t + 1.0f;
    }
    else
    {
        return 0.0f;
    }
}

inline float Oscillator::process() {
    if(amp_ == 0 || (!allowHighFrequency && freq_ >= sr_ * 0.5)) {
        return 0;
    }
    float out, t;
    switch(waveform_) {
        case WAVE_SIN: 
            out = sinf(phase_ * M_PI * 2.0f);
            break;
        case WAVE_TRI:
            t   = -1.0f + (2.0f * phase_);
            out = 2.0f * (fabsf(t) - 0.5f);
            break;
        case WAVE_SAW:
            out = -1.0f * (((phase_ * 2.0f)) - 1.0f);
            break;
        case WAVE_RAMP: out = ((phase_ * 2.0f)) - 1.0f; break;
        case WAVE_SQUARE: out = phase_ < 0.5f ? (1.0f) : -1.0f; break;
        case WAVE_POLYBLEP_TRI:
            t   = phase_;
            out = phase_ < 0.5f ? 1.0f : -1.0f;
            out += polyblep(phase_inc_, t);
            out -= polyblep(phase_inc_, fmodf(t + 0.5f, 1.0f));
            // Leaky Integrator:
            // y[n] = A + x[n] + (1 - A) * y[n-1]
            out = phase_inc_ * out + (1.0f - phase_inc_) * last_out_;
            break;
        case WAVE_POLYBLEP_SAW:
            t   = phase_;
            out = (2.0f * t) - 1.0f;
            out -= polyblep(phase_inc_, t);
            out *= -1.0f;
            break;
        case WAVE_POLYBLEP_SQUARE:
            t   = phase_;
            out = phase_ < 0.5f ? 1.0f : -1.0f;
            out += polyblep(phase_inc_, t);
            out -= polyblep(phase_inc_, fmodf(t + 0.5f, 1.0f));
            out *= 0.707f; // ?
            break;
        default: out = 0.0f; break;
    }
    phase_ += phase_inc_;
    if(phase_ > 1.0f) {
        phase_ -= 1.0f;
    }
    return out * amp_;
}

inline float Oscillator::calcPhaseInc(float f) {
    return f * sr_recip_;
}


}
#endif