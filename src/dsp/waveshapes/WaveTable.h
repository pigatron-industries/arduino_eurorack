#ifndef WaveTable_h
#define WaveTable_h

#include <stdlib.h>
#include "../base/WaveShape.h"
#include "../sample/SampleBuffer.h"

#define RANGE_OCTAVES 10.0

namespace eurorack {

    template<int TABLES, int SAMPLES>    
    class WaveTable : public WaveShape {
        public:
            WaveTable() {}
            void init(MemPool<float>& memPool);
            float get(float phase);

            void setFrequency(float frequency);
            float getTableFrequency(int tableIndex);

            SampleBuffer& getTempBuffer() { return tempBuffer; }
            void copyTempBufferToTable(int tableIndex);

        private:
            SampleBuffer buffer[TABLES];
            float tableFrequency[TABLES];
            int tableIndex;

            // when initialising wavetable, temporary buffer can be written to first then copied to each table.
            static SampleBuffer tempBuffer;

            void calcTableFrequencies();
    };


    template<int TABLES, int SAMPLES>  
    SampleBuffer WaveTable<TABLES, SAMPLES>::tempBuffer;

    template<int TABLES, int SAMPLES>
    void WaveTable<TABLES, SAMPLES>::init(MemPool<float>& memPool) {
        if(!tempBuffer.isInited()) {
            tempBuffer.init(SAMPLES, memPool);
        }
        for(int i = 0; i < TABLES; i++) {
            buffer[i].init(SAMPLES, memPool);
        }
        calcTableFrequencies();
    }

    template<int TABLES, int SAMPLES>
    void WaveTable<TABLES, SAMPLES>::copyTempBufferToTable(int tableIndex) {
        for(int i = 0; i < SAMPLES; i++) {
            buffer[tableIndex][i] += tempBuffer[i];
        }
    }

    template<int TABLES, int SAMPLES>
    float WaveTable<TABLES, SAMPLES>::get(float phase) {
        return buffer[tableIndex].read(phase * SAMPLES);
    }

    template<int TABLES, int SAMPLES>
    void WaveTable<TABLES, SAMPLES>::setFrequency(float frequency) {
        for(int i = 0; i < TABLES; i++) {
            if(frequency < tableFrequency[i]) {
                tableIndex = i;
            }
        }
        tableIndex = TABLES-1;
    }

    template<int TABLES, int SAMPLES>
    float WaveTable<TABLES, SAMPLES>::getTableFrequency(int tableIndex) {
        return tableFrequency(tableIndex);
    }

    template<int TABLES, int SAMPLES>
    void WaveTable<TABLES, SAMPLES>::calcTableFrequencies() {
        // Split 10 octave range equally between number of tables
        float baseFrequency = 46.875;
        float octaveInc = RANGE_OCTAVES / float(TABLES);
        float octave = 0;
        for(int i = 0; i < TABLES; i++) {
            tableFrequency[i] = baseFrequency * powf(2, octave);
            // if(tableFrequency[i] > sampleRate*0.5) {
            //     tableFrequency[i] = sampleRate*0.5;
            // }
            octave += octaveInc;
        }
    } 

}

#endif
