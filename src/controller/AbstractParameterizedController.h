#ifndef AbstractParameterizedController_h
#define AbstractParameterizedController_h

#include <inttypes.h>
#include "AbstractController.h"

template<int N>
class AbstractParameterizedController {
    public:
        AbstractParameterizedController() {}
        void configParam(uint8_t param, uint8_t defaultval, uint8_t maxval);
        void load();
        void save();
        int cycleParameter(int amount);
        void cycleValue(int amount);

    protected:
        ArraySelector<CycleEnum<int>, N> parameters;

        struct SaveParameters {
            uint8_t check = 0;
            uint8_t parameters[N];
        };
        ConfigField<SaveParameters> config;
};


template<int N>
void AbstractParameterizedController<N>::configParam(uint8_t index, uint8_t defaultval, uint8_t maxval) {
    parameters[index].last = maxval;
    if(config.data.check == 0 && parameters[index].value <= maxval) {
        parameters[index].value = config.data.parameters[index];
    } else {
        parameters[index].value = defaultval;
    }
}

template<int N>
void AbstractParameterizedController<N>::load() {
    Config::config.load(config);
}

template<int N>
void AbstractParameterizedController<N>::save() {
    config.data.check = 0;
    for(int i = 0; i < N; i++) {
        config.data.parameters[i] = parameters[i].value;
    }
    Config::config.save(config);
}

template<int N>
int AbstractParameterizedController<N>::cycleParameter(int amount) { 
    parameters.cycle(amount);
    return parameters.getSelectedIndex(); 
}

template<int N>
void AbstractParameterizedController<N>::cycleValue(int amount) {
    parameters.getSelected().cycle(amount);
    save();
}

#endif