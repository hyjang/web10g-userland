ACLOCAL_AMFLAGS = -I build-aux

SUBDIRS = lib util

#bin_SCRIPTS = tcpe-config
#CLEANFILES = tcpe-config

#m4datadir = $(datadir)/aclocal
#m4data_DATA = tcpe.m4

#EXTRA_DIST = tcpe-config.in tcpe.m4

EXTRA_DIST = estats-nl-0.4-3.5.patch libmnl-1.0.3.tar.bz2

edit = @STRIP_BEGIN@ \
   sed -e 's,@TCPE_VERSION\@,$(TCPE_VERSION),g' \
       -e 's,@PREFIX\@,$(prefix),g' \
       -e 's,@EXEC_PREFIX\@,$(exec_prefix),g' \
       -e 's,@TCPE_INCLUDE_DIR\@,$(TCPE_INCLUDE_DIR),g' \
       -e 's,@LIBDIR\@,$(libdir),g' \
       @STRIP_END@

tcpe-config: $(srcdir)/tcpe-config.in
	rm -f tcpe-config tcpe-config.tmp
	$(edit) $(srcdir)/tcpe-config.in > tcpe-config.tmp
	chmod +x tcpe-config.tmp
	mv tcpe-config.tmp tcpe-config
