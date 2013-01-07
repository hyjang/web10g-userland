bin_PROGRAMS = deltavars listconninfo listconns readvars watchvars writevar

LIBTCPESTATS_LDADDS = @STRIP_BEGIN@ \
	$(top_builddir)/lib/estats/libtcpestats.la \
	@STRIP_END@

AM_CPPFLAGS = @STRIP_BEGIN@ \
	$(LIBMNL_CFLAGS) \
	-I$(top_srcdir)/lib \
	@STRIP_END@

deltavars_SOURCES = deltavars.c scripts.h
deltavars_LDADD = $(LIBTCPESTATS_LDADDS)

readvars_SOURCES = readvars.c scripts.h
readvars_LDADD = $(LIBTCPESTATS_LDADDS)

listconninfo_SOURCES = listconninfo.c scripts.h
listconninfo_LDADD = $(LIBTCPESTATS_LDADDS)

listconns_SOURCES = listconns.c scripts.h
listconns_LDADD = $(LIBTCPESTATS_LDADDS)

watchvars_SOURCES = watchvars.c scripts.h
watchvars_LDADD = $(LIBTCPESTATS_LDADDS)

writevar_SOURCES = writevar.c scripts.h
writevar_LDADD = $(LIBTCPESTATS_LDADDS)
