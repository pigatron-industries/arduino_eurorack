#include "SampleBuffer.h"
#include <Arduino.h>

void SampleBuffer::init(size_t bufferSize, MemPool& memPool) { 
    init(0, 0, bufferSize, memPool);
}

void SampleBuffer::init(float sampleRate, float sampleFrequency, size_t bufferSize, MemPool& memPool) {
    this->bufferSize = bufferSize;
    this->sampleSize = bufferSize;
    this->sampleRate = sampleRate;
    this->sampleFrequency = sampleFrequency;
    this->playbackSampleRate = sampleRate;
    buffer = new (memPool.allocate(sizeof(float)*bufferSize)) float[bufferSize];
    reset();
    clear();
}

void SampleBuffer::reset() {
    writePointer = 0;
    sampleFull = false;
    bufferFull = false;
}

void SampleBuffer::clear() {
    for(size_t i = 0; i < bufferSize; i++) {
        buffer[i] = 0.0;
    }
}

void SampleBuffer::setSampleSize(size_t sampleSize) {
    if(sampleSize <= bufferSize) {
        this->sampleSize = sampleSize;
    } else {
        this->sampleSize = bufferSize;
    }
}

float SampleBuffer::calculateReadIncrement(float playbackFrequency) {
    return (sampleRate / playbackSampleRate) * (playbackFrequency / sampleFrequency);
}
