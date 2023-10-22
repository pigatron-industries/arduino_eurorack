#ifndef AbstractController_h
#define AbstractController_h

#include "../util/CycleEnum.h"

class AbstractController {
    public:
        AbstractController() {}
        virtual void load() {}
        virtual void save() {}
        virtual void init() {}
        virtual void update() {}
        virtual int cycleParameter(int amount) {}
        virtual void cycleValue(int amount) {}
        virtual void selectValue() {}
};


#endif
