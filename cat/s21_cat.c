#include "s21_cat.h"

int main(int argc, char **argv) {
  options opt = {0};

  if (parser(argc, argv, &opt)) {
    fprintf(stderr, "Usage: [-beEnstTv][file...]\n");
    return 1;
  }

  if (opt.b) {
    opt.n = 0;
  }
  open_file(argc, argv, opt);
  return 0;
}

int parser(int argc, char **argv, options *opt) {
  int c;
  int res = 0;
  // opterr = 0;
  while ((c = getopt_long(argc, argv, "beEnstTv", long_options, NULL)) != -1) {
    switch (c) {
      case 'b':
        opt->b = 1;
        break;
      case 'e':
        opt->e = 1;
        opt->v = 1;
        break;
      case 'E':
        opt->e = 1;
        break;
      case 'n':
        opt->n = 1;
        break;
      case 's':
        opt->s = 1;
        break;
      case 't':
        opt->t = 1;
        opt->v = 1;
        break;
      case 'T':
        opt->t = 1;
        break;
      case 'v':
        opt->v = 1;
        break;
      default:
        res = 1;
        break;
    }
  }
  return res;
}

void open_file(int argc, char **argv, options opt) {
  for (int i = optind; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (file == NULL) {
      fprintf(stderr, "%s: No such file or directory\n", argv[i]);
      continue;
    }
    print_file(opt, file);
    fclose(file);
  }
}

void print_file(options opt, FILE *file) {
  int current;
  static int count_str = 0;
  int start_new_line = 1;
  static int empty_str = 0;

  while ((current = fgetc(file)) != EOF) {
    if (opt.s && current == '\n') {
      empty_str += 1;
      if (empty_str > 2) {
        continue;
      }
    } else {
      empty_str = 0;
    }

    if (opt.b && current != '\n' && start_new_line) {
      printf("%6d\t", ++count_str);
      start_new_line = 0;
    }

    if (opt.e && current == '\n') {
      printf("$");
    }

    if (opt.n && start_new_line) {
      printf("%6d\t", ++count_str);
      start_new_line = 0;
    }

    if (opt.t && current == '\t') {
      printf("^I");
      continue;
    }

    if (opt.v && current != '\n' && current != '\t') {
      v_option(current);
    } else {
      printf("%c", current);
    }

    if (current == '\n') {
      start_new_line = 1;
    }
  }
}

void v_option(int current) {
  if (current >= 32 && current < 127) {
    printf("%c", current);
  } else if (current == 127) {
    printf("^?");
  } else if (current >= 128) {
    printf("M-");
    if (current >= 128 + 32 && current < 128 + 127) {
      printf("%c", current - 128);
    } else if (current == 128 + 127) {
      printf("^?");
    } else {
      printf("^%c", current - 128 + 64);
    }
  } else {
    printf("^%c", current + 64);
  }
}