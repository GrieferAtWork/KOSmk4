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
#ifndef _ASM_OS_NETBSD_OFLAGS_H
#define _ASM_OS_NETBSD_OFLAGS_H 1

#include <__stdinc.h>

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

#endif /* !_ASM_OS_NETBSD_OFLAGS_H */
