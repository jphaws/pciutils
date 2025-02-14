/*
 *	The PCI Utilities -- Declarations
 *
 *	Copyright (c) 1997--2018 Martin Mares <mj@ucw.cz>
 *
 *	Can be freely distributed and used under the terms of the GNU GPL v2+
 *
 *	SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "lib/pci.h"
#include "lib/sysdep.h"
#include "lib/bitops.h"

/*
 * gcc predefines macro __MINGW32__ for all MinGW targets.
 * Including some MinGW header (e.g. windef.h) defines additional
 * macro __MINGW32_MAJOR_VERSION (available for all MinGW targets).
 */
#if defined(PCI_OS_WINDOWS) && defined(__MINGW32__)
#include <windef.h>
#endif

/*
 * On Windows only MinGW 3.0 and higher versions provides <getopt.h>
 * header file. Older MinGW versions and MSVC do not have it.
 */
#if defined(PCI_OS_WINDOWS) && !(defined(__MINGW32_MAJOR_VERSION) && __MINGW32_MAJOR_VERSION >= 3)
#include "compat/getopt.h"
#else
#include <unistd.h>
#endif

#define PCIUTILS_VERSION PCILIB_VERSION

extern const char program_name[];

void die(char *msg, ...) NONRET PCI_PRINTF(1,2);
void *xmalloc(size_t howmuch);
void *xrealloc(void *ptr, size_t howmuch);
char *xstrdup(const char *str);
int parse_generic_option(int i, struct pci_access *pacc, char *arg);

#ifdef PCI_HAVE_PM_INTEL_CONF
#define GENOPT_INTEL "H:"
#define GENHELP_INTEL "-H <mode>\tUse direct hardware access (<mode> = 1 or 2)\n"
#else
#define GENOPT_INTEL
#define GENHELP_INTEL
#endif
#if defined(PCI_HAVE_PM_DUMP) && !defined(PCIUTILS_SETPCI)
#define GENOPT_DUMP "F:"
#define GENHELP_DUMP "-F <file>\tRead PCI configuration dump from a given file\n"
#else
#define GENOPT_DUMP
#define GENHELP_DUMP
#endif

#define GENERIC_OPTIONS "A:GO:" GENOPT_INTEL GENOPT_DUMP
#define GENERIC_HELP \
	"-A <method>\tUse the specified PCI access method (see `-A help' for a list)\n" \
	"-O <par>=<val>\tSet PCI access parameter (see `-O help' for a list)\n" \
	"-G\t\tEnable PCI access debugging\n" \
	GENHELP_INTEL GENHELP_DUMP
