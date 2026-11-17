#ifndef VERSION_H
#define VERSION_H

/*
 * Game release identifiers. The build defines VERSION as one of these (e.g.
 * make VERSION=jp builds with -DVERSION=VERSION_JP).
 *
 * The values are ordered by build date so code can test for changes that
 * carried forward, e.g. `#if VERSION >= VERSION_US_PROTO`. The prototype
 * positions are provisional until those builds are split and compared.
 */
#define VERSION_JP_PROTO 1
#define VERSION_JP       2
#define VERSION_US_PROTO 3
#define VERSION_US       4
#define VERSION_PAL      5

#ifndef VERSION
#error "VERSION is not defined; it is passed by the Makefile."
#endif

/* Regions, for differences that follow the market rather than the build date. */
#define REGION_JP  (VERSION == VERSION_JP_PROTO || VERSION == VERSION_JP)
#define REGION_US  (VERSION == VERSION_US_PROTO || VERSION == VERSION_US)
#define REGION_PAL (VERSION == VERSION_PAL)

#endif /* VERSION_H */
