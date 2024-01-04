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
#ifndef _ASM_OS_KOS_OFLAGS_H
#define _ASM_OS_KOS_OFLAGS_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __O_ACCMODE         0x0000003 /* Mask for access modes (O_RDONLY, O_WRONLY, O_RDWR) */
#define __O_RDONLY          0x0000000 /* Read-only file access */
#define __O_WRONLY          0x0000001 /* Write-only file access */
#define __O_RDWR            0x0000002 /* Read/Write file access */
#define __O_ACCMODE_INVALID 0x0000003 /* Invalid ACCMODE value. */
#define __O_CREAT           0x0000040 /* If missing, create a new file */
#define __O_EXCL            0x0000080 /* When used with `O_CREAT', throw an `E_FSERROR_FILE_ALREADY_EXISTS'
                                       * exception if the file already exists. */
#define __O_NOCTTY          0x0000100 /* If the calling process does not have a controlling terminal assigned,
                                       * do not attempt to assign the newly opened file as terminal, even when
                                       * `isatty(open(...))' would be true. */
#define __O_TRUNC           0x0000200 /* Truncate (clear) the named file if it already exists,
                                       * and  `O_WRONLY'  or  `O_RDWR'  access  is  specified. */
#define __O_APPEND          0x0000400 /* Always append data to the end of the file */
#define __O_NONBLOCK        0x0000800 /* Do not block when trying to read data that hasn't been written, yet. */
#define __O_SYNC            0x0101000 /* ??? */
#define __O_DSYNC           0x0001000 /* ??? */
#define __O_ASYNC           0x0002000 /* ??? */
#define __O_DIRECT          0x0004000 /* ??? */
#if defined(__KOS__) && !defined(__KERNEL__)
#define __O_LARGEFILE       0         /* Ignored... (set to `0' so programs can detect that it's ignored with the preprocessor) */
#else /* __KOS__ */
#define __O_LARGEFILE       0x0008000 /* Ignored... */
#endif /* !__KOS__ */
#define __O_DIRECTORY       0x0010000 /* Throw an `E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_OPEN' exception when the final
                                       * path component of  an open()  system call turns  out to  be something other  than a  directory. */
#define __O_NOFOLLOW        0x0020000 /* Throw an `E_FSERROR_IS_A_SYMBOLIC_LINK:E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN'  exception
                                       * when the final path component of an open() system call turns out to be a symbolic link. */
#define __O_NOATIME         0x0040000 /* Don't update last-accessed time stamps. */
#define __O_CLOEXEC         0x0080000 /* Close the file during exec() */
#define __O_PATH            0x0200000 /* Open a path for *at system calls. */
#define __O_TMPFILE         (0x0400000 | __O_DIRECTORY) /* Open a temporary file */
#define __O_TMPFILE_MASK    (__O_TMPFILE | __O_CREAT)
#ifdef __KOS__
#define __O_CLOFORK         0x1000000 /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#define __O_DOSPATH         0x4000000 /* Interpret  '\\'  as  '/',  and   ignore  casing  during  path   resolution.
                                       * Additionally,   recognize  DOS  mounting   points,  and  interpret  leading
                                       * slashes as relative to the closest DOS mounting point. (s.a.: `AT_DOSPATH') */
#endif /* __KOS__ */

#endif /* !_ASM_OS_KOS_OFLAGS_H */
