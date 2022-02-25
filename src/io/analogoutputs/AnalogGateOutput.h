#ifndef AnalogGateOutput_h
#define AnalogGateOutput_h

#include "../../hardware/device/DevicePin.h"
#include "../../hardware/native/NativeDevice.h"

template<class T = NativeDevice>
class AnalogGateOutput {

    public:
        AnalogGateOutput(AnalogOutputPin<T>& output, float gateVoltage = 5) : output(output) {
            this->gateVoltage = gateVoltage;
        }

        void gate(bool value) { 
            output.analogWrite(value ? gateVoltage : 0);
        }

    protected:
        AnalogOutputPin<T>& output;
        float gateVoltage;

};

#endif
