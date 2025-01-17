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
/* (#) Portability: libbsd  (/include/bsd/bsd.h) */
/* (#) Portability: libc4/5 (/include/bsd/bsd.h) */
#ifndef _BSD_BSD_H
#define _BSD_BSD_H 1

/* libc4/5 */
#undef _BSD_SOURCE
#define _BSD_SOURCE
#include <features.h>

#include <hybrid/minmax.h>

#include <asm/os/oflags.h>
#include <sys/file.h>
#include <sys/param.h> /* NCARGS, NBBY */

#include <endian.h>
#include <limits.h>

#if !defined(FAPPEND) && defined(__O_APPEND)
#define FAPPEND __O_APPEND
#endif /* !FAPPEND && __O_APPEND */



/* libbsd */
#include <bsd/sys/cdefs.h>
#include <bsd/sys/queue.h>
/* TODO:#include <bsd/sys/tree.h> */
/* TODO:#include <bsd/netinet/ip_icmp.h> */
#include <bsd/stdlib.h>
#include <bsd/string.h>
#include <bsd/err.h>
#include <bsd/getopt.h>
/* TODO:#include <bsd/md5.h> */


#endif /* !_BSD_BSD_H */
