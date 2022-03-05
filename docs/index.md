---
order: 1
---

# Arduino Eurorack

A library for creating Eurorack modules using Arduino devices.

- Provides APIs for analog/digital input/output handling for CVs and Potentiometers.
- DSP and library for processing and generation of audio and CV.
- Extendable device library with some common devices.

It is recommended to use [PlatformIO](https://platformio.org/) to write module code.


## Status

This library is still in an alpha stage. Breaking changes could be made at any time.

The following things are currently untested:
- Using the Arduino IDE (recommend using [PlatformIO](https://platformio.org/))
- Only tested on the following Devices. These are all 3.3V logic level devices. Not tested on any 5V logic devices.
 - Teensy LC / 4.0 / 4.1
 - Electrosmith Daisy

If you use with an untested configuration, then feel free to report problems and anything fixes you made, or let me know if it works ok!


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
