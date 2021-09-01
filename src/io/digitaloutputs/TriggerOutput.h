#ifndef TriggerOutput_h
#define TriggerOutput_h

#include "../../hardware/native/DigitalOutputPin.h"

template<class T = DigitalOutputPin>
class TriggerOutput {

    public:
        TriggerOutput(T output, unsigned long durationMicros = 1000) : output(output) {
            duration = durationMicros;
        }

        void update() {  
            if(triggered && timer.hasJustStopped()) {
                triggered = false; 
                output.setValue(false);   
            }
        }

        void trigger() { 
            triggered = true; 
            output.setValue(true); 
            timer.start(duration); 
        }

        void setValue(bool value) {
            output.setValue(value);
        }

        void setTriggerDurationMicros(unsigned long duration) { this->duration = duration; }

    protected:
        T output;
        bool triggered;
        unsigned long duration;
        Timer timer;

};

#endif
