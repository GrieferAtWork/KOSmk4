/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: POSIX.1c (Issue 3, IEEE Std 1003.1c-1995) */
/* (#) Portability: Cygwin        (/newlib/libc/include/tar.h) */
/* (#) Portability: FreeBSD       (/include/tar.h) */
/* (#) Portability: GNU C Library (/posix/tar.h) */
/* (#) Portability: NetBSD        (/include/tar.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/tar.h) */
/* (#) Portability: OpenBSD       (/include/tar.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/tar.h) */
/* (#) Portability: diet libc     (/include/tar.h) */
/* (#) Portability: musl libc     (/include/tar.h) */
/* (#) Portability: uClibc        (/include/tar.h) */
#ifndef _TAR_H
#define _TAR_H 1

#include <__stdinc.h>
#include <features.h>

/* Compatibility header for newlib:<tar.h>
 * https://github.com/bminor/newlib/blob/master/newlib/libc/include/tar.h
 * Documentation is taken from that same header. */


/* General definitions */
#define TMAGIC   "ustar" /* ustar plus null byte. */
#define TMAGLEN  6       /* Length of the above. */
#define TVERSION "00"    /* 00 without a null byte. */
#define TVERSLEN 2       /* Length of the above. */

/* Typeflag field definitions */
#define REGTYPE  '0'  /* Regular file. */
#define AREGTYPE '\0' /* Regular file. */
#define LNKTYPE  '1'  /* Link. */
#define SYMTYPE  '2'  /* Symbolic link. */
#define CHRTYPE  '3'  /* Character special. */
#define BLKTYPE  '4'  /* Block special. */
#define DIRTYPE  '5'  /* Directory. */
#define FIFOTYPE '6'  /* FIFO special. */
#define CONTTYPE '7'  /* Reserved. */

/* Mode field bit definitions (octal) */
#define TSUID   04000 /* Set UID on execution. */
#define TSGID   02000 /* Set GID on execution. */
#if defined(__USE_XOPEN) || (!defined(_POSIX_C_SOURCE) || (_POSIX_C_SOURCE + 0) < 200112)
#define TSVTX   01000 /* On directories, restricted deletion flag. */
#endif /* __USE_XOPEN || _POSIX_C_SOURCE < 200112 */
#define TUREAD  00400 /* Read by owner. */
#define TUWRITE 00200 /* Write by owner. */
#define TUEXEC  00100 /* Execute/search by owner. */
#define TGREAD  00040 /* Read by group. */
#define TGWRITE 00020 /* Write by group. */
#define TGEXEC  00010 /* Execute/search by group. */
#define TOREAD  00004 /* Read by other. */
#define TOWRITE 00002 /* Write by other. */
#define TOEXEC  00001 /* Execute/search by other. */

#endif /* !_TAR_H */
