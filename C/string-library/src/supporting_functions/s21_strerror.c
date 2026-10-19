#include "s21_strerror.h"

#include "../s21_string.h"

char* s21_strerror(int errnum) {
  static char str[BUFF_SIZE] = {'\0'};

  if (errnum < 0 || errnum >= MAX_ERROR)
#if defined(__APPLE__) || defined(__MACH__)
    s21_sprintf(str, "Unknown error: %d", errnum);
#elif defined(__unix__)
    s21_sprintf(str, "Unknown error %d", errnum);
#endif
  else
    s21_strcpy(str, errlist[errnum]);

  return str;
}
