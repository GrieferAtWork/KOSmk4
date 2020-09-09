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
#ifndef _ASM_STAT_H
#define _ASM_STAT_H 1

#include <__stdinc.h>

#define __S_ISVTX    01000 /* Save swapped text after use (sticky). */
#define __S_ISGID    02000 /* Set group ID on execution. */
#define __S_ISUID    04000 /* Set user ID on execution. */
#define __S_IFIFO  0010000 /* FIFO. */
#define __S_IFCHR  0020000 /* Character device. */
#define __S_IFDIR  0040000 /* Directory. */
#define __S_IFBLK  0060000 /* Block device. */
#define __S_IFREG  0100000 /* Regular file. */
#define __S_IFLNK  0120000 /* Symbolic link. */
#define __S_IFSOCK 0140000 /* Socket. */
#define __S_IFMT   0170000 /* These bits determine file type. */

#define __S_ISDIR(x)  (((x) & __S_IFMT) == __S_IFDIR)  /* Directory. */
#define __S_ISCHR(x)  (((x) & __S_IFMT) == __S_IFCHR)  /* Character device. */
#define __S_ISBLK(x)  (((x) & __S_IFMT) == __S_IFBLK)  /* Block device. */
#define __S_ISDEV(x)  (((x) & 0130000) == 0020000)     /* __S_ISCHR(x) || __S_ISBLK(x) */
#define __S_ISREG(x)  (((x) & __S_IFMT) == __S_IFREG)  /* Regular file. */
#define __S_ISFIFO(x) (((x) & __S_IFMT) == __S_IFIFO)  /* FIFO. */
#define __S_ISLNK(x)  (((x) & __S_IFMT) == __S_IFLNK)  /* Symbolic link. */
#define __S_ISSOCK(x) (((x) & __S_IFMT) == __S_IFSOCK) /* Socket. */

#if defined(__KOS__) || defined(__linux__)
#define __UTIME_NOW  ((1l << 30) - 1l)
#define __UTIME_OMIT ((1l << 30) - 2l)
#endif /* __KOS__ || __linux__ */

#endif /* !_ASM_STAT_H */
