AC_INIT([libboomblaster], 0.1)
AC_CONFIG_MACRO_DIR([build])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_HEADERS([config.h])
AC_PROG_CXX
AM_INIT_AUTOMAKE
AC_ENABLE_SHARED
AC_DISABLE_STATIC
LT_INIT

CPPFLAGS="$CPPFLAGS \
    -I../../src \
    -I../../include \
    -L/usr/local/lib"

AC_CONFIG_FILES([Makefile boomblaster.pc])

AC_OUTPUT

