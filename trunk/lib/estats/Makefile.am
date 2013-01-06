# Header files for public installation
tcpestats_pub_h_sources = \
	error.h \
	estats.h \
	estats-connection.h \
	estats-data.h \
	estats-genl.h \
	estats-nl.h \
	estats-nl-client.h \
	types.h

# Header files not installed
tcpestats_pri_h_sources = \
	debug-int.h \
	error-int.h \
	libcwrap-int.h \
	list-int.h \
	resolve-int.h \
	estats-int.h \
	types-int.h

# C sources to build the library from
tcpestats_c_sources = \
	debug-int.c \
	error.c \
	libcwrap-int.c \
	resolve-int.c \
	estats-connection.c \
	estats-data.c \
	estats-genl.c \
	estats-nl-client.c \
	estats-var.c

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
	-version-info $(LIBTCPESTATS_LT_CURRENT):$(LIBTCPESTATS_LT_REVISION):$(LIBTCPESTATS_LT_AGE) \
	-export-symbols-regex '^estats_.*' \
	@STRIP_END@

# Libraries to compile and install
lib_LTLIBRARIES = libtcpestats.la

libtcpestats_la_SOURCES = $(tcpestats_c_sources) $(tcpestats_pub_h_sources) $(tcpestats_pri_h_sources)
#libtcpestats_la_LDFLAGS = -version-info=0:1:0

# Install headers into include/tcpestats
# NOTE: If you update this, be sure to update tcpestats-config
libtcpestatsincludedir = $(TCPESTATS_INCLUDE_DIR)/tcpestats
libtcpestatsinclude_HEADERS = $(tcpestats_pub_h_sources)
