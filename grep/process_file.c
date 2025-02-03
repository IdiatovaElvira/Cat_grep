#include "s21_grep.h"

void open_file(int argc, char **argv, grep_opt *opt, regex_t *regex) {
  opt->files_count = argc - optind;
  for (; optind < argc; optind++) {
    FILE *file = fopen(argv[optind], "r");
    if (file != NULL) {
      output(file, opt, argv[optind], regex);
      fclose(file);
    } else if (!opt->s) {
      fprintf(stderr, "%s: No such file or directory\n", argv[optind]);
    }
  }
}

regex_t *compile_regex(grep_opt *opt) {
  int regflag = REG_EXTENDED;

  if (opt->i) {
    regflag |= REG_ICASE;
  }
  regex_t *regex = malloc(sizeof(regex_t));
  int res_comp = regcomp(regex, opt->pattern, regflag);
  if (res_comp) {
    if (!opt->s) {
      fprintf(stderr, "Error. Failed to compile expression\n");
    }
    free_resources(regex, opt);
    return NULL;
  }
  return regex;
}

char *read_str(FILE *file) {
  char *result = NULL;
  int size = 1024;
  int ch = 0;
  int len = 0;
  char *new_str;
  char *str = (char *)malloc(size * sizeof(char));
  if (str == NULL) {
    return NULL;
  }

  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      str[len++] = ch;
      break;
    }

    if (len >= size - 1) {
      size *= 2;
      new_str = (char *)realloc(str, size * sizeof(char));
      if (new_str == NULL) {
        free(str);
        return NULL;
      } else {
        str = new_str;
      }
    }
    str[len++] = ch;
  }

  str[len] = '\0';

  if (len == 0 && ch == EOF) {
    free(str);
    result = NULL;
  } else {
    result = str;
  }
  return result;
}
void print_line(char *str, size_t line_number, grep_opt *opt) {
  if (opt->n) {
    printf("%zu:", line_number);
  }
  if (str != NULL) {
    if (str[strlen(str) - 1] == '\n') {
      printf("%s", str);
    } else {
      printf("%s\n", str);
    }
  }
}

void print_str(char *str, grep_opt *opt, size_t line_number, char *filename,
               int *filename_printed, regex_t *regex, regmatch_t pmatch[1],
               int res_regexec) {
  if (!opt->c && !opt->l) {
    if (opt->v) {
      if (res_regexec == REG_NOMATCH) {
        print_filename(filename, opt);
        print_line(str, line_number, opt);
      }
    } else {
      print_filename(filename, opt);
      if (opt->o) {
        o_option(1, pmatch, str, regex, res_regexec);
        *filename_printed = 0;
      } else {
        print_line(str, line_number, opt);
      }
    }
  }
}

void output(FILE *file, grep_opt *opt, char *filename, regex_t *regex) {
  char *str = NULL;
  size_t line_number = 1;
  size_t lines_count = 0;
  regmatch_t pmatch[1] = {0};
  int filename_printed = 1;

  while ((str = read_str(file)) != NULL) {
    int res_regexec = regexec(regex, str, 1, pmatch, 0);
    if ((res_regexec != REG_NOMATCH && !opt->v) ||
        (res_regexec == REG_NOMATCH && opt->v)) {
      print_str(str, opt, line_number, filename, &filename_printed, regex,
                pmatch, res_regexec);
      lines_count += 1;
    }
    free(str);
    line_number += 1;
  }

  if (opt->c) {
    print_filename(filename, opt);
    if (opt->l && lines_count)
      printf("1\n");
    else
      printf("%zu\n", lines_count);
  }

  if (opt->l && lines_count && !opt->h) {
    printf("%s\n", filename);
  }
}

void free_resources(regex_t *regex, grep_opt *opt) {
  regfree(regex);
  free(regex);
  free(opt->pattern);
}

void print_filename(char *filename, grep_opt *opt) {
  if (filename != NULL && opt->files_count > 1 && !opt->h) {
    printf("%s:", filename);
  }
}