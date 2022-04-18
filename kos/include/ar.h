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
/* (#) Portability: Cygwin        (/newlib/libc/include/ar.h) */
/* (#) Portability: DJGPP         (/include/ar.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/ar.h) */
/* (#) Portability: FreeBSD       (/include/ar.h) */
/* (#) Portability: GNU C Library (/misc/ar.h) */
/* (#) Portability: NetBSD        (/include/ar.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/ar.h) */
/* (#) Portability: OpenBSD       (/include/ar.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/ar.h) */
/* (#) Portability: diet libc     (/include/ar.h) */
/* (#) Portability: libc4/5       (/include/ar.h) */
/* (#) Portability: libc6         (/include/ar.h) */
/* (#) Portability: mintlib       (/include/ar.h) */
/* (#) Portability: musl libc     (/include/ar.h) */
/* (#) Portability: uClibc        (/include/ar.h) */
#ifndef _AR_H
#define _AR_H 1

#include <__stdinc.h>

/* Header describing `ar' archive file format.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


/* Archive files start with the  ARMAG identifying string. Then follows  a
 * `struct ar_hdr', and as many bytes of member file data as its `ar_size'
 * member indicates, for each member file. */


#define ARMAG  "!<arch>\n" /* String that begins an archive file. */
#define SARMAG 8           /* Size of that string. */
#define ARFMAG "`\n"       /* String in ar_fmag at end of each header. */

#ifdef __CC__
__DECL_BEGIN

struct ar_hdr {
	char ar_name[16]; /* Member file name, sometimes / terminated. */
	char ar_date[12]; /* File date, decimal seconds since Epoch. */
	char ar_uid[6];   /* User IDs, in ASCII decimal. */
	char ar_gid[6];   /* Group IDs, in ASCII decimal. */
	char ar_mode[8];  /* File mode, in ASCII octal. */
	char ar_size[10]; /* File size, in ASCII decimal. */
	char ar_fmag[2];  /* Always contains ARFMAG. */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_AR_H */
