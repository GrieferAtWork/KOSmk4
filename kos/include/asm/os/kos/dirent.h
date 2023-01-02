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
#ifndef _ASM_OS_KOS_DIRENT_H
#define _ASM_OS_KOS_DIRENT_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __DT_UNKNOWN 0  /* Unknown file type */
#define __DT_FIFO    1  /* FistInFirstOut (pipe) file (s.a. `S_ISFIFO()', `S_IFMT & S_IFIFO') */
#define __DT_CHR     2  /* Character device file      (s.a. `S_ISCHR()', `S_IFMT & S_IFCHR') */
#define __DT_DIR     4  /* Directory                  (s.a. `S_ISDIR()', `S_IFMT & S_IFDIR') */
#define __DT_BLK     6  /* Block device file          (s.a. `S_ISBLK()', `S_IFMT & S_IFBLK') */
#define __DT_REG     8  /* Regular text file          (s.a. `S_ISREG()', `S_IFMT & S_IFREG') */
#define __DT_LNK     10 /* Symbolic link              (s.a. `S_ISLNK()', `S_IFMT & S_IFLNK') */
#define __DT_SOCK    12 /* Socket file                (s.a. `S_ISSOCK()', `S_IFMT & S_IFSOCK') */
#define __DT_WHT     14 /* Mounting point? */
#define __DT_CNT     16 /* Max possible # of different file type IDs. */

#define __IFTODT(mode)    (((mode) & 0xf000) >> 12)
#define __DTTOIF(dirtype) ((dirtype) << 12)

#endif /* !_ASM_OS_KOS_DIRENT_H */
