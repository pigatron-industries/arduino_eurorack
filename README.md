# Arduino Eurorack

Utilities for creating Eurorack modules using Arduino devices.

Tested with the following devices:

Teensy LC / 4.0 / 4.1
Electrosmith Daisy


## Usage

Include the library with 

    include <eurorack.h>

## Components

### Analog Inputs

Recommended circuit. Uses an inverting rail-to-rail op-amp powered by 3.3V. Scales an input of -5V/5V to 3.3V/0V required by the Arduino. 
The values are then re-inverted by the library code. Requires a -5V reference voltage.

![Analog Input Circuit](/docs/input_analog.png)


### Digital Inputs

Recommended circuit.

![Digital Input Circuit](/docs/input_digital.png)
