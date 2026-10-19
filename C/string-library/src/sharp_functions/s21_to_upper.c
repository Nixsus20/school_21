#include "../s21_string.h"

char *s21_to_upper(const char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }
  s21_size_t length = s21_strlen(str);
  char *up_str = (char *)malloc(length + 1);
  for (s21_size_t i = 0; i < length; i++) {
    if (str[i] >= 97 && str[i] <= 122) {
      up_str[i] = str[i] - 32;
    } else
      up_str[i] = str[i];
  }
  up_str[length] = '\0';
  return up_str;
}