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
#ifndef _ASM_OS_NETBSD_FCNTL_H
#define _ASM_OS_NETBSD_FCNTL_H 1

#include <__stdinc.h>

/************************************************************************/
/* NetBSD                                                               */
/************************************************************************/

#define __F_DUPFD               0
#define __F_GETFD               1
#define __F_SETFD               2
#define __F_GETFL               3
#define __F_SETFL               4
#define __F_GETOWN              5
#define __F_SETOWN              6
#define __F_GETLK               7
#define __F_SETLK               8
#define __F_SETLKW              9
#define __F_CLOSEM              10
#define __F_MAXFD               11
#define __F_DUPFD_CLOEXEC       12
#define __F_GETNOSIGPIPE        13
#define __F_SETNOSIGPIPE        14
#define __F_GETPATH             15
#define __FD_CLOEXEC            1
#define __F_RDLCK               1
#define __F_UNLCK               2
#define __F_WRLCK               3
#define __LOCK_SH               0x01
#define __LOCK_EX               0x02
#define __LOCK_NB               0x04
#define __LOCK_UN               0x08
#define __POSIX_FADV_NORMAL     0
#define __POSIX_FADV_RANDOM     1
#define __POSIX_FADV_SEQUENTIAL 2
#define __POSIX_FADV_WILLNEED   3
#define __POSIX_FADV_DONTNEED   4
#define __POSIX_FADV_NOREUSE    5
#define __AT_FDCWD              (-100)
#define __AT_EACCESS            0x100
#define __AT_SYMLINK_NOFOLLOW   0x200
#define __AT_SYMLINK_FOLLOW     0x400
#define __AT_REMOVEDIR          0x800

#endif /* !_ASM_OS_NETBSD_FCNTL_H */
