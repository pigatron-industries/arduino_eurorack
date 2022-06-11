#ifndef stringutil_h
#define stringutil_h

#include <string.h>

inline bool beginsWith(const char* str, const char* beginning) {
    return strncmp(str, beginning, strlen(beginning)) == 0;
}

inline bool wildcardMatch(const char *wild, const char *string) {
    const char *cp = NULL, *mp = NULL;

    while ((*string) && (*wild != '*')) {
        if ((*wild != *string) && (*wild != '?')) {
            return false;
        }
        wild++;
        string++;
    }

    while (*string) {
        if (*wild == '*') {
            if (!*++wild) {
                return true;
            }
            mp = wild;
            cp = string+1;
        } else if ((*wild == *string) || (*wild == '?')) {
            wild++;
            string++;
        } else {
            wild = mp;
            string = cp++;
        }
    }

    while (*wild == '*') {
        wild++;
    }
    return !*wild;
}

#endif