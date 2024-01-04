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
#ifndef _ASM_OS_STAT_H
#define _ASM_OS_STAT_H 1

#ifndef __DEEMON__
#include <__stdinc.h>

#if defined(__KOS__) || defined(__linux__)
#include <asm/os/kos/stat.h>
#endif /* ... */
#endif /* !__DEEMON__ */

#ifndef __S_IFMT
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
#endif /* !__S_IFMT */

#ifndef __S_ISDIR
#define __S_ISDIR(x)  (((x) & __S_IFMT) == __S_IFDIR)  /* Directory. */
#endif /* !__S_ISDIR */
#ifndef __S_ISCHR
#define __S_ISCHR(x)  (((x) & __S_IFMT) == __S_IFCHR)  /* Character device. */
#endif /* !__S_ISCHR */
#ifndef __S_ISBLK
#define __S_ISBLK(x)  (((x) & __S_IFMT) == __S_IFBLK)  /* Block device. */
#endif /* !__S_ISBLK */
#ifndef __S_ISDEV
#if __S_IFMT == 0170000 && __S_IFCHR == 0020000 && __S_IFBLK == 0060000
#define __S_ISDEV(x)  (((x) & 0130000) == 0020000)     /* __S_ISCHR(x) || __S_ISBLK(x) */
#else /* ... */
#define __S_ISDEV(x)  (__S_ISCHR(x) || __S_ISBLK(x))
#endif /* !... */
#endif /* !__S_ISDEV */
#ifndef __S_ISREG
#define __S_ISREG(x)  (((x) & __S_IFMT) == __S_IFREG)  /* Regular file. */
#endif /* !__S_ISREG */
#ifndef __S_ISFIFO
#define __S_ISFIFO(x) (((x) & __S_IFMT) == __S_IFIFO)  /* FIFO. */
#endif /* !__S_ISFIFO */
#ifndef __S_ISLNK
#define __S_ISLNK(x)  (((x) & __S_IFMT) == __S_IFLNK)  /* Symbolic link. */
#endif /* !__S_ISLNK */
#ifndef __S_ISSOCK
#define __S_ISSOCK(x) (((x) & __S_IFMT) == __S_IFSOCK) /* Socket. */
#endif /* !__S_ISSOCK */

#endif /* !_ASM_OS_STAT_H */
