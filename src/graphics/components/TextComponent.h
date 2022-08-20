#ifndef TextComponent_h
#define TextComponent_h

#include <inttypes.h>
#include "../Component.h"


template<class G>
class TextComponent : public Component<G> {

public:
    static const int MAX_LENGTH = 32;
    static const int DEFAULT_HEIGHT = 10;

    TextComponent(uint16_t width, const char* text = "", uint8_t font = 1, uint16_t colour = 0xFFFF);
    virtual void layout();
    virtual void render();

    void setText(const char* text);

protected:
    char text[MAX_LENGTH];
    uint8_t font;
    uint16_t colour;

};


template<class G>
TextComponent<G>::TextComponent(uint16_t width, const char* text, uint8_t font, uint16_t colour) {
    this->setHeight(DEFAULT_HEIGHT);
    this->setWidth(width);
    this->setText(text);
    this->font = font;
    this->colour = colour;
}

template<class G>
void TextComponent<G>::layout() {
    this->setHeight(this->graphicsContext->getFontHeight(font));
}

template<class G>
void TextComponent<G>::render() {
    this->graphicsContext->setFont(font);
    this->graphicsContext->setTextColour(colour);
    this->graphicsContext->text(&text[0], this->left, this->top);
}

template<class G>
void TextComponent<G>::setText(const char* text) {
    strncpy(this->text, text, MAX_LENGTH);
}

#endif
