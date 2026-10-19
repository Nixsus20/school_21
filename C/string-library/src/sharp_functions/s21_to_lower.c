#include "../s21_string.h"

char *s21_to_lower(const char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }
  s21_size_t length = s21_strlen(str);
  char *low_str = (char *)malloc(length + 1);
  for (s21_size_t i = 0; i < length; i++) {
    if (str[i] >= 65 && str[i] <= 90) {
      low_str[i] = str[i] + 32;
    } else
      low_str[i] = str[i];
  }
  low_str[length] = '\0';
  return low_str;
}