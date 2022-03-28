#ifndef AnalogGateOutput_h
#define AnalogGateOutput_h

#include "../../hardware/device/DevicePin.h"
#include "../../hardware/native/NativeDevice.h"

template<class T = NativeDevice>
class AnalogGateOutput {

    public:
        AnalogGateOutput(AnalogOutputPin<T>& output, float gateVoltage = 5, float zeroVoltage = 0) : output(output) {
            this->gateVoltage = gateVoltage;
            this->zeroVoltage = zeroVoltage;
        }

        void gate(bool value) { 
            this->value = value;
            output.analogWrite(value ? gateVoltage : zeroVoltage);
        }

        void setZeroVoltage(float zeroVoltage) { 
            this->zeroVoltage = zeroVoltage;
            gate(value);
        }

    protected:
        AnalogOutputPin<T>& output;
        bool value;
        float gateVoltage;
        float zeroVoltage;

};

#endif
