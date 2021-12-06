#ifndef DelayLine_h
#define DelayLine_h

#include <stdlib.h>
#include <stdint.h>
#include "SampleBuffer.h"

class DelayLine : public SampleBuffer
{
    public:
        DelayLine() {}

        void setDelay(size_t delay);
        void setDelay(float delay);
        const float read() const;

    private:
        float delay;
        float  delayFrac;
        size_t delayInt;
};


inline const float DelayLine::read() const {
    float pos = writePointer - delay;
    if(pos < 0) {
        pos += bufferSize;
    }
    return SampleBuffer::read(pos);
}

#endif
