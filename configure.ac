# barry/configure.ac

AC_PREREQ([2.68])
AC_INIT([barry],
        [0.1.0-snapshot],
        [rubicks00@gmail.com],
        [barry],
        [https://github.com/rubicks/barry])
AC_LANG_PUSH([C])
AC_CONFIG_SRCDIR([barry.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([subdir-objects])
LT_PREREQ([2.4])
LT_INIT([dlopen])

# Checks for programs.
AC_PROG_CC_C99
# AX_CXX_COMPILE_STDCXX_11
# AC_PROG_CC


# Checks for libraries.

dnl AX_BOOST_BASE([1.46.0],,AC_MSG_ERROR([Boost >= v1.46.0 missing]))

dnl AC_CHECK_LIB([boost_program_options],[main],[],
dnl   [AC_MSG_ERROR([libboost_program_options missing])])


# Checks for header files.

AC_CHECK_HEADER([getopt.h], [],[AC_MSG_ERROR([getopt.h missing])])
AC_CHECK_HEADER([stdbool.h],[],[AC_MSG_ERROR([stdbool.h missing])])
AC_CHECK_HEADER([stdint.h], [],[AC_MSG_ERROR([stdint.h missing])])
AC_CHECK_HEADER([stdlib.h], [],[AC_MSG_ERROR([stdlib.h missing])])


# Checks for typedefs, structures, and compiler characteristics.

AC_C_INLINE

AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T


# Checks for library functions.

AC_CHECK_FUNCS([fmemopen])


# Checks for symbol declarations

dnl AC_CHECK_DECLS([M_PI],
dnl   [],
dnl   [AC_MSG_ERROR([M_PI missing])],
dnl   [[#include <math.h>]])


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
