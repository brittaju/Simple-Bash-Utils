#include "s21_grep.h"

int main(int argc, char* argv[]) {
  flags f = {0};
  f.pattern = malloc(MAX_PATTERN_SIZE);
  if (f.pattern == NULL) {
    fprintf(stderr, "Error: Not enough memory\n");
    return 1;
  }
  int parse_result = parse_flags(argc, argv, &f);
  if (parse_result != 0 || strlen(f.pattern) == 0) {
    fprintf(stderr, "Usage: grep [OPTIONS] PATTERN [FILE...]\n");
    free(f.pattern);
    return 1;
  }
  if (optind < argc) {
    for (int i = optind; i < argc; i++) {
      grep_file(argv[i], f);
    }
  } else {
    grep_file(NULL, f);
  }
  free(f.pattern);
  return 0;
}

int parse_flags(int argc, char* argv[], flags* f) {
  int opt;
  int e_count = 0;
  while ((opt = getopt(argc, argv, "e:ivcln")) != -1) {
    switch (opt) {
      case 'e':
        strncpy(f->pattern, optarg, MAX_PATTERN_SIZE - 1);
        f->pattern[MAX_PATTERN_SIZE - 1] = '\0';
        e_count = 1;
        break;
      case 'i':
        f->i = REG_ICASE;
        break;
      case 'v':
        f->v = 1;
        break;
      case 'c':
        f->c = 1;
        break;
      case 'l':
        f->l = 1;
        break;
      case 'n':
        f->n = 1;
        break;
      default:
        fprintf(stderr, "grep: invalid option -- '%c'\n", optopt);
        return 1;
    }
  }
  if (!e_count && optind < argc) {
    strncpy(f->pattern, argv[optind], MAX_PATTERN_SIZE - 1);
    f->pattern[MAX_PATTERN_SIZE - 1] = '\0';
    optind++;
  }
  return 0;
}

void grep_file(char* filename, flags f) {
  FILE* fp = (filename == NULL) || (strcmp(filename, "-") == 0)
                 ? stdin
                 : fopen(filename, "r");
  if (fp == NULL) {
    fprintf(stderr, "grep: %s: No such file or directory\n", filename);
    return;
  }
  regex_t preg;
  if (regcomp(&preg, f.pattern, f.i) != 0) {
    fprintf(stderr, "grep: Invalid regular expression.\n");
    if (fp != stdin) {
      fclose(fp);
    }
    return;
  }
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  int line_counter = 0;
  int match_counter = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    line_counter++;
    int match = regexec(&preg, line, 0, NULL, 0);
    if ((match == 0 && !f.v) || (match != 0 && f.v)) {
      match_counter++;
      if (!f.l && !f.c) {
        if (f.n) {
          printf("%d:", line_counter);
        }
        printf("%s", line);
        if (read > 0 && line[read - 1] != '\n') {
          printf("\n");
        }
      }
    }
  }
  if (f.l && match_counter > 0) {
    printf("%s\n", filename);
  } else if (f.c) {
    printf("%d\n", match_counter);
  }
  free(line);
  regfree(&preg);
  if (fp != stdin) {
    fclose(fp);
  }
}