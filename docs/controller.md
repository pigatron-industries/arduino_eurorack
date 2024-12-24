---
order: 6
---

# Controllers

A controller is the main class for implementing a specific mode of operation for a hardware module. 
A module may have multiple controllers if they implement different modes with completely seperate functionality on the same hardware.


## Main Controller

The MainContoller class manages multiple controllers and switching between them.
A MainController class can inherit from either SingleEncoderController or DoubleEncoderController.

TODO

Draw typical call diagram

## Controller

A controller can inherit AbstractController is a simple contraller that does not have any parameters other than simple analogue inputs.

You will need to prove an abstract implementation specific to your use case. 
For example, the following abstract class implements a controller which is initialised with a specific sample rate.
Concrete subclasses must implement update and process functions. 
The update function is called in the microcontroller loop for non urgent operations such as reading inputs from hardware and updating the user interface.
The process function is called from a timed interrupt based on the sample rate and can implement timing critical operations such as synthesis of an output waveform.

```cpp
class Controller : virtual public AbstractController {
    public:
        Controller() : AbstractController() {}
        virtual void init(float sampleRate) { this->sampleRate = sampleRate; }
        virtual void init() {};
        virtual void update() = 0;
        virtual void process() = 0;
        float getSampleRate() { return sampleRate; }

    protected:
        bool sampleRate = 0;
};
```

There are 2 init functions in the Controller above. In this case the first one is called the first time the controller is initialised and the second one is called whenever the user switches to this controller again and it needs to be restarted.


## Parameterized Controller

A controller can inherit AbstractParameterizedController if it has multiple parameters that can be set using the encoder that cannot be set using simple analogue inputs.

As well as providing a controller implementation you will also need to provide the following abstract subclass to resolve load and save methods:

```cpp
template<int N>
class ParameterizedController : public Controller, public AbstractParameterizedController<N> {
    public:
        void load() { AbstractParameterizedController<N>::load(); }
        void save() { AbstractParameterizedController<N>::save(); }
};
```


### Parameterized Controller Implementation

In the implementation of a Controller class we specify the number of parameters as a template variable.
Analogue inputs, user interface outputs, and any sound generation objects can be defined as private variables, e.g:

```cpp
#define PARAMETERS 1

class SamplePlayerController : public ParameterizedController<PARAMETERS> {
    public:
        // Specify parameters names
        enum Parameter {
            SAMPLEFILE
        };

        SamplePlayerController() : ParameterizedController() {}
        void init(float sampleRate);
        void init();

        int cycleParameter(int amount);
        virtual void cycleValue(int amount);
        void selectValue();

        void update();
        virtual void process();


    private:
        // Analogue Inputs
        // TODO

        // User interface
        SamplePlayerInterface interface;

        // Waveform generation 
        SampleBuffer sampleBuffer;
};
```

### Initialisation

The init(sampleRate) function needs to configure each parameter using configParam:

```cpp
configParam(int parameterIndex, int defaultval, int maxval, bool autoSelect)
```

All parameters are stored as integers.
parameterIndex is index of the parameter we are configuring.
defaultval is the default value of the parameter, this is used on first init if there is no value saved in EEPROM.
maxval is the maximum value the parameter can have, going above this value will wrap around to 0.
autoSelect tells the controller if the new value should be used as soon as it is changed by turning the encoder, or wait until the encoder button is pushed. The latter is useful for expensive operation such as loading files.


Full exmaple of an init function:

```cpp
void SamplePlayerController::init(float sampleRate) {
    Controller::init(sampleRate);
    configParam(Parameter::SAMPLEFILE, 0, SAMPLE_COUNT, false);
    interface.init();
    init();
}

void SamplePlayerController::init() {
    Serial.println("SamplePlayerController::init");
    interface.render();
}
```

### Parameter Changes

The cycleParameter function is called when the selcted paramter is changed.
This can be used to update user interfaces to the currently selected parameter.

parameters.getSelectedIndex() will return the index of the current parameter.

```cpp
int SamplePlayerController::cycleParameter(int amount) {
    parameters.cycle(amount);

    switch(parameters.getSelectedIndex()) {
        case Parameter::SAMPLEFILE:
            interface.focusSampleFile();
            break;
    }

    return parameters.getSelectedIndex(); 
}
```

The cycle value function is called when the value of the current paramter is cycled.

```cpp
void SamplePlayerController::cycleValue(int amount) {
    int value = parameters.getSelected().cycle(amount);
    switch(parameters.getSelectedIndex()) {
        case Parameter::SAMPLEFILE: {
            FileInfo& file = getFileInfo(value);
            interface.setSampleFile(file.name);
            break;
        }
    }

    save();
}
```

The selectValue function will be called when autoSelect is false and the user selected the parameter value. We can get the previous and new value to compare them.

```cpp
void SamplePlayerController::selectValue() {
    int prevValue = parameters.getSelected().getValue();
    int newValue = parameters.getSelected().select();
    switch(parameters.getSelectedIndex()) {
        case Parameter::SAMPLEFILE:
            if (newValue != prevValue) {
                loadSampleFile(newValue);
            } 
            break;
    }
}
```