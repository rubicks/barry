# barry/Makefile.am

ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS = -Wall -Wextra -Werror -pedantic-errors # -rdynamic


noinst_LTLIBRARIES = libbarry.la

libbarry_la_SOURCES = barry.cc barry.hh barry_detail.hh


bin_PROGRAMS = barry

barry_SOURCES = main.cc

barry_LDADD = libbarry.la


check_PROGRAMS = \
  test_options

test_options_SOURCES = test/options.cc

test_options_LDADD = libbarry.la

TESTS = $(check_PROGRAMS)
