#ifndef ClockGate_h
#define ClockGate_h

class ClockGate {
    public:
        ClockGate(int length = 1) {
            this->length = length;
        }

        void setLength(int length) {
            this->length = length;
        }

        bool tick(bool trigger) {
            if(trigger) {
                count = 0;
                gate = true;
            } else if(gate) {
                count++;
                if(count >= length) {
                    gate = false;
                }
            }

            return gate;
        }

        void reset() {
            count = 0;
            gate = false;
        }

    private:
        int length = 1;
        int count = 0;
        bool gate;
        
};

#endif
