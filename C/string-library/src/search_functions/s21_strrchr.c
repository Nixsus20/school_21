#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = s21_NULL;
  for (const char *p = str; *p != '\0'; p++)
    if (*p == c) result = (char *)p;
  if (*str == c) result = (char *)str;
  return result;
}