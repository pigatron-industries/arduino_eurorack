#ifndef Array_h
#define Array_h

template<class T, int MAXSIZE>
class Array {

    public:
        int _size = 0;
        T items[MAXSIZE];

        T& operator [] (int i) { return items[i]; }
        int size() { return _size; }
        int add(const T& item) {
            items[_size] = item;
            return _size++;
        }
        void clear() {
            _size = 0;
        }

};

#endif