#include "s21_grep.h"

int parse_grep_option(int argc, char **argv, grep_opt *opt) {
  int res = 0, arg_count = 0, c;

  while ((c = getopt(argc, argv, "e:ivclnshf:o")) != -1) {
    switch (c) {
      case 'e':
        opt->e = 1;
        e_option(&arg_count, opt, optarg);
        break;
      case 'i':
        opt->i = 1;
        break;
      case 'v':
        opt->v = 1;
        break;
      case 'c':
        opt->c = 1;
        break;
      case 'l':
        opt->l = 1;
        break;
      case 'n':
        opt->n = 1;
        break;
      case 's':
        opt->s = 1;
        break;
      case 'h':
        opt->h = 1;
        break;
      case 'o':
        opt->o = 1;
        break;
      case 'f':
        opt->f = 1;
        f_option(&arg_count, opt, optarg);
        break;
      default:
        res = 1;
        break;
    }
  }
  if (!opt->e && optind < argc && !opt->f) {
    e_option(&arg_count, opt, argv[optind]);
    optind++;
  }
  return res;
}

void new_pattern(grep_opt *opt, char *add_pattern, int *arg_count) {
  size_t new_size = strlen(opt->pattern) + strlen(add_pattern) + 1;
  if (*arg_count) {
    new_size += 1;
  }

  char *new_pattern = realloc(opt->pattern, new_size);
  if (new_pattern == NULL) {
    free(opt->pattern);
    opt->pattern = NULL;
  }
  opt->pattern = new_pattern;

  if (*arg_count) {
    strcat(opt->pattern, "|");
  }

  strcat(opt->pattern, add_pattern);

  *arg_count += 1;
}

void e_option(int *arg_count, grep_opt *opt, char *add_pattern) {
  if (add_pattern == NULL || add_pattern[0] == '\0') {
    add_pattern = ".";
  }

  new_pattern(opt, add_pattern, arg_count);
}

void o_option(size_t nmatch, regmatch_t pmatch[1], char *ptr, regex_t *regex,
              int res_regexec) {
  while (!res_regexec) {
    if (pmatch[0].rm_eo == pmatch[0].rm_so) continue;

    if (ptr != NULL) {
      printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
             ptr + pmatch[0].rm_so);
      ptr += pmatch[0].rm_eo;
    }
    res_regexec = regexec(regex, ptr, nmatch, pmatch, REG_NOTBOL);
  }
}

void f_option(int *arg_count, grep_opt *opt, char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    if (!opt->s) {
      fprintf(stderr, "Error: cannot open file '%s'\n", filename);
    }
    return;
  }

  char *line = NULL;

  while ((line = read_str(file)) != NULL) {
    if (line[strlen(line) - 1] == '\n') {
      line[strlen(line) - 1] = '\0';
    }
    new_pattern(opt, line, arg_count);

    free(line);
  }

  fclose(file);
}