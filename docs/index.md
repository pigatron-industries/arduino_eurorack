---
order: 1
---

# Arduino Eurorack

Tested with the following devices, but will likely work with any 3.3v logic level device (may require changes for a 5v logic level):

- Teensy LC / 4.0 / 4.1
- Electrosmith Daisy


## Usage

### PlatfromIO

Add to a platformio project by adding the following to lib_deps in platformio.ini. Other dependencies may need to be added when using specific device drivers. See full documnetation for details.

    lib_deps = 
	    https://github.com/pigatron-industries/arduino_eurorack.git

### Include Headers

Include the following header for basic usage of input/output libraries and other utilities. Other includes may be needed for the DSP libraries and specific devices drivers. See full documentation for details.

    include <eurorack.h>

### Initialise

Initialise the library before using with the follwoing. This usually goes in the arduino setup() function.

    Eurorack::init();

## Documentation

- [IO](io.md)
- [DSP](dsp.md)
- [Devices](device.md)
- [Utilities](util.md)
