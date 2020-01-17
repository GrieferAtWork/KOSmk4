/* HASH CRC-32:0xcc5efe4c */
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

/* Documentation taken from Glibc /usr/include/arpa/inet.h */
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

#ifdef __CRT_HAVE_inet_addr
/* Convert Internet host address from numbers-and-dots
 * notation in CP into binary data in network byte order */
__CDECLARE(,in_addr_t,__NOTHROW_RPC_KOS,inet_addr,(char const *__cp),(__cp))
#endif /* inet_addr... */
#ifdef __CRT_HAVE_inet_lnaof
/* Return the local host address part of the Internet address in IN */
__CDECLARE(,in_addr_t,__NOTHROW_RPC_KOS,inet_lnaof,(struct in_addr __inaddr),(__inaddr))
#endif /* inet_lnaof... */
#ifdef __CRT_HAVE_inet_makeaddr
/* Make Internet host address in network byte order by
 * combining the network number NET with the local address HOST */
__CDECLARE(,struct in_addr,__NOTHROW_RPC_KOS,inet_makeaddr,(in_addr_t __net, in_addr_t __host),(__net,__host))
#endif /* inet_makeaddr... */
#ifdef __CRT_HAVE_inet_netof
/* Return network number part of the Internet address IN */
__CDECLARE(,in_addr_t,__NOTHROW_RPC_KOS,inet_netof,(struct in_addr __inaddr),(__inaddr))
#endif /* inet_netof... */
#ifdef __CRT_HAVE_inet_network
/* Extract the network number in network byte order from
 * the address in numbers-and-dots natation starting at CP */
__CDECLARE(,in_addr_t,__NOTHROW_RPC_KOS,inet_network,(char const *__cp),(__cp))
#endif /* inet_network... */
#ifdef __CRT_HAVE_inet_ntoa
/* Convert Internet number in IN to ASCII representation. The return
 * value is a pointer to an internal array containing the string */
__CDECLARE(,char *,__NOTHROW_RPC_KOS,inet_ntoa,(struct in_addr __inaddr),(__inaddr))
#endif /* inet_ntoa... */
#ifdef __CRT_HAVE_inet_pton
/* Convert from presentation format of an Internet number in buffer
 * starting at CP to the binary network format and store result for
 * interface type AF in buffer starting at BUF */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet_pton,(int __af, char const *__restrict __cp, void *__restrict __buf),(__af,__cp,__buf))
#endif /* inet_pton... */
#ifdef __CRT_HAVE_inet_ntop
/* Convert a Internet address in binary network format for interface
 * type AF in buffer starting at CP to presentation form and place
 * result in buffer of length LEN astarting at BUF */
__CDECLARE(,char const *,__NOTHROW_RPC_KOS,inet_ntop,(int __af, void const *__restrict __cp, char *__restrict __buf, socklen_t __len),(__af,__cp,__buf,__len))
#endif /* inet_ntop... */

/* The following functions are not part of XNS 5.2. */
#ifdef __USE_MISC
#ifdef __CRT_HAVE_inet_aton
/* Convert Internet host address from numbers-and-dots notation in CP
 * into binary data and store the result in the structure INP */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet_aton,(char const *__cp, struct in_addr *__inp),(__cp,__inp))
#endif /* inet_aton... */
#ifdef __CRT_HAVE_inet_neta
/* Format a network number NET into presentation format and place
 * result in buffer starting at BUF with length of LEN bytes */
__CDECLARE(,char *,__NOTHROW_RPC_KOS,inet_neta,(in_addr_t __net, char *__buf, size_t __len),(__net,__buf,__len))
#endif /* inet_neta... */
#ifdef __CRT_HAVE_inet_net_ntop
/* Convert network number for interface type AF in buffer starting at
 * CP to presentation format.  The result will specifiy BITS bits of
 * the number */
__CDECLARE(,char *,__NOTHROW_RPC_KOS,inet_net_ntop,(int __af, void const *__cp, int __bits, char *__buf, size_t __len),(__af,__cp,__bits,__buf,__len))
#endif /* inet_net_ntop... */
#ifdef __CRT_HAVE_inet_net_pton
/* Convert network number for interface type AF from presentation in
 * buffer starting at CP to network format and store result int
 * buffer starting at BUF of size LEN */
__CDECLARE(,int,__NOTHROW_RPC_KOS,inet_net_pton,(int __af, char const *__cp, void *__buf, size_t __len),(__af,__cp,__buf,__len))
#endif /* inet_net_pton... */
#ifdef __CRT_HAVE_inet_nsap_addr
/* Convert ASCII representation in hexadecimal form of the Internet
 * address to binary form and place result in buffer of length LEN
 * starting at BUF */
__CDECLARE(,unsigned int,__NOTHROW_RPC_KOS,inet_nsap_addr,(char const *__cp, unsigned char *__buf, int __len),(__cp,__buf,__len))
#endif /* inet_nsap_addr... */
#ifdef __CRT_HAVE_inet_nsap_ntoa
/* Convert internet address in binary form in LEN bytes starting
 * at CP a presentation form and place result in BUF */
__CDECLARE(,char *,__NOTHROW_RPC_KOS,inet_nsap_ntoa,(int __len, unsigned char const *__cp, char *__buf),(__len,__cp,__buf))
#endif /* inet_nsap_ntoa... */
#endif /* __USE_MISC */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_ARPA_INET_H */
