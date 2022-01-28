#ifndef ClockDivider_h
#define ClockDivider_h

class ClockDivider {
    public:
        ClockDivider(int divisor = 1, int offset = 0) {
            this->divisor = divisor;
            this->offset = offset;
            reset();
        }

        bool tick() {
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

        void reset() {
            counter = -1 + offset;
        }

        void setDivisor(int divisor) {
            this->divisor = divisor;
        }

        void setOffset(int offset) {
            this->offset = offset;
        }

        bool getAndResetTrigger() {
            if(triggered) {
                triggered = false;
                return true;
            } else {
                return false;
            }
        }

    private:
        int counter = -1;
        int divisor = 1;
        int offset = 0;
        bool triggered;
        
};

#endif
