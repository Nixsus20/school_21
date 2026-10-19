#include "../s21_string.h"

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  char* cur = dest;
  while (*src != '\0' && n > 0) {
    *dest = *src;
    dest++;
    src++;
    n--;
  }
  *dest = '\0';
  return cur;
}