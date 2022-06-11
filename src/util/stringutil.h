#ifndef stringutil_h
#define stringutil_h

#include <string.h>

inline bool beginsWith(const char* str, const char* beginning) {
    return strncmp(str, beginning, strlen(beginning)) == 0;
}

#endif