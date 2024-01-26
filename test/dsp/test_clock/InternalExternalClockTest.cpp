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
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_FALSE(clock.process());

    clock.externalTick();
    TEST_ASSERT_EQUAL_INT(InternalExternalClock::State::CLK_EXTERNAL, clock.getState());
    TEST_ASSERT_EQUAL_FLOAT(1.333333, clock.getFrequency()); // freqency changes to 1.333Hz as measured by external ticks
}

void test_externalClock() {
    InternalExternalClock clock = InternalExternalClock();
    clock.init(4); // 4Hz sample rate
    clock.setFrequency(0.1); // 0.1Hz frequency (ignored)
    clock.process();

    // switch to 2Hz external clock
    clock.externalTick();
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    clock.externalTick();
    TEST_ASSERT_EQUAL_FLOAT(2, clock.getFrequency());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    clock.externalTick();
    TEST_ASSERT_EQUAL_FLOAT(2, clock.getFrequency());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
}

void test_internalDivider() {
    InternalExternalClock clock = InternalExternalClock();
    clock.init(4); // 4Hz sample rate
    clock.setFrequency(2); // 2Hz frequency
    clock.setFrequencyMultiplierDivider(InternalExternalClock::MultiplierDivider::CLK_DIVIDER, 2);

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

void test_externalDivider() {
    InternalExternalClock clock = InternalExternalClock();
    clock.init(4); // 4Hz sample rate
    clock.setFrequency(0.1); // 0.1Hz frequency (ignored)
    clock.setFrequencyMultiplierDivider(InternalExternalClock::MultiplierDivider::CLK_DIVIDER, 2);

    // switch to 2Hz external clock
    clock.externalTick();
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    clock.externalTick();
    TEST_ASSERT_EQUAL_FLOAT(2, clock.getFrequency());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    clock.externalTick();
    TEST_ASSERT_EQUAL_FLOAT(2, clock.getFrequency());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    clock.externalTick();
    TEST_ASSERT_EQUAL_FLOAT(2, clock.getFrequency());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
}

void test_internalMultiplier() {
    InternalExternalClock clock = InternalExternalClock();
    clock.init(4); // 4Hz sample rate
    clock.setFrequency(1); // 1Hz frequency
    clock.setFrequencyMultiplierDivider(InternalExternalClock::MultiplierDivider::CLK_MULTIPLIER, 2);

    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
}

void test_externalMultiplier() {
    InternalExternalClock clock = InternalExternalClock();
    clock.init(4); // 4Hz sample rate
    clock.setFrequency(0.1); // 0.1Hz frequency (ignored)
    clock.setFrequencyMultiplierDivider(InternalExternalClock::MultiplierDivider::CLK_MULTIPLIER, 2);

    // switch to 2Hz external clock
    clock.externalTick();
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    clock.externalTick();
    TEST_ASSERT_EQUAL_FLOAT(1, clock.getFrequency());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    clock.externalTick();
    TEST_ASSERT_EQUAL_FLOAT(1, clock.getFrequency());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_FALSE(clock.process());  // if external tick is late wait for it
    clock.externalTick();
    TEST_ASSERT_EQUAL_FLOAT(0.8, clock.getFrequency());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    clock.externalTick();
    TEST_ASSERT_EQUAL_FLOAT(1, clock.getFrequency());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
}

void test_InternalExternalClock() {
    RUN_TEST(test_internal2Hz);
    RUN_TEST(test_internal1Hz);
    RUN_TEST(test_switchToExternal);
    RUN_TEST(test_externalClock);
    RUN_TEST(test_internalDivider);
    RUN_TEST(test_externalDivider);
    RUN_TEST(test_internalMultiplier);
    RUN_TEST(test_externalMultiplier);
}
