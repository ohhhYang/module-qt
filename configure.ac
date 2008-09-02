# Process this file with autoconf to produce a configure script.

# AC_PREREQ(2.59)
AC_INIT([qt], [0.0.1],
        [David Nichols <nicholsman@gmail.com>],
        [qt])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADER([config.h])

AC_LANG(C++)
AC_PROG_CXX
AC_PROG_CC
AC_DISABLE_STATIC
AC_LIBTOOL_DLOPEN
AM_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_RANLIB

# set system variables
OS=`uname -s`
if test "$OS" = "HP-UX"; then
   if test "$host_cpu" = "ia64"; then
      ARCH=itanium
   else
      ARCH=PA-RISC
   fi
else
   ARCH=`uname -p`
   if test $ARCH = i686 -o $ARCH = i586 -o $ARCH = athlon ; then
      ARCH=i386
   fi
fi

#AC_CANONICAL_HOST
# get CPU family
case "${host_cpu}" in
   i[[3456]]86) cpu_family=i386 ;;
   *)           cpu_family=${host_cpu} ;;
esac

# set OS-specific variables
SHLIB_SUFFIX=so
#echo host_os=${host_os}sss
case "${host_os}" in
     *linux*)   # set compile flags for Linux
		CPPFLAGS="${CPPFLAGS} -D_GNU_SOURCE"
		SHLIB_SUFFIX=so
		AC_DEFINE(LINUX, 1, if compiling on Linux)
		;;
     *solaris*) # set compile flags for Solaris
		CPPFLAGS="${CPPFLAGS} -D_POSIX_C_SOURCE=199506L -D_XPG4_2 -D_XPG5 -D__EXTENSIONS__"
		# for checking for some network functions on Solaris
		LDFLAGS="$LDFLAGS -lnsl"
		# assume we are using CC if not using g++, add -norunpath to link flags in this case
		if test "$GXX" != "yes"; then
		   LDFLAGS="$LDFLAGS -norunpath"
		fi
		AC_DEFINE(SOLARIS, 1, if compiling on Solaris)
		# add -ldl to libs if on Solaris 8
		if test "${host_os}" = "solaris2.8"; then
		   OTHER_LIBS="$OTHER_LIBS -ldl"
		fi
	        ;;
     *darwin*)  SHLIB_SUFFIX=dylib
		# libtool 1.5.* is creating modules on Darwin 8.* (OS/X 10.4.*) with a .so suffix for some reason
		MODULE_SUFFIX=so
		AC_DEFINE(DARWIN, 1, [if compiling on Darwin])
		darwin=true
		;;
     *hpux*)    if test "$host_cpu" = "ia64"; then
     		   SHLIB_SUFFIX=so
		else  # assume hppa (PA-RISC)
     		   SHLIB_SUFFIX=sl
		   AC_DEFINE(SHLIB_SUFFIX, "sl", shared library suffix)
		fi
		# add "-AA" and -D__STDC_EXT__ to aCC commandline to enable a clean compile
		if test -n "`echo $CXX|grep aCC`"; then
		   CXXFLAGS="$CXXFLAGS -AA -D__STDC_EXT__ -D_RWSTD_MULTI_THREAD"
		fi
		AC_DEFINE(HPUX, 1, if compiling on HP-UX)
		;;
esac
AC_SUBST(SHLIB_SUFFIX)
if test -z "$MODULE_SUFFIX" ; then
   MODULE_SUFFIX=$SHLIB_SUFFIX
fi
AC_SUBST(MODULE_SUFFIX)

AC_ARG_ENABLE([64bit],
  [AS_HELP_STRING([--enable-64bit],
		  [enable 64bit support (default: auto)])],
  [case "${enable_64bit}" in
       yes|no) ;;
       *)      AC_MSG_ERROR(bad value ${enable_64bit} for --enable-64bit) ;;
      esac],
  [enable_64bit=auto])

if test "$enable_64bit" = "auto"; then
   # turn on 64-bit by default if compiling on itanium or x86_64
   if test "$host_cpu" = "ia64" -o "$host_cpu" = "x86_64"; then
      enable_64bit=yes
   else
      enable_64bit=no
   fi
fi

# see if we know how to set flags properly for different hosts and architectures
# FIXME: add test on HP-UX if the compiler can generate the appropriate binaries
if test "$enable_64bit" = "yes"; then
   case "${host_os}" in
      *linux*)	if test "$GXX" = "yes"; then
		   CXXFLAGS="$CXXFLAGS -m64"
		fi
		LIBSUFFIX=64
		AC_SUBST(LIBSUFFIX)
		;;
      *hpux*)	if test "$host_cpu" != "ia64"; then
		    if test -n "`echo $CXX|grep aCC`"; then
		        CXXFLAGS="$CXXFLAGS +DA2.0W"
		    elif test "$GXX" = "yes"; then
			CXXFLAGS="$CXXFLAGS -march=2.0"
		    fi
		fi
		;;
     *solaris*) if test "$GXX" = "yes"; then
		    if test "$host_cpu" = "sparc"; then
		        CXXFLAGS="$CXXFLAGS -mcpu=ultrasparc3 -m64"  # NOTE we compile for minimum ultrasparc 3 in 64-bit mode
		    else
		        CXXFLAGS="$CXXFLAGS -m64"
		    fi
		else
		    CXXFLAGS="$CXXFLAGS -xarch=generic64"
		fi
		;;
   esac
   SYBLIBSUFFIX=64
   RVLIBSUFFIX=64
   bits=64
else
   case "${host_os}" in
     *linux*)	if test "$GXX" = "yes"; then
		   CXXFLAGS="$CXXFLAGS -m32"
		fi
		;;
     *hpux*)	if test "$host_cpu" != "ia64"; then
		    if test "$GXX" = "yes"; then
		        CXXFLAGS="$CXXFLAGS -march=2.0"
		    elif test -n "`echo $CXX|grep aCC`" -a "$host_cpu" != "ia64"; then
		        CXXFLAGS="$CXXFLAGS +DA2.0N"   # NOTE we compile for PA-RISC 2.0 32-bit, not PA-RISC 1.1
		    fi
		fi
		;;
     *solaris*) if test "$GXX" = "yes"; then
		    if test "$host_cpu" = "sparc"; then
		        CXXFLAGS="$CXXFLAGS -mcpu=v8 -m32"
		    else
		        CXXFLAGS="$CXXFLAGS -m32"
		    fi
		else
		    CXXFLAGS="$CXXFLAGS -xarch=generic"
		fi
		;;
   esac
   if test "$host_cpu" = "x86_64"; then
      cpu_family=i386
   fi
   bits=32
fi

AC_ARG_ENABLE([single-compilation-unit],
  [AS_HELP_STRING([--enable-single-compilation-unit],
                  [enable compilation as a single unit (default: on)])],
  [case "${enable_single_compilation_unit}" in
       yes|no) ;;
       *)      AC_MSG_ERROR(bad value ${enable_single_compilation_unit} for --enable-single-compilation-unit) ;;
      esac],
  [enable_single_compilation_unit=yes])

AC_ARG_ENABLE([scu],
  [AS_HELP_STRING([--enable-scu],
		  [short for --enable-single-compilation-unit: enable compilation as a single unit])],
  [case "${enable_scu}" in
       yes|no) enable_single_compilation_unit=$enable_scu;;
       *)      AC_MSG_ERROR(bad value ${enable_scu} for --enable-scu) ;;
      esac])

AC_ARG_ENABLE([single-compilation-unit-gui],
  [AS_HELP_STRING([--enable-single-compilation-unit-gui],
		  [enable compilation as a single unit for qt-gui - only if you have at least 1 Gig of RAM! (default: on)])],
  [case "${enable_single_compilation_unit_gui}" in
       yes|no) ;;
       *)      AC_MSG_ERROR(bad value ${enable_single_compilation_unit_gui} for --enable-single-compilation-unit-gui) ;;
      esac],
  [enable_single_compilation_unit_gui=yes])

AC_ARG_ENABLE([scu-gui],
  [AS_HELP_STRING([--enable-scu-gui],
		  [short for --enable-single-compilation-unit-gui: enable compilation as a single unit for qt-gui - only if you have at least 1 Gig of RAM!])],
  [case "${enable_scu_gui}" in
       yes|no) enable_single_compilation_unit_gui=$enable_scu_gui;;
       *)      AC_MSG_ERROR(bad value ${enable_scu_gui} for --enable-scu-gui) ;;
      esac],
  [enable_scu_gui=yes])

set_qore_cppflags()
{
    QORE_INC_DIR=$1
    if test "$1" != "/usr/include"; then
        QORE_CPPFLAGS=-I$1
    fi
}

find_qore()
{
    lib=$1/lib${LIBSUFFIX}

    # if we only want the static qore libraries
    if test -n "$qore_static"; then
        if test -f "$lib/libqore.a"; then
            QORE_LDFLAGS="$lib/libqore.a"
            AC_MSG_RESULT([$lib (forced static)])
        fi
    else
        if test -f "$lib/libqore.${SHLIB_SUFFIX}"; then
            if test "$lib" != "/lib" -a "$lib" != "/usr/lib"; then
                QORE_LDFLAGS="-L$lib"
            fi
            QORE_LDFLAGS="$QORE_LDFLAGS -lqore"
            AC_MSG_RESULT([$lib (shared)])
        elif test -f "$lib/libqore.a"; then
            if test "$lib" != "/lib" -a "$lib" != "/usr/lib"; then
                QORE_LDFLAGS="-L$lib"
            fi
            QORE_LDFLAGS="$QORE_LDFLAGS -lqore"
            AC_MSG_RESULT([$lib (static)])
        fi
    fi
    if test -z "$QORE_LDFLAGS"; then
        return
    fi

    AC_MSG_CHECKING([for qore include files])
    # try to find include files
    if test "$1" = "/"; then
        inc=/usr/include
    else
        inc=$1/include
    fi
    if test -f "$inc/qore/Qore.h"; then
        AC_MSG_RESULT([found: $inc])
        set_qore_cppflags $inc
    else
        AC_MSG_ERROR([not found])
    fi

    AC_SUBST(QORE_LDFLAGS)
    AC_SUBST(QORE_CPPFLAGS)
}

# see if we can figure out where the qore library is
AC_ARG_WITH([qore-dir],
  [AS_HELP_STRING([--with-qore-dir@<:@=DIR@:>@],
                  [Qore directory])],
  [if test ! -d "${with_qore_dir}"; then AC_MSG_ERROR(bad value ${with_qore_dir} for --with-qore-dir); unset with_qore_dir; fi],
  [with_qore_dir="$QORE_DIR"])

AC_MSG_CHECKING([for qore libraries and header files])
for dir in "${with_qore_dir}" /usr / /usr/local /opt/gnu /opt/qore /usr/local/qore /opt/local /sw /usr/sfw /opt/sfw; do
    find_qore $dir
    if test -n "$QORE_LDFLAGS"; then
        break
    fi
done
if test -z "$QORE_LDFLAGS"; then
    AC_MSG_ERROR([no qore library found])
else
   # test qore version
   AC_MSG_CHECKING([qore library version])
   qv_major=`grep QORE_VERSION_MAJOR $QORE_INC_DIR/qore/qore-version.h|cut -f3 -d\  2>/dev/null`
   if test -z "$qv_major"; then
      AC_MSG_ERROR([cannot determine; check Qore header files in $QORE_INC_DIR])
   elif test "$qv_major" = "0"; then
      qv_minor=`grep QORE_VERSION_MINOR $QORE_INC_DIR/qore/qore-version.h|cut -f3 -d\  2>/dev/null`
      if test "$qv_version_minor" = "7"; then
      	 AC_MSG_ERROR([invalid; this module requires version 0.7.0])
      fi
      qore_version=`grep QORE_VERSION.\" $QORE_INC_DIR/qore/qore-version.h|cut -f3 -d\ |sed s/\"//g 2>/dev/null`
      AC_MSG_RESULT([${qore_version} OK])

      libdir=`qore --module-dir|sed "s/\/qore-.*//"`
      mypkglibdir=`qore --module-dir`
      AC_SUBST([mypkglibdir])
   fi
fi

AC_ARG_ENABLE([profile],
     [AS_HELP_STRING([--enable-profile],
		     [turn on profiling support (default=no)])],
     [case "${enable_profile}" in
       yes|no) ;;
       *)      AC_MSG_ERROR(bad value ${enable_profile} for --enable-profile) ;;
      esac],
     [enable_profile=no])

AC_ARG_ENABLE([debug],
     [AS_HELP_STRING([--enable-debug],
		     [turn on debugging (default=no)])],
     [case "${enable_debug}" in
       yes|no) ;;
       *)      AC_MSG_ERROR(bad value ${enable_debug} for --enable-debug) ;;
      esac],
     [enable_debug=yes])

if test "${enable_debug}" = yes; then
   AC_DEFINE(DEBUG, 1, Define if debugging support should be included)
   # remove -O2 from CXXFLAGS so valgrind can report properly
   CXXFLAGS=`echo $CXXFLAGS | sed 's/\-O2//'`
else
   AC_DEFINE(NDEBUG, 1, Define if assert() declarations should be suppressed)
fi

if test "${enable_profile}" = yes; then
   AC_DEFINE(PROFILE, 1, Define if profiling support should be included)
fi

AC_ARG_ENABLE([optimization],
     [AS_HELP_STRING([--enable-optimization],
		     [turn on optimization (default=auto (yes unless debugging is enabled)])],
     [case "${enable_optimization}" in
       yes|no) ;;
       *)      AC_MSG_ERROR(bad value ${enable_optimization} for --enable-optimization) ;;
      esac],
     [enable_optimization=auto])

if test "$enable_optimization" = "auto"; then
   if test "${enable_debug}" = yes; then
      enable_optimization=no
   else
      enable_optimization=yes
   fi
fi

# check for gcc visibility support
AC_MSG_CHECKING([for gcc visibility support])
if test "$GXX" = "yes"; then
   gcc_version=`$CXX -dumpversion`
   if test "$gcc_version" \> "4"; then
      AC_DEFINE(HAVE_GCC_VISIBILITY, 1, if compiling with g++ and visibility support is available)
      AC_MSG_RESULT([yes, $CXX $gcc_version])
      # we no longer set visibility to hidden by default because it makes RTTI symbols invisible
      # all functions in the library are tagged anyway
      #CXXFLAGS="$CXXFLAGS -fvisibility=hidden"
   else
      AC_MSG_RESULT([no, gcc $gcc_version])
   fi
else
   AC_MSG_RESULT([no, $CXX])
fi

AC_ARG_WITH([opengl],
    [AS_HELP_STRING([--with-opengl@<:@=DIR@:>@],
                    [OpenGL base directory])],
    [if test "${with_opengl}" != "no" -a ! -d "${with_opengl}"; then AC_MSG_ERROR(directory ${with_opengl} does not exist for --with-opengl); unset with_opengl; fi])

AC_ARG_WITH([opengl-libs],
    [AS_HELP_STRING([--with-opengl-libs@<:@=DIR@:>@],
                    [OpenGL library directory])],
    [if test ! -d "${with_opengl_libs}"; then AC_MSG_ERROR(directory ${with_opengl_libs} does not exist for --with-opengl-libs); unset with_opengl_libs; fi])

AC_ARG_WITH([opengl-includes],
    [AS_HELP_STRING([--with-opengl-includes@<:@=DIR@:>@],
                    [OpenGL include file parent directory])],
    [if test ! -d "${with_opengl_includes}"; then AC_MSG_ERROR(directory ${with_opengl_includes} does not exist for --with-opengl-includes); unset with_opengl_includes; fi])

check_opengl_include()
{
    if test -f "$1/gl.h"; then
       found_opengl_includes=$1
    elif test -f "$1/GL/gl.h"; then
       found_opengl_includes=$1/GL
    elif test -f "$1/OpenGL/gl.h"; then
       found_opengl_includes=$1/OpenGL
    elif test -f "$1/mesa/gl.h"; then
       found_opengl_includes=$1/mesa
    elif test "$2" = "err"; then
       AC_MSG_ERROR([$1 is not a valid OpenGL parent include directory])
    fi
}

check_opengl_lib()
{
    if test -f "$1/libGL.${SHLIB_SUFFIX}" -a "$1/libGLU.${SHLIB_SUFFIX}"; then
       found_opengl_libs=$lib
    elif test "$2" = "err"; then
    	AC_MSG_ERROR([$1 is not a valid OpenGL library directory])
    fi
}

check_opengl_version()
{
    # check opengl version
    opengl_ver=`grep define.*GL_VERSION_1_3.*1 $with_opengl_includes/*.h`
    if test -z "$opengl_ver"; then
       AC_MSG_ERROR([can't find OpenGL API version 1.3])
    fi
}

check_opengl()
{
    if test -z "$with_opengl_includes"; then
        inc="$1/include"
        if test "$1" = "/"; then
       	    inc=/usr/include
        fi
	check_opengl_include $inc

	if test -z "$found_opengl_includes"; then
	    #echo DBG: opengl $1 $inc includes not found
       	    return
    	fi
	with_opengl_includes="$found_opengl_includes"
	unset found_opengl_includes
    fi

    if test -z "$with_opengl_libs"; then
        lib="$1/lib${LIBSUFFIX}"

	check_opengl_lib $lib
    	if test -z "$found_opengl_libs"; then
       	    #echo DBG: opengl $1 $lib libs not found
       	    unset with_opengl_includes
       	    return
    	fi
	with_opengl_libs="$found_opengl_libs"
    fi
    if test "$with_opengl_libs" != "/lib${LIBSUFFIX}"; then
        opengl_app_libs=true
    fi

    check_opengl_version
}

# see if we can figure out where the opengl include files and libraries are
if test "${with_opengl}" != "no"; then
   AC_MSG_CHECKING([for OpenGL includes and libraries])

   if test -n "$with_opengl_includes" -a -n "$with_opengl_libs"; then
      check_opengl_includes "$with_opengl_includes" err
      check_opengl_libs "$with_opengl_libs" err
   else
      if test -n "$with_opengl"; then
      	 check_opengl "$with_opengl"
      	 if test -z "$with_opengl_includes"; then
	    AC_MSG_ERROR([not found in $with_opengl])
      	 fi
      else
         # check for frameworks on darwin
	 if test -n "$darwin" -a -d /System/Library/Frameworks/OpenGL.framework; then
	    opengl_framework="/System/Library/Frameworks"
	    OPENGL_INCLUDES="-I /System/Library/Frameworks/OpenGL.framework/Headers"
	    OPENGL_LIBS="-framework OpenGL"
	 else
	    for dir in $OPENGL_DIR / /usr /usr/X11 /usr/X11R6 /usr/openwin /usr/local /opt/opengl /usr/opengl /sw /opt/local /opt/sfw /usr/sfw /opt/gnu; do
      	       check_opengl $dir
      	       if test -n "$with_opengl_includes"; then
	          break;
      	       fi
   	    done
         fi
      fi
   fi

   if test -n "$opengl_framework"; then
      AC_MSG_RESULT([using Darwin frameworks in $opengl_framework])
      with_opengl=yes
   else
      if test -n "$with_opengl_includes"; then
         if test -n "$opengl_static"; then
	    AC_MSG_RESULT([includes=$with_opengl_includes, libs=$with_opengl_libs (static)])
      	 else
	    AC_MSG_RESULT([includes=$with_opengl_includes, libs=$with_opengl_libs (shared)])
      	 fi
      	 with_opengl=yes
      else
	 AC_MSG_RESULT([not found])
         unset with_opengl
      fi
   fi
fi

if test "${with_opengl}" = yes; then
  if test -n "$with_opengl_includes" -o -n "$opengl_framework"; then
     if test -z "$OPENGL_INCLUDES"; then
        OPENGL_INCLUDES="-I$with_opengl_includes"
     fi
     if test -z "$OPENGL_LIBS"; then
	OPENGL_LIBS="-lGL -lGLU"
	if test -n "$opengl_app_libs"; then
	   OPENGL_LIBS="-L$with_opengl_libs $OPENGL_LIBS"
	fi
     fi

     # check if C++ compiler can link with OPENGL libs
     SAVE_CXXFLAGS="$CXXFLAGS"
     SAVE_LDFLAGS="$LDFLAGS"
     CXXFLAGS="$CXXFLAGS $OPENGL_INCLUDES"
     LDFLAGS="$LDFLAGS $OPENGL_LIBS"
     AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <gl.h>
	 ]],[[
   glBegin(GL_POINTS);
	]])], opengl_links=yes, opengl_links=no)

     CXXFLAGS="$SAVE_CXXFLAGS"
     LDFLAGS="$SAVE_LDFLAGS"

     if test "$opengl_links" = "no"; then
        AC_MSG_ERROR([could not compile a test OpenGL program])
     else
        AC_SUBST(OPENGL_INCLUDES)
	AC_SUBST(OPENGL_LIBS)
        with_opengl=yes
     fi
  else
     AC_MSG_WARN([no OpenGL libraries or includes found, disabling OpenGL support])
     unset with_opengl
  fi
fi

AC_ARG_WITH([qt],
    [AS_HELP_STRING([--with-qt@<:@=DIR@:>@],
                    [QT base directory])],
    [if test "${with_qt}" != "no" -a ! -d "${with_qt}"; then AC_MSG_ERROR(directory ${with_qt} does not exist for --with-qt); unset with_qt; fi])

AC_ARG_WITH([qt-libs],
    [AS_HELP_STRING([--with-qt-libs@<:@=DIR@:>@],
                    [QT library directory])],
    [if test ! -d "${with_qt_libs}"; then AC_MSG_ERROR(directory ${with_qt_libs} does not exist for --with-qt-libs); unset with_qt_libs; fi])

AC_ARG_WITH([qt-includes],
    [AS_HELP_STRING([--with-qt-includes@<:@=DIR@:>@],
                    [QT include file parent directory])],
    [if test ! -d "${with_qt_includes}"; then AC_MSG_ERROR(directory ${with_qt_includes} does not exist for --with-qt-includes); unset with_qt_includes; fi])

check_qt_include()
{
    if test -f "$1/QtCore/qglobal.h" -a -f "$1/QtGui/QApplication"; then
       found_qt_includes=$1
    elif test "$2" = "err"; then
       AC_MSG_ERROR([$1 is not a valid QT parent include directory])
    fi
}

check_qt_lib()
{
    if test -f "$1/libQtCore.${SHLIB_SUFFIX}"; then
       found_qt_libs=$lib
    elif test "$2" = "err"; then
    	AC_MSG_ERROR([$1 is not a valid QT 4 library directory])
    fi
}

check_qt_version()
{
    # check qt version
    qt_maj=`grep QT_VERSION_STR $with_qt_includes/QtCore/qglobal.h|cut -f2 -d\"|cut -f1 -d.`
    if test -z "$qt_maj"; then
       AC_MSG_ERROR([can't determine QT version])
    fi
    if test $qt_maj -ne 4; then
       AC_MSG_ERROR([QT version $version is not supported (must be = 4)])
    fi
}

check_qt()
{
    if test -z "$with_qt_includes"; then
        inc="$1/include"
        if test "$1" = "/"; then
       	    inc=/usr/include
        fi
	check_qt_include $inc

	if test -z "$found_qt_includes"; then
	    #echo DBG: qt $1 $inc includes not found
       	    return
    	fi
	with_qt_includes="$found_qt_includes"
	unset found_qt_includes
    fi

    if test -z "$with_qt_libs"; then
        lib="$1/lib${LIBSUFFIX}"

	check_qt_lib $lib
    	if test -z "$found_qt_libs"; then
       	    #echo DBG: qt $1 $lib libs not found
       	    unset with_qt_includes
       	    return
    	fi
	with_qt_libs="$found_qt_libs"
    fi
    if test "$with_qt_libs" != "/lib${LIBSUFFIX}"; then
        qt_app_libs=true
    fi

    check_qt_version
}

# see if we can figure out where the qt include files and libraries are
if test "${with_qt}" != "no"; then
   AC_MSG_CHECKING([for QT 4 Core includes and libraries])

   if test -n "$with_qt_includes" -a -n "$with_qt_libs"; then
      check_qt_includes "$with_qt_includes" err
      check_qt_libs "$with_qt_libs" err
   else
      if test -n "$with_qt"; then
      	 check_qt "$with_qt"
      	 if test -z "$with_qt_includes"; then
	    AC_MSG_ERROR([not found in $with_qt])
      	 fi
      else
         # check for frameworks on darwin
	 if test -n "$darwin" -a -d /Library/Frameworks/QtCore.framework; then
	    qt_framework="/Library/Frameworks/QtCore.framework"
	 else
	    for dir in $QT_DIR / /usr /usr/local /opt/qt /opt/qt /usr/qt /usr/qt /sw /opt/local /opt/sfw /usr/sfw /opt/gnu; do
      	       check_qt $dir
      	       if test -n "$with_qt_includes"; then
	          break;
      	       fi
   	    done
         fi
      fi
   fi

   if test -n "$qt_framework"; then
      AC_MSG_RESULT([using Darwin frameworks in $qt_framework])
      QT_CORE_INCLUDES="-I $qt_framework/Headers"
      QT_CORE_LIBS="-framework QtCore"
      with_qt=yes
   else
      if test -n "$with_qt_includes"; then
         if test -n "$qt_static"; then
	    AC_MSG_RESULT([includes=$with_qt_includes, libs=$with_qt_libs (static)])
      	 else
	    AC_MSG_RESULT([includes=$with_qt_includes, libs=$with_qt_libs (shared)])
      	 fi
      	 with_qt=yes
      else
	 AC_MSG_RESULT([not found])
         unset with_qt
      fi
   fi
fi

if test "${with_qt}" = yes; then
  if test -n "$with_qt_includes" -o -n "$qt_framework"; then
     if test -z "$QT_CORE_INCLUDES"; then
        QT_CORE_INCLUDES="-I$with_qt_includes/QtCore -I$with_qt_includes/QtGui"
     fi
     if test -z "$QT_CORE_LIBS"; then
	QT_CORE_LIBS="-lQtCore"
	if test -n "$qt_app_libs"; then
	   QT_CORE_LIBS="-L$with_qt_libs $QT_CORE_LIBS"
	fi
     fi

     # check if C++ compiler can link with QT libs
     SAVE_CXXFLAGS="$CXXFLAGS"
     SAVE_LDFLAGS="$LDFLAGS"
     CXXFLAGS="$CXXFLAGS $QT_CORE_INCLUDES"
     LDFLAGS="$LDFLAGS $QT_CORE_LIBS"
     AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <QCoreApplication>
	 ]],[[
   int argc = 0;
   char **argv = 0;
   QCoreApplication app(argc, argv);
	]])], qt_core_links=yes, qt_core_links=no)

     CXXFLAGS="$SAVE_CXXFLAGS"
     LDFLAGS="$SAVE_LDFLAGS"

     if test "$qt_core_links" = "no"; then
        AC_MSG_ERROR([could not compile a test QT Core program])
     else
        AC_SUBST(QT_CORE_INCLUDES)
	AC_SUBST(QT_CORE_LIBS)
        with_qt=yes
     fi
  else
     AC_MSG_WARN([no QT Core libraries or includes found, disabling QT Core support])
     unset with_qt
  fi
fi

AC_ARG_WITH([qt-gui],
    [AS_HELP_STRING([--with-qt-gui@<:@=DIR@:>@],
                    [QT 4 Gui base directory])],
    [if test ! -d "${with_qt_gui}"; then AC_MSG_ERROR(directory ${with_qt_gui} does not exist for --with-qt-gui); unset with_qt_gui; fi])

AC_ARG_WITH([qt-gui-libs],
    [AS_HELP_STRING([--with-qt-gui-libs@<:@=DIR@:>@],
                    [QT 4 Gui library directory])],
    [if test ! -d "${with_qt_gui_libs}"; then AC_MSG_ERROR(directory ${with_qt_gui_libs} does not exist for --with-qt-gui-libs); unset with_qt_gui_libs; fi])

AC_ARG_WITH([qt-gui-includes],
    [AS_HELP_STRING([--with-qt-gui-includes@<:@=DIR@:>@],
                    [QT 4 Gui include file parent directory])],
    [if test ! -d "${with_qt_gui_includes}"; then AC_MSG_ERROR(directory ${with_qt_gui_includes} does not exist for --with-qt-gui-includes); unset with_qt_gui_includes; fi])

check_qt_gui_include()
{
    if test -f "$1/QtGui/QApplication"; then
       found_qt_gui_includes=$1
    elif test "$2" = "err"; then
       AC_MSG_ERROR([$1 is not a valid QT Gui parent include directory])
    fi
}

check_qt_gui_lib()
{
    if test -f "$1/libQtGui.${SHLIB_SUFFIX}"; then
       found_qt_gui_libs=$lib
    elif test "$2" = "err"; then
    	AC_MSG_ERROR([$1 is not a valid QT 4 Gui library directory])
    fi
}

check_qt_gui()
{
    if test -z "$with_qt_gui_includes"; then
        inc="$1/include"
        if test "$1" = "/"; then
       	    inc=/usr/include
        fi
	check_qt_gui_include $inc

	if test -z "$found_qt_gui_includes"; then
	    #echo DBG: qt $1 $inc includes not found
       	    return
    	fi
	with_qt_gui_includes="$found_qt_gui_includes"
	unset found_qt_gui_includes
    fi

    if test -z "$with_qt_gui_libs"; then
        lib="$1/lib${LIBSUFFIX}"

	check_qt_gui_lib $lib
    	if test -z "$found_qt_gui_libs"; then
       	    #echo DBG: qt $1 $lib libs not found
       	    unset with_qt_gui_includes
       	    return
    	fi
	with_qt_gui_libs="$found_qt_libs"
    fi
    if test "$with_qt_gui_libs" != "/lib${LIBSUFFIX}"; then
        qt_app_gui_libs=true
    fi
}

# see if we can figure out where the qt include files and libraries are
if test "${with_qt}" = "yes" -a "${with_qt_gui}" != "no"; then
   AC_MSG_CHECKING([for QT 4 Gui includes and libraries])

   if test -n "$with_qt_gui_includes" -a -n "$with_qt_gui_libs"; then
      check_qt_gui_includes "$with_qt_gui_includes" err
      check_qt_gui_libs "$with_qt_gui_libs" err
   else
      if test -n "$with_qt_gui"; then
      	 check_qt "$with_qt_gui"
      	 if test -z "$with_qt_gui_includes"; then
	    AC_MSG_ERROR([not found in $with_qt_gui])
      	 fi
      else
         # check for frameworks on darwin
	 if test -n "$darwin" -a -d /Library/Frameworks/QtGui.framework; then
	    qt_gui_framework="/Library/Frameworks/QtGui.framework"
	 else
	    for dir in $QT_DIR / /usr /usr/local /opt/qt /opt/qt /usr/qt /usr/qt /sw /opt/local /opt/sfw /usr/sfw /opt/gnu; do
      	       check_qt_gui $dir
      	       if test -n "$with_qt_gui_includes"; then
	          break;
      	       fi
   	    done
         fi
      fi
   fi

   if test -n "$qt_gui_framework"; then
      AC_MSG_RESULT([using Darwin frameworks in $qt_gui_framework])
      QT_GUI_INCLUDES="-I $qt_gui_framework/Headers"
      QT_GUI_LIBS="-framework QtGui"
      with_qt_gui=yes
   else
      if test -n "$with_qt_gui_includes"; then
         if test -n "$qt_gui_static"; then
	    AC_MSG_RESULT([includes=$with_qt_gui_includes, libs=$with_qt_gui_libs (static)])
      	 else
	    AC_MSG_RESULT([includes=$with_qt_gui_includes, libs=$with_qt_gui_libs (shared)])
      	 fi
      	 with_qt_gui=yes
      else
	 AC_MSG_RESULT([not found])
         unset with_qt_gui
      fi
   fi
fi

if test "${with_qt_gui}" = yes; then
  if test -n "$with_qt_gui_includes" -o -n "$qt_gui_framework"; then
     if test -z "$QT_GUI_INCLUDES"; then
        QT_GUI_INCLUDES="-I$with_qt_includes/QtGui"
     fi
     if test -z "$QT_GUI_LIBS"; then
	QT_GUI_LIBS="-lQtGui"
	if test -n "$qt_gui_app_libs"; then
	   QT_GUI_LIBS="-L$with_qt_libs $QT_GUI_LIBS"
	fi
     fi

     # check if C++ compiler can link with QT libs
     SAVE_CXXFLAGS="$CXXFLAGS"
     SAVE_LDFLAGS="$LDFLAGS"
     CXXFLAGS="$CXXFLAGS $QT_CORE_INCLUDES $QT_GUI_INCLUDES"
     LDFLAGS="$LDFLAGS $QT_CORE_LIBS $QT_GUI_LIBS"
     AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <QApplication>
#include <QPushButton>
	 ]],[[
   int argc = 0;
   char **argv = 0;
   QApplication app(argc, argv);

   QPushButton hello("Hello world!");
   hello.resize(100, 30);

   hello.show();
   return app.exec();
	]])], qt_gui_links=yes, qt_gui_links=no)

     CXXFLAGS="$SAVE_CXXFLAGS"
     LDFLAGS="$SAVE_LDFLAGS"

     if test "$qt_gui_links" = "no"; then
        AC_MSG_ERROR([could not compile a test QT 4 Gui program])
     else
        AC_SUBST(QT_GUI_INCLUDES)
	AC_SUBST(QT_GUI_LIBS)
        with_qt_gui=yes
     fi
  else
     AC_MSG_WARN([no QT 4 Gui libraries or includes found, disabling QT 4 Gui support])
     unset with_qt_gui
  fi
fi

AC_ARG_WITH([qt-opengl],
    [AS_HELP_STRING([--with-qt-opengl@<:@=DIR@:>@],
                    [QT OpenGL base directory])],
    [if test ! -d "${with_qt_opengl}"; then AC_MSG_ERROR(directory ${with_qt_opengl} does not exist for --with-qt-opengl); unset with_qt_opengl; fi])

AC_ARG_WITH([qt-opengl-libs],
    [AS_HELP_STRING([--with-qt-opengl-libs@<:@=DIR@:>@],
                    [QT OpenGL library directory])],
    [if test ! -d "${with_qt_opengl_libs}"; then AC_MSG_ERROR(directory ${with_qt_opengl_libs} does not exist for --with-qt-opengl-libs); unset with_qt_opengl_libs; fi])

AC_ARG_WITH([qt-opengl-includes],
    [AS_HELP_STRING([--with-qt-opengl-includes@<:@=DIR@:>@],
                    [QT OpenGL include file parent directory])],
    [if test ! -d "${with_qt_opengl_includes}"; then AC_MSG_ERROR(directory ${with_qt_opengl_includes} does not exist for --with-qt-opengl-includes); unset with_qt_opengl_includes; fi])

check_qt_opengl_include()
{
    if test -f "$1/QtOpenGL/QtOpenGL"; then
       found_qt_opengl_includes=$1
    elif test "$2" = "err"; then
       AC_MSG_ERROR([$1 is not a valid QT OpenGL parent include directory])
    fi
}

check_qt_opengl_lib()
{
    if test -f $1/libQtOpenGL.${SHLIB_SUFFIX}; then
       found_qt_opengl_libs=$lib
    elif test "$2" = "err"; then
    	AC_MSG_ERROR([$1 is not a valid QT OpenGL library directory])
    fi
}

check_qt_opengl()
{
    if test -z "$with_qt_opengl_includes"; then
        inc="$1/include"
        if test "$1" = "/"; then
       	    inc=/usr/include
        fi
	check_qt_opengl_include $inc

	if test -z "$found_qt_opengl_includes"; then
	    #echo DBG: qt $1 $inc includes not found
       	    return
    	fi
	with_qt_opengl_includes="$found_qt_opengl_includes"
	unset found_qt_opengl_includes
    fi

    if test -z "$with_qt_opengl_libs"; then
        lib="$1/lib${LIBSUFFIX}"

	check_qt_opengl_lib $lib
    	if test -z "$found_qt_opengl_libs"; then
       	    #echo DBG: qt $1 $lib libs not found
       	    unset with_qt_opengl_includes
       	    return
    	fi
	with_qt_opengl_libs="$found_qt_opengl_libs"
    fi
    if test "$with_qt_opengl_libs" != "$with_qt_libs"; then
        qt_app_opengl_libs=true
    fi
}

# see if we can figure out where the qt include files and libraries are
if test "${with_qt_gui}" = "yes" -a "${with_qt_opengl}" != "no"; then
   AC_MSG_CHECKING([for QT 4 OpenGL includes and libraries])

   if test -n "$with_qt_opengl_includes" -a -n "$with_qt_opengl_libs"; then
      check_qt_opengl_includes "$with_qt_opengl_includes" err
      check_qt_opengl_libs "$with_qt_opengl_libs" err
   else
      if test -n "$with_qt_opengl"; then
      	 check_qt_opengl "$with_qt_opengl"
      	 if test -z "$with_qt_opengl_includes"; then
	    AC_MSG_ERROR([not found in $with_qt_opengl])
      	 fi
      else
         # check for frameworks on darwin
	 if test -n "$darwin" -a -d /Library/Frameworks/QtOpenGL.framework; then
	    qt_opengl_framework="/Library/Frameworks/QtOpenGL.framework"
	 else
	    for dir in $QT_DIR / /usr /usr/local /opt/qt /opt/qt /usr/qt /usr/qt /sw /opt/local /opt/sfw /usr/sfw /opt/gnu; do
      	       check_qt_opengl $dir
      	       if test -n "$with_qt_opengl_includes"; then
	          break;
      	       fi
   	    done
         fi
      fi
   fi

   if test -n "$qt_opengl_framework"; then
      QT_OPENGL_INCLUDES="-I $qt_opengl_framework/Headers"
      QT_OPENGL_LIBS="-framework QtOpenGL"
      AC_MSG_RESULT([using Darwin frameworks in $qt_opengl_framework])
      with_qt_opengl=yes
   else
      if test -n "$with_qt_opengl_includes"; then
         if test -n "$qt_static"; then
	    AC_MSG_RESULT([includes=$with_qt_opengl_includes, libs=$with_qt_opengl_libs (static)])
      	 else
	    AC_MSG_RESULT([includes=$with_qt_opengl_includes, libs=$with_qt_opengl_libs (shared)])
      	 fi
      	 with_qt_opengl=yes
      else
	 AC_MSG_RESULT([not found])
         unset with_qt_opengl
      fi
   fi
fi

if test "${with_qt_opengl}" = yes; then
  if test -n "$with_qt_opengl_includes" -o -n "$qt_opengl_framework"; then
     if test -z "$QT_OPENGL_INCLUDES"; then
        QT_OPENGL_INCLUDES="-I$with_qt_includes/QtOpenGL"
     fi
     if test -z "$QT_OPENGL_LIBS"; then
        QT_OPENGL_LIBS="-lQtOpenGL"
        if test -n "$qt_app_opengl_libs"; then
           QT_OPENGL_LIBS="-L$with_qt_opengl_libs $QT_OPENGL_LIBS"
        fi
     fi

     # check if C++ compiler can link with QT opengl libs
     SAVE_CXXFLAGS="$CXXFLAGS"
     SAVE_LDFLAGS="$LDFLAGS"
     CXXFLAGS="$CXXFLAGS $QT_CORE_INCLUDES $QT_GUI_INCLUDES $QT_OPENGL_INCLUDES"
     LDFLAGS="$LDFLAGS $QT_CORE_LIBS $QT_GUI_LIBS $QT_OPENGL_LIBS"
     AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <QApplication>
#include <QPushButton>
#include <QGLWidget>
	 ]],[[
   int argc = 0;
   char **argv = 0;
   QApplication app(argc, argv);

   QPushButton hello("Hello world!");
   hello.resize(100, 30);

   QGLWidget test();

   hello.show();
   return app.exec();
	]])], qt_opengl_links=yes, qt_opengl_links=no)

     CXXFLAGS="$SAVE_CXXFLAGS"
     LDFLAGS="$SAVE_LDFLAGS"

     if test "$qt_opengl_links" = "no"; then
        AC_MSG_ERROR([could not compile a test QT OpenGL program])
     else
        AC_SUBST(QT_OPENGL_INCLUDES)
	AC_SUBST(QT_OPENGL_LIBS)
        with_qt_opengl=yes
     fi
  else
     AC_MSG_WARN([no QT OpenGL libraries or includes found, disabling QT OpenGL support])
     unset with_qt_opengl
  fi
fi

AC_ARG_WITH([qt-svg],
    [AS_HELP_STRING([--with-qt-svg@<:@=DIR@:>@],
                    [QT SVG base directory])],
    [if test ! -d "${with_qt_svg}"; then AC_MSG_ERROR(directory ${with_qt_svg} does not exist for --with-qt-svg); unset with_qt_svg; fi])

AC_ARG_WITH([qt-svg-libs],
    [AS_HELP_STRING([--with-qt-svg-libs@<:@=DIR@:>@],
                    [QT SVG library directory])],
    [if test ! -d "${with_qt_svg_libs}"; then AC_MSG_ERROR(directory ${with_qt_svg_libs} does not exist for --with-qt-svg-libs); unset with_qt_svg_libs; fi])

AC_ARG_WITH([qt-svg-includes],
    [AS_HELP_STRING([--with-qt-svg-includes@<:@=DIR@:>@],
                    [QT SVG include file parent directory])],
    [if test ! -d "${with_qt_svg_includes}"; then AC_MSG_ERROR(directory ${with_qt_svg_includes} does not exist for --with-qt-svg-includes); unset with_qt_svg_includes; fi])

check_qt_svg_include()
{
    if test -f "$1/QtSvg/QtSvg" -a -f "$1/QtXml/QtXml"; then
       found_qt_svg_includes=$1
    elif test "$2" = "err"; then
       AC_MSG_ERROR([$1 is not a valid QT SVG parent include directory])
    fi
}

check_qt_svg_lib()
{
    if test -f $1/libQtSvg.${SHLIB_SUFFIX} -a -f $1/libQtXml.${SHLIB_SUFFIX}; then
       found_qt_svg_libs=$lib
    elif test "$2" = "err"; then
    	AC_MSG_ERROR([$1 is not a valid QT Svg library directory])
    fi
}

check_qt_svg()
{
    if test -z "$with_qt_svg_includes"; then
        inc="$1/include"
        if test "$1" = "/"; then
       	    inc=/usr/include
        fi
	check_qt_svg_include $inc

	if test -z "$found_qt_svg_includes"; then
	    #echo DBG: qt $1 $inc includes not found
       	    return
    	fi
	with_qt_svg_includes="$found_qt_svg_includes"
	unset found_qt_svg_includes
    fi

    if test -z "$with_qt_svg_libs"; then
        lib="$1/lib${LIBSUFFIX}"

	check_qt_svg_lib $lib
    	if test -z "$found_qt_svg_libs"; then
       	    #echo DBG: qt $1 $lib libs not found
       	    unset with_qt_svg_includes
       	    return
    	fi
	with_qt_svg_libs="$found_qt_svg_libs"
    fi
    if test "$with_qt_svg_libs" != "$with_qt_libs"; then
        qt_app_svg_libs=true
    fi
}

# see if we can figure out where the qt include files and libraries are
if test "${with_qt_gui}" = "yes" -a "${with_qt_svg}" != "no"; then
   AC_MSG_CHECKING([for QT 4 SVG includes and libraries])

   if test -n "$with_qt_svg_includes" -a -n "$with_qt_svg_libs"; then
      check_qt_svg_includes "$with_qt_svg_includes" err
      check_qt_svg_libs "$with_qt_svg_libs" err
   else
      if test -n "$with_qt_svg"; then
      	 check_qt_svg "$with_qt_svg"
      	 if test -z "$with_qt_svg_includes"; then
	    AC_MSG_ERROR([not found in $with_qt_svg])
      	 fi
      else
         # check for frameworks on darwin
	 if test -n "$darwin" -a -d /Library/Frameworks/QtSvg.framework -a -d /Library/Frameworks/QtXml.framework; then
	    qt_svg_framework="/Library/Frameworks/QtSvg.framework"
	    qt_xml_framework="/Library/Frameworks/QtXml.framework"
	 else
	    for dir in $QT_DIR / /usr /usr/local /opt/qt /opt/qt /usr/qt /usr/qt /sw /opt/local /opt/sfw /usr/sfw /opt/gnu; do
      	       check_qt_svg $dir
      	       if test -n "$with_qt_svg_includes"; then
	          break;
      	       fi
   	    done
         fi
      fi
   fi

   if test -n "$qt_svg_framework"; then
      QT_SVG_INCLUDES="-I $qt_svg_framework/Headers -I $qt_xml_framework/Headers"
      QT_SVG_LIBS="-framework QtSvg -framework QtXml"
      AC_MSG_RESULT([using Darwin frameworks in $qt_svg_framework])
      with_qt_svg=yes
   else
      if test -n "$with_qt_svg_includes"; then
         if test -n "$qt_static"; then
	    AC_MSG_RESULT([includes=$with_qt_svg_includes, libs=$with_qt_svg_libs (static)])
      	 else
	    AC_MSG_RESULT([includes=$with_qt_svg_includes, libs=$with_qt_svg_libs (shared)])
      	 fi
      	 with_qt_svg=yes
      else
	 AC_MSG_RESULT([not found])
         unset with_qt_svg
      fi
   fi
fi

if test "${with_qt_svg}" = yes; then
  if test -n "$with_qt_svg_includes" -o -n "$qt_svg_framework"; then
     if test -z "$QT_SVG_INCLUDES"; then
        QT_SVG_INCLUDES="-I$with_qt_includes/QtSvg -I$with_qt_includes/QtXml"
     fi
     if test -z "$QT_SVG_LIBS"; then
        QT_SVG_LIBS="-lQtSvg -lQtXml"
        if test -n "$qt_app_svg_libs"; then
           QT_SVG_LIBS="-L$with_qt_svg_libs $QT_SVG_LIBS"
        fi
     fi

     # check if C++ compiler can link with QT svg libs
     SAVE_CXXFLAGS="$CXXFLAGS"
     SAVE_LDFLAGS="$LDFLAGS"
     CXXFLAGS="$CXXFLAGS $QT_CORE_INCLUDES $QT_GUI_INCLUDES $QT_SVG_INCLUDES"
     LDFLAGS="$LDFLAGS $QT_CORE_LIBS $QT_GUI_LIBS $QT_SVG_LIBS"
     AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <QApplication>
#include <QPushButton>
#include <QSvgWidget>
	 ]],[[
   int argc = 0;
   char **argv = 0;
   QApplication app(argc, argv);

   QPushButton hello("Hello world!");
   hello.resize(100, 30);

   QSvgWidget test();

   hello.show();
   return app.exec();
	]])], qt_svg_links=yes, qt_svg_links=no)

     CXXFLAGS="$SAVE_CXXFLAGS"
     LDFLAGS="$SAVE_LDFLAGS"

     if test "$qt_svg_links" = "no"; then
        AC_MSG_ERROR([could not compile a test QT SVG program])
     else
        AC_SUBST(QT_SVG_INCLUDES)
	AC_SUBST(QT_SVG_LIBS)
        with_qt_svg=yes
     fi
  else
     AC_MSG_WARN([no QT SVG libraries or includes found, disabling QT SVG support])
     unset with_qt_svg
  fi
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_CHECK_MEMBERS([struct stat.st_blksize])
AC_STRUCT_ST_BLOCKS
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_HEADER_TIME
AC_STRUCT_TM
AC_C_VOLATILE

# turn on optimizations if we know how
if test "$enable_optimization" = "yes"; then
    if test "$GXX" = "yes"; then
        CXXFLAGS="$CXXFLAGS -O3"  # gcc
    elif test "$CXX" = "CC" -a "`echo $host_os|cut -b-7`" = "solaris"; then
        # remove -g with Solaris CC as it reduces optimization levels
	CXXFLAGS="`echo $CXXFLAGS| sed s/-g//` -xO5" # Solaris CC
    elif test -n "`echo $CXX|grep aCC`"; then 
        # remove -g with HP-UX aCC as it reduces optimization levels
	CXXFLAGS="`echo $CXXFLAGS| sed s/-g//` +O4" # HP-UX aCC
    fi
else
    if test "$GXX" = "yes"; then
        CXXFLAGS="`echo $CXXFLAGS| sed s/-O2//`"  # gcc
    fi
fi

# turn on some build flags for non-debugging, non-profiling builds
if test "$enable_debug" = "no" -a "$enable_profile" = "no"; then
    # strip binaries and libraries on darwin with -x
    if test "`echo $host_os|cut -b-6`" = "darwin"; then
       LDFLAGS="$LDFLAGS -Wl,-x"
    fi	
fi

# turn on warnings if we know how
if test "$GXX" = "yes"; then
   CXXFLAGS="$CXXFLAGS -Wall"  # gcc
fi

AC_SUBST(OTHER_LIBS)

# save more version information in config.h
MODULE_VERSION_MAJOR=`echo $PACKAGE_VERSION | cut -f3 -d\  | sed s/\"//g | cut -f1 -d.`
MODULE_VERSION_MINOR=`echo $PACKAGE_VERSION | cut -f3 -d\  | sed s/\"//g | cut -f2 -d.`
MODULE_VERSION_SUB=`echo $PACKAGE_VERSION | cut -f3 -d\  | sed s/\"//g | cut -f3 -d.`

# set version information
AC_DEFINE_UNQUOTED([MODULE_VERSION_MAJOR], $MODULE_VERSION_MAJOR, [major version number])
AC_DEFINE_UNQUOTED([MODULE_VERSION_MINOR], $MODULE_VERSION_MINOR, [minor version number])
AC_DEFINE_UNQUOTED([MODULE_VERSION_SUB], $MODULE_VERSION_SUB, [sub version number])
AC_DEFINE_UNQUOTED([MODULE_TARGET_ARCH], "$ARCH", [host type])
AC_DEFINE_UNQUOTED([MODULE_TARGET_OS], "$OS", [host type])
AC_DEFINE_UNQUOTED([MODULE_TARGET_BITS], $bits, [32 or 64 bit build])

AM_CONDITIONAL([COND_DEBUG],      [test "$enable_debug" = yes])
AM_CONDITIONAL([COND_PROFILE],    [test "$enable_profile" = yes])
AM_CONDITIONAL([COND_MACOSX],     [test "$darwin" = true])
AM_CONDITIONAL([COND_SINGLE_COMPILATION_UNIT], [test "$enable_single_compilation_unit" = yes])
AM_CONDITIONAL([COND_SINGLE_COMPILATION_UNIT_GUI], [test "$enable_single_compilation_unit_gui" = yes])

AC_CONFIG_FILES([Makefile qt-core/Makefile qt-gui/Makefile qt-svg/Makefile qt-opengl/Makefile])
AC_OUTPUT

echo "*** MODULE FEATURES ***"
printf "%-24s: %s %s" module "$OS" "$cpu_family"
if test "$enable_64bit" = "yes"; then
   printf " (64-bit)\n"
else
   printf " (32-bit)\n"
fi

show_library_feature()
{
   printf "%-24s: " "$1"
   if test "$2" = "yes"; then
      printf "%-8s" yes
   else
      printf disabled
   fi
   if test -n "$3"; then
      printf " (%s)" $3
   fi
   echo
}

show_library_feature optimizations $enable_optimization
show_library_feature debug $enable_debug
show_library_feature profiling $enable_profile
show_library_feature qt-core $with_qt
show_library_feature qt-gui $with_qt_gui scu=$enable_single_compilation_unit_gui
show_library_feature qt-opengl $with_qt_opengl
show_library_feature qt-svg $with_qt_svg
