#include "../s21_string.h"

void transform_float(double num, char* str, int accuracy) {
  int integer_part = (int)num;
  double fractional_part = num - integer_part;

  int i = 0;
  if (num < 0) {
    str[i++] = '-';
    integer_part = -integer_part;
    fractional_part = -fractional_part;
  }

  int temp = integer_part;
  char temp_str[64];
  int temp_i = 0;

  do {
    temp_str[temp_i++] = '0' + temp % 10;
    temp /= 10;
  } while (temp > 0);

  for (int j = temp_i - 1; j >= 0; j--) {
    str[i++] = temp_str[j];
  }

  str[i++] = '.';

  if (accuracy <= 0) {
    accuracy = 6;
  }

  double rounding = 0.5;
  for (int j = 0; j < accuracy; j++) {
    rounding /= 10.0;
  }
  fractional_part += rounding;

  for (int j = 0; j < accuracy; j++) {
    fractional_part *= 10;
    int digit = (int)fractional_part;
    str[i++] = '0' + digit;
    fractional_part -= digit;
  }

  str[i] = '\0';
}

void transform_int(int num, char* str) {
  int i = 0, isNegative = 0;
  if (num < 0) {
    isNegative = 1;
    num = -num;
  }
  if (num < 0) {
    isNegative = 1;
    num = -num;
  }
  do {
    str[i++] = (num % 10) + '0';
    num /= 10;
  } while (num > 0);
  if (isNegative) {
    str[i++] = '-';
  }

  str[i] = '\0';

  for (int j = 0; j < i / 2; j++) {
    char temp = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = temp;
  }
}

void transform_unsigned_int(unsigned int num, char* str) {
  int i = 0;
  do {
    str[i++] = (num % 10) + '0';
    num /= 10;
  } while (num > 0);
  str[i] = '\0';
  for (int j = 0; j < i / 2; j++) {
    char temp = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = temp;
  }
}

void write_result(char* buffer, const char* str, int* writen, int* index) {
  while (*str) {
    buffer[(*index)++] = *str++;
    (*writen)++;
  }
}

void write_int(char* buffer, int* writen, int* index, int num, int flag_plus,
               int flag_minus, int competition, int flag_space) {
  if (flag_plus == 1 && num >= 0) {
    buffer[(*index)++] = '+';
    (*writen)++;
  }
  char number[12];
  transform_int(num, number);
  if (flag_space == 1) {
    buffer[(*index)++] = ' ';
    (*writen)++;
  }
  write_result(buffer, number, writen, index);

  if (flag_minus == 1) {
    for (int i = 0; i <= competition; i++) {
      buffer[(*index)++] = ' ';
    }
  }
}

void write_float(char* buffer, int* writen, int* index, double num,
                 int accuracy, int flag_plus, int flag_minus, int competition,
                 int flag_space) {
  if (flag_plus == 1 && num >= 0) {
    buffer[(*index)++] = '+';
    (*writen)++;
  }
  char number[64];
  transform_float(num, number, accuracy);
  if (flag_space == 1) {
    buffer[(*index)++] = ' ';
    (*writen)++;
  }
  write_result(buffer, number, writen, index);
  if (flag_minus == 1) {
    for (int i = 0; i <= competition; i++) {
      buffer[(*index)++] = ' ';
    }
  }
}

void write_str(char* buffer, int* writen, int* index, const char* str,
               int accuracy, int flag_minus, int competition) {
  int count = 0;
  while (*str && (accuracy == 0 || count < accuracy)) {
    buffer[(*index)++] = *str++;
    (*writen)++;
    count++;
  }
  if (flag_minus == 1) {
    for (int i = 0; i <= competition; i++) {
      buffer[(*index)++] = ' ';
    }
  }
}

void write_char(char* buffer, int* writen, int* index, char c, int flag_minus,
                int competition) {
  buffer[(*index)++] = c;
  (*writen)++;
  if (flag_minus == 1) {
    for (int i = 0; i <= competition; i++) {
      buffer[(*index)++] = ' ';
    }
  }
}

void write_unsigned(char* buffer, int* writen, int* index, unsigned int num,
                    int flag_minus, int competition, int flag_space) {
  char number[12];
  transform_unsigned_int(num, number);
  if (flag_space == 1) {
    buffer[(*index)++] = ' ';
    (*writen)++;
  }
  write_result(buffer, number, writen, index);
  if (flag_minus == 1) {
    for (int i = 0; i <= competition; i++) {
      buffer[(*index)++] = ' ';
    }
  }
}

int s21_sprintf(char* buffer, const char* format,
                ...) {  // s21_printf(buffer, "age:%d", age)
  va_list args;
  va_start(args, format);
  int writen = 0, i = 0, flag_plus = 0, flag_minus = 0, flag_space = 0,
      accuracy = 0, competition = 0;
  for (int j = 0; format[j] != '\0'; j++) {
    if (format[j] == '%') {
      flag_plus = 0, flag_minus = 0, flag_space = 0, accuracy = 0, j++;
      if (format[j] == '.') {
        int temp_number = 0;
        char temp_accuracy[256];
        for (int i = j + 1; format[i] != 's' && format[i] != 'f'; i++) {
          temp_accuracy[temp_number] = format[i];
          temp_number++;
        }
        j += temp_number + 1;
        accuracy = atoi(temp_accuracy);
      }
      if (format[j] == '-') {
        flag_minus = 1;
        int temp_number = 0;
        char temp_competition[256];
        for (int i = j + 1;
             format[i] != 's' && format[i] != 'f' && format[i] != 'd' &&
             format[i] != 'c' && format[i] != 'u';
             i++) {
          temp_competition[temp_number] = format[i];
          temp_number++;
        }
        j += temp_number + 1;
        competition = atoi(temp_competition);
      }
      if (format[j] == '+') {
        flag_plus = 1, j++;
      }
      if (format[j] == ' ') {
        flag_space = 1, j++;
      }
      if (format[j] == 'c') {
        char target = (char)va_arg(args, int);
        write_char(buffer, &writen, &i, target, flag_minus, competition);
      } else if (format[j] == 's') {
        const char* target = va_arg(args, const char*);
        write_str(buffer, &writen, &i, target, accuracy, flag_minus,
                  competition);
      } else if (format[j] == 'd') {
        int target = va_arg(args, int);
        write_int(buffer, &writen, &i, target, flag_plus, flag_minus,
                  competition, flag_space);
      } else if (format[j] == '%') {
        buffer[i++] = '%';
        writen++;
      } else if (format[j] == 'f') {
        double target = va_arg(args, double);
        write_float(buffer, &writen, &i, target, accuracy, flag_plus,
                    flag_minus, competition, flag_space);
      } else if (format[j] == 'u') {
        unsigned int target = va_arg(args, unsigned int);
        write_unsigned(buffer, &writen, &i, target, flag_minus, competition,
                       flag_space);
      }
    } else {
      buffer[i++] = format[j];
      writen++;
    }
  }
  buffer[i] = '\0';
  va_end(args);
  return writen;
}
