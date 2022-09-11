/* HASH CRC-32:0x7ec5b6f5 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/fsuid.h) */
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

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_setfsuid
/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,setfsuid,(__uid_t __uid),(__uid))
#elif defined(__CRT_HAVE___setfsuid)
/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(,int,__NOTHROW_NCX,setfsuid,(__uid_t __uid),__setfsuid,(__uid))
#elif defined(__CRT_HAVE___libc_setfsuid)
/* >> setfsuid(2)
 * Set the  user ID  for the  cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETUID' privilege.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(,int,__NOTHROW_NCX,setfsuid,(__uid_t __uid),__libc_setfsuid,(__uid))
#endif /* ... */
#ifdef __CRT_HAVE_setfsgid
/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno') */
__CDECLARE(,int,__NOTHROW_NCX,setfsgid,(__gid_t __gid),(__gid))
#elif defined(__CRT_HAVE___setfsgid)
/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(,int,__NOTHROW_NCX,setfsgid,(__gid_t __gid),__setfsgid,(__gid))
#elif defined(__CRT_HAVE___libc_setfsgid)
/* >> setfsgid(2)
 * Set the group  ID for  the cred-context (s.a.  `CLONE_CRED') of  the
 * calling thread. The calling thread needs the `CAP_SETGID' privilege.
 * @return: 0:  Success.
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(,int,__NOTHROW_NCX,setfsgid,(__gid_t __gid),__libc_setfsgid,(__gid))
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_FSUID_H */
