#ifndef CycleEnum_h
#define CycleEnum_h

template <class T>
class CycleEnum {
    public:
        T value;
        T last;

        CycleEnum(T value, T last) {
            this->value = value;
            this->last = last;
        }

        T cycle(int amount) {
            if(amount > 0) {
                value = static_cast<T>((value + 1)%(last + 1));
            } else {
                value = static_cast<T>(value > 0 ? value - 1 : last);
            }
            return value;
        }
};

#endif