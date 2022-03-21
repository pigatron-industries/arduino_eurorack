#ifndef Array_h
#define Array_h

template<class T, int MAXSIZE>
class Array {

    public:

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

    private:
        int _size = 0;
        T items[MAXSIZE];

};

#endif