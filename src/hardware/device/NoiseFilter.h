#ifndef NoiseFilter_h
#define NoiseFilter_h

#include <inttypes.h>

template<int N = 8>
class NoiseFilter {
    public:
        // Average of n readings, discard number of outliers at each side
        NoiseFilter(uint8_t n = N, uint8_t discard = N/4) : n(n), discard(discard), averageDivisor(n - (discard*2)) {
        }

        bool addValue(uint16_t value) {
            values[index++] = value;
            if(index >= n) {
                index = 0;
                return true;
            } else {
                return false;
            }
        }

        uint16_t getFiltered() {
            qsort(values, n, sizeof(uint16_t), NoiseFilter::compare);
            uint16_t total = 0;
            for(uint8_t i = discard; i < n - discard; i++) {
                total += values[i];
            }
            return total / averageDivisor;
        }

        static int compare(const void *cmp1, const void *cmp2) {
            uint16_t a = *((uint16_t *)cmp1);
            uint16_t b = *((uint16_t *)cmp2);
            return b - a;
        }


    private:
        uint16_t values[N];
        uint8_t index = 0;
        const uint8_t n;
        const uint8_t discard;
        const uint8_t averageDivisor;
};

#endif