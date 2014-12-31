# barry/configure.ac

AC_PREREQ([2.68])
AC_INIT([barry],
        [m4_esyscmd_s([git describe --always --dirty])],
        [rubicks00@gmail.com],
        [barry],
        [https://github.com/rubicks/barry])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AC_LANG_PUSH([C])
AC_CONFIG_SRCDIR([barry.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([subdir-objects])
LT_PREREQ([2.4])
LT_INIT([dlopen])

AC_MSG_NOTICE([build_cpu     == $build_cpu])
AC_MSG_NOTICE([build_vendor  == $build_vendor])
AC_MSG_NOTICE([build_os      == $build_os])
AC_MSG_NOTICE([host_cpu      == $host_cpu])
AC_MSG_NOTICE([host_vendor   == $host_vendor])
AC_MSG_NOTICE([host_os       == $host_os])
AC_MSG_NOTICE([target_cpu    == $target_cpu])
AC_MSG_NOTICE([target_vendor == $target_vendor])
AC_MSG_NOTICE([target_os     == $target_os])

# Checks for programs.
AC_PROG_CC_C99
# AX_CXX_COMPILE_STDCXX_11
# AC_PROG_CC


# Checks for libraries.
#
# nothing here yet


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


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
