#ifndef FieldComponent_h
#define FieldComponent_h

#include <inttypes.h>
#include "TextComponent.h"
#include "../Component.h"

#ifndef EU_FOCUS_COLOUR
    #define EU_FOCUS_COLOUR 0
#endif

template<class G>
class FieldComponent : public Component<G> {

public:
    static const int MAX_LABEL_LENGTH = 32;
    static const int MAX_VALUE_LENGTH = 32;

    FieldComponent(uint16_t width, uint16_t labelWidth, const char* label = "", uint8_t font = 1, uint16_t colourText = 0xFFFF);
    virtual void layout();
    virtual void render();

    void setLabel(const char* text);
    void setValue(const char* value);
    void setValue(int value);

protected:
    char label[MAX_LABEL_LENGTH];
    char value[MAX_VALUE_LENGTH];

    uint16_t labelWidth;
    uint8_t font;
    uint16_t colourText;
    uint16_t colourFocus = EU_FOCUS_COLOUR;
    uint8_t paddingTop = 1;
    uint8_t paddingBottom = 1;

    uint16_t valueLeft;
    uint16_t valueWidth;
    uint16_t textTop;

    void renderLabel();
    void renderValue();
};


template<class G>
FieldComponent<G>::FieldComponent(uint16_t width, uint16_t labelWidth, const char* label, uint8_t font, uint16_t colourText) {
    this->setHeight(TextComponent<G>::DEFAULT_HEIGHT);
    this->setLabel(label);
    this->setWidth(width);
    this->labelWidth = labelWidth;
    this->font = font;
    this->colourText = colourText;
}

template<class G>
void FieldComponent<G>::layout() {
    valueLeft = this->left + labelWidth;
    valueWidth = this->width - valueLeft;
    textTop = this->top + paddingTop;
    this->setHeight(this->graphicsContext->getFontHeight(font) + paddingTop + paddingBottom);
}

template<class G>
void FieldComponent<G>::render() {
    renderLabel();
    renderValue();
}

template<class G>
void FieldComponent<G>::renderLabel() {
    this->graphicsContext->setFont(font);
    this->graphicsContext->setTextColour(colourText);
    this->graphicsContext->text(&label[0], this->left, textTop);
}

template<class G>
void FieldComponent<G>::renderValue() {
    this->graphicsContext->fillRectangle(this->valueLeft, this->top, valueWidth, this->height, this->focus ? colourFocus : 0);
    this->graphicsContext->setFont(font);
    this->graphicsContext->setTextColour(colourText);
    this->graphicsContext->text(&value[0], this->valueLeft, textTop);
}

template<class G>
void FieldComponent<G>::setLabel(const char* label) {
    strncpy(this->label, label, MAX_LABEL_LENGTH);
}

template<class G>
void FieldComponent<G>::setValue(const char* value) {
    strncpy(this->value, value, MAX_VALUE_LENGTH);
    renderValue();
}

template<class G>
void FieldComponent<G>::setValue(int value) {
    snprintf_P(this->value, MAX_VALUE_LENGTH, PSTR("%d"), value);
    renderValue();
}


#endif