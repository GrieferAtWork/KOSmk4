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
#ifndef _ASM_OFLAGS_H
#define _ASM_OFLAGS_H 1

#include <__crt.h>

#if defined(__KOS__) || defined(__linux__)
/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __O_ACCMODE         0x0000003 /* Mask for access modes (O_RDONLY, O_WRONLY, O_RDWR) */
#define __O_RDONLY          0x0000000 /* Read-only file access */
#define __O_WRONLY          0x0000001 /* Write-only file access */
#define __O_RDWR            0x0000002 /* Read/Write file access */
#define __O_ACCMODE_INVALID 0x0000003 /* Invalid ACCMODE value. */
#define __O_TRUNC           0x0000200 /* Truncate (clear) the named file if it already exists,
                                       * and `O_WRONLY' or `O_RDWR' access is specified. */
#define __O_CREAT           0x0000040 /* If missing, create a new file */
#define __O_EXCL            0x0000080 /* When used with `O_CREAT', throw an `E_FSERROR_FILE_ALREADY_EXISTS'
                                       * exception if the file already exists. */
#define __O_NOCTTY          0x0000100 /* If the calling process does not have a controlling terminal assigned,
                                       * do not attempt to assign the newly opened file as terminal, even when
                                       * `isatty(open(...))' would be true. */
#define __O_APPEND          0x0000400 /* Always append data to the end of the file */
#define __O_NONBLOCK        0x0000800 /* Do not block when trying to read data that hasn't been written, yet. */
#define __O_SYNC            0x0001000 /* ??? */
#define __O_DSYNC           0x0001000 /* ??? */
#define __O_ASYNC           0x0002000 /* ??? */
#define __O_DIRECT          0x0004000 /* ??? */
#define __O_LARGEFILE       0x0008000 /* Ignored... */
#define __O_DIRECTORY       0x0010000 /* Throw an `E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_OPEN' exception when the final
                                       * path component of an open() system call turns out to be something other than a directory. */
#define __O_NOFOLLOW        0x0020000 /* Throw an `E_FSERROR_IS_A_SYMBOLIC_LINK:E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN' exception when the
                                       * final path component of an open() system call turns out to be a symbolic link, unless `O_SYMLINK'
                                       * is given, in which case the link itself is opened. */
#define __O_NOATIME         0x0040000 /* Don't update last-accessed time stamps. */
#define __O_CLOEXEC         0x0080000 /* Close the file during exec() */
#define __O_PATH            0x0200000 /* Open a path for *at system calls. */
#define __O_TMPFILE        (0x0400000 | __O_DIRECTORY) /* Open a temporary file */
#ifdef __KOS__
#define __O_CLOFORK         0x0100000 /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#define __O_SYMLINK         0x2000000 /* Open a symlink itself, rather than dereferencing it. (This flag implies `O_NOFOLLOW')
                                       * NOTE: When combined with `O_EXCL', throw an `E_FSERROR_NOT_A_SYMBOLIC_LINK:
                                       *       E_FILESYSTEM_NOT_A_SYMBOLIC_LINK_OPEN' if the file isn't a symbolic link. */
#define __O_DOSPATH         0x4000000 /* Interpret '\\' as '/', and ignore casing during path resolution.
                                       * Additionally, recognize DOS mounting points, and interpret leading
                                       * slashes as relative to the closest DOS mounting point. (s.a.: `AT_DOSPATH') */
#define __O_ANYTHING __O_SYMLINK
#endif /* __KOS__ */

#elif defined(__CRT_DOS_PRIMARY)
/************************************************************************/
/* DOS/MSVCRT                                                           */
/************************************************************************/

#define __O_ACCMODE      0x00003 /* Mask for access modes (O_RDONLY, O_WRONLY, O_RDWR) */
#define __O_RDONLY       0x00000 /* Read-only file access */
#define __O_WRONLY       0x00001 /* Write-only file access */
#define __O_RDWR         0x00002 /* Read/Write file access */
#define __O_APPEND       0x00008 /* Always append data to the end of the file */
#define __O_RANDOM       0x00010 /* Ignored */
#define __O_SEQUENTIAL   0x00020 /* Ignored */
#define __O_TMPFILE      0x00040 /* Open a temporary file */
#define __O_CLOEXEC      0x00080 /* Close the file during exec() */
#define __O_CREAT        0x00100 /* If missing, create a new file */
#define __O_TRUNC        0x00200 /* Truncate (clear) the named file if it already exists,
                                  * and `O_WRONLY' or `O_RDWR' access is specified. */
#define __O_EXCL         0x00400 /* When used with `O_CREAT', throw an `E_FSERROR_FILE_ALREADY_EXISTS'
                                  * exception if the file already exists. */
#define __O_SHORT_LIVED  0x01000 /* Ignored */
#define __O_OBTAIN_DIR   0x02000 /* Similar to `O_DIRECTORY' (while `O_DIRECTORY' requires that the
                                  * named file be a directory, this flag will _allow_ it to be one)
                                  * However, when it comes to the use-cases, this flag usually ends up
                                  * being used in the same places. */
#define __O_TEXT         0x04000 /* ??? */
#define __O_BINARY       0x08000 /* ??? */
#define __O_WTEXT        0x10000 /* ??? */
#define __O_U16TEXT      0x20000 /* ??? */
#define __O_U8TEXT       0x40000 /* ??? */
#define __O_NOCTTY       0x00000 /* Concept doesn't exist under DOS */
#define __O_ANYTHING     __O_OBTAIN_DIR

#elif defined(__CRT_CYG_PRIMARY)
/************************************************************************/
/* CYGWIN                                                               */
/************************************************************************/

#define __O_ACCMODE    0x0000003 /* Mask for access modes (O_RDONLY, O_WRONLY, O_RDWR) */
#define __O_RDONLY     0x0000000 /* Read-only file access */
#define __O_WRONLY     0x0000001 /* Write-only file access */
#define __O_RDWR       0x0000002 /* Read/Write file access */
#define __O_FOPEN      (-1)      /* ??? */
#define __O_FREAD      0x0000001 /* ??? */
#define __O_FWRITE     0x0000002 /* ??? */
#define __O_FAPPEND    0x0000008 /* ??? */
#define __O_FMARK      0x0000010 /* ??? */
#define __O_FDEFER     0x0000020 /* ??? */
#define __O_ASYNC      0x0000040 /* ??? */
#define __O_SHLOCK     0x0000080 /* ??? */
#define __O_EXLOCK     0x0000100 /* ??? */
#define __O_CREAT      0x0000200 /* If missing, create a new file */
#define __O_TRUNC      0x0000400 /* Truncate (clear) the named file if it already exists,
                                  * and `O_WRONLY' or `O_RDWR' access is specified. */
#define __O_EXCL       0x0000800 /* When used with `O_CREAT', throw an `E_FSERROR_FILE_ALREADY_EXISTS'
                                  * exception if the file already exists. */
#define __O_NBIO       0x0001000 /* Do not block when trying to read data that hasn't been written, yet. */
#define __O_SYNC       0x0002000 /* ??? */
#define __O_NONBLOCK   0x0004000 /* Do not block when trying to read data that hasn't been written, yet. */
#define __O_NOCTTY     0x0008000 /* If the calling process does not have a controlling terminal assigned,
                                  * do not attempt to assign the newly opened file as terminal, even when
                                  * `isatty(open(...))' would be true. */
#define __O_BINARY     0x0010000 /* ??? */
#define __O_TEXT       0x0020000 /* ??? */
#define __O_CLOEXEC    0x0040000 /* Close the file during exec() */
#define __O_DIRECT     0x0080000 /* ??? */
#define __O_NOFOLLOW   0x0100000 /* Throw an `E_FSERROR_IS_A_SYMBOLIC_LINK:E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN' exception when the
                                  * final path component of an open() system call turns out to be a symbolic link, unless `O_SYMLINK'
                                  * is given, in which case the link itself is opened. */
#define __O_DIRECTORY  0x0200000 /* Throw an `E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_OPEN' exception when the final
                                  * path component of an open() system call turns out to be something other than a directory. */
#define __O_EXECSRCH   0x0400000 /* ??? */
#define __O_TMPFILE    0x0800000 /* Open a temporary file */
#define __O_NOATIME    0x1000000 /* Don't update last-accessed time stamps. */

#elif defined(__NetBSD__)
/************************************************************************/
/* NetBSD                                                               */
/************************************************************************/

#define __O_RDONLY    0x00000000
#define __O_WRONLY    0x00000001
#define __O_RDWR      0x00000002
#define __O_ACCMODE   0x00000003
#define __O_FREAD     0x00000001
#define __O_FWRITE    0x00000002
#define __O_NONBLOCK  0x00000004
#define __O_APPEND    0x00000008
#define __O_SHLOCK    0x00000010
#define __O_EXLOCK    0x00000020
#define __O_ASYNC     0x00000040
#define __O_SYNC      0x00000080
#define __O_NOFOLLOW  0x00000100
#define __O_CREAT     0x00000200
#define __O_TRUNC     0x00000400
#define __O_EXCL      0x00000800
#define __O_NOCTTY    0x00008000
#define __O_DSYNC     0x00010000
#define __O_RSYNC     0x00020000
#define __O_ALT_IO    0x00040000
#define __O_DIRECT    0x00080000
#define __O_DIRECTORY 0x00200000
#define __O_CLOEXEC   0x00400000
#define __O_SEARCH    0x00800000
#define __O_NOSIGPIPE 0x01000000
#define __O_REGULAR   0x02000000
#define __O_EXEC      0x04000000

#elif defined(__solaris__)
/************************************************************************/
/* SOLARIS                                                              */
/************************************************************************/

#define __O_RDONLY    0x00000
#define __O_WRONLY    0x00001
#define __O_RDWR      0x00002
#define __O_ACCMODE   0x00003
#define __O_NDELAY    0x00004
#define __O_APPEND    0x00008
#define __O_SYNC      0x00010
#define __O_DSYNC     0x00040
#define __O_NONBLOCK  0x00080
#define __O_PRIV      0x01000
#define __O_LARGEFILE 0x02000
#define __O_RSYNC     0x08000
#define __O_CREAT     0x00100
#define __O_TRUNC     0x00200
#define __O_EXCL      0x00400
#define __O_NOCTTY    0x00800
#define __O_XATTR     0x04000
#define __O_NOFOLLOW  0x20000
#define __O_NOLINKS   0x40000

#else /* ... */
/************************************************************************/
/* GENERIC                                                              */
/************************************************************************/

#define __O_ACCMODE 0x003 /* Mask for access modes (O_RDONLY, O_WRONLY, O_RDWR) */
#define __O_RDONLY  0x000 /* Read-only file access */
#define __O_WRONLY  0x001 /* Write-only file access */
#define __O_RDWR    0x002 /* Read/Write file access */

#endif /* !... */


/* Open anything directly (as best as possible). (file, directory or symlink)
 * KOS: Open a file, directory or symlink directly.
 * DOS: Open a file or directory directly.
 * GLC: Open a file or directory directly. */
#ifndef __O_ANYTHING
#define __O_ANYTHING 0
#endif /* !__O_ANYTHING */

#ifndef __O_LARGEFILE
#define __O_LARGEFILE 0 /* Assume native supported (if necessary CRT functions are available) */
#endif /* !__O_LARGEFILE */


#endif /* !_ASM_OFLAGS_H */
