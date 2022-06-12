#ifndef MemPool_h
#define MemPool_h

#include <stddef.h>
#include <Arduino.h>

template <class T = char>
class MemPool {
    public:
        MemPool(T* poolMem, size_t poolSize) : poolMem(poolMem), poolSize(poolSize) {}
        T* allocate(size_t size);
        void reset();
    private:
        T* poolMem;
        size_t poolSize;
        size_t poolIndex;
};

template <class T>
T* MemPool<T>::allocate(size_t size) {
    if (poolIndex + size >= poolSize) {
        Serial.println("Pool memory space exceeded");
        return 0;
    }
    T* ptr = &poolMem[poolIndex];
    poolIndex += size;
    return ptr;
}

template <class T>
void MemPool<T>::reset() {
    poolIndex = 0;
}


#endif
