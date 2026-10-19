#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef unsigned long s21_size_t;
#define s21_NULL (void *)0

s21_size_t s21_strcspn(const char *s1, const char *s2);
s21_size_t s21_strlen(const char *str);
s21_size_t s21_strspn(const char *s1, const char *s2);
int s21_memcmp(const void *s1, const void *s2, s21_size_t n);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *s, int c, s21_size_t n);
char* s21_strcpy(char* dest, const char* src);
char* s21_strncpy(char* dest, const char* src, s21_size_t n);
void *s21_memchr(const void *s, int val, s21_size_t n);
char *s21_strchr(const char *str, int c);
char *s21_strpbrk(const char *s1, const char *s2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
char *s21_to_lower(const char *str);
char *s21_to_upper(const char *str);
char *s21_trim(char *src, char *trim_chars);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strtok(char *str, const char *delim);
char *s21_strerror(int errnum);
int s21_sprintf(char* buffer, const char *format, ...);


#endif