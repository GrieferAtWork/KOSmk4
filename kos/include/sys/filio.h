/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: DragonFly BSD (/sys/sys/filio.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/filio.h) */
/* (#) Portability: FreeBSD       (/sys/sys/filio.h) */
/* (#) Portability: NetBSD        (/sys/sys/filio.h) */
/* (#) Portability: OpenBSD       (/sys/sys/filio.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/filio.h) */
#ifndef _SYS_FILIO_H
#define _SYS_FILIO_H 1

#include <__stdinc.h>

#include <asm/os/socket-ioctls.h>
#include <asm/os/tty.h>
#include <asm/os/file-ioctls.h>

/* This file only needs to define the following macros:
 * >> #define FIOCLEX   ...
 * >> #define FIONCLEX  ...
 * >> #define FIONREAD  ...
 * >> #define FIONBIO   ...
 * >> #define FIOASYNC  ...
 * >> #define FIOSETOWN ...
 * >> #define FIOGETOWN ... */

#if !defined(FIONCLEX) && defined(__FIONCLEX)
#define FIONCLEX __FIONCLEX /* Clear O_CLOEXEC / IO_CLOEXEC */
#endif /* !FIONCLEX && __FIONCLEX */
#if !defined(FIOCLEX) && defined(__FIOCLEX)
#define FIOCLEX  __FIOCLEX  /* Set O_CLOEXEC / IO_CLOEXEC */
#endif /* !FIOCLEX && __FIOCLEX */
#if !defined(FIONREAD) && defined(__TIOCINQ)
#define FIONREAD __TIOCINQ  /* [int *count] Save the number of pending input bytes */
#endif /* !FIONREAD && __TIOCINQ */
#if !defined(FIONBIO) && defined(__FIONBIO)
#define FIONBIO  __FIONBIO  /* [int const *arg] Set (*arg != 0) or clear (*arg == 0) O_NONBLOCK / IO_NONBLOCK */
#endif /* !FIONBIO && __FIONBIO */
#if !defined(FIOASYNC) && defined(__FIOASYNC)
#define FIOASYNC __FIOASYNC /* [int const *arg] Set (*arg != 0) or clear (*arg == 0) O_ASYNC / IO_ASYNC */
#endif /* !FIOASYNC && __FIOASYNC */

#if !defined(FIOSETOWN) && defined(__FIOSETOWN)
#define FIOSETOWN  __FIOSETOWN  /* ... */
#endif /* !FIOSETOWN && __FIOSETOWN */
#if !defined(FIOGETOWN) && defined(__FIOGETOWN)
#define FIOGETOWN  __FIOGETOWN  /* ... */
#endif /* !FIOGETOWN && __FIOGETOWN */


/************************************************************************/
/* Additional stuff normally only found on OpenSolaris                  */
/************************************************************************/
#if !defined(_FIOLFS) && defined(__FIOLFS)
#define _FIOLFS __FIOLFS
#endif /* !_FIOLFS && __FIOLFS */
#if !defined(_FIOLFSS) && defined(__FIOLFSS)
#define _FIOLFSS __FIOLFSS
#endif /* !_FIOLFSS && __FIOLFSS */
#if !defined(_FIOFFS) && defined(__FIOFFS)
#define _FIOFFS __FIOFFS
#endif /* !_FIOFFS && __FIOFFS */
#if !defined(_FIOAI) && defined(__FIOAI)
#define _FIOAI __FIOAI
#endif /* !_FIOAI && __FIOAI */
#if !defined(_FIOOBSOLETE67) && defined(__FIOOBSOLETE67)
#define _FIOOBSOLETE67 __FIOOBSOLETE67
#endif /* !_FIOOBSOLETE67 && __FIOOBSOLETE67 */
#if !defined(_FIOSATIME) && defined(__FIOSATIME)
#define _FIOSATIME __FIOSATIME
#endif /* !_FIOSATIME && __FIOSATIME */
#if !defined(_FIOSDIO) && defined(__FIOSDIO)
#define _FIOSDIO __FIOSDIO
#endif /* !_FIOSDIO && __FIOSDIO */
#if !defined(_FIOGDIO) && defined(__FIOGDIO)
#define _FIOGDIO __FIOGDIO
#endif /* !_FIOGDIO && __FIOGDIO */
#if !defined(_FIOIO) && defined(__FIOIO)
#define _FIOIO __FIOIO
#endif /* !_FIOIO && __FIOIO */
#if !defined(_FIOISLOG) && defined(__FIOISLOG)
#define _FIOISLOG __FIOISLOG
#endif /* !_FIOISLOG && __FIOISLOG */
#if !defined(_FIOISLOGOK) && defined(__FIOISLOGOK)
#define _FIOISLOGOK __FIOISLOGOK
#endif /* !_FIOISLOGOK && __FIOISLOGOK */
#if !defined(_FIOLOGRESET) && defined(__FIOLOGRESET)
#define _FIOLOGRESET __FIOLOGRESET
#endif /* !_FIOLOGRESET && __FIOLOGRESET */
#if !defined(_FIOISBUSY) && defined(__FIOISBUSY)
#define _FIOISBUSY __FIOISBUSY
#endif /* !_FIOISBUSY && __FIOISBUSY */
#if !defined(_FIODIRECTIO) && defined(__FIODIRECTIO)
#define _FIODIRECTIO __FIODIRECTIO
#endif /* !_FIODIRECTIO && __FIODIRECTIO */
#if !defined(_FIOTUNE) && defined(__FIOTUNE)
#define _FIOTUNE __FIOTUNE
#endif /* !_FIOTUNE && __FIOTUNE */
#if !defined(_FIOLOGENABLE) && defined(__FIOLOGENABLE)
#define _FIOLOGENABLE __FIOLOGENABLE
#endif /* !_FIOLOGENABLE && __FIOLOGENABLE */
#if !defined(_FIOLOGDISABLE) && defined(__FIOLOGDISABLE)
#define _FIOLOGDISABLE __FIOLOGDISABLE
#endif /* !_FIOLOGDISABLE && __FIOLOGDISABLE */
#if !defined(_FIOSNAPSHOTCREATE) && defined(__FIOSNAPSHOTCREATE)
#define _FIOSNAPSHOTCREATE __FIOSNAPSHOTCREATE
#endif /* !_FIOSNAPSHOTCREATE && __FIOSNAPSHOTCREATE */
#if !defined(_FIOSNAPSHOTDELETE) && defined(__FIOSNAPSHOTDELETE)
#define _FIOSNAPSHOTDELETE __FIOSNAPSHOTDELETE
#endif /* !_FIOSNAPSHOTDELETE && __FIOSNAPSHOTDELETE */
#if !defined(_FIOGETSUPERBLOCK) && defined(__FIOGETSUPERBLOCK)
#define _FIOGETSUPERBLOCK __FIOGETSUPERBLOCK
#endif /* !_FIOGETSUPERBLOCK && __FIOGETSUPERBLOCK */
#if !defined(_FIOGETMAXPHYS) && defined(__FIOGETMAXPHYS)
#define _FIOGETMAXPHYS __FIOGETMAXPHYS
#endif /* !_FIOGETMAXPHYS && __FIOGETMAXPHYS */
#if !defined(_FIO_SET_LUFS_DEBUG) && defined(__FIO_SET_LUFS_DEBUG)
#define _FIO_SET_LUFS_DEBUG __FIO_SET_LUFS_DEBUG
#endif /* !_FIO_SET_LUFS_DEBUG && __FIO_SET_LUFS_DEBUG */
#if !defined(_FIO_SET_LUFS_ERROR) && defined(__FIO_SET_LUFS_ERROR)
#define _FIO_SET_LUFS_ERROR __FIO_SET_LUFS_ERROR
#endif /* !_FIO_SET_LUFS_ERROR && __FIO_SET_LUFS_ERROR */
#if !defined(_FIO_GET_TOP_STATS) && defined(__FIO_GET_TOP_STATS)
#define _FIO_GET_TOP_STATS __FIO_GET_TOP_STATS
#endif /* !_FIO_GET_TOP_STATS && __FIO_GET_TOP_STATS */
#if !defined(_FIOSNAPSHOTCREATE_MULTI) && defined(__FIOSNAPSHOTCREATE_MULTI)
#define _FIOSNAPSHOTCREATE_MULTI __FIOSNAPSHOTCREATE_MULTI
#endif /* !_FIOSNAPSHOTCREATE_MULTI && __FIOSNAPSHOTCREATE_MULTI */
#if !defined(_FIO_SEEK_DATA) && defined(__FIO_SEEK_DATA)
#define _FIO_SEEK_DATA __FIO_SEEK_DATA
#endif /* !_FIO_SEEK_DATA && __FIO_SEEK_DATA */
#if !defined(_FIO_SEEK_HOLE) && defined(__FIO_SEEK_HOLE)
#define _FIO_SEEK_HOLE __FIO_SEEK_HOLE
#endif /* !_FIO_SEEK_HOLE && __FIO_SEEK_HOLE */
#if !defined(_FIO_COMPRESSED) && defined(__FIO_COMPRESSED)
#define _FIO_COMPRESSED __FIO_COMPRESSED
#endif /* !_FIO_COMPRESSED && __FIO_COMPRESSED */



/************************************************************************/
/* Additional stuff normally only found on BSD                          */
/************************************************************************/

/* Possible values for `FIODTYPE' */
#if !defined(D_TAPE) && defined(__D_TAPE)
#define D_TAPE __D_TAPE /* *unused* */
#endif /* !D_TAPE && __D_TAPE */
#if !defined(D_DISK) && defined(__D_DISK)
#define D_DISK __D_DISK /* /dev/hda */
#endif /* !D_DISK && __D_DISK */
#if !defined(D_TTY) && defined(__D_TTY)
#define D_TTY  __D_TTY  /* isatty() */
#endif /* !D_TTY && __D_TTY */
#if !defined(D_MEM) && defined(__D_MEM)
#define D_MEM  __D_MEM  /* /dev/mem and /dev/kmem */
#endif /* !D_MEM && __D_MEM */

#if !defined(FIODTYPE) && defined(__FIODTYPE)
#define FIODTYPE __FIODTYPE /* Returns set of `__D_*' */
#endif /* !FIODTYPE && __FIODTYPE */

#endif /* !_SYS_FILIO_H */
