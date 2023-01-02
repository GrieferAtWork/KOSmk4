/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin        (/newlib/libc/posix/sysexits.h) */
/* (#) Portability: DragonFly BSD (/include/sysexits.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sysexits.h) */
/* (#) Portability: FreeBSD       (/include/sysexits.h) */
/* (#) Portability: GNU C Library (/misc/sysexits.h) */
/* (#) Portability: GNU Hurd      (/usr/include/sysexits.h) */
/* (#) Portability: NetBSD        (/include/sysexits.h) */
/* (#) Portability: Newlib        (/newlib/libc/posix/sysexits.h) */
/* (#) Portability: OpenBSD       (/include/sysexits.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/sysexits.h) */
/* (#) Portability: diet libc     (/include/sysexits.h) */
/* (#) Portability: libc4/5       (/include/sysexits.h) */
/* (#) Portability: libc6         (/include/sysexits.h) */
/* (#) Portability: mintlib       (/include/sysexits.h) */
/* (#) Portability: musl libc     (/include/sysexits.h) */
/* (#) Portability: uClibc        (/include/sysexits.h) */
#ifndef _SYSEXITS_H
#define _SYSEXITS_H 1

#include "__stdinc.h"

#define EX_OK          0  /* Alias for `EXIT_SUCCESS' */
#define EX__BASE       64 /* First exit value to indicate standardized errors */
#define EX_USAGE       64 /* Wrong argument / # of arguments given on the commandline */
#define EX_DATAERR     65 /* User input data was malformed */
#define EX_NOINPUT     66 /* Specified input data does not exist (fs) */
#define EX_NOUSER      67 /* Specified user does not exist (pwd) */
#define EX_NOHOST      68 /* Specified host does not exist (networking) */
#define EX_UNAVAILABLE 69 /* A required helper program / system service doesn't exist */
#define EX_SOFTWARE    70 /* Internal software error (non-os-related) */
#define EX_OSERR       71 /* System error (e.g. `fork() == -1') */
#define EX_OSFILE      72 /* Missing/corrupt system file (e.g. `/etc/passwd') */
#define EX_CANTCREAT   73 /* Specified output file cannot be O_CREAT-ed (fs) */
#define EX_IOERR       74 /* File-related I/O error. (e.g. failed read(2)/write(2)) */
#define EX_TEMPFAIL    75 /* Temporary error. - Try re-running the program later */
#define EX_PROTOCOL    76 /* Protocol error (networking) */
#define EX_NOPERM      77 /* High-level you're-not-allowed (not meant to filesystem, \
                           * but rather `if (getuid() != 0) exit(EX_NOPERM);') */
#define EX_CONFIG      78 /* Program was badly configured. */
#define EX__MAX        78 /* Last exit value to indicate standardized errors */

#endif /* !_SYSEXITS_H */
