#ifndef S21_GREP
#define S21_GREP

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct grep_options {
  int e, i, v, c, l, n, s, h, f, o;
  char *pattern;
  int files_count;
} grep_opt;

int parse_grep_option(int argc, char **argv, grep_opt *opt);
void open_file(int argc, char **argv, grep_opt *opt, regex_t *regex);
void output(FILE *file, grep_opt *opt, char *filename, regex_t *regex);
regex_t *compile_regex(grep_opt *opt);
char *read_str(FILE *file);
void e_option(int *arg_count, grep_opt *opt, char *add_pattern);
void f_option(int *arg_count, grep_opt *opt, char *filename);

void o_option(size_t nmatch, regmatch_t pmatch[1], char *ptr, regex_t *regex,
              int res_regexec);
void print_filename(char *filename, grep_opt *opt);
void print_str(char *str, grep_opt *opt, size_t line_number, char *filename,
               int *filename_printed, regex_t *regex, regmatch_t pmatch[1],
               int res_regexec);
void print_line(char *str, size_t line_number, grep_opt *opt);
void free_resources(regex_t *regex, grep_opt *opt);

#endif
