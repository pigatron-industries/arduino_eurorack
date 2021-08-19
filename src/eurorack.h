#ifndef Eurorack_h
#define Eurorack_h

#include "EurorackConfig.h"

#include "util/util.h"
#include "util/CycleEnum.h"
#include "util/SlewLimiter.h"
#include "util/ControllerList.h"

#include "hardware/TriggerInput.h"
#include "hardware/RotaryEncoder.h"
#include "hardware/MultiplexGateOutput.h"
#include "hardware/native/AnalogInputPin.h"
#include "hardware/native/DigitalOutputPin.h"

#include "io/analoginputs/LinearInput.h"
#include "io/analoginputs/ExpInput.h"
#include "io/analoginputs/PowInput.h"
#include "io/analoginputs/AnalogGateInput.h"
#include "io/analoginputs/FilterInput.h"
#include "io/analoginputs/CrossfadeInput.h"
#include "io/digitalinputs/GateInput.h"
#include "io/digitalinputs/PushButton.h"

#endif