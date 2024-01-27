#ifndef Array_h
#define Array_h

#include <Arduino.h>

// use ArrayPtr for pasing around arrays without needing to know the size at compile time.
template<class T>
class ArrayPtr {

    public:
        ArrayPtr(T* ptr, int size) : ptr(ptr), _size(size) {}
        T& operator[](int i) { return ptr[i]; }
        const T& operator[](int i) const { return ptr[i]; }
        int size() { return _size; }

    private:
        T* ptr;
        int _size = 0;
};


template<class T, int MAXSIZE>
class Array {

    public:

        Array() {}
        Array(T& initItem, int size) {
            init(initItem, size);
        }
        Array(std::initializer_list<T> list) {
            for(auto& item : list) {
                add(item);
            }
        }

        void init(T& initItem, int size) {
            clear();
            for(int i = 0; i < size; i++) {
                add(initItem);
            }
        }

        setItems(T* itemsptr, int size) {
            items = itemsptr;
            _size = size;
        }

        T& get(int i) { return items[i]; }
        T& operator[](int i) { return items[i]; }
        const T& operator[](int i) const { return items[i]; }
        
        int size() { return _size; }
        bool isFull() { return _size == MAXSIZE; }

        int add(const T& item) {
            if(_size == MAXSIZE) {
                Serial.println("ERROR: Array overflow!");
                return -1;
            }
            items[_size] = item;
            return _size++;
        }

        int remove(int index) {
            for(int i = index; i < _size-1; i++) {
                items[i] = items[i+1];
            }
            _size--;
            return _size;
        }

        void clear() {
            _size = 0;
        }

        bool contains(T& findItem) {
            for(int i = 0; i < _size; i++) {
                if(items[i] == findItem) {
                    return true;
                }
            }
            return false;
        }

        T* begin() { return &items[0]; }
        T* end() { return &items[_size]; }

        ArrayPtr<T> ptr() { return ArrayPtr<T>(&items[0], _size); }

    private:
        int _size = 0;
        T items[MAXSIZE];

};

#endif