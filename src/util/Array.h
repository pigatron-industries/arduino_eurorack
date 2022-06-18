#ifndef Array_h
#define Array_h

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
            for(int i = 0; i < size; i++) {
                add(initItem);
            }
        }
        Array(std::initializer_list<T> list) {
            for(auto& item : list) {
                add(item);
            }
        }

        T& operator[](int i) { return items[i]; }
        const T& operator[](int i) const { return items[i]; }
        
        int size() { return _size; }

        int add(const T& item) {
            items[_size] = item;
            return _size++;
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