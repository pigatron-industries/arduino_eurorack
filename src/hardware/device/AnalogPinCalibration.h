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

        AbstractAnalogPin* getPin() {
            return analogPin;
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

        int16_t getDigitalOffset() {
            int16_t zeroPoint = analogPin->getScale().convertReverse(0);
            int16_t calibratedZeroPoint = analogPin->getCalibratedScale().convertReverse(0);
            return calibratedZeroPoint - zeroPoint;
        }

        int16_t getDigitalScale() {
            int16_t positivePoint = analogPin->getScale().convertReverse(1);
            int16_t negativePoint = analogPin->getScale().convertReverse(-1);
            int16_t calibratedPositivePoint = analogPin->getCalibratedScale().convertReverse(1);
            int16_t calibratedNegativePoint = analogPin->getCalibratedScale().convertReverse(-1);
            int16_t scale = negativePoint - positivePoint;
            int16_t calibratedScale = calibratedNegativePoint - calibratedPositivePoint;
            return calibratedScale - scale;
        }

    private:
        AbstractAnalogPin* analogPin = nullptr;
        float increment = 0;
};

#endif