#include "MemPool.h"
#include <Arduino.h>

MemPool::MemPool(char* poolMem, size_t poolSize) : poolMem(poolMem), poolSize(poolSize) {
}

void* MemPool::allocate(size_t size) {
    if (poolIndex + size >= poolSize) {
        Serial.println("Pool memory space exceeded");
        return 0;
    }
    void* ptr = &poolMem[poolIndex];
    poolIndex += size;
    return ptr;
}

void MemPool::reset() {
    poolIndex = 0;
}
