#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  const char *s = str;
  if (str) {
    for (; *s && result == s21_NULL; s++)
      if (*s == c) result = (char *)s;
    if (result == s21_NULL && *s == c) result = (char *)s;
  }
  return result;
}