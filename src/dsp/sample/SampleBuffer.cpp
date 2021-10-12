#include "SampleBuffer.h"
#include <Arduino.h>

void SampleBuffer::init(size_t bufferSize, void* (*allocate)(size_t)) { 
    init(0, 0, bufferSize, allocate);
}

void SampleBuffer::init(float sampleRate, float sampleFrequency, size_t bufferSize, void* (*allocate)(size_t)) {
    this->bufferSize = bufferSize;
    this->sampleSize = bufferSize;
    buffer = new (allocate(sizeof(float)*bufferSize)) float[bufferSize];
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