#ifndef util_h
#define util_h

inline float smooth(float currentValue, float prevValue, float smoothing = 0.2) {
    return (currentValue*smoothing) + prevValue*(1-smoothing);
}

#endif