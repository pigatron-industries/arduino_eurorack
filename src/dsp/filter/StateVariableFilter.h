#ifndef StateVariableFilter_h
#define StateVariableFilter_h


/**      Double Sampled, Stable State Variable Filter

Credit to Andrew Simper from musicdsp.org

This is his "State Variable Filter (Double Sampled, Stable)"

Additional thanks to Laurent de Soras for stability limit, and 
Stefan Diedrichsen for the correct notch output

Ported by: Stephen Hensley
Performance Enhancements: Robert Ellis
*/
class StateVariableFilter
{
  public:
    StateVariableFilter() {}
    /** Initializes the filter
        float sample_rate - sample rate of the audio engine being run, and the frequency that the Process function will be called.
    */
    void init(float sample_rate);

    /** 
        Process the input signal, updating all of the outputs.
    */
    void process(float in);

    /** sets the frequency of the cutoff frequency. 
        f must be between 0.0 and sample_rate / 2
    */
    void setFrequency(float f);

    /** sets the resonance of the filter.
        Must be between 0.0 and 1.0 to ensure stability.
    */
    void setResonance(float r);

    /** lowpass output
        \return low pass output of the filter
    */
    inline float low() { return 0.5f * out_low_; }
    /** highpass output
        \return high pass output of the filter
    */
    inline float high() { return 0.5f * out_high_; }
    /** bandpass output
        \return band pass output of the filter
    */
    inline float band() { return 0.5f * out_band_; }
    /** notchpass output
        \return notch pass output of the filter
    */
    inline float notch() { return 0.5f * out_notch_; }
    /** peak output
        \return peak output of the filter
    */
    inline float peak() { return 0.5f * out_peak_; }

  private:
    float sr_, fc_, res_, freq_, damp_;
    float notch_, low_, high_, band_, peak_;
    float input_;
    float out_low_, out_high_, out_band_, out_peak_, out_notch_;
};


inline void StateVariableFilter::process(float in)
{
    input_ = in;
    // first pass
    notch_     = input_ - damp_ * band_;
    low_       = low_ + freq_ * band_;
    high_      = notch_ - low_;
    band_      = freq_ * high_ + band_;
    out_low_   = low_;
    out_high_  = high_;
    out_band_  = band_;
    out_peak_  = low_ - high_;
    out_notch_ = notch_;
    // second pass
    notch_ = input_ - damp_ * band_;
    low_   = low_ + freq_ * band_;
    high_  = notch_ - low_;
    band_  = freq_ * high_ + band_;
    out_low_ += low_;
    out_high_ += high_;
    out_band_ += band_;
    out_peak_ += low_ - high_;
    out_notch_ += notch_;
}

#endif
