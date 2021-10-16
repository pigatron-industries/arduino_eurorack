#ifndef SamplePlayer_h
#define SamplePlayer_h

#include "SampleBuffer.h"

class SamplePlayer
{
    public:
        SamplePlayer() {}
        void init(float sampleRate);

        void setSample(SampleBuffer* sample);
        void setFrequency(float frequency);


    private:
        SampleBuffer* sample = nullptr;
        float sampleRate;

        size_t readPointer;
        float readIncrement;
        float frequency = 0;
};

#endif
