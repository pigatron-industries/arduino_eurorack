#ifndef SingleEncoderController_h
#define SingleEncoderController_h

#include "eeprom/Config.h"
#include "hardware/RotaryEncoderButton.h"

#define AbstractMainController SingleEncoderController


class ControllerConfig {
    public:
        uint8_t controllerIndex;
        uint8_t parameterIndex;
};

template <class B, class... Ts>
class SingleEncoderController {
    public:
        SingleEncoderController(RotaryEncoderButton& rotaryEncoderButton) : 
            encoder(rotaryEncoderButton) {}

        void init();
        void update();

    protected:
        TypeSelector<B, Ts...> controllers;

        RotaryEncoderButton& encoder;

        ConfigField<ControllerConfig> controllerConfig;

        void (SingleEncoderController<B, Ts...>::*encoderHeldTurn)(int8_t direction) = &SingleEncoderController::changeController;
        void (SingleEncoderController<B, Ts...>::*encoderShortPress)() = &SingleEncoderController::changeParameter;
        void (SingleEncoderController<B, Ts...>::*encoderTurn)(int8_t direction) = &SingleEncoderController::changeValue;
        bool initOnModeSelect = true;

        virtual void controllerInit();
        void doEncoderEvent(RotaryEncoderButton::EncoderEvent event);
        void saveState();

        void changeController(int8_t direction);
        void changeParameter();
        void changeValue(int8_t direction);
};


template <class B, class... Ts>
void SingleEncoderController<B, Ts...>::init() {
    Config::config.load(controllerConfig);
    controllers.select(controllerConfig.data.controllerIndex);
    for(B* controller : controllers.getItems()) {
        controller->load();
    }
    controllerInit();
}

template <class B, class... Ts>
void SingleEncoderController<B, Ts...>::update() {
    doEncoderEvent(encoder.getEncoderEvent());
    controllers.getSelected()->update();
}

template <class B, class... Ts>
void SingleEncoderController<B, Ts...>::controllerInit() {
    saveState();
    controllers.getSelected()->init();
}

template <class B, class... Ts>
void SingleEncoderController<B, Ts...>::saveState() {
    controllerConfig.data.controllerIndex = controllers.getSelectedIndex();
    Config::config.save(controllerConfig);
}

template <class B, class... Ts>
void SingleEncoderController<B, Ts...>::changeController(int8_t direction) {
    controllers.cycle(direction);
    controllerInit();
}

template <class B, class... Ts>
void SingleEncoderController<B, Ts...>::changeParameter() {
    controllerConfig.data.parameterIndex = controllers.getSelected()->cycleParameter(1);
    if(initOnModeSelect) {
        controllers.getSelected()->init();
    }
        
    Config::config.save(controllerConfig);
}

template <class B, class... Ts>
void SingleEncoderController<B, Ts...>::changeValue(int8_t direction) {
    controllers.getSelected()->cycleValue(direction);
}

template <class B, class... Ts>
void SingleEncoderController<B, Ts...>::doEncoderEvent(RotaryEncoderButton::EncoderEvent event) {
    switch(event) {
        case RotaryEncoderButton::EncoderEvent::EVENT_CLOCKWISE:
            (this->*encoderTurn)(1);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_ANTICLOCKWISE:
            (this->*encoderTurn)(-1);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_CLOCKWISE:
            (this->*encoderHeldTurn)(1);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_ANTICLOCKWISE:
            (this->*encoderHeldTurn)(-1);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_SHORT_PRESS:
            (this->*encoderShortPress)();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_NONE:
            break;
    }
}

#endif