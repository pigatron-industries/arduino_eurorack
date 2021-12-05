#ifndef TriggerOutput_h
#define TriggerOutput_h

#include "../../hardware/device/DevicePin.h"
#include "../../hardware/native/NativeDevice.h"

template<class T = NativeDevice>
class TriggerOutput {

    public:
        TriggerOutput(DigitalOutputPin<T>& output, unsigned long durationMicros = 1000) : output(output) {
            duration = durationMicros;
        }

        void update() {  
            if(triggered && timer.hasJustStopped()) {
                triggered = false; 
                output.digitalWrite(false);   
            }
        }

        void trigger() { 
            triggered = true; 
            output.digitalWrite(true);
            timer.start(duration); 
        }

        void setValue(bool value) {
            output.digitalWrite(value);
        }

        void setTriggerDurationMicros(unsigned long duration) { this->duration = duration; }

    protected:
        DigitalOutputPin<T>& output;
        bool triggered;
        unsigned long duration;
        Timer timer;

};

#endif
