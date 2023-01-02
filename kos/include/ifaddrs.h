/* HASH CRC-32:0x7e8fb220 */
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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/ifaddrs.h) */
/* (#) Portability: DragonFly BSD (/include/ifaddrs.h) */
/* (#) Portability: FreeBSD       (/include/ifaddrs.h) */
/* (#) Portability: GNU C Library (/inet/ifaddrs.h) */
/* (#) Portability: GNU Hurd      (/usr/include/ifaddrs.h) */
/* (#) Portability: NetBSD        (/include/ifaddrs.h) */
/* (#) Portability: OpenBSD       (/include/ifaddrs.h) */
/* (#) Portability: libc6         (/include/ifaddrs.h) */
/* (#) Portability: mintlib       (/include/ifaddrs.h) */
/* (#) Portability: musl libc     (/include/ifaddrs.h) */
/* (#) Portability: uClibc        (/include/ifaddrs.h) */
#ifndef _IFADDRS_H
#define _IFADDRS_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/crt/ifaddrs.h>

#ifdef __USE_GLIBC_BLOAT
#include <sys/socket.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

/* >> getifaddrs(3) */
__CDECLARE_OPT(,int,__NOTHROW_NCX,getifaddrs,(struct ifaddrs **__ifap),(__ifap))
/* >> freeifaddrs(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,freeifaddrs,(struct ifaddrs *__ifa),(__ifa))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_IFADDRS_H */
