#ifndef MessageBoxComponent_h
#define MessageBoxFieldComponent_h

#include <inttypes.h>
#include "TextComponent.h"
#include "../Component.h"


template<class G>
class MessageBoxComponent : public Component<G> {

public:
    MessageBoxComponent(uint16_t width, uint16_t height, uint8_t font = 1, uint16_t colourText = 0xFFFF);
    virtual void layout();
    virtual void render();
    void showMessage(const char* message);

protected:
    uint8_t font;
    uint16_t colourText;

    const char* message;
    uint16_t textLeft;
    uint16_t textTop;
};


template<class G>
MessageBoxComponent<G>::MessageBoxComponent(uint16_t width, uint16_t height, uint8_t font, uint16_t colourText) {
    this->setHeight(height);
    this->setWidth(width);
    this->font = font;
    this->colourText = colourText;
}

template<class G>
void MessageBoxComponent<G>::layout() {
    this->setLeft((this->graphicsContext->getWidth() - this->getWidth()) * 0.5);
    this->setTop((this->graphicsContext->getHeight() - this->getHeight()) * 0.5);
    textTop = (this->graphicsContext->getHeight() - this->graphicsContext->getFontHeight(font)) * 0.5;
}

template<class G>
void MessageBoxComponent<G>::render() {
    this->graphicsContext->fillRectangle(this->left, this->top, this->width, this->height, 0);
    this->graphicsContext->drawRectangle(this->left, this->top, this->width, this->height, colourText);
    this->graphicsContext->setFont(font);
    this->graphicsContext->setTextColour(colourText);
    this->graphicsContext->text(message, textLeft, textTop);
}

template<class G>
void MessageBoxComponent<G>::showMessage(const char* message) {
    this->message = message;
    textLeft = (this->graphicsContext->getWidth() - (strlen(message)*this->graphicsContext->getFontWidth(font))) * 0.5;
    render();
}

#endif