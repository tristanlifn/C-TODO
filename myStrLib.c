#include "myStrLib.h"
#include <stddef.h>

int mystrlen(const char *str) {
    int len = 0;

    while (*str++ != '\0') {
        ++len;
        if (*str == '\0') {
            break;
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

char *mystrcat(char *dest, char *src) {
    char *orignal_dest = dest;

    while (*dest != '\0') {
        dest++;
    }

    while ((*dest++ = *src++) != '\0') {
    }

    return orignal_dest;
}

char *mystrstr(const char *str, const char *substr) {
    // does not work, still need to implement checking
    char *match_ptr;
    int match_len = 0;

    while (*str != '\0') {
        if ((*str == *substr) && (match_len <= mystrlen(substr))){
            
        } else {
            match_len = 0;
        }

    }

    return match_ptr;
}
