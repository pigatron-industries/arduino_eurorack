# Utilities

## RangeScale

Scales a value from one range to another range.

    RangeScale scale(fromMin, fromMax, toMin, toMax);
    
    float toValue = scale.convert(fromValue);
    
## CycleEnum

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

