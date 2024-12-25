#include "SamplePlayer.h"

using namespace eurorack;

void SamplePlayer::init(float sampleRate) {
    this->sampleRate = sampleRate;
    if (sample != nullptr) {
        sample->setPlaybackSampleRate(sampleRate);
    }
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

void SamplePlayer::play() {
    if (sample != nullptr) {
        playing = true;

    }
}

void SamplePlayer::pause() {
    playing = false;
}

void SamplePlayer::stop() {
    playing = false;
    readPointer = 0;
}