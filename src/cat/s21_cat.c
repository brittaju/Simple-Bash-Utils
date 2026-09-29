#include "s21_cat.h"

int main(int argc, char* argv[]) {
  flags f = {0};
  parse_flags(argc, argv, &f);
  if (optind >= argc) {
    cat_file(NULL, f);
  } else {
    for (int i = optind; i < argc; i++) {
      cat_file(argv[i], f);
    }
  }
  return 0;
}

void parse_flags(int argc, char* argv[], flags* f) {
  int opt;
  static struct option long_options[] = {
      {"number-nonblank", no_argument, 0, 'b'},
      {"number", no_argument, 0, 'n'},
      {"squeeze-blank", no_argument, 0, 's'},
      {0, 0, 0, 0}};
  while ((opt = getopt_long(argc, argv, "bevEnstT", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        f->b = 1;
        break;
      case 'e':
        f->e = 1;
        f->v = 1;
        break;
      case 'v':
        f->v = 1;
        break;
      case 'E':
        f->e = 1;
        break;
      case 'n':
        f->n = 1;
        break;
      case 's':
        f->s = 1;
        break;
      case 't':
        f->t = 1;
        f->v = 1;
        break;
      case 'T':
        f->t = 1;
        break;
      default:
        fprintf(stderr, "cat: invalid option -- '%c'\n", optopt);
        fprintf(stderr, "Usage: cat [OPTIONS] [FILE...]\n");
        exit(1);
    }
  }
}

void cat_file(char* filename, flags f) {
  FILE* fp = (filename == NULL) || (strcmp(filename, "-") == 0)
                 ? stdin
                 : fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "cat: %s: No such file or directory\n", filename);
    return;
  }
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  int line_counter = 1;
  int empty_line_counter = 0;
  char last_char = '\n';
  while ((read = getline(&line, &len, fp)) != -1) {
    int empty_line = (read == 1 && line[0] == '\n');
    if (f.s && empty_line) {
      empty_line_counter++;
      if (empty_line_counter > 1) {
        continue;
      }
    } else {
      empty_line_counter = 0;
    }
    if (f.n || (f.b && !empty_line)) {
      printf("%6d\t", line_counter++);
    }
    for (int i = 0; i < read; i++) {
      char current_char = line[i];
      if (f.t && current_char == '\t') {
        printf("^I");
      } else if (f.e && current_char == '\n') {
        if (last_char == '\r') {
          printf("^M$\n");
        } else {
          printf("$\n");
        }
      } else if (f.v && current_char != '\t' && current_char != '\n') {
        unsigned char unsigned_current_char = (unsigned char)current_char;
        if (unsigned_current_char >= 128) {
          printf("M-");
          unsigned_current_char -= 128;
        }
        if (unsigned_current_char == 127) {
          printf("^?");
        } else if (unsigned_current_char < 32) {
          printf("^%c", unsigned_current_char + 64);
        } else {
          putchar(unsigned_current_char);
        }
      } else {
        putchar(current_char);
      }
      last_char = current_char;
    }
  }
  free(line);
  if (fp != stdin) {
    fclose(fp);
  }
}