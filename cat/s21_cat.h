#ifndef S21_CAT
#define S21_CAT
#include <getopt.h>
#include <stdio.h>
#include <string.h>

typedef struct options {
  int b, e, n, s, t, v;
  int file_count;

} options;
struct option long_options[] = {{"number", no_argument, NULL, 'n'},
                                {"number-nonblank", no_argument, NULL, 'b'},
                                {"squeeze-blank", no_argument, NULL, 's'},
                                {0, 0, 0, 0}};

int parser(int argc, char **argv, options *opt);
void print_file(options opt, FILE *file);
void open_file(int argc, char **argv, options opt);
void v_option(int current);
#endif
