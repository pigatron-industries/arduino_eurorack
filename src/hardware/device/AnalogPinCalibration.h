#ifndef AnalogPinCalibration_h
#define AnalogPinCalibration_h

#include <eurorack.h>

class AnalogPinCalibration {
    public:
        AnalogPinCalibration() {
        }

        void calibratePin(AbstractAnalogPin* pin) {
            this->analogPin = pin;
            increment = analogPin->getScale().convert(0) - analogPin->getScale().convert(1);
        }

        void offset(int amount) {
            analogPin->getCalibratedScale().offset(increment * amount);
        }

        void scale(int amount) {
            analogPin->getCalibratedScale().scale(increment * amount);
        }

        void reset() {
            analogPin->getCalibratedScale().setInputRange(analogPin->getScale().getFromMin(), analogPin->getScale().getFromMax());
            analogPin->getCalibratedScale().setOutputRange(analogPin->getScale().getToMin(), analogPin->getScale().getToMax());
        }

        float convertReverse(float value) {
            return analogPin->getCalibratedScale().convertReverse(value);
        }

        float convert(float value) {
            return analogPin->getCalibratedScale().convert(value);
        }

    private:
        AbstractAnalogPin* analogPin = nullptr;
        float increment = 0;
};

#endif