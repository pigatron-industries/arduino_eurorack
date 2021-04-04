#ifndef MultiplexGateOutput_h
#define MultiplexGateOutput_h

#include <inttypes.h>
#include "../util/Timer.h"

#define CLOCKINTERVAL 1 //us
#define TRIGGER_TIME 4000 //us

#define MAX_SIZE 32

class MultiplexGateOutput {

public:
    MultiplexGateOutput(uint8_t dataPin, uint8_t latchPin, uint8_t clockPin, uint8_t size);

    void setValue(uint8_t index, bool value);
    void setTrigger(uint8_t index);
    void update();
    void sendData();

    uint8_t getSize() { return size; };
    bool* getData() { return data; };

private:
    uint8_t dataPin;
    uint8_t latchPin;
    uint8_t clockPin;
    uint8_t size;

    bool data[MAX_SIZE];

    Timer triggerTimer[MAX_SIZE];

};

#endif
