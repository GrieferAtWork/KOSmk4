/* HASH CRC-32:0x32315511 */
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
#ifndef _ARPA_INET_H
#define _ARPA_INET_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <netinet/in.h>

/* Documentation derived from Glibc /usr/include/arpa/inet.h */
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

#ifndef __socklen_t_defined
#define __socklen_t_defined 1
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */

#ifdef __CRT_HAVE_inet_netof
/* Return network number part of the Internet address IN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT32_TYPE__,__NOTHROW_NCX,inet_netof,(struct in_addr __inaddr),(__inaddr))
#else /* LIBC: inet_netof */
#include <local/arpa.inet/inet_netof.h>
/* Return network number part of the Internet address IN */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_netof, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL inet_netof)(struct in_addr __inaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_netof))(__inaddr); })
#endif /* inet_netof... */
#ifdef __CRT_HAVE_inet_lnaof
/* Return the local host address part of the Internet address in IN */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT32_TYPE__,__NOTHROW_NCX,inet_lnaof,(struct in_addr __inaddr),(__inaddr))
#else /* LIBC: inet_lnaof */
#include <local/arpa.inet/inet_lnaof.h>
/* Return the local host address part of the Internet address in IN */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_lnaof, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL inet_lnaof)(struct in_addr __inaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_lnaof))(__inaddr); })
#endif /* inet_lnaof... */
#ifdef __CRT_HAVE_inet_makeaddr
/* Make Internet host address in network byte order by
 * combining the network number NET with the local address HOST */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,struct in_addr,__NOTHROW_NCX,inet_makeaddr,(__UINT32_TYPE__ __net, __UINT32_TYPE__ __host),(__net,__host))
#else /* LIBC: inet_makeaddr */
#include <local/arpa.inet/inet_makeaddr.h>
/* Make Internet host address in network byte order by
 * combining the network number NET with the local address HOST */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_makeaddr, __FORCELOCAL __ATTR_CONST __ATTR_WUNUSED struct in_addr __NOTHROW_NCX(__LIBCCALL inet_makeaddr)(__UINT32_TYPE__ __net, __UINT32_TYPE__ __host) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_makeaddr))(__net, __host); })
#endif /* inet_makeaddr... */
#ifdef __CRT_HAVE_inet_addr
/* Convert Internet host address from numbers-and-dots
 * notation in CP into binary data in network byte order
 * Accepted notations are:
 *     a.b.c.d  (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd    (1.564)
 *     abcd     (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123    (hex)
 *     0123     (oct) */
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((1)),in_addr_t,__NOTHROW_NCX,inet_addr,(char const *__restrict __cp),(__cp))
#else /* LIBC: inet_addr */
#include <local/arpa.inet/inet_addr.h>
/* Convert Internet host address from numbers-and-dots
 * notation in CP into binary data in network byte order
 * Accepted notations are:
 *     a.b.c.d  (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd    (1.564)
 *     abcd     (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123    (hex)
 *     0123     (oct) */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_addr, __FORCELOCAL __ATTR_PURE __ATTR_NONNULL((1)) in_addr_t __NOTHROW_NCX(__LIBCCALL inet_addr)(char const *__restrict __cp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_addr))(__cp); })
#endif /* inet_addr... */
#ifdef __CRT_HAVE_inet_ntoa
/* Convert Internet number in IN to ASCII representation. The return
 * value is a pointer to an internal array containing the string */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,inet_ntoa,(struct in_addr __inaddr),(__inaddr))
#else /* LIBC: inet_ntoa */
#include <local/arpa.inet/inet_ntoa.h>
/* Convert Internet number in IN to ASCII representation. The return
 * value is a pointer to an internal array containing the string */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_ntoa, __FORCELOCAL __ATTR_RETNONNULL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL inet_ntoa)(struct in_addr __inaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_ntoa))(__inaddr); })
#endif /* inet_ntoa... */
#ifdef __USE_KOS
#define INET_NTOA_R_MAXLEN 16 /* Max # of characters written by `inet_ntoa_r' (e.g. `111.111.111.111\0') */
#ifdef __CRT_HAVE_inet_ntoa_r
/* Re-entrant version of `inet_ntoa()' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_NONNULL((2)),char *,__NOTHROW_NCX,inet_ntoa_r,(struct in_addr __inaddr, char __buf[16]),(__inaddr,__buf))
#else /* LIBC: inet_ntoa_r */
#include <local/arpa.inet/inet_ntoa_r.h>
/* Re-entrant version of `inet_ntoa()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_ntoa_r, __FORCELOCAL __ATTR_RETNONNULL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL inet_ntoa_r)(struct in_addr __inaddr, char __buf[16]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_ntoa_r))(__inaddr, __buf); })
#endif /* inet_ntoa_r... */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_inet_network
/* This function is the same as `inet_addr()', except that
 * the return value is in host-endian, rather than net-endian */
__CDECLARE(__ATTR_PURE __ATTR_NONNULL((1)),__UINT32_TYPE__,__NOTHROW_NCX,inet_network,(char const *__restrict __cp),(__cp))
#else /* LIBC: inet_network */
#include <local/arpa.inet/inet_network.h>
/* This function is the same as `inet_addr()', except that
 * the return value is in host-endian, rather than net-endian */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_network, __FORCELOCAL __ATTR_PURE __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL inet_network)(char const *__restrict __cp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_network))(__cp); })
#endif /* inet_network... */

/* The following functions are not part of XNS 5.2. */
#ifdef __USE_MISC
#ifdef __CRT_HAVE_inet_aton
/* Convert Internet host address from numbers-and-dots notation in
 * CP into binary data and store the result in the structure INP
 * Accepted notations are:
 *     a.b.c.d  (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd    (1.564)
 *     abcd     (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123    (hex)
 *     0123     (oct)
 * @return: 0: Bad input format
 * @return: 1: Success */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,inet_aton,(char const *__restrict __cp, struct in_addr *__restrict __inp),(__cp,__inp))
#else /* LIBC: inet_aton */
#include <local/arpa.inet/inet_aton.h>
/* Convert Internet host address from numbers-and-dots notation in
 * CP into binary data and store the result in the structure INP
 * Accepted notations are:
 *     a.b.c.d  (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd    (1.564)
 *     abcd     (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123    (hex)
 *     0123     (oct)
 * @return: 0: Bad input format
 * @return: 1: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_aton, __FORCELOCAL __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL inet_aton)(char const *__restrict __cp, struct in_addr *__restrict __inp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_aton))(__cp, __inp); })
#endif /* inet_aton... */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_inet_paton
/* Same as `inet_aton()', but update `*pcp' to point after the address
 * Accepted notations are:
 *     a.b.c.d  (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd    (1.564)
 *     abcd     (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123    (hex)
 *     0123     (oct)
 * @param: network_addr: When non-zero, `*pcp' is a network address
 * @return: 0: Bad input format
 * @return: 1: Success */
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,inet_paton,(char const **__restrict __pcp, struct in_addr *__restrict __inp, int __network_addr),(__pcp,__inp,__network_addr))
#else /* LIBC: inet_paton */
#include <local/arpa.inet/inet_paton.h>
/* Same as `inet_aton()', but update `*pcp' to point after the address
 * Accepted notations are:
 *     a.b.c.d  (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd    (1.564)
 *     abcd     (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123    (hex)
 *     0123     (oct)
 * @param: network_addr: When non-zero, `*pcp' is a network address
 * @return: 0: Bad input format
 * @return: 1: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_paton, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int __NOTHROW_NCX(__LIBCCALL inet_paton)(char const **__restrict __pcp, struct in_addr *__restrict __inp, int __network_addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_paton))(__pcp, __inp, __network_addr); })
#endif /* inet_paton... */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_inet_neta
/* Format a network number NET into presentation format and place
 * result in buffer starting at BUF with length of LEN bytes */
__CDECLARE(__ATTR_NONNULL((2)),char *,__NOTHROW_NCX,inet_neta,(__UINT32_TYPE__ __net, char *__buf, __SIZE_TYPE__ __len),(__net,__buf,__len))
#else /* LIBC: inet_neta */
#include <local/arpa.inet/inet_neta.h>
/* Format a network number NET into presentation format and place
 * result in buffer starting at BUF with length of LEN bytes */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_neta, __FORCELOCAL __ATTR_NONNULL((2)) char *__NOTHROW_NCX(__LIBCCALL inet_neta)(__UINT32_TYPE__ __net, char *__buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_neta))(__net, __buf, __len); })
#endif /* inet_neta... */
#ifdef __CRT_HAVE_inet_net_ntop
/* Convert network number for interface type AF in buffer starting at CP
 * to presentation format. The result will specify BITS bits of the number */
__CDECLARE(,char *,__NOTHROW_RPC_KOS,inet_net_ntop,(int __af, void const *__cp, int __bits, char *__buf, __SIZE_TYPE__ __len),(__af,__cp,__bits,__buf,__len))
#endif /* inet_net_ntop... */
#ifdef __CRT_HAVE_inet_net_pton
/* Convert network number for interface type AF from presentation in buffer starting
 * at CP to network format and store result int buffer starting at BUF of size LEN */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet_net_pton,(int __af, char const *__cp, void *__buf, __SIZE_TYPE__ __len),(__af,__cp,__buf,__len))
#endif /* inet_net_pton... */
#ifdef __CRT_HAVE_inet_nsap_addr
/* Convert ASCII representation in hexadecimal form of the Internet address
 * to binary form and place result in buffer of length LEN starting at BUF */
__CDECLARE(,unsigned int,__NOTHROW_RPC_KOS,inet_nsap_addr,(char const *__cp, unsigned char *__buf, int __len),(__cp,__buf,__len))
#endif /* inet_nsap_addr... */
#ifdef __CRT_HAVE_inet_nsap_ntoa
/* Convert internet address in binary form in LEN bytes
 * starting at CP a presentation form and place result in BUF */
__CDECLARE(,char *,__NOTHROW_RPC_KOS,inet_nsap_ntoa,(int __len, unsigned char const *__cp, char *__buf),(__len,__cp,__buf))
#endif /* inet_nsap_ntoa... */
#endif /* __USE_MISC */
#ifdef __CRT_HAVE_inet_pton
/* Convert from presentation format of an Internet number in buffer
 * starting at CP to the binary network format and store result for
 * interface type AF in buffer starting at BUF */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet_pton,(int __af, char const *__restrict __cp, void *__restrict __buf),(__af,__cp,__buf))
#endif /* inet_pton... */
#ifdef __CRT_HAVE_inet_ntop
/* Convert a Internet address in binary network format for interface
 * type AF in buffer starting at CP to presentation form and place
 * result in buffer of length LEN starting at BUF */
__CDECLARE(,char const *,__NOTHROW_RPC_KOS,inet_ntop,(int __af, void const *__restrict __cp, char *__restrict __buf, socklen_t __len),(__af,__cp,__buf,__len))
#endif /* inet_ntop... */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_ARPA_INET_H */
