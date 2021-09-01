#ifndef AnalogTriggerOutput_h
#define AnalogTriggerOutput_h

#include "../../hardware/native/AnalogOutputPin.h"

template<class T = AnalogOutputPin>
class AnalogTriggerOutput {

    public:
        AnalogTriggerOutput(T output, unsigned long durationMicros = 1000, float triggerVoltage = 5) : output(output) {
            this->duration = durationMicros;
            this->triggerVoltage = triggerVoltage;
        }

        void update() {  
            if(triggered && timer.hasJustStopped()) {
                triggered = false; 
                output.writeVoltage(0);
            }
        }

        void trigger() { 
            triggered = true; 
            output.writeVoltage(triggerVoltage); 
            timer.start(duration); 
        }

        void setVoltage(float voltage) {
            output.writeVoltage(voltage);
        }

        void setTriggerDurationMicros(unsigned long duration) { this->duration = duration; }

    protected:
        T output;
        bool triggered;
        unsigned long duration;
        float triggerVoltage;
        Timer timer;

};

#endif
