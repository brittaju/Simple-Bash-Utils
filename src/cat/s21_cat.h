#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int v;
  int n;
  int s;
  int t;
} flags;

void parse_flags(int argc, char* argv[], flags* f);
void cat_file(char* argv, flags f);

#endif
