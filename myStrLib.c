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
    char *original_dest = dest;

    while ((*dest++ = *src++) != '\0') {
    }
    return original_dest;
}

int mystrcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}
