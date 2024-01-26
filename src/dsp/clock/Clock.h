#ifndef Clock_h
#define Clock_h

class Clock {
    public:
        void init(float sampleRate);
        void setFrequency(float frequency);
        void reset();
        float getFrequency() { return frequency; } 
        bool process();

        float getPhaseIncrement() { return phaseInc; }
        float getPhase() { return phase; }

    protected:
        void setPhaseMax(float phaseMax) { this->phaseMax = phaseMax; }

        float sampleRate, sampleTime;

        float frequency;
        float phaseInc;
        float phase = 1.0;
        float phaseMax = 1.0;
};

#endif
