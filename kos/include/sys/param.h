/* Copyright (c) 2019-2024 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/param.h) */
/* (#) Portability: DJGPP         (/include/sys/param.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/param.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/param.h) */
/* (#) Portability: FreeBSD       (/sys/sys/param.h) */
/* (#) Portability: GNU C Library (/misc/sys/param.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/sys/param.h) */
/* (#) Portability: NetBSD        (/sys/sys/param.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/param.h) */
/* (#) Portability: OpenBSD       (/sys/sys/param.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/param.h) */
/* (#) Portability: diet libc     (/include/sys/param.h) */
/* (#) Portability: libbsd        (/include/bsd/sys/param.h) */
/* (#) Portability: libc4/5       (/include/sys/param.h) */
/* (#) Portability: mintlib       (/include/sys/param.h) */
/* (#) Portability: musl libc     (/include/sys/param.h) */
/* (#) Portability: uClibc        (/include/sys/param.h) */
#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/__minmax.h>

#include <asm/os/limits.h>
#include <asm/pagesize.h>

#include <limits.h>

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>

#include <endian.h>
#include <signal.h>
#endif /* __USE_GLIBC_BLOAT */

/* NOTE: This  differs from the version defined by <hybrid/minmax.h>,
 *       in that this one can safely be used in constant expressions,
 *       with the downside that it (may) evaluate its arguments  more
 *       than once. */
#ifndef MIN
#define MIN(a, b) __hybrid_min_c2(a, b)
#endif /* !MIN */
#ifndef MAX
#define MAX(a, b) __hybrid_max_c2(a, b)
#endif /* !MAX */

#if !defined(__EXEC_PAGESIZE) && defined(__ARCH_PAGESIZE)
#define __EXEC_PAGESIZE __ARCH_PAGESIZE
#endif /* !__EXEC_PAGESIZE && __ARCH_PAGESIZE */

/* System memory page size */
#if !defined(EXEC_PAGESIZE) && defined(__EXEC_PAGESIZE)
#define EXEC_PAGESIZE __EXEC_PAGESIZE
#endif /* !EXEC_PAGESIZE && __EXEC_PAGESIZE */

/* Scheduler frequency */
#if !defined(HZ) && defined(__HZ)
#define HZ __HZ
#endif /* !HZ && __HZ != -1 */

/* NR_OPEN: Alias for `OPEN_MAX' */
#ifndef NR_OPEN
#ifdef OPEN_MAX
#define NR_OPEN OPEN_MAX
#elif defined(__OPEN_MAX) && (__OPEN_MAX + 0) != -1
#define NR_OPEN __OPEN_MAX
#endif /* ... */
#endif /* !NR_OPEN */

/* NOGROUP: Alias for `NGROUPS_MAX' */
#ifndef NOGROUP
#ifdef NGROUPS_MAX
#define NOGROUP NGROUPS_MAX
#elif defined(__NGROUPS_MAX) && (__NGROUPS_MAX + 0) != -1
#define NOGROUP __NGROUPS_MAX
#endif /* ... */
#endif /* !NOGROUP */

/* MAXHOSTNAMELEN: Alias for `HOST_NAME_MAX' */
#ifndef MAXHOSTNAMELEN
#ifdef HOST_NAME_MAX
#define MAXHOSTNAMELEN HOST_NAME_MAX
#elif defined(__HOST_NAME_MAX) && (__HOST_NAME_MAX + 0) != -1
#define MAXHOSTNAMELEN __HOST_NAME_MAX
#endif /* ... */
#endif /* !MAXHOSTNAMELEN */

/* MAXGETHOSTNAME: Alias for `HOST_NAME_MAX' (defined in djgpp) */
#ifndef MAXGETHOSTNAME
#ifdef HOST_NAME_MAX
#define MAXGETHOSTNAME HOST_NAME_MAX
#elif defined(__HOST_NAME_MAX) && (__HOST_NAME_MAX + 0) != -1
#define MAXGETHOSTNAME __HOST_NAME_MAX
#endif /* ... */
#endif /* !MAXGETHOSTNAME */

/* Max # of supplemental group IDs that may be set () */
#if !defined(NGROUPS_MAX) && defined(__NGROUPS_MAX) && (__NGROUPS_MAX + 0) != -1
#define NGROUPS_MAX __NGROUPS_MAX
#endif /* !NGROUPS_MAX && __NGROUPS_MAX != -1 */

/* Max # of bytes of args + environ for exec(); */
#if !defined(ARG_MAX) && defined(__ARG_MAX) && (__ARG_MAX + 0) != -1
#define ARG_MAX __ARG_MAX
#endif /* !ARG_MAX && __ARG_MAX != -1 */

/* Max # of links a file may have (fs-dependent) */
#if !defined(LINK_MAX) && defined(__LINK_MAX) && (__LINK_MAX + 0) != -1
#define LINK_MAX __LINK_MAX
#endif /* !LINK_MAX && __LINK_MAX != -1 */

/* Max size of the canonical input queue */
#if !defined(MAX_CANON) && defined(__MAX_CANON) && (__MAX_CANON + 0) != -1
#define MAX_CANON __MAX_CANON
#endif /* !MAX_CANON && __MAX_CANON != -1 */

/* Max size of the type-ahead buffer */
#if !defined(MAX_INPUT) && defined(__MAX_INPUT) && (__MAX_INPUT + 0) != -1
#define MAX_INPUT __MAX_INPUT
#endif /* !MAX_INPUT && __MAX_INPUT != -1 */

/* Max # of chars in a file name */
#if !defined(NAME_MAX) && defined(__NAME_MAX) && (__NAME_MAX + 0) != -1
#define NAME_MAX __NAME_MAX
#endif /* !NAME_MAX && __NAME_MAX != -1 */

/* Max # of chars in a path name including nul */
#if !defined(PATH_MAX) && defined(__PATH_MAX) && (__PATH_MAX + 0) != -1
#define PATH_MAX __PATH_MAX
#endif /* !PATH_MAX && __PATH_MAX != -1 */

/* Max # of bytes in atomic write to a pipe (Default value, assuming
 * that backing  memory  isn't  VIO or  re-mapped  during  a  write) */
#if !defined(PIPE_BUF) && defined(__PIPE_BUF) && (__PIPE_BUF + 0) != -1
#define PIPE_BUF __PIPE_BUF
#endif /* !PIPE_BUF && __PIPE_BUF != -1 */

/* # of realtime signals */
#if !defined(RTSIG_MAX) && defined(__RTSIG_MAX) && (__RTSIG_MAX + 0) != -1
#define RTSIG_MAX __RTSIG_MAX
#endif /* !RTSIG_MAX && __RTSIG_MAX != -1 */

/* NBBY: Alias for `CHAR_BIT' (Number_of_Bits_in_a_BYte) */
#ifndef NBBY
#define NBBY CHAR_BIT
#endif /* !NBBY */

/* NGROUPS: Alias for `NGROUPS_MAX' */
#if !defined(NGROUPS) && defined(NGROUPS_MAX)
#define NGROUPS NGROUPS_MAX
#endif /* !NGROUPS && NGROUPS_MAX */

/* MAXSYMLINKS: Alias for `SYMLOOP_MAX' */
#if !defined(MAXSYMLINKS) && defined(SYMLOOP_MAX)
#define MAXSYMLINKS SYMLOOP_MAX
#endif /* !MAXSYMLINKS && SYMLOOP_MAX */

/* CANBSIZ: Alias for `MAX_CANON' */
#if !defined(CANBSIZ) && defined(MAX_CANON)
#define CANBSIZ MAX_CANON
#endif /* !CANBSIZ && MAX_CANON */

/* MAXPATHLEN: Alias for `PATH_MAX' (that still gets defined, even when `PATH_MAX' isn't).
 * WARNING: If this one doesn't get defined, some 3rd party programs break (e.g. bsdgames).
 * WARNING: If this does get defined, gnulib will try to link against `chdir_long()' */
#if !defined(MAXPATHLEN) && defined(PATH_MAX)
#define MAXPATHLEN PATH_MAX
#endif /* !MAXPATHLEN && PATH_MAX */

/* NOFILE: Alias for `OPEN_MAX' */
#if !defined(NOFILE) && defined(OPEN_MAX)
#define NOFILE OPEN_MAX
#endif /* !NOFILE && OPEN_MAX */

/* NCARGS: Alias for `ARG_MAX' */
#ifndef NCARGS
#ifdef ARG_MAX
#define NCARGS ARG_MAX
#else /* ARG_MAX */
#define NCARGS INT_MAX
#endif /* !ARG_MAX */
#endif /* !NCARGS */


/************************************************************************/
/* MISC CONSTANTS AND HELPER MACROS                                     */
/************************************************************************/

#ifndef NODEV
#define NODEV (__CCAST(dev_t)-1)
#endif /* !NODEV */

#ifndef DEV_BSIZE
#define DEV_BSIZE 512
#endif /* !DEV_BSIZE */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

#ifndef setbit
#define setbit(a, i) ((a)[(i) / NBBY] |= 1 << ((i) % NBBY))
#endif /* !setbit */

#ifndef clrbit
#define clrbit(a, i) ((a)[(i) / NBBY] &= ~(1 << ((i) % NBBY)))
#endif /* !clrbit */

#ifndef isset
#define isset(a, i) ((a)[(i) / NBBY] & (1 << ((i) % NBBY)))
#endif /* !isset */

#ifndef isclr
#define isclr(a, i) (!((a)[(i) / NBBY] & (1 << ((i) % NBBY))))
#endif /* !isclr */

#ifndef howmany
#define howmany(x, y) (((x) + ((y)-1)) / (y))
#endif /* !howmany */

#ifndef powerof2
#define powerof2(x) (!(((x)-1) & (x)))
#endif /* !powerof2 */

#ifndef roundup
#ifndef __NO_builtin_constant_p
#define roundup(x, y)                       \
	(__builtin_constant_p(y) && powerof2(y) \
	 ? (((x) + (y)-1) & ~((y)-1))           \
	 : ((((x) + ((y)-1)) / (y)) * (y)))
#else /* !__NO_builtin_constant_p */
#define roundup(x, y) \
	((((x) + ((y)-1)) / (y)) * (y))
#endif /* __NO_builtin_constant_p */
#endif /* !roundup */

#endif /* !_SYS_PARAM_H */
