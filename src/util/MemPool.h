#ifndef MemPool_h
#define MemPool_h

#include <stddef.h>

class MemPool {
    public:
        MemPool(char* poolMem, size_t poolSize);
        void* allocate(size_t size);
        void reset();
    private:
        char* poolMem;
        size_t poolSize;
        size_t poolIndex;
};


#endif
