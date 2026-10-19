#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 10000

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} flags;

#define GREP_FLAGS \
  {.e = 0,         \
   .i = 0,         \
   .v = 0,         \
   .c = 0,         \
   .l = 0,         \
   .n = 0,         \
   .h = 0,         \
   .s = 0,         \
   .f = 0,         \
   .o = 0}

int parse_flags(int argc, char* argv[], flags* flag, char* pattern);
void count_files(flags* flag, char* pattern, int argc, char* argv[]);
void process_file(flags* flag, char* pattern, char* filename, int fileCount);
void process_line(flags* flag, FILE* fp, regex_t re, char* file, int fileCount);
void output_line(flags* flag, char* text, char* file, int nline, int fileCount);
void read_patterns_from_file(char* filename, char* pattern);

#endif