/* HASH CRC-32:0xdd52d456 */
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
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/[...]/sys/fsuid.h) */
/* (#) Portability: diet libc     (/include/sys/fsuid.h) */
/* (#) Portability: musl libc     (/include/sys/fsuid.h) */
/* (#) Portability: uClibc        (/include/sys/fsuid.h) */
#ifndef _SYS_FSUID_H
#define _SYS_FSUID_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

/* Documentation taken from Glibc /usr/include/i386-linux-gnu/sys/fsuid.c */
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__SYSDECL_BEGIN

#ifdef __CC__

/* Change uid used for file access control to UID, without affecting
 * other privileges (such as who can send signals at the process) */
__CDECLARE_OPT(,int,__NOTHROW_NCX,setfsuid,(__uid_t __uid),(__uid))
/* Same as `setfsuid()', but for group id */
__CDECLARE_OPT(,int,__NOTHROW_NCX,setfsgid,(__gid_t __gid),(__gid))

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_FSUID_H */
