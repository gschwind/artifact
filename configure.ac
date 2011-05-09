#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([artifact], [0.0.1], [gschwind@gnu-log.net])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
SDL_VERSION=1.2.5
AM_PATH_SDL($SDL_VERSION,
            SDL_LIBS=`$SDL_CONFIG --libs`,
            AC_MSG_ERROR([You need to install the SDL library $SDL_VERSION])
)

	 
PKG_CHECK_MODULES([GL], [gl >= 7.5.2])
PKG_CHECK_MODULES([IL], [IL >= 1.7.7])
PKG_CHECK_MODULES([ILU], [ILU >= 1.7.7])
PKG_CHECK_MODULES([ILUT], [ILUT >= 1.7.7])
PKG_CHECK_MODULES([GTK], [gtk+-2.0 >= 2.16.6])
PKG_CHECK_MODULES([GTKGL], [gtkglext-1.0 >= 0.23])
PKG_CHECK_MODULES([SDL], [sdl >= 1.2.13])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_UINT32_T

# Checks for library functions.
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
