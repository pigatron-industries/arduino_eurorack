#ifndef Eurorack_h
#define Eurorack_h

#include "EurorackConfig.h"

#include "util/util.h"
#include "util/CycleEnum.h"
#include "util/SlewLimiter.h"

#include "hardware/AnalogInputPin.h"
#include "hardware/DigitalOutputPin.h"
#include "hardware/GateInput.h"
#include "hardware/TriggerInput.h"
#include "hardware/PushButton.h"
#include "hardware/RotaryEncoder.h"
#include "hardware/MultiplexGateOutput.h"

#include "analogmodifiers/LinearInput.h"
#include "analogmodifiers/ExpInput.h"
#include "analogmodifiers/PowInput.h"
#include "analogmodifiers/AnalogGateInput.h"
#include "analogmodifiers/FilterInput.h"
#include "analogmodifiers/CrossfadeInput.h"

#endif