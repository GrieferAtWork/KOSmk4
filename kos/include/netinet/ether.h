/* HASH CRC-32:0x78b9ff4 */
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
#ifndef _NETINET_ETHER_H
#define _NETINET_ETHER_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <netinet/if_ether.h>

__SYSDECL_BEGIN

/* Documentation taken from Glibc /usr/include/netinet/ether.h */
/* Functions for storing Ethernet addresses in ASCII and mapping to hostnames.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
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

#ifdef __CC__

#ifdef __CRT_HAVE_ether_ntoa
/* Convert 48 bit Ethernet ADDRess to ASCII */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,ether_ntoa,(struct ether_addr const *__restrict __addr),(__addr))
#else /* __CRT_HAVE_ether_ntoa */
#include <libc/local/netinet.ether/ether_ntoa.h>
/* Convert 48 bit Ethernet ADDRess to ASCII */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_ntoa, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *__NOTHROW_NCX(__LIBCCALL ether_ntoa)(struct ether_addr const *__restrict __addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_ntoa))(__addr); })
#endif /* !__CRT_HAVE_ether_ntoa */
#ifdef __CRT_HAVE_ether_ntoa_r
/* Convert 48 bit Ethernet ADDRess to ASCII */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,ether_ntoa_r,(struct ether_addr const *__restrict __addr, char *__restrict __buf),(__addr,__buf))
#else /* __CRT_HAVE_ether_ntoa_r */
#include <libc/local/netinet.ether/ether_ntoa_r.h>
/* Convert 48 bit Ethernet ADDRess to ASCII */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_ntoa_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *__NOTHROW_NCX(__LIBCCALL ether_ntoa_r)(struct ether_addr const *__restrict __addr, char *__restrict __buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_ntoa_r))(__addr, __buf); })
#endif /* !__CRT_HAVE_ether_ntoa_r */
#ifdef __CRT_HAVE_ether_aton
/* Convert ASCII string S to 48 bit Ethernet address */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((1)),struct ether_addr *,__NOTHROW_NCX,ether_aton,(char const *__restrict __asc),(__asc))
#else /* __CRT_HAVE_ether_aton */
#include <libc/local/netinet.ether/ether_aton.h>
/* Convert ASCII string S to 48 bit Ethernet address */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_aton, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_NONNULL((1)) struct ether_addr *__NOTHROW_NCX(__LIBCCALL ether_aton)(char const *__restrict __asc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_aton))(__asc); })
#endif /* !__CRT_HAVE_ether_aton */
#ifdef __CRT_HAVE_ether_aton_r
/* Convert ASCII string S to 48 bit Ethernet address */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),struct ether_addr *,__NOTHROW_NCX,ether_aton_r,(char const *__restrict __asc, struct ether_addr *__restrict __addr),(__asc,__addr))
#else /* __CRT_HAVE_ether_aton_r */
#include <libc/local/netinet.ether/ether_aton_r.h>
/* Convert ASCII string S to 48 bit Ethernet address */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_aton_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) struct ether_addr *__NOTHROW_NCX(__LIBCCALL ether_aton_r)(char const *__restrict __asc, struct ether_addr *__restrict __addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_aton_r))(__asc, __addr); })
#endif /* !__CRT_HAVE_ether_aton_r */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_ether_paton_r
/* Convert ASCII string S to 48 bit Ethernet address */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),struct ether_addr *,__NOTHROW_NCX,ether_paton_r,(char const **__restrict __pasc, struct ether_addr *__restrict __addr),(__pasc,__addr))
#else /* __CRT_HAVE_ether_paton_r */
#include <libc/local/netinet.ether/ether_paton_r.h>
/* Convert ASCII string S to 48 bit Ethernet address */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_paton_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) struct ether_addr *__NOTHROW_NCX(__LIBCCALL ether_paton_r)(char const **__restrict __pasc, struct ether_addr *__restrict __addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_paton_r))(__pasc, __addr); })
#endif /* !__CRT_HAVE_ether_paton_r */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_ether_line
/* Scan LINE and set ADDR and HOSTNAME */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,ether_line,(char const *__line, struct ether_addr *__addr, char *__hostname),(__line,__addr,__hostname))
#else /* __CRT_HAVE_ether_line */
#include <libc/local/netinet.ether/ether_line.h>
/* Scan LINE and set ADDR and HOSTNAME */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_line, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL ether_line)(char const *__line, struct ether_addr *__addr, char *__hostname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_line))(__line, __addr, __hostname); })
#endif /* !__CRT_HAVE_ether_line */
/* Map 48 bit Ethernet number ADDR to HOSTNAME */
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,ether_ntohost,(char *__hostname, struct ether_addr const *__addr),(__hostname,__addr))
/* Map HOSTNAME to 48 bit Ethernet address */
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,ether_hostton,(char const *__hostname, struct ether_addr *__addr),(__hostname,__addr))

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_NETINET_ETHER_H */
