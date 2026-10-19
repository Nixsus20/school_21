#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  for (const char *p = haystack; *p != '\0' && result == s21_NULL; p++) {
    if (*p == *needle) {
      const char *q = p;
      const char *r = needle;
      while (*q == *r && *r != '\0') {
        q++;
        r++;
      }
      if (*r == '\0') result = (char *)p;
    }
    if (*needle == '\0') result = (char *)p;
  }
  return result;
}