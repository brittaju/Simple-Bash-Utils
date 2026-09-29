#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATTERN_SIZE 256

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  char* pattern;
} flags;

int parse_flags(int argc, char* argv[], flags* f);
void grep_file(char* argv, flags f);

#endif
