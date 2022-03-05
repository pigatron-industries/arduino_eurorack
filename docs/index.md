---
order: 1
---

# Arduino Eurorack

A library for creating Eurorack modules using Arduino devices.

- Provides APIs for analog/digital input/output handling for CVs and Potentiometers.
- DSP and library for processing and generation of audio and CV.
- Extendable device library with some common devices.

It is recommended to use [PlatformIO](https://platformio.org/) to write module code.

See documentation links on the left for usage information.

## Status

This library is still in an alpha stage. Breaking changes could be made at any time.

The following things are currently untested and may or may not work ok:
- Using the Arduino IDE (recommend using [PlatformIO](https://platformio.org/))
- Not tested with 5V logic devices.

The following devices have been tested and work, it is likely to work with other Teensy microcontrollers and other 3.3V logic level devices.
- Teensy LC / 4.0 / 4.1
- Electrosmith Daisy

If you use with an untested configuration, then feel free to report problems and anything fixes you made, or let me know if it works ok!
