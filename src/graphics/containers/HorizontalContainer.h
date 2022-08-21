#ifndef HorizontalContainer_h
#define HorizontalContainer_h

#include "Container.h"

template<class G, int N>
class HorizontalContainer : public Container<G, N> {

public:
    HorizontalContainer() {}
    virtual void layout();
};


template<class G, int N>
void HorizontalContainer<G, N>::layout() {
    int childLeft = this->left;
    for(Component<G>* component : this->components) {
        component->setLeft(childLeft);
        component->setTop(this->top);
        component->layout();
        childLeft += component->getWidth();
        if(component->getHeight() > this->getWidth()) {
            this->setHeight(component->getHeight());
        }
    }
    this->setWidth(childLeft);
}

#endif
