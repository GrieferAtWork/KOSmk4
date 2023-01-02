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
#ifndef _ASM_OS_SOLARIS_OFLAGS_H
#define _ASM_OS_SOLARIS_OFLAGS_H 1

#include <__stdinc.h>

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

#endif /* !_ASM_OS_SOLARIS_OFLAGS_H */
