#ifndef Component_h
#define Component_h

#include <Arduino.h>
#include "GraphicsContext.h"

template<class G>
class Component {

public:
    Component() {}
    virtual void setContext(G* graphicsContext);
    virtual void layout() {};
    virtual void render() = 0;

    uint16_t getTop() { return top; }
    uint16_t getLeft() { return left; }
    uint16_t getHeight() { return height; }
    uint16_t getWidth() { return width; }
    bool isVisibile() { return visible; }
    bool isFocusable() { return focusable; }

    void setTop(uint16_t top) { this->top = top; }
    void setLeft(uint16_t left) { this->left = left; }
    void setHeight(uint16_t height) { this->height = height; }
    void setWidth(uint16_t width) { this->width = width; }
    void setVisibility(bool visible) { this->visible = visible; }
    void setFocusable(bool focusable) { this->focusable = focusable; }

    void setFocus(bool focus) { this->focus = focus; }

protected:
    G* graphicsContext = nullptr;

    uint16_t top = 0;
    uint16_t left = 0;
    uint16_t height = 0;
    uint16_t width = 0;
    bool visible = true;
    bool focusable = false;
    bool focus = false;

};

template<class G>
void Component<G>::setContext(G* graphicsContext) {
    this->graphicsContext = graphicsContext;
}


#endif
