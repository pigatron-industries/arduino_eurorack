#include <unity.h>
#include "ClockTest.h"
#include "../src/dsp/clock/Clock.cpp"

void test_process2Hz() {
    Clock clock = Clock();
    clock.init(4); // 4Hz sample rate
    clock.setFrequency(2); // 2Hz frequency

    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
    TEST_ASSERT_FALSE(clock.process());
    TEST_ASSERT_TRUE(clock.process());
}

void test_process1Hz() {
    Clock clock = Clock();
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

void test_Clock() {
    RUN_TEST(test_process2Hz);
    RUN_TEST(test_process1Hz);
}
