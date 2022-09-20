#ifndef AbstractController_h
#define AbstractController_h

#include "../util/CycleEnum.h"

class AbstractController {
    public:
        AbstractController(int lastMode = 0) : mode(0, lastMode) {}
        virtual void load() {};
        virtual void save() {};
        virtual void init() {};
        virtual void update() {};
        int cycleMode(int amount) { mode.cycle(amount); return mode.value; }
        void setMode(int value) { mode.setValue(value); }
    
    protected: 
        CycleEnum<int> mode;
};

#endif
