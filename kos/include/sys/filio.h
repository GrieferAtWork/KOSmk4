/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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
#define FIONBIO  __FIONBIO  /* [int *arg] Set (*arg != 0) or clear (*arg == 0) O_NONBLOCK / IO_NONBLOCK */
#endif /* !FIONBIO && __FIONBIO */
#if !defined(FIOASYNC) && defined(__FIOASYNC)
#define FIOASYNC __FIOASYNC /* [int *arg] Set (*arg != 0) or clear (*arg == 0) O_ASYNC / IO_ASYNC */
#endif /* !FIOASYNC && __FIOASYNC */

#if !defined(FIOSETOWN) && defined(__FIOSETOWN)
#define FIOSETOWN  __FIOSETOWN  /* ... */
#endif /* !FIOSETOWN && __FIOSETOWN */
#if !defined(FIOGETOWN) && defined(__FIOGETOWN)
#define FIOGETOWN  __FIOGETOWN  /* ... */
#endif /* !FIOGETOWN && __FIOGETOWN */



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
