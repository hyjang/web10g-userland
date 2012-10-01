bin_PROGRAMS = deltavars listconns readvars watchvars writevar

LIBTCPE_LDADDS = @STRIP_BEGIN@ \
	$(top_builddir)/lib/tcpe/libtcpe.la \
	@STRIP_END@

AM_CPPFLAGS = @STRIP_BEGIN@ \
	$(LIBMNL_CFLAGS) \
	-I$(top_srcdir)/lib \
	@STRIP_END@

deltavars_SOURCES = deltavars.c scripts.h
deltavars_LDADD = $(LIBTCPE_LDADDS)

readvars_SOURCES = readvars.c scripts.h
readvars_LDADD = $(LIBTCPE_LDADDS)

listconns_SOURCES = listconns.c scripts.h
listconns_LDADD = $(LIBTCPE_LDADDS)

watchvars_SOURCES = watchvars.c scripts.h
watchvars_LDADD = $(LIBTCPE_LDADDS)

writevar_SOURCES = writevar.c scripts.h
writevar_LDADD = $(LIBTCPE_LDADDS)
