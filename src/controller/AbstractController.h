#ifndef AbstractController_h
#define AbstractController_h

#include "../util/CycleEnum.h"

class AbstractController {
    public:
        AbstractController(int lastMode = 0) : mode(0, lastMode) {}
        virtual void load() {}
        virtual void save() {}
        virtual void init() {}
        virtual void update() {}
        virtual int cycleMode(int amount) { mode.cycle(amount); this->save(); return mode.value; }
        virtual void cycleValue(int amount) { mode.cycle(amount); this->save(); init(); }
        virtual void setMode(int value) { mode.setValue(value); }
    
    protected: 
        CycleEnum<int> mode;
};

#endif
