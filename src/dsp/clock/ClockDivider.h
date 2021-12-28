#ifndef ClockDivider_h
#define ClockDivider_h

class ClockDivider {
    public:
        ClockDivider(int divisor = 1) {
            this->divisor = divisor;
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
            counter = -1;
        }

        void setDivisor(int divisor) {
            this->divisor = divisor;
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
        bool triggered;
        
};

#endif
