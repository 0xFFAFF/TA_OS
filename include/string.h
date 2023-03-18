#ifndef _TAOS_STRING_H
#define _TAOS_STRING_H
#include <types.h>
char *strcpy(char *dest, char *src);
char *strcat(char *dest, char *src);
size_t strlen(const char *src);
int strcmp(const char *lhs, const char *rhs);
char *strchr(const char *str, int ch);
char *strrchr(const char *str, int ch);
int memcmp(const void *lhs, const void *rhs, size_t count);
void *memset(void *dest, int ch, size_t count);
void *memcpy(void *dest, const void *src, size_t count);
void *memchr(const void *str, int ch, size_t count);
#endif