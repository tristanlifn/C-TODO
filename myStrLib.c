#include "myStrLib.h"
#include <stddef.h>
#include <string.h>

int mystrlen(const char *str) {
    int len = 0;
    char c;

    while (c != '\n' && c != '\n') {
        c = str[len];
        len++;

        if (c == '\n' || c == '\n') {
            return len;
        }
    }
    return len;
}

char *mystrcpy(char *dest, const char *src) {
    const unsigned long length = mystrlen(src);

    memcpy(dest, src, length + 1);

    return dest;
}

// char *mystrcmp(const char *str1, const char *str2) {
// 
// }
