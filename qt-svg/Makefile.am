pkglibdir = $(mypkglibdir)

if COND_SINGLE_COMPILATION_UNIT
QT_SVG_SOURCES = single-compilation-unit.cc
else
QT_SVG_SOURCES = qt-svg.cc \
        QC_QSvgRenderer.cc \
        QC_QSvgGenerator.cc \
        QC_QSvgWidget.cc
endif

pkglib_LTLIBRARIES = qt-svg.la
qt_svg_la_SOURCES = $(QT_SVG_SOURCES)
qt_svg_la_LDFLAGS = -module -avoid-version ${QT_SVG_LIBS} ${QT_CORE_LIBS} ${QT_GUI_LIBS}
qt_svg_la_LIBADD = ../qt-core/libqore-qt-core.la ../qt-gui/libqore-qt-gui.la

INCLUDES = -I$(top_srcdir)/include $(QT_CORE_INCLUDES) $(QT_GUI_INCLUDES) $(QT_SVG_INCLUDES) -I ../qt-core -I ../qt-gui

AM_CPPFLAGS = $(QORE_CPPFLAGS)
AM_CXXFLAGS = ${PTHREAD_CFLAGS}

if COND_PROFILE
AM_CXXFLAGS += -g -pg
else
if COND_DEBUG
AM_CXXFLAGS += -g
endif
endif

install-exec-hook:
	mv $(DESTDIR)$(pkglibdir)/qt-svg.$(MODULE_SUFFIX) $(DESTDIR)$(pkglibdir)/qt-svg-api-$(MODULE_API).qmod
	rm -f $(DESTDIR)$(pkglibdir)/qt-svg.la $(DESTDIR)$(pkglibdir)/qt-svg.a
