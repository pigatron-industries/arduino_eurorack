#ifndef SamplePlayer_h
#define SamplePlayer_h

#include "SampleBuffer.h"

namespace eurorack {

    class SamplePlayer
    {
        public:
            SamplePlayer() {}
            void init(float sampleRate);

            void setSample(SampleBuffer* sample);
            void setFrequency(float frequency);

            float process();

        private:
            SampleBuffer* sample = nullptr;
            float sampleRate;

            float readPointer = 0;
            float readIncrement = 1.0;
            float frequency = 440;

            void calcReadIncrement();
    };


    inline float SamplePlayer::process() {
        if (sample != nullptr) {
            float output = sample->read(readPointer);
            readPointer += readIncrement;
            if (readPointer >= sample->getSampleSize()) {
                readPointer = 0;
            }
            return output;
        }
        return 0;
    }


}

#endif
