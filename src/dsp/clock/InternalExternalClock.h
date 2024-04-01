#ifndef InternalExternalClock_h
#define InternalExternalClock_h

#include "Clock.h"
#include "ClockDivider.h"

class InternalExternalClock : public Clock {
    public:
        enum State {
            CLK_INTERNAL, CLK_EXTERNAL_WAITING, CLK_EXTERNAL
        };
        enum MultiplierDivider {
            CLK_NONE, CLK_MULTIPLIER, CLK_DIVIDER
        };

        void externalTick();
        void setFrequency(float frequency);
        void setFrequencyMultiplierDivider(MultiplierDivider type, int value);
        
        State getState() { return state; }
        bool process();

    protected:
        virtual bool processExternal();
        virtual bool processInternal();

    private:
        State state = CLK_INTERNAL;
        bool externalTicked;

        float externalTimeCounter = 0;
        float externalTime = 0;
        float externalWaitTime;

        MultiplierDivider frequencyMultiplierDividerType = CLK_NONE;
        int frequencyMultiplierDivider = 1;
        ClockDivider clockDivider;
        int multiplierCounter = 0;
};

#endif
