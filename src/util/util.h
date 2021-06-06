#ifndef util_h
#define util_h

inline float smooth(float currentValue, float prevValue, float smoothing = 0.2) {
    return (currentValue*smoothing) + prevValue*(1-smoothing);
}

inline int cycle(int value, int max, int direction) {
    if(direction < 0) {
        return value == 0 ? max : value-1;
    } else if (direction > 0) {
        return (value+1) % max+1;
    }
}

#endif