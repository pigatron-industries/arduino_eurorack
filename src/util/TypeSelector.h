#ifndef TypeSelector_h
#define TypeSelector_h

#include <tuple>

template<size_t I = 0, typename Func, typename... Ts>
inline typename std::enable_if<I == sizeof...(Ts), void>::type
for_each(std::tuple<Ts...> &, Func) {}

template<size_t I = 0, typename Func, typename... Ts>
inline typename std::enable_if<I < sizeof...(Ts), void>::type
for_each(std::tuple<Ts...>& t, Func func) {
    func(&std::get<I>(t));
    for_each<I + 1, Func, Ts...>(t, func);
}

template<class B, int N>
class ObjectSelector {
    public:
        TypeSelector() {
            select(0);
        }
    
        B* operator [] (int i) const { return objectPtrs[i]; }
        B* getSelected() { return selected; }
        size_t getSize() { return N; }

        B* select(size_t i) { 
            selectedIndex = 0; 
            selected = objectPtrs[i]; 
            return selected; 
        }

        B* increment() {
            selectedIndex = (selectedIndex + 1) % N;
            selected = objectPtrs[selectedIndex];
            return selected;
        }

        B* decrement() {
            selectedIndex = selectedIndex > 0 ? selectedIndex - 1 : N - 1;
            selected = objectPtrs[selectedIndex];
            return selected;
        }

        B* cycle(int direction) {
            if(direction > 0) {
                return incrementController();
            } else if(direction < 0) {
                return decrementController();
            }
            return selected;
        }

    protected:
        B* objectPtrs[N];
        size_t selectedIndex;
        B* selected;
};

template<class B, class... Ts>
class TypeSelector : public ObjectSelector<B, sizeof...(Ts)> {
    public:
        TypeSelector() { 
            buildList();
        }

        void buildList() { 
            int i = 0;
            for_each(objects, [this, &i](B* object) {
                this->objectPtrs[i] = object;
                i++;
            });
            ObjectSelector<B, sizeof...(Ts)>::select(0);
        }

    protected:
        std::tuple<Ts...> objects;
};

#endif