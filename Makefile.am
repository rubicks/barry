# barry/Makefile.am

ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS = -Wall -Wextra -Werror -pedantic-errors # -rdynamic


# noinst_LTLIBRARIES = libbarry.la

# libbarry_la_SOURCES = barry.cc barry.hh barry_detail.hh


bin_PROGRAMS = barry

barry_SOURCES = barry.c

# barry_LDADD = libbarry.la


# check_PROGRAMS = \
#   test_options

# test_options_SOURCES = test/options.cc

# test_options_LDADD = libbarry.la

# TESTS = $(check_PROGRAMS)



check_SCRIPTS = \
    test.sh


TESTS = $(check_SCRIPTS)

EXTRA_DIST = $(check_SCRIPTS)
