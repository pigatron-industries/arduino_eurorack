#include <unity.h>
#include "ClockTest.h"
#include "../src/dsp/clock/InternalExternalClock.cpp"

void test_internal2Hz() {
    InternalExternalClock clock = InternalExternalClock();
    clock.init(4); // 4Hz sample rate
    clock.setFrequency(2); // 2Hz frequency

    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
}

void test_internal1Hz() {
    InternalExternalClock clock = InternalExternalClock();
    clock.init(4); // 4Hz sample rate
    clock.setFrequency(1); // 1Hz frequency
    
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
}

void test_switchToExternal() {
    InternalExternalClock clock = InternalExternalClock();
    clock.init(4); // 4Hz sample rate
    clock.setFrequency(2); // 2Hz frequency

    TEST_ASSERT_EQUAL_INT(InternalExternalClock::State::CLK_INTERNAL, clock.getState());

    clock.externalTick();
    TEST_ASSERT_EQUAL_INT(InternalExternalClock::State::CLK_EXTERNAL_WAITING, clock.getState());
    // Keeps processing using internal clock
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());

    clock.externalTick();
    TEST_ASSERT_EQUAL_INT(InternalExternalClock::State::CLK_EXTERNAL, clock.getState());
    TEST_ASSERT_EQUAL_FLOAT(1.333333, clock.getFrequency()); // freqency changes to 1.333Hz as measured by external ticks
}

void test_InternalExternalClock() {
    RUN_TEST(test_internal2Hz);
    RUN_TEST(test_internal1Hz);
    RUN_TEST(test_switchToExternal);
}
