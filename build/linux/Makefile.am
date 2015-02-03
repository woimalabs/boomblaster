lib_LTLIBRARIES = libboomblaster.la

# public headers
library_boomblaster_includedir = $(includedir)/boomblaster
library_boomblaster_include_HEADERS = \
	../../include/boomblaster/AudioEngine.hpp \
	../../include/boomblaster/AudioAsset.hpp

# sources
libboomblaster_la_SOURCES = \
	../../src/helpers/Referenced.cpp \
	../../src/helpers/ResourceManager.cpp \
	../../src/helpers/ResourceManagerPrivate.cpp \
	../../src/helpers/FileHandle.cpp \
	../../src/helpers/Thread.cpp \
	../../src/helpers/Mutex.cpp \
	../../src/helpers/Timer.cpp \
	../../src/helpers/Log.cpp \
	../../src/AudioResource.cpp \
	../../src/AudioAssetPrivate.cpp \
	../../src/AudioAsset.cpp \
	../../src/TrackerSample.cpp \
	../../src/TrackerProducerThread.cpp \
	../../src/Tracker.cpp \
	../../src/AudioEngine.cpp \
	../../src/AudioEnginePrivate-Pulse.cpp

libboomblaster_la_CPPFLAGS = -I$(top_srcdir)/include -Wall -Wextra
libboomblaster_la_LDFLAGS = -g -module -avoid-version -shared --disable-static

# pkgconfig
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = boomblaster.pc

EXTRA_DIST = autogen.sh

install-exec-hook:
	find $(DESTDIR)$(libdir) -type f -name \*.la -delete
