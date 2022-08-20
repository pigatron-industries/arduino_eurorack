#ifndef GraphicsContext_h
#define GraphicsContext_h

#include <inttypes.h>

class GraphicsContext {
    public:
        GraphicsContext() {}
        virtual void init() = 0;

        virtual void clear() = 0;
        virtual void update() = 0;

        // display info
        virtual uint16_t getWidth() = 0;
        virtual uint16_t getHeight() = 0;

        // fonts
        virtual void setFont(uint8_t font) = 0;
        virtual uint16_t getFontHeight(uint8_t font) = 0;
        virtual uint16_t getFontWidth(uint8_t font) = 0;

        // colours
        virtual void setTextColour(uint16_t colour) = 0;

        // text
        virtual void text(const char* text, uint8_t x = 0, uint8_t y = 0) = 0;

        // shapes
        virtual void fillRectangle(int x, int y, int w, int h, int color) = 0;
        virtual void drawRectangle(int x, int y, int w, int h, int color) = 0;
    
    protected: 
};

#endif
