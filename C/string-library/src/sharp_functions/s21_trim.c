#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

char *s21_trim(char *src, char *trim_chars) {
  if (src == s21_NULL || trim_chars == s21_NULL) {
    return s21_NULL;
  }
  int left_index = 0;
  int right_index = s21_strlen(src) - 1;
  while (left_index <= right_index &&
         s21_strchr(trim_chars, src[left_index]) != s21_NULL) {
    left_index++;
  }
  while (right_index >= left_index &&
         s21_strchr(trim_chars, src[right_index]) != s21_NULL) {
    right_index--;
  }
  char *result = s21_NULL;
  if (left_index > right_index) {
    result = (char *)calloc(1, sizeof(char));
    result[0] = '\0';
  } else if (right_index - left_index > 0) {
    result = (char *)calloc(right_index - left_index + 2, sizeof(char));
    s21_strncpy(result, src + left_index, right_index - left_index + 1);
  }
  return (void *)result;
}
