# Header files for public installation
tcpe_pub_h_sources = \
	error.h \
	tcpe.h \
	tcpe-client.h \
	tcpe-data.h \
	tcpe-genl.h \
	tcpe-nl.h \
	types.h

# Header files not installed
tcpe_pri_h_sources = \
	debug-int.h \
	error-int.h \
	libcwrap-int.h \
	list-int.h \
	resolve-int.h \
	tcpe-int.h \
	types-int.h

# C sources to build the library from
tcpe_c_sources = \
	debug-int.c \
	error.c \
	libcwrap-int.c \
	resolve-int.c \
	tcpe-client.c \
	tcpe-data.c \
	tcpe-genl.c \
	tcpe-var.c

# cpp flags to be used with all compilation
# Note: -D_GNU_SOURCE required so headers declare vfscanf (possibly among
#       others)
AM_CPPFLAGS = @STRIP_BEGIN@ \
	$(LIBMNL_CFLAGS) \
	-I$(top_srcdir)/lib \
	-D_GNU_SOURCE \
	@STRIP_END@

AM_LDFLAGS = @STRIP_BEGIN@ \
	$(LIBMNL_LIBS) \
	-version-info $(LIBTCPE_LT_CURRENT):$(LIBTCPE_LT_REVISION):$(LIBTCPE_LT_AGE) \
	-export-symbols-regex '^tcpe_.*' \
	@STRIP_END@

# Libraries to compile and install
lib_LTLIBRARIES = libtcpe.la

libtcpe_la_SOURCES = $(tcpe_c_sources) $(tcpe_pub_h_sources) $(tcpe_pri_h_sources)
#libtcpe_la_LDFLAGS = -version-info=0:1:0

# Install headers into include/tcpe
# NOTE: If you update this, be sure to update tcpe-config
libtcpeincludedir = $(TCPE_INCLUDE_DIR)/tcpe
libtcpeinclude_HEADERS = $(tcpe_pub_h_sources)
