/* HASH CRC-32:0xe7ac795 */
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
/* (#) Portability: GNU C Library (/inet/netinet/ether.h) */
/* (#) Portability: GNU Hurd      (/usr/include/netinet/ether.h) */
/* (#) Portability: diet libc     (/include/netinet/ether.h) */
/* (#) Portability: libc6         (/include/netinet/ether.h) */
/* (#) Portability: musl libc     (/include/netinet/ether.h) */
/* (#) Portability: uClibc        (/include/netinet/ether.h) */
#ifndef _NETINET_ETHER_H
#define _NETINET_ETHER_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <net/ethernet.h>
#include <netinet/if_ether.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_ether_ntoa
/* Convert `addr' into a 20-character-long string that
 * uses the the standard `AA:BB:CC:DD:EE:FF' notation. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,ether_ntoa,(struct ether_addr const *__restrict __addr),(__addr))
#else /* __CRT_HAVE_ether_ntoa */
#include <libc/local/netinet.ether/ether_ntoa.h>
/* Convert `addr' into a 20-character-long string that
 * uses the the standard `AA:BB:CC:DD:EE:FF' notation. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_ntoa, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL ether_ntoa)(struct ether_addr const *__restrict __addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_ntoa))(__addr); })
#endif /* !__CRT_HAVE_ether_ntoa */
#ifdef __CRT_HAVE_ether_ntoa_r
/* Convert `addr' into a 20-character-long string that
 * uses the the standard `AA:BB:CC:DD:EE:FF' notation. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,ether_ntoa_r,(struct ether_addr const *__restrict __addr, char *__restrict __buf),(__addr,__buf))
#else /* __CRT_HAVE_ether_ntoa_r */
#include <libc/local/netinet.ether/ether_ntoa_r.h>
/* Convert `addr' into a 20-character-long string that
 * uses the the standard `AA:BB:CC:DD:EE:FF' notation. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_ntoa_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(1) __ATTR_OUT(2) char *__NOTHROW_NCX(__LIBCCALL ether_ntoa_r)(struct ether_addr const *__restrict __addr, char *__restrict __buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_ntoa_r))(__addr, __buf); })
#endif /* !__CRT_HAVE_ether_ntoa_r */
#ifdef __CRT_HAVE_ether_aton
/* To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct ether_addr *,__NOTHROW_NCX,ether_aton,(char const *__restrict __asc),(__asc))
#else /* __CRT_HAVE_ether_aton */
#include <libc/local/netinet.ether/ether_aton.h>
/* To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_aton, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct ether_addr *__NOTHROW_NCX(__LIBCCALL ether_aton)(char const *__restrict __asc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_aton))(__asc); })
#endif /* !__CRT_HAVE_ether_aton */
#ifdef __CRT_HAVE_ether_aton_r
/* To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),struct ether_addr *,__NOTHROW_NCX,ether_aton_r,(char const *__restrict __asc, struct ether_addr *__restrict __addr),(__asc,__addr))
#else /* __CRT_HAVE_ether_aton_r */
#include <libc/local/netinet.ether/ether_aton_r.h>
/* To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_aton_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) struct ether_addr *__NOTHROW_NCX(__LIBCCALL ether_aton_r)(char const *__restrict __asc, struct ether_addr *__restrict __addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_aton_r))(__asc, __addr); })
#endif /* !__CRT_HAVE_ether_aton_r */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_ether_paton_r
/* To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2),struct ether_addr *,__NOTHROW_NCX,ether_paton_r,(char const **__restrict __pasc, struct ether_addr *__restrict __addr),(__pasc,__addr))
#else /* __CRT_HAVE_ether_paton_r */
#include <libc/local/netinet.ether/ether_paton_r.h>
/* To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_paton_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) struct ether_addr *__NOTHROW_NCX(__LIBCCALL ether_paton_r)(char const **__restrict __pasc, struct ether_addr *__restrict __addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_paton_r))(__pasc, __addr); })
#endif /* !__CRT_HAVE_ether_paton_r */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_ether_line
/* Scan  a  given  `line',   as  read  from  `/etc/ethers'   for
 * its `addr' and `hostname' parts. For this purpose, the  given
 * `line' must be formatted as `AA:BB:CC:DD:EE:FF  hostname  \n'
 * @return: 0 : Success
 * @return: -1: Failed to parse the  `addr'-portion
 *              (`ether_paton_r()' returned `NULL') */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_NCX,ether_line,(char const *__line, struct ether_addr *__addr, char *__hostname),(__line,__addr,__hostname))
#else /* __CRT_HAVE_ether_line */
#include <libc/local/netinet.ether/ether_line.h>
/* Scan  a  given  `line',   as  read  from  `/etc/ethers'   for
 * its `addr' and `hostname' parts. For this purpose, the  given
 * `line' must be formatted as `AA:BB:CC:DD:EE:FF  hostname  \n'
 * @return: 0 : Success
 * @return: -1: Failed to parse the  `addr'-portion
 *              (`ether_paton_r()' returned `NULL') */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_line, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) __ATTR_OUT(3) int __NOTHROW_NCX(__LIBCCALL ether_line)(char const *__line, struct ether_addr *__addr, char *__hostname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_line))(__line, __addr, __hostname); })
#endif /* !__CRT_HAVE_ether_line */
/* Map a given `addr' to its corresponding hostname from `/etc/ethers'
 * @return: 0 : Success
 * @return: * : No entry for `addr' found, or `/etc/ethers' doesn't exist. */
__CDECLARE_OPT(__ATTR_IN(2) __ATTR_OUT(1),int,__NOTHROW_RPC_KOS,ether_ntohost,(char *__hostname, struct ether_addr const *__addr),(__hostname,__addr))
/* Map a given `hostname' into its corresponding address from `/etc/ethers'
 * @return: 0 : Success
 * @return: * : No entry for `hostname' found, or `/etc/ethers' doesn't exist. */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_RPC_KOS,ether_hostton,(char const *__hostname, struct ether_addr *__addr),(__hostname,__addr))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NETINET_ETHER_H */
