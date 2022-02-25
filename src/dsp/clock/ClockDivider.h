#ifndef ClockDivider_h
#define ClockDivider_h

class ClockDivider {
    public:
        ClockDivider(int divisor = 1, int offset = 0);
        bool tick();
        void reset();

        void setDivisor(int divisor) { this->divisor = divisor; }
        void setOffset(int offset) { this->offset = offset; }

        bool getAndResetTrigger();

    private:
        int counter = -1;
        int divisor = 1;
        int offset = 0;
        bool triggered;
        
};

inline ClockDivider::ClockDivider(int divisor, int offset) {
    this->divisor = divisor;
    this->offset = offset;
    reset();
}

inline bool ClockDivider::tick() {
    counter++;
    if(counter >= divisor) {
        counter = 0;
    }

    if(counter == 0) {
        triggered = true;
        return true;
    } else {
        return false;
    }
}

inline void ClockDivider::reset() {
    counter = -1 + offset;
}

inline bool ClockDivider::getAndResetTrigger() {
    if(triggered) {
        triggered = false;
        return true;
    } else {
        return false;
    }
}

#endif
