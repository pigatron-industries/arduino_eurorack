#ifndef MemPool_h
#define MemPool_h

#include <stddef.h>
#include <Arduino.h>

template <class T = unsigned char>
class MemPool {
    public:
        MemPool(T* poolMem, size_t poolSize) : poolMem(poolMem), poolSize(poolSize) {}
        MemPool(size_t poolSize) : poolSize(poolSize) { poolMem = new T[poolSize]; }
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


template <class T>
T* allocateObject(MemPool<>* memPool = nullptr) {
    T* obj = nullptr;
    if(memPool == nullptr) {
        obj = new T();
    } else {
        T* mem = (T*)memPool->allocate(sizeof(T));
        obj = new(mem) T();
    }
    return obj;
}

template <class T>
T* allocateBuffer(size_t size, MemPool<>* memPool = nullptr) {
    T* buffer = nullptr;
    if(memPool == nullptr) {
        buffer = new T[size]();
    } else {
        T* mem = (T*)memPool->allocate(size * sizeof(T));
        buffer = mem;
    }
    return buffer;
}


#endif
