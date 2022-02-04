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
        AbstractMainController(RotaryEncoderButton& rotaryEncoderButton) : 
            encoder(rotaryEncoderButton) {}

        void init();
        void update();

    protected:
        TypeSelector<B, Ts...> controllers;

        RotaryEncoderButton& encoder;

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
    RotaryEncoderButton::EncoderEvent event = encoder.getEncoderEvent();
    switch(event) {
        case RotaryEncoderButton::EncoderEvent::EVENT_CLOCKWISE:
            configMode.data.controllerMode = controllers.getSelected()->cycleMode(1);
            Serial.print("Mode: ");
            Serial.println(configMode.data.controllerMode);
            controllers.getSelected()->init();
            Config::config.save(configMode);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_ANTICLOCKWISE:
            configMode.data.controllerMode = controllers.getSelected()->cycleMode(-1);
            Serial.print("Mode: ");
            Serial.println(configMode.data.controllerMode);
            controllers.getSelected()->init();
            Config::config.save(configMode);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_CLOCKWISE:
            controllers.increment();
            controllerInit();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_ANTICLOCKWISE:
            controllers.decrement();
            controllerInit();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_SHORT_PRESS:
            controllerInit();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_NONE:
            break;
    }
}

#endif