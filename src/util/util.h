#ifndef util_h
#define util_h

inline int cycleIndex(int value, int size, int direction) {
    if(direction < 0) {
        return value == 0 ? size-1 : value-1;
    } else if (direction > 0) {
        return (value+1) % size;
    }
}

#endif