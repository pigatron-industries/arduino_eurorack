#ifndef SampleBuffer_h
#define SampleBuffer_h
#include <stdlib.h>
#include <stdint.h>
#include "memory/MemPool.h"

namespace eurorack {

    class SampleBuffer
    {
        public:
            SampleBuffer() {}

            void init(size_t bufferSize, MemPool<float>& memPool);
            void init(float sampleRate, size_t bufferSize, MemPool<float>& memPool);
            void init(float sampleRate, float sampleFrequency, size_t bufferSize, MemPool<float>& memPool);
            bool isInited() { return inited; }
            void setPlaybackSampleRate(float playbackSampleRate) { this->playbackSampleRate = playbackSampleRate; }
            void reset();
            void clear();

            size_t getSampleSize() { return sampleSize; }
            size_t getBufferSize() { return bufferSize; }
            void setSampleSize(size_t sampleSize);

            float& operator [] (size_t i) { return buffer[i]; }
            float operator [] (float i) { return read(i); }

            bool write(const float sample);
            bool mix(const float sample);
            const float read(int position) const;
            const float read(float position) const;
            float calculateReadIncrement(float playbackFrequency);

            bool isSampleFull() { return sampleFull; }
            bool isBufferFull() { return bufferFull; }

        protected:
            bool inited;
            size_t bufferSize;        // size of buffer
            size_t sampleSize;        // size of the sample within the buffer
            float* buffer;
            
            size_t writePointer;
            bool sampleFull;
            bool bufferFull;

            float sampleRate;         // sample rate that the sample was recorded at
            float sampleFrequency;    // actual frequency of waveform
            float playbackSampleRate; // sample rate of playback

            const float read(size_t position, float fraction) const;
    };


    inline bool SampleBuffer::write(const float sample) {
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

    inline bool SampleBuffer::mix(const float sample) {
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

    inline const float SampleBuffer::read(int position) const {
        return buffer[position];
    }

    inline const float SampleBuffer::read(float position) const {
        int32_t intPosition = static_cast<int32_t>(position);
        float fracPosition = position - static_cast<float>(intPosition);
        intPosition = static_cast<size_t>(intPosition) < bufferSize ? intPosition : bufferSize - 1;
        return read(intPosition, fracPosition);
    }

    inline const float SampleBuffer::read(size_t intPosition, float fracPosition) const {
        float a = buffer[intPosition % bufferSize];
        float b = buffer[(intPosition + 1) % bufferSize];
        return a + (b - a) * fracPosition;
    }
    
}

#endif
