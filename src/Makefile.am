AM_CPPFLAGS = @VMOD_INCLUDES@ -Wall -Werror

vmoddir = @VMOD_DIR@
vmod_LTLIBRARIES = libvmod_types.la

libvmod_types_la_LDFLAGS = -module -export-dynamic -avoid-version -shared

libvmod_types_la_SOURCES = \
	vmod_types_string.c \
	vmod_types_integer.c

nodist_libvmod_types_la_SOURCES = \
	vcc_if.c \
	vcc_if.h

vmod_types_*.lo: vcc_if.c vcc_if.h

vcc_if.c: vcc_if.h

vcc_if.h: @VMODTOOL@ $(top_srcdir)/src/vmod_types.vcc
	@VMODTOOL@ $(top_srcdir)/src/vmod_types.vcc

VMOD_TESTS = $(top_srcdir)/src/tests/*.vtc
.PHONY: $(VMOD_TESTS)

$(top_srcdir)/src/tests/*.vtc: libvmod_types.la
	@VARNISHTEST@ -Dvarnishd=@VARNISHD@ -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_types.vcc \
	$(VMOD_TESTS)

CLEANFILES = \
	$(builddir)/vcc_if.c \
	$(builddir)/vcc_if.h \
	$(builddir)/vmod_types.rst \
	$(builddir)/vmod_types.man.rst
