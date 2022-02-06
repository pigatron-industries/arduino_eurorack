#include "SamplePlayer.h"

using namespace eurorack;

void SamplePlayer::init(float sampleRate) {
    this->sampleRate = sampleRate;
    sample->setPlaybackSampleRate(sampleRate);
}

void SamplePlayer::setSample(SampleBuffer* sample) { 
    this->sample = sample; 
    sample->setPlaybackSampleRate(sampleRate);
}