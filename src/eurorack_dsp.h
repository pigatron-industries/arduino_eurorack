#ifndef EurorackDsp_h
#define EurorackDsp_h

#include "dsp/clock/Clock.h"
#include "dsp/clock/InternalExternalClock.h"
#include "dsp/clock/ClockDivider.h"
#include "dsp/clock/ClockGate.h"
#include "dsp/envelope/Envelope.h"
#include "dsp/envelope/EnvelopePlayer.h"
#include "dsp/oscillator/WaveOscillator.h"
#include "dsp/oscillator/PhaseDistortionOscillator.h"
#include "dsp/filter/StateVariableFilter.h"
#include "dsp/sample/SampleBuffer.h"
#include "dsp/sample/SamplePlayer.h"
#include "dsp/sample/DelayLine.h"

#include "dsp/distortionfunctions/TwoLineFunction.h"
#include "dsp/distortionfunctions/SmoothStepFunction.h"

#include "dsp/waveshapes/Line.h"
#include "dsp/waveshapes/Pulse.h"
#include "dsp/waveshapes/Saw.h"
#include "dsp/waveshapes/Sine.h"
#include "dsp/waveshapes/Triangle.h"
#include "dsp/waveshapes/AsymmetricalTriangle.h"
#include "dsp/waveshapes/WaveSelector.h"
#include "dsp/waveshapes/WaveSequence.h"

#include "dsp/waveshapes/interpolation/WaveInterpolator.h"
#include "dsp/waveshapes/interpolation/WaveInterpolator2D.h"
#include "dsp/waveshapes/interpolation/WaveInterpolator3D.h"

#include "dsp/waveshapes/wavetable/WaveTable.h"
#include "dsp/waveshapes/wavetable/WaveTableFactory.h"

#endif