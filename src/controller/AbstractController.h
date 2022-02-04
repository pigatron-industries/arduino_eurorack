#ifndef AbstractController_h
#define AbstractController_h

class AbstractController {
    public:
        AbstractController() {}
        virtual void init(float sampleRate) {}
        virtual void init() {}
        virtual void setMode() {}
        virtual void update() {}
};

#endif
