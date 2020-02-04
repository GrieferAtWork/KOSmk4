/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LINUX_LIMITS_H
#define _LINUX_LIMITS_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/linux/limits.h' */

#include <__stdinc.h>

#define NR_OPEN         1024 /* # of open files (dynamic in KOS; really is up
                              *   to INT_MAX, but also limited by avail. RAM) */
#define NGROUPS_MAX    65536 /* supplemental group IDs are available */
#define ARG_MAX       131072 /* # bytes of args + environ for exec(); */
#define LINK_MAX         127 /* # links a file may have (fs-dependent in KOS) */
#define MAX_CANON        255 /* size of the canonical input queue */
#define MAX_INPUT        255 /* size of the type-ahead buffer */
#define NAME_MAX         255 /* # chars in a file name (2^16 in KOS) */
#define PATH_MAX        4096 /* # chars in a path name including nul (Unlimited in KOS) */
#define PIPE_BUF        4096 /* # bytes in atomic write to a pipe (Default value) */
#if 0
#define XATTR_NAME_MAX   255 /* # chars in an extended attribute name */
#define XATTR_SIZE_MAX 65536 /* size of an extended attribute value (64k) */
#define XATTR_LIST_MAX 65536 /* size of extended attribute namelist (64k) */
#endif
#define RTSIG_MAX         32

#endif /* !_LINUX_LIMITS_H */
