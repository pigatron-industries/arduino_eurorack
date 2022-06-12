#ifndef ObjectManager_h
#define ObjectManager_h

#include "MemPool.h"
#include "../util/LinkedList.h"

template <class T = char>
class ObjectManager {
    public:
        ObjectManager(MemPool<>& memPool) : memPool(memPool), objects(memPool) {}

    private:
        MemPool<>& memPool;

        LinkedList<T> objects;
};

// template <class T>
// T* MemPool<T>::allocate(size_t size) {
//     if (poolIndex + size >= poolSize) {
//         Serial.println("Pool memory space exceeded");
//         return 0;
//     }
//     T* ptr = &poolMem[poolIndex];
//     poolIndex += size;
//     return ptr;
// }


#endif
