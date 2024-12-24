#include "SamplePlayer.h"

using namespace eurorack;

void SamplePlayer::init(float sampleRate) {
    this->sampleRate = sampleRate;
    sample->setPlaybackSampleRate(sampleRate);
}

void SamplePlayer::setSample(SampleBuffer* sample) { 
    this->sample = sample; 
    sample->setPlaybackSampleRate(sampleRate);
    calcReadIncrement();
}

void SamplePlayer::setFrequency(float frequency) {
    this->frequency = frequency;
    calcReadIncrement();
}

void SamplePlayer::calcReadIncrement() {
    if (sample != nullptr) {
        float originalFrequency = sample->getSampleFrequency();
        float originalSampleRate = sample->getSampleRate();
        readIncrement = (frequency / originalFrequency) * (originalSampleRate / sampleRate);
    }
}
