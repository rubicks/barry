/* barry/barry.c */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <getopt.h>
#include <string.h>

#include "config.h"

#define WHEREAMI(STREAM)                                          \
  do {                                                            \
    fprintf(STREAM, "%s; %s:%d\n", __func__, __FILE__, __LINE__); \
  } while (0) /**/

#define FAIL_UNLESS(EXPR) \
  do {                    \
    if (!(EXPR)) {        \
      perror(#EXPR);      \
      WHEREAMI(stderr);   \
      exit(EXIT_FAILURE); \
    }                     \
  } while (0) /**/

#define MIN(X, Y) ((X) <= (Y) ? (X) : (Y))

static bool _goodc(char const c) { return isalnum(c) || ('_' == c); }

static char *_symbolize(char const *str) {
  static char buf[64];
  size_t i = 0;
  size_t n = MIN(strlen(str), sizeof(buf) - 1);
  memset(buf, 0, sizeof(buf));
  for (; i < n; ++i) {
    buf[i] = _goodc(str[i]) ? str[i] : '_';
  }
  return buf;
}

static void _usage(FILE *f, char *argv0) {
  fprintf(f, "\nUsage:");
  fprintf(f, "\n  %s [option]... [<file>...]", argv0);
  fprintf(f, "\n");
  fprintf(f, "\nOptions:");
  fprintf(f, "\n");
  fprintf(f, "\n  -V, --version     output version information and exit");
  fprintf(f, "\n  -h, --help        display this help and exit");
  fprintf(f, "\n  -o, --out <file>  write to specified file (default stdout)");
  fprintf(f, "\n  -n, --name <sym>  symbol name for stdin");
  fprintf(f, "\n");
  fprintf(f, "\n");
}

static void _readwrite(FILE *fin, FILE *fout, char *name) {
  if (name) {
    FAIL_UNLESS(
        0 <= fprintf(fout, "unsigned char const %s [] =\n", _symbolize(name)));
  }

  fprintf(fout, "{");
  char const *del = " ";
  for (int c = fgetc(fin), m = 0; EOF != c; c = fgetc(fin)) {
    FAIL_UNLESS(0 <= fprintf(fout, "%s0x%02x", del, c));
    del = (++m % 8) ? ", " : ",\n  ";
  }
  fprintf(fout, " };\n");
}

int main(int argc, char **argv) {
  FILE *fout = stdout;
  char *name = NULL;
  int c = 0;
  int optidx = 0;
  static struct option opts[] = {{"help", no_argument, 0, 'h'},
                                 {"version", no_argument, 0, 'V'},
                                 {"out", required_argument, 0, 'o'},
                                 {"name", required_argument, 0, 'n'},
                                 {0, 0, 0, 0}};
  while (-1 != (c = getopt_long(argc, argv, "Vho:n:", opts, &optidx))) {
    switch (c) {
      case 0:
        /* If this option set a flag, do nothing else now. */
        if (0 != opts[optidx].flag) {
          break;
        }
        printf("option %s", opts[optidx].name);
        if (optarg) {
          printf(" with arg %s", optarg);
        }
        printf("\n");
        break;
      case 'V':
        printf("%s\n", "barry v0.2.1");
        return EXIT_SUCCESS;
      case 'h':
        _usage(stdout, argv[0]);
        return EXIT_SUCCESS;
      case 'o': {
        FAIL_UNLESS(fout = fopen(optarg, "w"));
        break;
      }
      case 'n': {
        size_t len = 1 + strlen(optarg);
        FAIL_UNLESS(name = malloc(len));
        FAIL_UNLESS(memcpy(name, optarg, len));
        break;
      }
      default:
        fprintf(stderr, "getopt_long() returned '%c'", c);
      case '?':
        /* getopt_long already printed an error message. */
        _usage(stderr, argv[0]);
        return EXIT_FAILURE;
    }
  }
  if (optind < argc) {
    for (int i = optind, n = argc; i < n; ++i) {
      if (!strcmp("-", argv[i])) {
        /* do explicit stdin */
        _readwrite(stdin, fout, name);
      } else {
        /* do named file */
        FILE *fin;
        FAIL_UNLESS(fin = fopen(argv[i], "r"));
        _readwrite(fin, fout, argv[i]);
        FAIL_UNLESS(0 == fclose(fin));
      }
    }
  } else {
    _readwrite(stdin, fout, name);
  }
  free(name);
  name = NULL;
  FAIL_UNLESS(0 == fclose(fout));
  return EXIT_SUCCESS;
}
