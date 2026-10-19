#include "../s21_string.h"

s21_size_t s21_strspn(const char *s1, const char *s2) {
  s21_size_t result = 0;
  if (s1 != s21_NULL && s2 != s21_NULL) {
    for (const char *p1 = s1; *p1 != '\0'; p1++) {
      const char *p2 = s2;
      int found = 0;
      while (*p2 != '\0') {
        if (*p1 == *p2) {
          found = 1;
          break;
        }
        p2++;
      }
      if (!found) break;
      result++;
    }
  }
  return result;
}
