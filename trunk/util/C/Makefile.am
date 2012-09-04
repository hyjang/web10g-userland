bin_PROGRAMS = listconns readconn watchconn

LIBTCPE_LDADDS = @STRIP_BEGIN@ \
	$(top_builddir)/lib/tcpe/libtcpe.la \
	@STRIP_END@

AM_CPPFLAGS = @STRIP_BEGIN@ \
	$(LIBMNL_CFLAGS) \
	-I$(top_srcdir)/lib \
	@STRIP_END@

readconn_SOURCES = readconn.c scripts.h
readconn_LDADD = $(LIBTCPE_LDADDS)

listconns_SOURCES = listconns.c scripts.h
listconns_LDADD = $(LIBTCPE_LDADDS)

watchconn_SOURCES = watchconn.c scripts.h
watchconn_LDADD = $(LIBTCPE_LDADDS)
