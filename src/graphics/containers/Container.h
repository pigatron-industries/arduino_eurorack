#ifndef Container_h
#define Container_h

#include "../Component.h"
#include "../../util/Array.h"

template<class G, int N>
class Container : public Component<G> {

public:
    Container() {}
    virtual void setContext(G* graphicsContext);
    virtual void render();
    void addComponent(Component<G>* component);

protected:
    Array<Component<G>*, N> components;

};


template<class G, int N>
void Container<G, N>::setContext(G* graphicsContext) {
    this->graphicsContext = graphicsContext;
    for(Component<G>* component : components) {
        component->setContext(graphicsContext);
    }
}


template<class G, int N>
void Container<G, N>::render() {
    for(Component<G>* component : components) {
        component->render();
    }
}

template<class G, int N>
void Container<G, N>::addComponent(Component<G>* component) {
    components.add(component);
}

#endif
