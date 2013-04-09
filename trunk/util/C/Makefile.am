bin_PROGRAMS = deltavars listconninfo listconns readvars record_read record_write watchvars writevar

LIBESTATS_LDADDS = @STRIP_BEGIN@ \
	$(top_builddir)/lib/estats/libestats.la \
	@STRIP_END@

AM_CPPFLAGS = @STRIP_BEGIN@ \
	$(LIBMNL_CFLAGS) \
	-I$(top_srcdir)/lib \
	@STRIP_END@

deltavars_SOURCES = deltavars.c scripts.h
deltavars_LDADD = $(LIBESTATS_LDADDS)

readvars_SOURCES = readvars.c scripts.h
readvars_LDADD = $(LIBESTATS_LDADDS)

record_read_SOURCES = record_read.c scripts.h
record_read_LDADD = $(LIBESTATS_LDADDS)

record_write_SOURCES = record_write.c scripts.h
record_write_LDADD = $(LIBESTATS_LDADDS)

listconninfo_SOURCES = listconninfo.c scripts.h
listconninfo_LDADD = $(LIBESTATS_LDADDS)

listconns_SOURCES = listconns.c scripts.h
listconns_LDADD = $(LIBESTATS_LDADDS)

watchvars_SOURCES = watchvars.c scripts.h
watchvars_LDADD = $(LIBESTATS_LDADDS)

writevar_SOURCES = writevar.c scripts.h
writevar_LDADD = $(LIBESTATS_LDADDS)
