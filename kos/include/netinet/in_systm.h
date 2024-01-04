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
/* (#) Portability: Cygwin        (/winsup/cygwin/include/netinet/in_systm.h) */
/* (#) Portability: DragonFly BSD (/sys/netinet/in_systm.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/netinet/in_systm.h) */
/* (#) Portability: FreeBSD       (/sys/netinet/in_systm.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/netinet/in_systm.h) */
/* (#) Portability: GNU Hurd      (/usr/include/netinet/in_systm.h) */
/* (#) Portability: NetBSD        (/sys/netinet/in_systm.h) */
/* (#) Portability: OpenBSD       (/sys/netinet/in_systm.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/netinet/in_systm.h) */
/* (#) Portability: diet libc     (/include/netinet/in_systm.h) */
/* (#) Portability: libc4/5       (/include/netinet/in_systm.h) */
/* (#) Portability: libc6         (/include/netinet/in_systm.h) */
/* (#) Portability: mintlib       (/include/netinet/in_systm.h) */
/* (#) Portability: musl libc     (/include/netinet/in_systm.h) */
/* (#) Portability: uClibc        (/include/netinet/in_systm.h) */
#ifndef _NETINET_IN_SYSTM_H
#define _NETINET_IN_SYSTM_H 1

/* System specific type definitions for networking code.
   Copyright (C) 1997-2016 Free Software Foundation, Inc.
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

#include <__stdinc.h>
#include <features.h>

#include <net/bits/types.h>

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

__SYSDECL_BEGIN

#ifdef __CC__
typedef __u_net16_t n_short; /* short as received from the net. */
typedef __u_net32_t n_long;  /* long as received from the net. */
typedef __u_net32_t n_time;  /* ms since 00:00 GMT, byte rev. */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_NETINET_IN_SYSTM_H */
