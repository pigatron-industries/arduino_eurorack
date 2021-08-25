#ifndef util_h
#define util_h

#define M_PI 3.14159265358979323846f
#define ONE_OVER_ROOT_TWO 0.70710678

inline float smooth(float currentValue, float prevValue, float smoothing = 0.2) {
    return (currentValue*smoothing) + prevValue*(1-smoothing);
}

inline int cycleIndex(int value, int size, int direction) {
    if(direction < 0) {
        return value == 0 ? size-1 : value-1;
    } else if (direction > 0) {
        return (value+1) % size;
    }
}

#endif