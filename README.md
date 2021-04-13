# Arduino Eurorack

Utilities for creating Eurorack modules using Arduino devices.

Tested with the following devices:

    Teensy LC / 4.0 / 4.1
    Electrosmith Daisy


## Usage

Include the library with 

    include <eurorack.h>
    
Initialise the library with

    Eurorack::init();
    

## Components

### Analog Inputs

Recommended circuit. Uses an inverting rail-to-rail op-amp powered by 3.3V. Scales an input of -5V/5V to 3.3V/0V required by the Arduino. 
The values are then re-inverted by the library code. Requires a -5V reference voltage.

![Analog Input Circuit](/docs/input_analogue.png)

#### LinearInput

Instantiate a linear input on pin number A0, where the real voltage range goes from -5 to 5 and the output of getValue() is scaled from 0 to 10:

    LinearInput cvInput = LinearInput(A0, -5, 5, 0, 10);
    
In main loop get value with:

    if(cvInput.update()) {
        float value = cvInput.getValue();
    }

#### ExpInput

Useful for frequency controls and other input that require an exponential response

    ExpInput pitchInput = ExpInput(A0);

Can optionally specifiy a mid value, which is the value when te voltage is at 0V. The default is 523.25 which is the frequency of midi note C5:

    ExpInput pitchInput = ExpInput(A0, 440);

The output will then be divided by 2 for each 1V below 0 and multipled by 2 for each 1V above 0. The value is given by the formual:

    midValue * 2^voltage

#### AnalogGateInput

Use an analogue input as a gate. This is useful to reuse an input with analogue circuitry as a gate input.

    AnalogGateInput gateInput = AnalogGateInput(A0);

Trigger voltage default to 3V, bt van also be specified:

    AnalogGateInput gateInput = AnalogGateInput(A0, 2.5);

Detect trigger in main loop:

    if(gateInput.update()) {
        bool trigger = gateInput.isTriggered();
    }


### Digital Inputs

Recommended circuit.

![Digital Input Circuit](/docs/input_digital.png)

#### TriggerInput

    TriggerInput triggerInput = TriggerInput(0);

Main loop:

    if(triggerInput.didRise()) {
        
    } else if (triggerInput.didFall()) {
    
    }
    
Trigger input uses interrupts to detect pin changes and can detect much shorter pulses that the other inputs. Has no debouncing so cannot be used for user pressable buttons.

### Control Inputs

#### PushButton

Switch or push button connected to 0V and Arduino pin. Switch debouncing included.

    PushButton button = PushButton(0);
    
Main loop:

    if(button.update() && button.pressed()) {
        
    }

#### RotaryEncoder

A quadrature rotary ender connected to 2 pins, whihth the common pin conencted to 0V.

    RotaryEncoder encoder = RotaryEncoder(1, 2);
    
getMovement() will return negative or positive depending on direction the encoder was moved:
    
    if(encoder.update()) {
        int movement = encoder.getMovement()
    }

### Utilities

#### RangeScale

Scales a value from one range to another range.

    RangeScale scale(fromMin, fromMax, toMin, toMax);
    
    float toValue = scale.convert(fromValue);
    
#### CycleEnum

Cycles through a list of enums. Useful to make a rotary encoder cycle through an enumerated list of modes. e.g.

    enum Mode {
        FIRST_MODE,
        SECOND_MODE,
        LAST_MODE
    };
    
    CycleEnum<Mode> mode = CycleEnum<Mode>(FIRST_MODE, LAST_MODE); //first and last modes in enum
    
Cycle using RotaryEncoder:
    
    if(encoder.update()) {
        mode.cycle(encoder.getMovement());
    }

Get value of enum using ```mode.value```
