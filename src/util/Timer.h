#ifndef Timer_h
#define Timer_h

#include <inttypes.h>


class Timer {

public:
    Timer();
    void start(unsigned long waitTime);
    bool isRunning();
    bool isStopped();
    bool hasJustStopped();

private:
    bool _wasRunning = false;
    bool _running = false;
    unsigned long _startTime;
    unsigned long _waitTime;

    void update();

};

#endif
