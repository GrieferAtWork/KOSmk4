/* HASH CRC-32:0x5c54f45 */
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
/* (#) Portability: DragonFly BSD (/sys/sys/acct.h) */
/* (#) Portability: FreeBSD       (/sys/sys/acct.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/acct.h) */
/* (#) Portability: NetBSD        (/sys/sys/acct.h) */
/* (#) Portability: OpenBSD       (/sys/sys/acct.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/acct.h) */
/* (#) Portability: musl libc     (/include/sys/acct.h) */
#ifndef _SYS_ACCT_H
#define _SYS_ACCT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <hybrid/typecore.h>
#include <bits/os/acct.h>
#include <bits/types.h>

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#include <endian.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __time_t_defined
#define __time_t_defined
typedef __time_t time_t;
#endif /* !__time_t_defined */

#ifdef __CRT_HAVE_acct
/* Switch process accounting on and off */
__CDECLARE(__ATTR_IN_OPT(1),int,__NOTHROW_RPC,acct,(char const *__filename),(__filename))
#elif defined(__CRT_HAVE___acct)
/* Switch process accounting on and off */
__CREDIRECT(__ATTR_IN_OPT(1),int,__NOTHROW_RPC,acct,(char const *__filename),__acct,(__filename))
#elif defined(__CRT_HAVE___libc_acct)
/* Switch process accounting on and off */
__CREDIRECT(__ATTR_IN_OPT(1),int,__NOTHROW_RPC,acct,(char const *__filename),__libc_acct,(__filename))
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_ACCT_H */
