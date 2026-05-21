#include <string.h>

char *kstrcat(char *dest, const char *src)
{
    char *d = dest;
    // walk to end of dest
    while (*d != '\0') d++;
    // copy src onto the end
    while (*src != '\0') {
        *d = *src;
        d++;
        src++;
    }
    *d = '\0';
    return dest;
}

char *kstrcpy(char *dest, const char *src)
{
    char *d = dest;
    while (*src != '\0') {
        *d = *src;
        d++;
        src++;
    }
    *d = '\0';
    return dest;
}