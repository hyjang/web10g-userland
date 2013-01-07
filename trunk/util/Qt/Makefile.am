
include $(top_srcdir)/build-aux/autotroll.mk

# For a program:
bin_PROGRAMS = estatsview
#estatsview_SOURCES = main.cc qt_main.cpp
estatsview_SOURCES = main.cpp
estatsview_CXXFLAGS = $(QT_CXXFLAGS) $(AM_CXXFLAGS)
estatsview_CPPFLAGS = $(QT_CPPFLAGS) $(AM_CPPFLAGS)
estatsview_LDFLAGS  = $(QT_LDFLAGS) $(LDFLAGS)
estatsview_LDADD    = $(QT_LIBS) $(LDADD)

#BUILT_SOURCES = estatsview.moc.cpp
