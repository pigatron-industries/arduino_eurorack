#ifndef Array_h
#define Array_h

template<class T, int MAXSIZE>
class Array {

    public:
        int size = 0;
        T items[MAXSIZE];

        T& operator [] (int i) { return items[i]; }
        int size() { return size; }
        int add(const T& item) {
            items[size] = item;
            return size++;
        }
        void clear() {
            size = 0;
        }

};

#endif