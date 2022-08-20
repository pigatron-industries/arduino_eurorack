#ifndef FocusManager_h
#define FocusManager_h

#include "../Component.h"

template<class G>
class FocusManager {

    public:
        FocusManager() {}
        void setFocus(Component<G>* component);

    private:
        Component<G>* focus = nullptr;

};

template<class G>
void FocusManager<G>::setFocus(Component<G>* component) {
    if(focus != nullptr) {
        focus->setFocus(false);
        focus->render();
    }
    focus = component;
    focus->setFocus(true);
    focus->render();
}



#endif
