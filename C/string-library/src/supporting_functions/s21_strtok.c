#include <string.h>

#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *current = s21_NULL;
  char *start;
  if (str == s21_NULL && current == s21_NULL) return s21_NULL;
  if (str != s21_NULL)
    current = str;
  else if (current == s21_NULL)
    return s21_NULL;
  while (*current != '\0' && strchr(delim, *current) != s21_NULL) current++;
  if (*current == '\0') return s21_NULL;
  start = current;
  while (*current && strchr(delim, *current) == s21_NULL) current++;
  if (*current) {
    *current = '\0';
    current++;
  }
  return start;
}
