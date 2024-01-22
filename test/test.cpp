#include <unity.h>

#include "dsp/test_clock/ClockTest.h"
#include "dsp/test_clock/InternalExternalClockTest.h"

int main() {
    UNITY_BEGIN();
    test_Clock();
    test_InternalExternalClock();
    return UNITY_END();
}
