#include "SampleBuffer.h"
#include <Arduino.h>
#include "memory/MemPool.h"

namespace eurorack {

    template <typename T>
    void SampleBuffer<T>::init(size_t bufferSize, MemPool<>& memPool) { 
        init(0, 0, bufferSize, memPool);
    }

    template <typename T>
    void SampleBuffer<T>::init(float sampleRate, size_t bufferSize, MemPool<>& memPool) {
        init(sampleRate, 0, bufferSize, memPool);
    }

    template <typename T>
    void SampleBuffer<T>::init(float sampleRate, float sampleFrequency, size_t bufferSize, MemPool<>& memPool) {
        this->bufferSize = bufferSize;
        this->sampleSize = bufferSize;
        this->sampleRate = sampleRate;
        this->sampleFrequency = sampleFrequency;
        this->playbackSampleRate = sampleRate;
        buffer = allocateBuffer<float>(bufferSize, &memPool);
        reset();
        clear();
        inited = true;
    }

    template <typename T>
    void SampleBuffer<T>::reset() {
        writePointer = 0;
        sampleFull = false;
        bufferFull = false;
    }

    template <typename T>
    void SampleBuffer<T>::clear() {
        for(size_t i = 0; i < bufferSize; i++) {
            buffer[i] = 0.0;
        }
    }

    template <typename T>
    void SampleBuffer<T>::setSampleSize(size_t sampleSize) {
        if(sampleSize <= bufferSize) {
            this->sampleSize = sampleSize;
        } else {
            this->sampleSize = bufferSize;
        }
    }

    template <typename T>
    float SampleBuffer<T>::calculateReadIncrement(float playbackFrequency) {
        return (sampleRate / playbackSampleRate) * (playbackFrequency / sampleFrequency);
    }

    template <typename T>
    inline bool SampleBuffer<T>::write(const float sample) {
        buffer[writePointer] = sample;
        writePointer++;
        if(!sampleFull && writePointer >= sampleSize) {
            sampleFull = true;
        }
        if(writePointer >= bufferSize) {
            bufferFull = true;
            writePointer = 0;
        }
        return sampleFull;
    }

    template <typename T>
    inline bool SampleBuffer<T>::mix(const float sample) {
        buffer[writePointer] += sample;
        writePointer++;
        if(!sampleFull && writePointer >= sampleSize) {
            sampleFull = true;
        }
        if(writePointer >= bufferSize) {
            bufferFull = true;
            writePointer = 0;
        }
        return sampleFull;
    }

    template <typename T>
    inline const float SampleBuffer<T>::read(int position) const {
        return buffer[position];
    }

    template <typename T>
    inline const float SampleBuffer<T>::read(float position) const {
        int32_t intPosition = static_cast<int32_t>(position);
        float fracPosition = position - static_cast<float>(intPosition);
        intPosition = static_cast<size_t>(intPosition) < bufferSize ? intPosition : bufferSize - 1;
        return read(intPosition, fracPosition);
    }

    template <typename T>
    inline const float SampleBuffer<T>::read(size_t intPosition, float fracPosition) const {
        float a = buffer[intPosition % bufferSize];
        float b = buffer[(intPosition + 1) % bufferSize];
        return a + (b - a) * fracPosition;
    }

}