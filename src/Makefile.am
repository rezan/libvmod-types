AM_CFLAGS = $(VARNISHAPI_CFLAGS) -Wall -Werror
AM_LDFLAGS = $(VARNISHAPI_LIBS) $(VMOD_LDFLAGS)

vmod_LTLIBRARIES = libvmod_types.la

libvmod_types_la_SOURCES = \
	vmod_types_integer.c \
	vmod_types_string.c

nodist_libvmod_types_la_SOURCES = \
	vcc_types_if.c \
	vcc_types_if.h

dist_man_MANS = vmod_types.3

@BUILD_VMOD_TYPES@

AM_TESTS_ENVIRONMENT = \
	PATH="$(VMOD_TEST_PATH)" \
	LD_LIBRARY_PATH="$(VARNISH_LIBRARY_PATH)"
TEST_EXTENSIONS = .vtc
VTC_LOG_COMPILER = varnishtest -v
AM_VTC_LOG_FLAGS = -Dvmod_types="$(VMOD_TYPES)"

TESTS = @VMOD_TESTS@

EXTRA_DIST = \
	vmod_types.vcc \
	$(VMOD_TESTS)
