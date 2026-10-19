#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} flags;

#define FLAGS {0, 0, 0, 0, 0, 0}

void added_file(int argc, char **argv, flags *flag);
void print_file(flags flag, const char *file_name);
void print_unprint(flags flag, int c);
void print_char(flags flag, int c);
int flags_cat(int argc, char *argv[], flags *flag);

#endif