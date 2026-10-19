#include "../s21_string.h"

void *s21_memchr(const void *s, int val, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)s;
  void *result = s21_NULL;

  for (size_t i = 0; i < n; i++) {
    if (ptr[i] == (unsigned char)val) {
      result = &ptr[i];
      break;
    }
  }
  return result;
}
