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
            void setLoop(boolean loop) { this->loop = loop; }

            void play();
            void pause();
            void stop();

            float process();

        private:
            SampleBuffer* sample = nullptr;
            float sampleRate;
            
            boolean playing = false;
            boolean loop = false;
            float readIncrement = 1.0;
            float frequency = 440;
            float readPointer = 0;

            void calcReadIncrement();
    };


    inline float SamplePlayer::process() {
        if(playing) {
            float output = sample->read(readPointer);
            readPointer += readIncrement;
            if (readPointer >= sample->getSampleSize()) {
                readPointer = 0;
                if(!loop) {
                    playing = false;
                }
            }
            return output;
        }
        return 0;
    }


}

#endif
