#ifndef FieldComponent_h
#define FieldComponent_h

#include <inttypes.h>
#include "TextComponent.h"
#include "../Component.h"

#ifndef EU_FOCUS_COLOUR
    #define EU_FOCUS_COLOUR 1
#endif

template<class G>
class FieldComponent : public Component<G> {

public:
    static const int MAX_LABEL_LENGTH = 32;
    static const int MAX_VALUE_LENGTH = 32;

    FieldComponent(uint16_t width, uint16_t labelWidth, const char* label = "", uint8_t font = 1, uint16_t colourText = G::DEF_COLOUR_TEXT);
    virtual void layout();
    virtual void render();

    void setLabel(const char* text);
    void setFormat(const char* format);
    void setValue(const char* value);
    void setValue(int value);

protected:
    char label[MAX_LABEL_LENGTH];
    char value[MAX_VALUE_LENGTH];
    char* format = "%d";

    uint16_t labelWidth;
    uint8_t font;
    uint16_t colourText;
    uint16_t colourBack = G::DEF_COLOUR_BACK;
    uint16_t colourFocusText = G::DEF_COLOUR_FOCUS_TEXT;
    uint16_t colourFocusBack = G::DEF_COLOUR_FOCUS_BACK;
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
    valueWidth = this->width - labelWidth;
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
void FieldComponent<G>::setFormat(const char* format) {
    this->format = format;
}

template<class G>
void FieldComponent<G>::renderValue() {
    this->graphicsContext->fillRectangle(this->valueLeft, this->top, this->valueWidth, this->height, this->focus ? colourFocusBack : colourBack);
    this->graphicsContext->setFont(font);
    this->graphicsContext->setTextColour(this->focus ? colourFocusText : colourText);
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
    snprintf(this->value, MAX_VALUE_LENGTH, format, value);
    renderValue();
}


#endif