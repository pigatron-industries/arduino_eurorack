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
        void doEncoderEvent(RotaryEncoderButton::EncoderEvent event);
        void saveMode();
        void incrementController();
        void decrementController();
        void incrementMode();
        void decrementMode();
};


template <class B, class... Ts>
void AbstractMainController<B, Ts...>::init() {
    Config::config.load(configMode);
    controllers.select(configMode.data.controllerIndex);
    controllers.getSelected()->setMode(configMode.data.controllerMode);
    controllerInit();
}

template <class B, class... Ts>
void AbstractMainController<B, Ts...>::update() {
    doEncoderEvent(encoder.getEncoderEvent());
    controllers.getSelected()->update();
}

template <class B, class... Ts>
void AbstractMainController<B, Ts...>::controllerInit() {
    saveMode();
    controllers.getSelected()->init();
}

template <class B, class... Ts>
void AbstractMainController<B, Ts...>::saveMode() {
    configMode.data.controllerIndex = controllers.getSelectedIndex();
    Config::config.save(configMode);
}

template <class B, class... Ts>
void AbstractMainController<B, Ts...>::incrementController() {
    controllers.increment();
    controllerInit();
}

template <class B, class... Ts>
void AbstractMainController<B, Ts...>::decrementController() {
    controllers.decrement();
    controllerInit();
}

template <class B, class... Ts>
void AbstractMainController<B, Ts...>::incrementMode() {
    configMode.data.controllerMode = controllers.getSelected()->cycleMode(1);
    Serial.print("Mode: ");
    Serial.println(configMode.data.controllerMode);
    controllers.getSelected()->init();
    Config::config.save(configMode);
}

template <class B, class... Ts>
void AbstractMainController<B, Ts...>::decrementMode() {
    configMode.data.controllerMode = controllers.getSelected()->cycleMode(1);
    Serial.print("Mode: ");
    Serial.println(configMode.data.controllerMode);
    controllers.getSelected()->init();
    Config::config.save(configMode);
}

template <class B, class... Ts>
void AbstractMainController<B, Ts...>::doEncoderEvent(RotaryEncoderButton::EncoderEvent event) {
    switch(event) {
        case RotaryEncoderButton::EncoderEvent::EVENT_CLOCKWISE:
            incrementMode();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_ANTICLOCKWISE:
            decrementMode();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_CLOCKWISE:
            incrementController();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_ANTICLOCKWISE:
            decrementController();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_SHORT_PRESS:
            controllerInit();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_NONE:
            break;
    }
}

#endif