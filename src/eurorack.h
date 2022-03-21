#ifndef Eurorack_h
#define Eurorack_h

#include <Wire.h>

#include "EurorackConfig.h"

#include "debug/Profiler.h"

#include "util/util.h"
#include "util/Array.h"
#include "util/CycleEnum.h"
#include "util/MemPool.h"
#include "util/SlewLimiter.h"
#include "util/TypeSelector.h"

#include "hardware/device/Device.h"
#include "hardware/device/DevicePin.h"
#include "hardware/device/AnalogInputPinSum.h"
#include "hardware/native/NativeDevice.h"

#include "hardware/RotaryEncoder.h"
#include "hardware/RotaryEncoderButton.h"

#include "io/analoginputs/LinearInput.h"
#include "io/analoginputs/EnumInput.h"
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

#include "controller/AbstractMainController.h"
#include "controller/AbstractController.h"
#include "controller/Config.h"

#endif