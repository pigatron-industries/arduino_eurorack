#ifndef ObjectManager_h
#define ObjectManager_h

#include "MemPool.h"
#include "../util/LinkedList.h"

template <class T = char>
class ObjectManager {
    public:
        ObjectManager(MemPool<>& memPool) : memPool(memPool), objects(memPool) {}
        T* add(T& t);

    private:
        MemPool<>& memPool;

        LinkedList<T> objects;
};

template <class T>
T* ObjectManager<T>::add(T& t) {
    return objects.add(t);

}


#endif
