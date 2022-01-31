#ifndef ObjectSelector_h
#define ObjectSelector_h

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

template<class B, class... Ts>
class ObjectSelector {
    public:
        ObjectSelector() { 
            buildList();
            select(0);
        }

        void buildList() { 
            int i = 0;
            for_each(objects, [this, &i](B* object) {
                Serial.println(i);
                Serial.println((int)object);
                this->objectPtrs[i] = object;
                i++;
            });
            select(0);
        }

        B* operator [] (int i) const { return objectPtrs[i]; }
        B* getSelected() { return selected; }

        B* select(int n) { 
            selectedIndex = 0; 
            selected = objectPtrs[n]; 
            return selected; 
        }

        B* increment() {
            selectedIndex = ((selectedIndex + 1) % (sizeof...(Ts)));
            selected = objectPtrs[selectedIndex];
            return selected;
        }

        B* decrement() {
            selectedIndex = selectedIndex > 0 ? selectedIndex - 1 : (sizeof...(Ts)) - 1;
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
        std::tuple<Ts...> objects;
        B* objectPtrs[sizeof...(Ts)];
        size_t selectedIndex;
        B* selected;
};

#endif