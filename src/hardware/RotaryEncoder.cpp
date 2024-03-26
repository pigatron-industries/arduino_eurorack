#include "RotaryEncoder.h"

/*
 * The below state table has, for each state (row), the new state
 * to set based on the next encoder output. From left to right in,
 * the table, the encoder outputs are 00, 01, 10, 11, and the value
 * in that position is the new state to set.
 */

#define R_START 0x0

#ifdef HALF_STEP
// Use the half-step state table (emits a code at 00 and 11)
#define R_CCW_BEGIN 0x1
#define R_CW_BEGIN 0x2
#define R_START_M 0x3
#define R_CW_BEGIN_M 0x4
#define R_CCW_BEGIN_M 0x5
const unsigned char ttable[6][4] = {
  // R_START (00)
  {R_START_M,            R_CW_BEGIN,     R_CCW_BEGIN,  R_START},
  // R_CCW_BEGIN
  {R_START_M | DIR_CCW, R_START,        R_CCW_BEGIN,  R_START},
  // R_CW_BEGIN
  {R_START_M | DIR_CW,  R_CW_BEGIN,     R_START,      R_START},
  // R_START_M (11)
  {R_START_M,            R_CCW_BEGIN_M,  R_CW_BEGIN_M, R_START},
  // R_CW_BEGIN_M
  {R_START_M,            R_START_M,      R_CW_BEGIN_M, R_START | DIR_CW},
  // R_CCW_BEGIN_M
  {R_START_M,            R_CCW_BEGIN_M,  R_START_M,    R_START | DIR_CCW},
};
#else
// Use the full-step state table (emits a code at 00 only)
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

const unsigned char ttable[7][4] = {
  // R_START
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
  // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
  // R_CCW_NEXT
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};
#endif

RotaryEncoder* RotaryEncoder::encoderPtrs[MAX_ENCODERS];
int RotaryEncoder::encoderCount = 0;

RotaryEncoder::RotaryEncoder(uint8_t pin1, uint8_t pin2, bool useInterrupt) {
    encoderPtrs[encoderCount] = this;
    encoderCount++;
    this->pin1 = pin1;
    this->pin2 = pin2;

    pinMode(pin1, INPUT_PULLUP);
    pinMode(pin2, INPUT_PULLUP);
    #ifdef ENABLE_PULLUPS
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, HIGH);
    #endif

    state = R_START;

    this->useInterrupt = useInterrupt;
    if(useInterrupt) {
        attachInterrupt(pin1, RotaryEncoder::interrupt, CHANGE);
        attachInterrupt(pin2, RotaryEncoder::interrupt, CHANGE);
    }
}

void RotaryEncoder::interrupt() {
    for(int i = 0; i<encoderCount; i++) {
        RotaryEncoder* encoderPtr = encoderPtrs[i];
        encoderPtr->poll();
    }
}

void RotaryEncoder::poll() {
    unsigned char result = this->process();
    if (result == DIR_CW) {
        this->position++;
    } else if (result == DIR_CCW) {
        this->position--;
    }
}

unsigned char RotaryEncoder::process() {
    unsigned char pinstate = (digitalRead(pin2) << 1) | digitalRead(pin1);
    state = ttable[state & 0xf][pinstate];
    return state & 0x30;
}