#ifndef eur_TriggerInput_h
#define eur_TriggerInput_h

#include "../../hardware/device/DevicePin.h"
#include <inttypes.h>

#define MAX_INTERRUPT_TRIGGERS 4

namespace eurorack {

    template<class T = NativeDevice>
    class TriggerInput {

    public:
        TriggerInput(DigitalInputPin<T>& inputPin, bool inverted = true, uint8_t interruptPin = -1);
        bool getValue() { return value; } 
        bool rose() { return inverted ? didFallInternal() : didRiseInternal(); }
        bool fell() { return inverted ? didRiseInternal() : didFallInternal(); }
        bool update(); // need to call update if pin doesn't use interrupt

    private:
        DigitalInputPin<T>& inputPin;
        bool value;
        bool inverted;
        uint8_t interruptPin;
        bool interruptFired;

        bool didRise;
        bool didFall;

        static TriggerInput<T>* interruptInputs[MAX_INTERRUPT_TRIGGERS];
        static uint8_t interruptInputCount;
        static void interrupt();

        void setValue(bool value) { 
            this->value = value;
            this->didRise = didRise || value;
            this->didFall = didFall || !value;
        }

        bool didRiseInternal() {
            bool returnValue = didRise;
            didRise = false;
            return returnValue;
        }

        bool didFallInternal() {
            bool returnValue = didFall;
            didFall = false;
            return returnValue;
        }
    };


    template<class T>
    uint8_t TriggerInput<T>::interruptInputCount = 0;

    template<class T>
    TriggerInput<T>* TriggerInput<T>::interruptInputs[MAX_INTERRUPT_TRIGGERS];

    template<class T>
    TriggerInput<T>::TriggerInput(DigitalInputPin<T>& inputPin, bool inverted, uint8_t interruptPin) : inputPin(inputPin) {
        this->inverted = inverted;
        this->interruptPin = interruptPin;
        value = inputPin.digitalRead();
        if(interruptPin >= 0) {
            interruptInputs[interruptInputCount] = this;
            interruptInputCount++;
            attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt, CHANGE);
        }
    }

    template<class T>
    void TriggerInput<T>::interrupt() {
        for(uint8_t i = 0; i < interruptInputCount; i++) {
            TriggerInput<T>* triggerInput = interruptInputs[i];
            bool value = triggerInput->inputPin.digitalRead();
            if(value != triggerInput->getValue()) {    
                triggerInput->setValue(value);
                triggerInput->interruptFired = true;
            }
        }
    }

    template<class T>
    bool TriggerInput<T>::update() {
        bool updatedValue = inputPin.digitalRead();
        if(updatedValue != value || interruptFired) {
            setValue(updatedValue);
            interruptFired = false;
            return true;
        }
        return false;
    }
}

#endif
