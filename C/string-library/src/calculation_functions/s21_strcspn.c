#include "../s21_string.h"

s21_size_t s21_strcspn(const char *s1, const char *s2) {
  s21_size_t result = 0;
  for (const char *p1 = s1; *p1 != '\0'; p1++) {
    for (const char *p2 = s2; *p2 != '\0'; p2++) {
      if (*p1 == *p2) {
        return result;
      }
    }
    result++;
  }
  return result;
}