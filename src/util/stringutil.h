#ifndef stringutil_h
#define stringutil_h

#include <string.h>

inline bool beginsWith(const char* str, const char* beginning) {
    return strncmp(str, beginning, strlen(beginning)) == 0;
}

inline bool endsWith(const char* str, const char* ending) {
    size_t strLength = strlen(str);
    size_t endingLength = strlen(ending);
    if (endingLength > strLength) {
        return false;
    }
    const char* strEnd = str + strLength - endingLength;
    return strcmp(strEnd, ending) == 0;
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


/*
 * The memmem() function finds the start of the first occurrence of the
 * substring 'needle' of length 'nlen' in the memory area 'haystack' of
 * length 'hlen'.
 *
 * The return value is a pointer to the beginning of the sub-string, or
 * NULL if the substring is not found.
 */
inline const char* memmem(const char *haystack, size_t hlen, const char *needle, size_t nlen) {
    int needle_first;
    const char *p = haystack;
    size_t plen = hlen;

    if (!nlen)
        return nullptr;

    needle_first = *(unsigned char *)needle;

    while (plen >= nlen && (p = (const char*)memchr(p, needle_first, plen - nlen + 1)))
    {
        if (!memcmp(p, needle, nlen))
            return p;

        p++;
        plen = hlen - (p - haystack);
    }

    return nullptr;
}


#endif