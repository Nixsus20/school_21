#include "../s21_string.h"

char *s21_strpbrk(const char *s1, const char *s2) {
  char *result = s21_NULL;
  for (const char *p1 = s1; *p1 != '\0' && result == s21_NULL; p1++)
    for (const char *p2 = s2; *p2 != '\0' && result == s21_NULL; p2++)
      if (*p1 == *p2) result = (char *)p1;
  return result;
}