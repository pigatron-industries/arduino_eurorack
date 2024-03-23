#ifndef Eurorack_h
#define Eurorack_h

#include <Wire.h>
#include <SPI.h>

#include "debug/Profiler.h"

#include "util/util.h"
#include "util/stringutil.h"
#include "util/Array.h"
#include "util/CycleEnum.h"
#include "util/SlewLimiter.h"
#include "util/TypeSelector.h"
#include "util/LinkedList.h"

#include "memory/MemPool.h"
#include "memory/ObjectManager.h"

#include "hardware/device/Device.h"
#include "hardware/device/DevicePin.h"
#include "hardware/device/AnalogInputSumPin.h"
#include "hardware/device/AnalogPinCalibration.h"
#include "hardware/native/NativeDevice.h"

#include "hardware/RotaryEncoder.h"
#include "hardware/RotaryEncoderButton.h"

#include "io/analoginputs/LinearInput.h"
#include "io/analoginputs/IntegerInput.h"
#include "io/analoginputs/ExpInput.h"
#include "io/analoginputs/PowInput.h"
#include "io/analoginputs/AnalogGateInput.h"
#include "io/analoginputs/FilterInput.h"
#include "io/analoginputs/CrossfadeInput.h"
#include "io/analogoutputs/AnalogTriggerOutput.h"
#include "io/analogoutputs/AnalogGateOutput.h"
#include "io/digitalinputs/GateInput.h"
#include "io/digitalinputs/PushButton.h"
#include "io/digitalinputs/TriggerInput.h"
#include "io/digitaloutputs/TriggerOutput.h"

#include "controller/SingleEncoderController.h"
#include "controller/DoubleEncoderController.h"
#include "controller/AbstractController.h"
#include "controller/AbstractParameterizedController.h"

#include "eeprom/Config.h"

#endif