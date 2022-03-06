---
order: 2
---

# Basic Usage

### PlatformIO

Add to a platformio project by adding the following to lib_deps in platformio.ini. Other dependencies may need to be added when using specific device drivers. See full documnetation for details.

    lib_deps = 
	    https://github.com/pigatron-industries/arduino_eurorack.git

### Include Headers

Include the following header for basic usage of input/output libraries and other utilities. Other includes may be needed for the DSP libraries and specific devices drivers. See full documentation for details.

    include <eurorack.h>

### Initialise

Initialise the library before using with the follwoing. This usually goes in the arduino setup() function.

    Eurorack::init();
