#include "../s21_string.h"

// Функция memset() заполняет первые n байтов той области памяти, на которую
// указывает s, постоянным байтом c.

void *s21_memset(void *s, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)s;
  for (size_t i = 0; i < n; i++) {
    ptr[i] = (unsigned char)c;
  }
  return s;
}
