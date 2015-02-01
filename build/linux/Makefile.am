lib_LTLIBRARIES = boomblaster.la

# sources
libboomblaster_la_SOURCES = \
	../../src/TrackerSample.cpp

# public headers
library_boomblaster_includedir = $(includedir)/w/audio
library_boomblaster_include_HEADERS = \
	../include/w/audio/AudioEngine.hpp \
	../include/w/audio/AudioAsset.hpp

libboomblaster_la_CPPFLAGS = -I$(top_srcdir)/include -Wall -Wextra
libboomblaster_la_LDFLAGS = -g -module -avoid-version -shared --disable-static

# pkgconfig
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = boomblaster.pc

EXTRA_DIST = autogen.sh

install-exec-hook:
	find $(DESTDIR)$(libdir) -type f -name \*.la -delete
