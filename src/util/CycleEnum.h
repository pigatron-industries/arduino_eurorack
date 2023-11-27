#ifndef CycleEnum_h
#define CycleEnum_h

template <class T>
class CycleEnum {
    public:
        T value;
        T last;

        CycleEnum() {
            this->value = 0;
            this->last = 0;
        }

        CycleEnum(T value, T last) {
            this->value = value;
            this->last = last;
        }

        T cycle(int amount) {
            if(amount > 0) {
                value = static_cast<T>((value + 1)%(last + 1));
            } else if(amount < 0) {
                value = static_cast<T>(value > 0 ? value - 1 : last);
            }
            return value;
        }

        T setValue(T value) {
            if(value > last) {
                this->value = value % (last + 1);
            } else if (value < 0) {
                this->value = value + (last + 1);
            } else {
                this->value = value;
            }
            
            return value;
        }

        T getValue() {
            return value;
        }

        const T operator=(const T& other) {
            return setValue(other);
        }

        const T operator-(const T& other) const {
            T returnValue = value - other;
            if(returnValue < 0) {
                return returnValue + (last + 1);
            } else {
                return returnValue;
            }
        }

        const T operator+(const T& other) const {
            T returnValue = value + other;
            if(returnValue > last) {
                return returnValue % (last + 1);
            } else {
                return returnValue;
            }
        }
};

#endif