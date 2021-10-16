#ifndef pitchutil_h
#define pitchutil_h

#include <math.h>

inline float midiToFrequency(float midi) {
    return 440.0 * powf(2, (midi - 69.0) / 12.0);
}

inline float octaveToFrequency(float octave, float midFrequency = 440) {
    return midFrequency * powf(2, octave);
}


#endif