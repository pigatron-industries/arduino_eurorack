---
order: 7
---

# Hardware

## Teensy Motherboard 8CV

Motherboard for teensy containing circuits to enable the following:

- 8 CV Inputs
- 8 Potentiometer Inputs
- 8 CV Outputs using DAC8164
- 16 Digital Inputs or Outputs using MCP23S17 IO expander

Works with Teensy LC/4.0/4.1

### Soldering

Depending on requirements not all of the components need to be soldered.

Do not solder both section A and B at the same time.
- **A.** Solder these resistors if there are 4 or less potentiometers. They connect the potentiometers directy to analog input on the Teensy. 
- **B.** Solder the CD4051 if there are more than 4 potentiometers. They will be multiplexed to a sinlge analog input on the Teensy.
- **C.** 8 control voltage inputs with range -5V to 5V.
- **D.** IO expander providing 16 digital input or output pins.
- **E.** 8 control voltage outputs with a range from -5V to 5V. An offset can be added to change the range.

![Teensy Motherboard](images/hardware_teensy_motherboard_8cv_mki.drawio.png)

### Teensy Connections


