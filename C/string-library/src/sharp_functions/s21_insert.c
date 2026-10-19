#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == s21_NULL || str == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t src_length = s21_strlen(src);
  s21_size_t str_length = s21_strlen(str);

  if (start_index > src_length) {
    return s21_NULL;
  }

  char *now_str = (char *)malloc(src_length + str_length + 1);
  if (now_str == s21_NULL) {
    return s21_NULL;
  }

  s21_strncpy(now_str, src, start_index);
  now_str[start_index] = '\0';

  s21_strcpy(now_str + start_index, str);
  s21_strcpy(now_str + start_index + str_length, src + start_index);

  return now_str;
}
