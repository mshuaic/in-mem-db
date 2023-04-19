AC_INIT(test, 1.0)
AC_CONFIG_SRCDIR([src/main.cpp])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_PROG_CXX
AC_LANG(C++)
AX_CXX_COMPILE_STDCXX(20, [], [])


# Check for Boost library
AC_ARG_WITH(boost,
	AS_HELP_STRING([--with-boost], [boost libraries]),
	[CXXFLAGS="${CXXFLAGS} -I${withval}/include" LDFLAGS="${LDFLAGS} -L${withval}/lib"])
AC_CHECK_LIB(boost_system, main, [], [AC_CHECK_LIB(boost_system-mt, main, [], [AC_MSG_ERROR(boost_system not found)])])


AC_CONFIG_FILES(Makefile)

AC_OUTPUT

