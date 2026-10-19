#include "../s21_string.h"
// Функция memcpy() копирует n байтов из области памяти src в область памяти
// dest. Области памяти не могут пересекаться

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *ptr1 = (unsigned char *)dest;
  unsigned char *ptr2 = (unsigned char *)src;
  for (size_t i = 0; i < n; i++) {
    ptr1[i] = ptr2[i];
  }
  return dest;
}
