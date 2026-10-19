#include "s21_grep.h"

// grep exits with status 1 when no lines were selected.
static int found_any_match = 0;

int main(int argc, char* argv[]) {
  flags flag = GREP_FLAGS;
  char pattern[BUFF_SIZE] = {0};
  int res = parse_flags(argc, argv, &flag, pattern);
  if (res == 0) {
    count_files(&flag, pattern, argc, argv);
    if (!found_any_match) res = 1;
  }
  if (argc < 3) {
    fprintf(stderr, "Usage: %s [options] pattern [file...]\n", argv[0]);
    res = 1;
  }
  return res;
}

int parse_flags(int argc, char* argv[], flags* flag, char* pattern) {
  int c = 0;
  int res = 0;
  const char* options = "e:ivclnhsf:o";

  while ((c = getopt(argc, argv, options)) != -1) {
    switch (c) {
      case 'e':
        flag->e = 1;
        snprintf(pattern, BUFF_SIZE, "%s", optarg);
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'f':
        flag->f = 1;
        read_patterns_from_file(optarg, pattern);
        break;
      case 'o':
        flag->o = 1;
        break;
      default:
        fprintf(stderr, "Error: Unknown option\n");
        res = 1;
    }
  }
  if (!flag->e && !flag->f) {
    snprintf(pattern, BUFF_SIZE, "%s", argv[optind++]);
  }
  return res;
}

void read_patterns_from_file(char* filename, char* pattern) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Error: Cannot open file %s\n", filename);
    exit(1);
  }
  char line[BUFF_SIZE];
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = 0;
    strcat(pattern, line);
    strcat(pattern, "|");
  }
  pattern[strlen(pattern) - 1] = '\0';
  fclose(file);
}
void count_files(flags* flag, char* pattern, int argc, char* argv[]) {
  int fileCount = (argc - optind > 1);
  for (int i = optind; i < argc; i++) {
    process_file(flag, pattern, argv[i], fileCount);
  }
}

void process_file(flags* flag, char* pattern, char* filename, int fileCount) {
  regex_t re;
  int cflags = REG_EXTENDED;
  if (flag->i) {
    cflags |= REG_ICASE;
  }

  FILE* file = fopen(filename, "r");
  if (file != NULL) {
    if (regcomp(&re, pattern, cflags) != 0) {
      if (!flag->s) fprintf(stderr, "Error compiling regex\n");
      fclose(file);
      return;
    }
    process_line(flag, file, re, filename, fileCount);
    regfree(&re);
    fclose(file);
  } else if (!flag->s) {
    fprintf(stderr, "Error opening file: %s\n", filename);
  }
}

void process_line(flags* flag, FILE* fp, regex_t re, char* file,
                  int fileCount) {
  char text[BUFF_SIZE] = {0};
  regmatch_t pmatch[1];
  int lineMatches = 0;
  int nline = 1;

  while (fgets(text, BUFF_SIZE, fp) != NULL) {
    int match = 0;
    int result = regexec(&re, text, 1, pmatch, 0);
    if (strchr(text, '\n') == NULL) {
      strcat(text, "\n");
    }
    if (result == 0 && !flag->v) {
      match = 1;
    }
    if (result == REG_NOMATCH && flag->v) {
      match = 1;
    }
    if (match && !flag->l && !flag->c) {
      output_line(flag, text, file, nline, fileCount);
    }
    lineMatches += match;
    nline++;
  }

  if (lineMatches > 0) found_any_match = 1;

  if (flag->c && flag->l) {
    if (fileCount && !flag->h) {
      printf("%s:", file);
    }
    if (lineMatches > 0) {
      printf("1\n");
    } else {
      printf("0\n");
    }
  }
  if (flag->l && lineMatches > 0) {
    printf("%s\n", file);
  }
  if (flag->c && !flag->l) {
    if (fileCount && !flag->h) {
      printf("%s:", file);
    }
    printf("%d\n", lineMatches);
  }
}

void output_line(flags* flag, char* text, char* file, int nline,
                 int fileCount) {
  if (fileCount && !flag->h && flag->n) {
    printf("%s:%d:", file, nline);
  } else if (fileCount && !flag->h) {
    printf("%s:", file);
  } else if (flag->n) {
    printf("%d:", nline);
  }

  if (flag->o && !flag->v) {
    regex_t re;
    regmatch_t pmatch[1];
    regcomp(&re, text, REG_EXTENDED | (flag->i ? REG_ICASE : 0));
    char* start = text;
    while (regexec(&re, start, 1, pmatch, 0) == 0) {
      printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
             start + pmatch[0].rm_so);
      start += pmatch[0].rm_eo;
    }
    regfree(&re);
  } else {
    printf("%s", text);
  }
}