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

#ifndef __O_ACCMODE
#define __O_ACCMODE         0x003 /* Mask for access modes (O_RDONLY, O_WRONLY, O_RDWR) */
#define __O_RDONLY          0x000 /* Read-only file access */
#define __O_WRONLY          0x001 /* Write-only file access */
#define __O_RDWR            0x002 /* Read/Write file access */
#define __O_ACCMODE_INVALID 0x003 /* Invalid ACCMODE value. */
/*      __O_RDWR            0x003 */
#endif /* !__O_ACCMODE */

#ifndef __O_TRUNC
#define __O_TRUNC       0x200 /* Truncate (clear) the named file if it already exists,
                               * and `O_WRONLY' or `O_RDWR' access is specified. */
#endif /* !__O_TRUNC */


/* DOS open flag values. */
#define __DOS_O_APPEND       0x00008 /* Same as `O_APPEND' */
#define __DOS_O_RANDOM       0x00010 /* Ignored */
#define __DOS_O_SEQUENTIAL   0x00020 /* Ignored */
#define __DOS_O_TEMPORARY    0x00040 /* Same as `O_TMPFILE' */
#define __DOS_O_NOINHERIT    0x00080 /* Same as `O_CLOEXEC' */
#define __DOS_O_CREAT        0x00100 /* Same as `O_CREAT' */
#define __DOS_O_TRUNC        0x00200 /* Same as `O_TRUNC' */
#define __DOS_O_EXCL         0x00400 /* Same as `O_EXCL' */
#define __DOS_O_SHORT_LIVED  0x01000 /* Ignored */
#define __DOS_O_OBTAIN_DIR   0x02000 /* Similar to `O_DIRECTORY' (while `O_DIRECTORY' requires that the
                                      * named file be a directory, this flag will _allow_ it to be one)
                                      * However, when it comes to the use-cases, this flag usually ends up
                                      * being used in the same places. */
#define __DOS_O_TEXT         0x04000 /* Ignored */
#define __DOS_O_BINARY       0x08000 /* Ignored */
#define __DOS_O_WTEXT        0x10000 /* Ignored */
#define __DOS_O_U16TEXT      0x20000 /* Ignored */
#define __DOS_O_U8TEXT       0x40000 /* Ignored */
#define __DOS_O_RAW          __DOS_O_BINARY


#if defined(__KOS__) || defined(__linux__) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL) || defined(__CRT_GLC)
#define __O_CREAT      0x0000040 /* If missing, create a new file */
#define __O_EXCL       0x0000080 /* When used with `O_CREAT', throw an `E_FSERROR_FILE_ALREADY_EXISTS'
                                  * exception if the file already exists. */
#define __O_NOCTTY     0x0000100 /* If the calling process does not have a controlling terminal assigned,
                                  * do not attempt to assign the newly opened file as terminal, even when
                                  * `isatty(open(...))' would be true. */
#define __O_APPEND     0x0000400 /* Always append data to the end of the file */
#define __O_NONBLOCK   0x0000800 /* Do not block when trying to read data that hasn't been written, yet. */
#define __O_SYNC       0x0001000 /* ??? */
#define __O_DSYNC      0x0001000 /* ??? */
#define __O_ASYNC      0x0002000 /* ??? */
#define __O_DIRECT     0x0004000 /* ??? */
#define __O_LARGEFILE  0x0008000 /* Ignored... */
#define __O_DIRECTORY  0x0010000 /* Throw an `E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_OPEN' exception when the final
                                  * path component of an open() system call turns out to be something other than a directory. */
#define __O_NOFOLLOW   0x0020000 /* Throw an `E_FSERROR_IS_A_SYMBOLIC_LINK:E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN' exception when the
                                  * final path component of an open() system call turns out to be a symbolic link, unless `O_SYMLINK'
                                  * is given, in which case the link itself is opened. */
#define __O_NOATIME    0x0040000 /* Don't update last-accessed time stamps. */
#define __O_CLOEXEC    0x0080000 /* Close the file during exec() */
#define __O_PATH       0x0200000 /* Open a path for *at system calls. */
#define __O_TMPFILE   (0x0400000 | __O_DIRECTORY)
#endif /* __KOS__ || __linux__ || __CRT_KOS || __CRT_KOS_KERNEL || __CRT_GLC */

#if defined(__KOS__) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL)
#define __O_CLOFORK    0x0100000 /* Close the handle when the file descriptors are unshared (s.a. `CLONE_FILES') */
#define __O_SYMLINK    0x2000000 /* Open a symlink itself, rather than dereferencing it. (This flag implies `O_NOFOLLOW')
                                  * NOTE: When combined with `O_EXCL', throw an `E_FSERROR_NOT_A_SYMBOLIC_LINK:
                                  *       E_FILESYSTEM_NOT_A_SYMBOLIC_LINK_OPEN' if the file isn't a symbolic link. */
#define __O_DOSPATH    0x4000000 /* Interpret '\\' as '/', and ignore casing during path resolution.
                                  * Additionally, recognize DOS mounting points, and interpret leading
                                  * slashes as relative to the closest DOS mounting point. (s.a.: `AT_DOSPATH') */
#endif /* __KOS__ || __CRT_KOS || __CRT_KOS_KERNEL */



#if !defined(__O_APPEND) && defined(__CRT_DOS)
#define __O_APPEND __DOS_O_APPEND
#endif /* !__O_APPEND && __CRT_DOS */
#if !defined(__O_CREAT) && defined(__CRT_DOS)
#define __O_CREAT __DOS_O_CREAT
#endif /* !__O_CREAT && __CRT_DOS */
#if !defined(__O_EXCL) && defined(__CRT_DOS)
#define __O_EXCL __DOS_O_EXCL
#endif /* !__O_EXCL && __CRT_DOS */
#if !defined(__O_CLOEXEC) && defined(__CRT_DOS)
#define __O_CLOEXEC __DOS_O_NOINHERIT
#endif /* !__O_CLOEXEC && __CRT_DOS */
#if !defined(__O_TMPFILE) && defined(__CRT_DOS)
#define __O_TMPFILE __DOS_O_TEMPORARY
#endif /* !__O_TMPFILE && __CRT_DOS */
#if !defined(__O_NOFOLLOW) && defined(__CRT_DOS)
#define __O_NOFOLLOW 0
#endif /* !__O_NOFOLLOW && __CRT_DOS */





/* Substitute unimportant flags if they aren't supported. */
#ifndef __O_NOCTTY
#define __O_NOCTTY 0 /* If the calling process does not have a controlling terminal assigned,
                      * do not attempt to assign the newly opened file as terminal, even when
                      * `isatty(open(...))' would be true. */
#endif /* !__O_NOCTTY */
#ifndef __O_SYNC
#define __O_SYNC   0 /* ??? */
#endif /* !__O_SYNC */
#ifndef __O_ASYNC
#define __O_ASYNC  0 /* ??? */
#endif /* !__O_ASYNC */
#ifndef __O_PATH
#define __O_PATH   0 /* Open a path for *at system calls. */
#endif /* !__O_PATH */
#ifndef __O_DSYNC
#define __O_DSYNC  0 /* ??? */
#endif /* !__O_DSYNC */
#ifndef __O_DIRECT
#define __O_DIRECT 0 /* ??? */
#endif /* !__O_DIRECT */
#ifndef __O_LARGEFILE
#define __O_LARGEFILE 0 /* Enable 64-bit file support */
#endif /* !__O_LARGEFILE */
#ifndef __O_NOATIME
#define __O_NOATIME 0 /* Don't update last-accessed time stamps. */
#endif /* !__O_NOATIME */


/* Open anything directly (as best as possible). (file, directory or symlink)
 * KOS: Open a file, directory or symlink directly.
 * DOS: Open a file or directory directly.
 * GLC: Open a file or directory directly. */
#ifdef __CRT_DOS_PRIMARY
#define __O_ANYTHING   __DOS_O_OBTAIN_DIR
#elif defined(__O_SYMLINK)
#define __O_ANYTHING   __O_SYMLINK
#else
#define __O_ANYTHING   0
#endif


#endif /* !_ASM_OFLAGS_H */
