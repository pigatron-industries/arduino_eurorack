#ifndef AbstractParameterizedController_h
#define AbstractParameterizedController_h

#include <inttypes.h>
#include "AbstractController.h"
#include "../util/CycleSelectEnum.h"

template<int N>
class AbstractParameterizedController {
    public:
        AbstractParameterizedController() {}
        void configParam(int param, int defaultval, int maxval, bool autoSelect = true);
        int getParameterValue(int index) { return parameters[index].value; }
        void load();
        void save();
        int cycleParameter(int amount);
        void cycleValue(int amount);

    protected:
        ArraySelector<CycleSelectEnum<int>, N> parameters;

        struct SaveParameters {
            uint8_t check = 0;
            int parameters[N];
        };
        ConfigField<SaveParameters> config;
};


template<int N>
void AbstractParameterizedController<N>::configParam(int index, int defaultval, int maxval, bool autoSelect) {
    parameters[index].setAutoSelect(autoSelect);
    parameters[index].last = maxval;
    if(config.data.check == 0 && config.data.parameters[index] <= maxval) {
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