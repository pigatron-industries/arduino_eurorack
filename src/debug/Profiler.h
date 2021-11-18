#ifndef Profiler_h
#define Profiler_h

#include <Arduino.h>

#ifdef PROFILE_PROCESS
    #define PROFILE_START Profiler::profiler.start();                                                                     
    #define PROFILE_END Profiler::profiler.end();  
    #define PROFILE_PRINT if(Profiler::profiler.isFull()) { Profiler::profiler.dumpAverageTime(); }
#else
    #define PROFILE_START                                                                   
    #define PROFILE_END
    #define PROFILE_PRINT
#endif

#define PROFILER_SAMPLES 1000

#ifdef PROFLE_CYCLES
    #define TIME ARM_DWT_CYCCNT
#else
    #define TIME micros()
#endif

class Profiler {
    public:
        static Profiler profiler;

        Profiler() {}

        inline void start() {
            startTime = TIME;
        }

        inline void end() {
            if(!full) {
                unsigned long endTime = TIME;
                if(endTime > startTime) {
                    times[position++] = endTime - startTime;
                    if(position >= PROFILER_SAMPLES) {
                        position = 0;
                        full = true;
                    }
                }
            } 
        }

        inline bool isFull() {
            return full;
        }

        inline void printAverageTime() {
            unsigned long average = 0;
            for(int i = 0; i < PROFILER_SAMPLES; i++) {
                average += times[i];
            }
            average = average / PROFILER_SAMPLES;
            Serial.print("Average time: ");
            Serial.println(average);
            full = false;
            position = 0;
        }

    private:
        unsigned long startTime;
        unsigned long times[PROFILER_SAMPLES];
        bool full;
        int position = 0;

};

#endif