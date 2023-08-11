/* HASH CRC-32:0xf87ae512 */
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
/* >> ether_ntoa(3), ether_ntoa_r(3)
 * Convert `addr' into a 20-character-long string that
 * uses the the standard `AA:BB:CC:DD:EE:FF' notation. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,ether_ntoa,(struct ether_addr const *__restrict __addr),(__addr))
#else /* __CRT_HAVE_ether_ntoa */
#include <libc/local/netinet.ether/ether_ntoa.h>
/* >> ether_ntoa(3), ether_ntoa_r(3)
 * Convert `addr' into a 20-character-long string that
 * uses the the standard `AA:BB:CC:DD:EE:FF' notation. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_ntoa, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *__NOTHROW_NCX(__LIBCCALL ether_ntoa)(struct ether_addr const *__restrict __addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_ntoa))(__addr); })
#endif /* !__CRT_HAVE_ether_ntoa */
#ifdef __CRT_HAVE_ether_ntoa_r
/* >> ether_ntoa(3), ether_ntoa_r(3)
 * Convert `addr' into a 20-character-long string that
 * uses the the standard `AA:BB:CC:DD:EE:FF' notation. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,ether_ntoa_r,(struct ether_addr const *__restrict __addr, char *__restrict __buf),(__addr,__buf))
#else /* __CRT_HAVE_ether_ntoa_r */
#include <libc/local/netinet.ether/ether_ntoa_r.h>
/* >> ether_ntoa(3), ether_ntoa_r(3)
 * Convert `addr' into a 20-character-long string that
 * uses the the standard `AA:BB:CC:DD:EE:FF' notation. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_ntoa_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_IN(1) __ATTR_OUT(2) char *__NOTHROW_NCX(__LIBCCALL ether_ntoa_r)(struct ether_addr const *__restrict __addr, char *__restrict __buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_ntoa_r))(__addr, __buf); })
#endif /* !__CRT_HAVE_ether_ntoa_r */
#ifdef __CRT_HAVE_ether_aton
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),struct ether_addr *,__NOTHROW_NCX,ether_aton,(char const *__restrict __asc),(__asc))
#else /* __CRT_HAVE_ether_aton */
#include <libc/local/netinet.ether/ether_aton.h>
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_aton, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) struct ether_addr *__NOTHROW_NCX(__LIBCCALL ether_aton)(char const *__restrict __asc) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_aton))(__asc); })
#endif /* !__CRT_HAVE_ether_aton */
#ifdef __CRT_HAVE_ether_aton_r
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),struct ether_addr *,__NOTHROW_NCX,ether_aton_r,(char const *__restrict __asc, struct ether_addr *__restrict __addr),(__asc,__addr))
#else /* __CRT_HAVE_ether_aton_r */
#include <libc/local/netinet.ether/ether_aton_r.h>
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_aton_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) struct ether_addr *__NOTHROW_NCX(__LIBCCALL ether_aton_r)(char const *__restrict __asc, struct ether_addr *__restrict __addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_aton_r))(__asc, __addr); })
#endif /* !__CRT_HAVE_ether_aton_r */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_ether_aton_np
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,ether_aton_np,(char const *__restrict __asc, struct ether_addr *__restrict __addr),(__asc,__addr))
#else /* __CRT_HAVE_ether_aton_np */
#include <libc/local/netinet.ether/ether_aton_np.h>
/* >> ether_aton(3), ether_aton_r(3), ether_aton_np(3)
 * To   the   reverse  of   `ether_ntoa()'   and  convert
 * a `AA:BB:CC:DD:EE:FF'-string into an ethernet address. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_aton_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) char *__NOTHROW_NCX(__LIBCCALL ether_aton_np)(char const *__restrict __asc, struct ether_addr *__restrict __addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_aton_np))(__asc, __addr); })
#endif /* !__CRT_HAVE_ether_aton_np */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_ether_line
/* >> ether_line(3), ether_line_np(3)
 * Scan  a  given  `line',   as  read  from  `/etc/ethers'   for
 * its `addr' and `hostname' parts. For this purpose, the  given
 * `line' must be formatted as `AA:BB:CC:DD:EE:FF  hostname  \n'
 * @return: 0 : Success
 * @return: -1: Failed to parse the  `addr'-portion (`ether_aton_np()' returned `NULL') */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) __ATTR_OUT(3),int,__NOTHROW_NCX,ether_line,(char const *__line, struct ether_addr *__addr, char *__hostname),(__line,__addr,__hostname))
#else /* __CRT_HAVE_ether_line */
#include <libc/local/netinet.ether/ether_line.h>
/* >> ether_line(3), ether_line_np(3)
 * Scan  a  given  `line',   as  read  from  `/etc/ethers'   for
 * its `addr' and `hostname' parts. For this purpose, the  given
 * `line' must be formatted as `AA:BB:CC:DD:EE:FF  hostname  \n'
 * @return: 0 : Success
 * @return: -1: Failed to parse the  `addr'-portion (`ether_aton_np()' returned `NULL') */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_line, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) __ATTR_OUT(3) int __NOTHROW_NCX(__LIBCCALL ether_line)(char const *__line, struct ether_addr *__addr, char *__hostname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_line))(__line, __addr, __hostname); })
#endif /* !__CRT_HAVE_ether_line */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_ether_line_np
/* >> ether_line(3), ether_line_np(3)
 * Scan  a  given  `line',   as  read  from  `/etc/ethers'   for
 * its `addr' and `hostname' parts. For this purpose, the  given
 * `line' must be formatted as `AA:BB:CC:DD:EE:FF  hostname  \n'
 * @return: 0 : Success
 * @return: -1: Failed to parse the  `addr'-portion (`ether_aton_np()' returned `NULL') */
__CDECLARE(__ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2),char *,__NOTHROW_NCX,ether_line_np,(char *__line, struct ether_addr *__addr),(__line,__addr))
#else /* __CRT_HAVE_ether_line_np */
#include <libc/local/netinet.ether/ether_line_np.h>
/* >> ether_line(3), ether_line_np(3)
 * Scan  a  given  `line',   as  read  from  `/etc/ethers'   for
 * its `addr' and `hostname' parts. For this purpose, the  given
 * `line' must be formatted as `AA:BB:CC:DD:EE:FF  hostname  \n'
 * @return: 0 : Success
 * @return: -1: Failed to parse the  `addr'-portion (`ether_aton_np()' returned `NULL') */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_line_np, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) char *__NOTHROW_NCX(__LIBCCALL ether_line_np)(char *__line, struct ether_addr *__addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_line_np))(__line, __addr); })
#endif /* !__CRT_HAVE_ether_line_np */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_ether_ntohost
/* >> ether_ntohost(3)
 * Map a given `addr' to its corresponding hostname from `/etc/ethers'
 * @return: 0 : Success
 * @return: * : No entry for `addr' found, or `/etc/ethers' doesn't exist. */
__CDECLARE(__ATTR_IN(2) __ATTR_OUT(1),int,__NOTHROW_RPC_KOS,ether_ntohost,(char *__hostname, struct ether_addr const *__addr),(__hostname,__addr))
#else /* __CRT_HAVE_ether_ntohost */
#include <asm/os/oflags.h>
#if ((defined(__CRT_HAVE_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE__IO_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_fopen64)) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/netinet.ether/ether_ntohost.h>
/* >> ether_ntohost(3)
 * Map a given `addr' to its corresponding hostname from `/etc/ethers'
 * @return: 0 : Success
 * @return: * : No entry for `addr' found, or `/etc/ethers' doesn't exist. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_ntohost, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUT(1) int __NOTHROW_RPC_KOS(__LIBCCALL ether_ntohost)(char *__hostname, struct ether_addr const *__addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_ntohost))(__hostname, __addr); })
#endif /* ((__CRT_HAVE_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || (__CRT_HAVE__IO_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_fopen64) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
#endif /* !__CRT_HAVE_ether_ntohost */
#ifdef __CRT_HAVE_ether_hostton
/* >> ether_hostton(3)
 * Map a given `hostname' into its corresponding address from `/etc/ethers'
 * @return: 0 : Success
 * @return: * : No entry for `hostname' found, or `/etc/ethers' doesn't exist. */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_RPC_KOS,ether_hostton,(char const *__hostname, struct ether_addr *__addr),(__hostname,__addr))
#else /* __CRT_HAVE_ether_hostton */
#include <asm/os/oflags.h>
#if ((defined(__CRT_HAVE_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || (defined(__CRT_HAVE__IO_fopen) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)) || defined(__CRT_HAVE_fopen64)) && (defined(__CRT_HAVE_fparseln) || ((defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))))
#include <libc/local/netinet.ether/ether_hostton.h>
/* >> ether_hostton(3)
 * Map a given `hostname' into its corresponding address from `/etc/ethers'
 * @return: 0 : Success
 * @return: * : No entry for `hostname' found, or `/etc/ethers' doesn't exist. */
__NAMESPACE_LOCAL_USING_OR_IMPL(ether_hostton, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) int __NOTHROW_RPC_KOS(__LIBCCALL ether_hostton)(char const *__hostname, struct ether_addr *__addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_hostton))(__hostname, __addr); })
#endif /* ((__CRT_HAVE_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || (__CRT_HAVE__IO_fopen && (!__USE_FILE_OFFSET64 || !__O_LARGEFILE || !__O_LARGEFILE)) || __CRT_HAVE_fopen64) && (__CRT_HAVE_fparseln || ((__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc))) */
#endif /* !__CRT_HAVE_ether_hostton */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NETINET_ETHER_H */
