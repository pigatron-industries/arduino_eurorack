#ifndef AbstractMainController_h
#define AbstractMainController_h

#include <eurorack.h>
#include "Config.h"

#define CHANNELS 4
#define OUTPUTS 8

class ModeConfig {
    public:
        uint8_t controllerIndex;
        uint8_t controllerMode;
};


template <class T, int N>
class AbstractMainController {
    public:
        AbstractMainController(RotaryEncoder& encoder, PushButton<>& encoderButton) : 
            encoder(encoder), encoderButton(encoderButton) {}

        void init();
        void update();

        void registerController(T& controller);

    protected:
        ObjectSelector<T, N> controllers;

        RotaryEncoder& encoder;
        PushButton<>& encoderButton;

        ConfigField<ModeConfig> configMode;

        virtual void controllerInit();
        void updateEncoder();
};


template <class T, int N>
void AbstractMainController<T, N>::init() {
    Eurorack::init();
    Config::config.load(configMode);
    controllers.select(configMode.data.controllerIndex);
    controllers.getSelected()->setMode(configMode.data.controllerMode);
    controllerInit();
}

template <class T, int N>
void AbstractMainController<T, N>::update() {
    updateEncoder();
    controllers.getSelected()->update();
}

template <class T, int N>
void AbstractMainController<T, N>::registerController(T& controller) {
    controllers.addItem(&controller);
}

template <class T, int N>
void AbstractMainController<T, N>::controllerInit() {
    configMode.data.controllerIndex = controllers.getSelectedIndex();
    Config::config.save(configMode);
    controllers.getSelected()->init();
}

template <class T, int N>
void AbstractMainController<T, N>::updateEncoder() {
    encoderButton.update();
    bool cycled = false;
    if(encoder.update()) {
        if(encoderButton.held()) {
            //change controller when button held down
            if(encoder.getMovement() != 0) {
                cycled = true;
                controllers.cycle(encoder.getMovement());
                controllerInit();
            }
        } else {
            //change controller mode
            if(encoder.getMovement() != 0) {
                configMode.data.controllerMode = controllers.getSelected()->cycleMode(encoder.getMovement());
                Serial.print("Mode: ");
                Serial.println(configMode.data.controllerMode);
                controllers.getSelected()->init();
                Config::config.save(configMode);
            }
        }
    }
    if(encoderButton.released()) {
        if(!cycled) {
            controllerInit();
        }
    }
}

#endif