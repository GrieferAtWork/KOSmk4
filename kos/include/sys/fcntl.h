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
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/fcntl.h) */
/* (#) Portability: DJGPP         (/include/sys/fcntl.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/fcntl.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/fcntl.h) */
/* (#) Portability: FreeBSD       (/sys/sys/fcntl.h) */
/* (#) Portability: GNU C Library (/io/sys/fcntl.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/sys/fcntl.h) */
/* (#) Portability: NetBSD        (/sys/sys/fcntl.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/fcntl.h) */
/* (#) Portability: OpenBSD       (/sys/sys/fcntl.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/fcntl.h) */
/* (#) Portability: libc4/5       (/include/sys/fcntl.h) */
/* (#) Portability: mintlib       (/include/sys/fcntl.h) */
/* (#) Portability: musl libc     (/include/sys/fcntl.h) */
/* (#) Portability: uClibc        (/include/sys/fcntl.h) */
#ifndef _SYS_FCNTL_H
#define _SYS_FCNTL_H 1

#include <fcntl.h>

#include <features.h>

#ifdef __USE_SOLARIS
#include <asm/os/file-ioctls.h>

/* Arguments for `_FIODIRECTIO' from <sys/filio.h> */
#if !defined(DIRECTIO_OFF) && defined(__DIRECTIO_OFF)
#define DIRECTIO_OFF __DIRECTIO_OFF /* Disable optional direct I/O (clear O_DIRECT and IO_OPTDIRECT) */
#endif /* !DIRECTIO_OFF && __DIRECTIO_OFF */
#if !defined(DIRECTIO_ON) && defined(__DIRECTIO_ON)
#define DIRECTIO_ON __DIRECTIO_ON /* Enable optional direct I/O  (set O_DIRECT and IO_OPTDIRECT) */
#endif /* !DIRECTIO_ON && __DIRECTIO_ON */
#if !defined(DIRECTIO_MAND) && defined(__DIRECTIO_MAND)
#define DIRECTIO_MAND __DIRECTIO_MAND /* Enable mandatory direct I/O (only set O_DIRECT; KOS-specific) */
#endif /* !DIRECTIO_MAND && __DIRECTIO_MAND */

#endif /* __USE_SOLARIS */

#endif /* !_SYS_FCNTL_H */
