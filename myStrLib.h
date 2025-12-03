#ifndef MYSTRLIB_H

#define MYSTRLIB_H

int mystrlen(const char *str);
char *mystrcpy(char *dest, const char *src);
int mystrcmp(const char *str1, const char *str2);
char *mystrcat(char *dest, char *src);
char *mystrstr(const char *srt, const char *substr);

#endif
