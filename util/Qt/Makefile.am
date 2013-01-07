
include $(top_srcdir)/build-aux/autotroll.mk

LIBESTATS_LDADDS = @STRIP_BEGIN@ \
	$(top_builddir)/lib/estats/libestats.la \
	@STRIP_END@
			
# For a program:
bin_PROGRAMS = estatsview
#estatsview_SOURCES = main.cc qt_main.cpp
estatsview_SOURCES = EstatsView.cpp conn_tablemodel.cpp estats_itemdelegate.cpp estats_tablemodel.cpp main.cpp mainwindow.cpp var_tablemodel.cpp varwindow.cpp moc_conn_tablemodel.cpp moc_estats_itemdelegate.cpp moc_estats_tablemodel.cpp moc_mainwindow.cpp moc_var_tablemodel.cpp moc_varwindow.cpp

estatsview_CXXFLAGS = $(QT_CXXFLAGS) $(AM_CXXFLAGS)
estatsview_CPPFLAGS = $(QT_CPPFLAGS) $(AM_CPPFLAGS)
estatsview_LDFLAGS  = $(QT_LDFLAGS) $(LDFLAGS)
estatsview_LDADD    = $(QT_LIBS) $(LIBESTATS_LDADDS) $(LDADD)

BUILT_SOURCES = moc_conn_tablemodel.cpp moc_estats_itemdelegate.cpp moc_estats_tablemodel.cpp moc_mainwindow.cpp moc_var_tablemodel.cpp moc_varwindow.cpp
