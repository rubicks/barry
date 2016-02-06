# barry/configure.ac

AC_PREREQ([2.68])
AC_INIT([barry],
        [m4_esyscmd_s([git describe --always --dirty --tags])],
        [rubicks00@gmail.com],
        [barry],
        [https://github.com/rubicks/barry])

AC_LANG_PUSH([C])
AC_CONFIG_SRCDIR([barry.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
#AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE([foreign subdir-objects dist-bzip2 dist-xz tar-pax])
LT_PREREQ([2.4])
LT_INIT

# Checks for programs.
AC_PROG_CC_C99

# Checks for header files.
AC_HEADER_STDC # stdlib, stdarg, string, float.h
AC_CHECK_HEADER([getopt.h],[],[AC_MSG_ERROR([getopt.h missing])])

AC_CHECK_FUNCS([fmemopen])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
