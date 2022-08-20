#ifndef VerticalContainer_h
#define VerticalContainer_h

#include "Container.h"

template<class G, int N>
class VerticalContainer : public Container<G, N> {

public:
    VerticalContainer() {}
    virtual void layout();
};


template<class G, int N>
void VerticalContainer<G, N>::layout() {
    int childTop = this->top;
    for(Component<G>* component : this->components) {
        component->setTop(childTop);
        component->setLeft(0);
        component->layout();
        childTop += component->getHeight();
    }
    this->height = childTop;
}

#endif
