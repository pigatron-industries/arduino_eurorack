#ifndef DoubleEncoderController_h
#define DoubleEncoderController_h

#include "eeprom/Config.h"
#include "hardware/RotaryEncoderButton.h"

class ControllerConfig {
    public:
        uint8_t controllerIndex;
        uint8_t parameterIndex;
};

template <class B, class... Ts>
class DoubleEncoderController {
    public:
        DoubleEncoderController(RotaryEncoderButton& rotaryEncoderButton1, RotaryEncoderButton& rotaryEncoderButton2) : 
            encoder1(rotaryEncoderButton1),
            encoder2(rotaryEncoderButton2)
        {}

        void init();
        void update();

    protected:
        TypeSelector<B, Ts...> controllers;

        RotaryEncoderButton& encoder1;
        RotaryEncoderButton& encoder2;

        ConfigField<ControllerConfig> controllerConfig;

        void (DoubleEncoderController<B, Ts...>::*encoder1HeldTurn)(int8_t direction) = &DoubleEncoderController::changeController;
        void (DoubleEncoderController<B, Ts...>::*encoder1Turn)(int8_t direction) = &DoubleEncoderController::changeParameter;
        void (DoubleEncoderController<B, Ts...>::*encoder1ShortPress)() = &DoubleEncoderController::controllerInit;
        void (DoubleEncoderController<B, Ts...>::*encoder2Turn)(int8_t direction) = &DoubleEncoderController::changeValue;

        bool initOnModeSelect = true;

        virtual void controllerInit();
        void doEncoder1Event(RotaryEncoderButton::EncoderEvent event);
        void doEncoder2Event(RotaryEncoderButton::EncoderEvent event);
        void saveState();
        void changeController(int8_t direction);
        void changeParameter(int8_t direction);
        void changeValue(int8_t direction);
};


template <class B, class... Ts>
void DoubleEncoderController<B, Ts...>::init() {
    Config::config.load(controllerConfig);
    controllers.select(controllerConfig.data.controllerIndex);
    for(B* controller : controllers.getItems()) {
        controller->load();
    }
    controllerInit();
}

template <class B, class... Ts>
void DoubleEncoderController<B, Ts...>::update() {
    doEncoder1Event(encoder1.getEncoderEvent());
    doEncoder2Event(encoder2.getEncoderEvent());
    controllers.getSelected()->update();
}

template <class B, class... Ts>
void DoubleEncoderController<B, Ts...>::controllerInit() {
    saveState();
    controllers.getSelected()->init();
}

template <class B, class... Ts>
void DoubleEncoderController<B, Ts...>::saveState() {
    controllerConfig.data.controllerIndex = controllers.getSelectedIndex();
    Config::config.save(controllerConfig);
}

template <class B, class... Ts>
void DoubleEncoderController<B, Ts...>::changeController(int8_t direction) {
    controllers.cycle(direction);
    controllerInit();
}

template <class B, class... Ts>
void DoubleEncoderController<B, Ts...>::changeParameter(int8_t direction) {
    controllerConfig.data.parameterIndex = controllers.getSelected()->cycleParameter(direction);
    if(initOnModeSelect) {
        controllers.getSelected()->init();
    }
        
    Config::config.save(controllerConfig);
}

template <class B, class... Ts>
void DoubleEncoderController<B, Ts...>::changeValue(int8_t direction) {
    controllers.getSelected()->cycleValue(direction);
}

template <class B, class... Ts>
void DoubleEncoderController<B, Ts...>::doEncoder1Event(RotaryEncoderButton::EncoderEvent event) {
    switch(event) {
        case RotaryEncoderButton::EncoderEvent::EVENT_CLOCKWISE:
            (this->*encoder1Turn)(1);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_ANTICLOCKWISE:
            (this->*encoder1Turn)(-1);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_CLOCKWISE:
            (this->*encoder1HeldTurn)(1);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_ANTICLOCKWISE:
            (this->*encoder1HeldTurn)(-1);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_SHORT_PRESS:
            (this->*encoder1ShortPress)();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_NONE:
            break;
    }
}

template <class B, class... Ts>
void DoubleEncoderController<B, Ts...>::doEncoder2Event(RotaryEncoderButton::EncoderEvent event) {
    switch(event) {
        case RotaryEncoderButton::EncoderEvent::EVENT_CLOCKWISE:
            (this->*encoder2Turn)(1);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_ANTICLOCKWISE:
            (this->*encoder2Turn)(-1);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_NONE:
            break;
    }
}

#endif