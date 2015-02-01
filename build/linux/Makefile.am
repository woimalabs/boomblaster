lib_LTLIBRARIES = libboomblaster.la

# public headers
library_boomblaster_includedir = $(includedir)/w/audio
library_boomblaster_include_HEADERS = \
	../../include/boomblaster/AudioEngine.hpp \
	../../include/boomblaster/AudioAsset.hpp

# sources
libboomblaster_la_SOURCES = \
	../../src/AudioResource.cpp \
	../../src/AudioAssetPrivate.cpp

libboomblaster_la_CPPFLAGS = -I$(top_srcdir)/include -Wall -Wextra
libboomblaster_la_LDFLAGS = -g -module -avoid-version -shared --disable-static

# pkgconfig
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = boomblaster.pc

EXTRA_DIST = autogen.sh

install-exec-hook:
	find $(DESTDIR)$(libdir) -type f -name \*.la -delete
