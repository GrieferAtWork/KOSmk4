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
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/dir.h) */
/* (#) Portability: DJGPP         (/include/sys/dir.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/dir.h) */
/* (#) Portability: GNU C Library (/misc/sys/dir.h) */
/* (#) Portability: NetBSD        (/sys/sys/dir.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/dir.h) */
/* (#) Portability: OpenBSD       (/sys/sys/dir.h) */
/* (#) Portability: OpenSolaris   (/usr/src/lib/libbc/inc/include/sys/dir.h) */
/* (#) Portability: libc4/5       (/include/sys/dir.h) */
/* (#) Portability: mintlib       (/include/sys/dir.h) */
/* (#) Portability: musl libc     (/include/sys/dir.h) */
/* (#) Portability: uClibc        (/include/sys/dir.h) */
#ifndef _SYS_DIR_H
#define _SYS_DIR_H 1

#include <dirent.h>
#define direct   dirent
#ifdef __USE_LARGEFILE64
#define direct64 dirent64
#endif /* __USE_LARGEFILE64 */

#endif /* !_SYS_DIR_H */
