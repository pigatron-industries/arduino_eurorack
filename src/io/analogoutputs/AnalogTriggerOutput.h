#ifndef AnalogTriggerOutput_h
#define AnalogTriggerOutput_h

#include "../../hardware/device/DevicePin.h"
#include "../../hardware/native/NativeDevice.h"
#include "../../util/Timer.h"

template<class T = NativeDevice>
class AnalogTriggerOutput {

    public:
        AnalogTriggerOutput(AnalogOutputPin<T>& output, unsigned long durationMicros = 20000, float triggerVoltage = 5) : output(output) {
            this->duration = durationMicros;
            this->triggerVoltage = triggerVoltage;
        }

        void setDuration(unsigned long durationMillis) {
            duration = durationMillis;
        }

        void update() {  
            if(triggered && timer.hasJustStopped()) {
                triggered = false; 
                output.analogWrite(0);
            }
        }

        void trigger() { 
            triggered = true; 
            output.analogWrite(triggerVoltage); 
            timer.start(duration); 
        }

        void setVoltage(float voltage) {
            output.analogWrite(voltage);
        }

        void setTriggerDurationMicros(unsigned long duration) { this->duration = duration; }

    protected:
        AnalogOutputPin<T>& output;
        bool triggered;
        unsigned long duration;
        float triggerVoltage;
        Timer timer;

};

#endif
