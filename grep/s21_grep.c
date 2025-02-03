#include "s21_grep.h"

int main(int argc, char **argv) {
  grep_opt opt = {0};
  opt.pattern = malloc(1);
  opt.pattern[0] = '\0';

  int parse_error = parse_grep_option(argc, argv, &opt);
  if (parse_error) {
    fprintf(stderr, "Usage: [-eivcln][file...]\n");
    free(opt.pattern);
    return 1;
  }

  regex_t *regex = compile_regex(&opt);
  if (regex == NULL) {
    free(opt.pattern);
    return 1;
  }

  open_file(argc, argv, &opt, regex);
  free_resources(regex, &opt);
  return 0;
}