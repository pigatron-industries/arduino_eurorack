#ifndef Clock_h
#define Clock_h

class Clock {
    public:
        enum State {
            CLK_INTERNAL, CLK_EXTERNAL_WAITING, CLK_EXTERNAL
        };

        void init(float sampleRate);
        void setFrequency(float frequency);
        void reset();
        void externalTick();

        bool process();

    private:
        float sampleRate, sampleTime;

        float frequency;
        float phaseInc;
        float phase = 0;

        State state = CLK_INTERNAL;
        bool externalTicked;

        float externalTimeCounter = 0;
        float externalTime = 0;
        float externalWaitTime;

        bool processInternal();
        bool processExternal();
};


inline bool Clock::process() {
    switch(state) {
        case CLK_EXTERNAL_WAITING:
            externalTimeCounter += sampleTime;
        case CLK_INTERNAL:
            return processInternal();
        case CLK_EXTERNAL:
            return processExternal();
    }
    return false;
}

inline bool Clock::processInternal() {
    phase += phaseInc;
    if(phase > 1.0f) {
        phase -= 1.0f;
        return true;
    } else if (phase < 0.0f) {
        phase += 1.0f;
        return true;
    }
    return false;
}

inline bool Clock::processExternal() {
    externalTimeCounter += sampleTime;
    if(externalTicked) {
        externalTicked = false;
        return true;
    } else {
        if(externalTimeCounter > externalWaitTime) {
            state = CLK_INTERNAL;
        }
        return false;
    }
}

#endif
