#include "s21_cat.h"

int main(int argc, char **argv) {
  flags flag = FLAGS;
  flags_cat(argc, argv, &flag);
  added_file(argc, argv, &flag);
  return 0;
}

void added_file(int argc, char **argv, flags *flag) {
  if (optind < argc) {
    for (int i = optind; i < argc; i++) {
      print_file(*flag, argv[i]);
      optind++;
    }
  } else {
    fprintf(stderr, "No input files provided.\n");
  }
}

void print_file(flags flag, const char *file_name) {
  FILE *fp = fopen(file_name, "r");
  if (!fp) {
    fprintf(stderr, "Cannot open file: %s\n", file_name);
    return;
  }

  int c = 0;
  int prev_c = '\n';
  int count = 1;
  int squeeze = 0;

  while ((c = getc(fp)) != EOF) {
    if (flag.s && c == '\n' && prev_c == '\n') {
      squeeze++;
    } else {
      squeeze = 0;
    }
    if (squeeze > 1) {
      prev_c = c;
    } else {
      if (flag.n && prev_c == '\n') {
        printf("%6d\t", count++);
      }
      if (flag.b && prev_c == '\n' && c != '\n') {
        printf("%6d\t", count++);
      }

      print_unprint(flag, c);
      prev_c = c;
    }
  }
  fclose(fp);
}

void print_unprint(flags flag, int c) {
  if (flag.v || flag.e || flag.t) {
    if (c < 32 && c != 9 && c != 10) {
      printf("^%c", c + 64);
    } else if (c == 127) {
      printf("^?");
    } else {
      print_char(flag, c);
    }
  } else {
    print_char(flag, c);
  }
}

void print_char(flags flag, int c) {
  if (flag.t && c == '\t') {
    printf("^I");
  } else if (flag.e && c == '\n') {
    printf("$\n");
  } else {
    putchar(c);
  }
}

int flags_cat(int argc, char *argv[], flags *flag) {
  int c;
  const char *f_options = "bEnstTve";
  static struct option long_options[] = {
      {"number-nonblank", no_argument, 0, 'b'},
      {"number", no_argument, 0, 'n'},
      {"squeeze-blank", no_argument, 0, 's'},
      {0, 0, 0, 0},
  };
  int error_flag = 0;

  while ((c = getopt_long(argc, argv, f_options, long_options, NULL)) != -1) {
    switch (c) {
      case 'b':
        flag->b = 1;
        break;
      case 'E':
        flag->e = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->t = 1;
        flag->v = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'e':

        flag->e = 1;
        flag->v = 1;
        break;
      case 'T':
        flag->t = 1;
        break;
      default:
        fprintf(stderr, "error\n");
        error_flag = 1;
    }
    if (flag->b && flag->n) flag->n = 0;
  }

  return error_flag;
}