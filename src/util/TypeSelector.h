#ifndef TypeSelector_h
#define TypeSelector_h

#include <tuple>
#include "Array.h"

template<size_t I = 0, typename Func, typename... Ts>
inline typename std::enable_if<I == sizeof...(Ts), void>::type
for_each(std::tuple<Ts...> &, Func) {}

template<size_t I = 0, typename Func, typename... Ts>
inline typename std::enable_if<I < sizeof...(Ts), void>::type
for_each(std::tuple<Ts...>& t, Func func) {
    func(&std::get<I>(t));
    for_each<I + 1, Func, Ts...>(t, func);
}

/**
 * Select an object from an array of objects. 
 * T is the class of all the objects.
 * N is the number of objects.
 * Objects are automatically instantated using default constructor.
 */
template<class T, int N>
class ArraySelector {
    public:
        ArraySelector() {}  
        ArraySelector(std::initializer_list<T> list) : items(list) {}
        T& operator[](int i) { return items[i]; }
        const T& operator[](int i) const { return items[i]; }
        T& getSelected() { return items[selectedIndex]; }
        size_t getSelectedIndex() { return selectedIndex; }
        Array<T, N>& getItems() { return items; }

        T& select(size_t i) { 
            if(i < N) {
                selectedIndex = i;
            }
            return getSelected();
        }

        T& increment() {
            selectedIndex = (selectedIndex + 1) % N;
            return getSelected();
        }

        T& decrement() {
            selectedIndex = selectedIndex > 0 ? selectedIndex - 1 : N - 1;
            return getSelected();
        }

        T& cycle(int direction) {
            if(direction > 0) {
                return increment();
            } else if(direction < 0) {
                return decrement();
            }
            return getSelected();
        }

        unsigned int getSize() {
            return N;
        }

    protected:
        Array<T, N> items;
        size_t selectedIndex;
};


/**
 * Select a type instance from a list of types.
 * B is the base class of all the objects.
 * Ts are the classes of each item in the list.
 * Default constructor automatically instantiates the types using their default constructors.
 * Instances can be passed into the constructor to use pre-constructed objects.
 */
template<class B, class... Ts>
class TypeSelector : public ArraySelector<B*, sizeof...(Ts)> {
    public:
        TypeSelector() { 
            buildList();
        }

        TypeSelector(Ts&&... args) : objects(args...) { 
            buildList();
        }

        void buildList() {
            for_each(objects, [this](B* object) {
                this->items.add(object);
            });
            ArraySelector<B*, sizeof...(Ts)>::select(0);
        }

        std::tuple<Ts...>& getObjects() { return objects; }

    protected:
        std::tuple<Ts...> objects;
};

#endif