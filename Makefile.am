# barry/Makefile.am

ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic-errors

bin_PROGRAMS = barry
barry_SOURCES = barry.c

TESTS = $(bin_PROGRAMS)

LOG_COMPILER = $(srcdir)/test-wrapper.sh

EXTRA_DIST = $(LOG_COMPILER)
