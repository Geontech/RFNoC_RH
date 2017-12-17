incdir=$(prefix)/include/
libdir=$(prefix)/lib/

ACLOCAL_AMFLAGS = -I m4 -I${OSSIEHOME}/share/aclocal/ossie
AUTOMAKE_OPTIONS = subdir-objects

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = RFNoC_RH.pc

distclean-local:
	rm -rf autom4te.cache
	rm -rf m4
	rm -f aclocal.m4
	rm -f config.guess
	rm -f config.h
	rm -f config.h.in
	rm -f config.log
	rm -f config.status
	rm -f config.sub
	rm -f configure
	rm -f depcomp
	rm -f libtool
	rm -f ltmain.sh
	rm -f Makefile
	rm -f Makefile.in
	rm -f missing
	rm -f stamp-h1


lib_LTLIBRARIES = libRFNoC_RH.la
libRFNoC_RH_la_SOURCES = \
	src/RFNoC_Component.h \
	src/RFNoC_Persona.h \
	src/RFNoC_Programmable.h \
	src/RFNoC_Utils.cpp
libRFNoC_RH_la_CXXFLAGS = -Wall $(PROJECTDEPS_CFLAGS) $(LIBUHD_CFLAGS) -Iinclude
libRFNoC_RH_la_LDFLAGS = -Wall $(PROJECTDEPS_LIBS) $(LIBUHD_LIBS)
