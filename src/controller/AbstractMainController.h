#ifndef AbstractMainController_h
#define AbstractMainController_h

#include "Config.h"

class ModeConfig {
    public:
        uint8_t controllerIndex;
        uint8_t controllerMode;
};

template <class B, class... Ts>
class AbstractMainController {
    public:
        AbstractMainController(RotaryEncoder& encoder, PushButton<>& encoderButton) : 
            encoder(encoder), encoderButton(encoderButton) {}

        void init();
        void update();

    protected:
        TypeSelector<B, Ts...> controllers;

        RotaryEncoder& encoder;
        PushButton<>& encoderButton;

        ConfigField<ModeConfig> configMode;

        virtual void controllerInit();
        void updateEncoder();
};


template <class B, class... Ts>
void AbstractMainController<B, Ts...>::init() {
    Eurorack::init();
    Config::config.load(configMode);
    controllers.select(configMode.data.controllerIndex);
    controllers.getSelected()->setMode(configMode.data.controllerMode);
    controllerInit();
}

template <class B, class... Ts>
void AbstractMainController<B, Ts...>::update() {
    updateEncoder();
    controllers.getSelected()->update();
}

template <class B, class... Ts>
void AbstractMainController<B, Ts...>::controllerInit() {
    configMode.data.controllerIndex = controllers.getSelectedIndex();
    Config::config.save(configMode);
    controllers.getSelected()->init();
}

template <class B, class... Ts>
void AbstractMainController<B, Ts...>::updateEncoder() {
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