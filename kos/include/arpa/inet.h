/* HASH CRC-32:0x880b8155 */
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
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/arpa/inet.h) */
/* (#) Portability: DragonFly BSD (/include/arpa/inet.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/arpa/inet.h) */
/* (#) Portability: FreeBSD       (/include/arpa/inet.h) */
/* (#) Portability: GNU C Library (/inet/arpa/inet.h) */
/* (#) Portability: GNU Hurd      (/usr/include/arpa/inet.h) */
/* (#) Portability: NetBSD        (/include/arpa/inet.h) */
/* (#) Portability: OpenBSD       (/include/arpa/inet.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/arpa/inet.h) */
/* (#) Portability: diet libc     (/include/arpa/inet.h) */
/* (#) Portability: libc4/5       (/include/arpa/inet.h) */
/* (#) Portability: libc6         (/include/arpa/inet.h) */
/* (#) Portability: mintlib       (/include/arpa/inet.h) */
/* (#) Portability: musl libc     (/include/arpa/inet.h) */
/* (#) Portability: uClibc        (/include/arpa/inet.h) */
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

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __socklen_t_defined
#define __socklen_t_defined
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */

#ifdef __CRT_HAVE_inet_netof
/* >> inet_netof(3)
 * Return the network-number-part of the Internet address `INADDR' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT32_TYPE__,__NOTHROW_NCX,inet_netof,(struct in_addr __inaddr),(__inaddr))
#else /* __CRT_HAVE_inet_netof */
#include <libc/local/arpa.inet/inet_netof.h>
/* >> inet_netof(3)
 * Return the network-number-part of the Internet address `INADDR' */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_netof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL inet_netof)(struct in_addr __inaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_netof))(__inaddr); })
#endif /* !__CRT_HAVE_inet_netof */
#ifdef __CRT_HAVE_inet_lnaof
/* >> inet_lnaof(3)
 * Return the local-host-address-part of the Internet address `INADDR' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,__UINT32_TYPE__,__NOTHROW_NCX,inet_lnaof,(struct in_addr __inaddr),(__inaddr))
#else /* __CRT_HAVE_inet_lnaof */
#include <libc/local/arpa.inet/inet_lnaof.h>
/* >> inet_lnaof(3)
 * Return the local-host-address-part of the Internet address `INADDR' */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_lnaof, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL inet_lnaof)(struct in_addr __inaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_lnaof))(__inaddr); })
#endif /* !__CRT_HAVE_inet_lnaof */
#ifdef __CRT_HAVE_inet_makeaddr
/* >> inet_makeaddr(3)
 * Construct  an  Internet-host-address in  network byte  order from
 * the combination of its network (`net'), and host (`host') number.
 * The `net' and `host' arguments  can later be re-extracted by  use
 * of `inet_netof(3)' and `inet_lnaof(3)' */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,struct in_addr,__NOTHROW_NCX,inet_makeaddr,(__UINT32_TYPE__ __net, __UINT32_TYPE__ __host),(__net,__host))
#else /* __CRT_HAVE_inet_makeaddr */
#include <libc/local/arpa.inet/inet_makeaddr.h>
/* >> inet_makeaddr(3)
 * Construct  an  Internet-host-address in  network byte  order from
 * the combination of its network (`net'), and host (`host') number.
 * The `net' and `host' arguments  can later be re-extracted by  use
 * of `inet_netof(3)' and `inet_lnaof(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_makeaddr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED struct in_addr __NOTHROW_NCX(__LIBCCALL inet_makeaddr)(__UINT32_TYPE__ __net, __UINT32_TYPE__ __host) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_makeaddr))(__net, __host); })
#endif /* !__CRT_HAVE_inet_makeaddr */
#ifdef __CRT_HAVE_inet_addr
/* >> inet_addr(3)
 * Convert an  Internet host  address  `CP' from  its  numbers-and-dots
 * notational form into its binary representation in network byte order
 * Accepted notations are:
 *     a.b.c.d (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd     (1.564)
 *     abcd (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123 (hex)
 *     0123  (oct) */
__CDECLARE(__ATTR_PURE __ATTR_IN(1),in_addr_t,__NOTHROW_NCX,inet_addr,(char const *__restrict __cp),(__cp))
#else /* __CRT_HAVE_inet_addr */
#include <libc/local/arpa.inet/inet_addr.h>
/* >> inet_addr(3)
 * Convert an  Internet host  address  `CP' from  its  numbers-and-dots
 * notational form into its binary representation in network byte order
 * Accepted notations are:
 *     a.b.c.d (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd     (1.564)
 *     abcd (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123 (hex)
 *     0123  (oct) */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_addr, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_IN(1) in_addr_t __NOTHROW_NCX(__LIBCCALL inet_addr)(char const *__restrict __cp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_addr))(__cp); })
#endif /* !__CRT_HAVE_inet_addr */
#ifdef __CRT_HAVE_inet_ntoa
/* >> inet_ntoa(3)
 * Return   the   conventional  numbers-and-dots   representation   of  a
 * given  Internet  host  address  `inaddr'.  The  returned  pointer   is
 * apart of a static buffer and  may change in subsequence (or  parallel)
 * calls. For a re-entrant version of this function, see `inet_ntoa_r(3)' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,inet_ntoa,(struct in_addr __inaddr),(__inaddr))
#else /* __CRT_HAVE_inet_ntoa */
#include <libc/local/arpa.inet/inet_ntoa.h>
/* >> inet_ntoa(3)
 * Return   the   conventional  numbers-and-dots   representation   of  a
 * given  Internet  host  address  `inaddr'.  The  returned  pointer   is
 * apart of a static buffer and  may change in subsequence (or  parallel)
 * calls. For a re-entrant version of this function, see `inet_ntoa_r(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_ntoa, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_WUNUSED char *__NOTHROW_NCX(__LIBCCALL inet_ntoa)(struct in_addr __inaddr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_ntoa))(__inaddr); })
#endif /* !__CRT_HAVE_inet_ntoa */
#ifdef __USE_KOS
#define INET_NTOA_R_MAXLEN 16 /* Max # of characters written by `inet_ntoa_r' (e.g. `111.111.111.111\0') */
#ifdef __CRT_HAVE_inet_ntoa_r
/* >> inet_ntoa_r(3)
 * Re-entrant version of `inet_ntoa()' */
__CDECLARE(__ATTR_RETNONNULL __ATTR_OUT(2),char *,__NOTHROW_NCX,inet_ntoa_r,(struct in_addr __inaddr, char __buf[16]),(__inaddr,__buf))
#else /* __CRT_HAVE_inet_ntoa_r */
#include <libc/local/arpa.inet/inet_ntoa_r.h>
/* >> inet_ntoa_r(3)
 * Re-entrant version of `inet_ntoa()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_ntoa_r, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_RETNONNULL __ATTR_OUT(2) char *__NOTHROW_NCX(__LIBCCALL inet_ntoa_r)(struct in_addr __inaddr, char __buf[16]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_ntoa_r))(__inaddr, __buf); })
#endif /* !__CRT_HAVE_inet_ntoa_r */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_inet_network
/* >> inet_network(3)
 * This function is  the same as  `inet_addr()', except  that
 * the return value is in host-endian, rather than net-endian */
__CDECLARE(__ATTR_PURE __ATTR_IN(1),__UINT32_TYPE__,__NOTHROW_NCX,inet_network,(char const *__restrict __cp),(__cp))
#else /* __CRT_HAVE_inet_network */
#include <libc/local/arpa.inet/inet_network.h>
/* >> inet_network(3)
 * This function is  the same as  `inet_addr()', except  that
 * the return value is in host-endian, rather than net-endian */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_network, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_IN(1) __UINT32_TYPE__ __NOTHROW_NCX(__LIBCCALL inet_network)(char const *__restrict __cp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_network))(__cp); })
#endif /* !__CRT_HAVE_inet_network */

/* The following functions are not part of XNS 5.2. */
#ifdef __USE_MISC
#ifdef __CRT_HAVE_inet_aton
/* >> inet_aton(3)
 * Convert an Internet host address `CP' from its numbers-and-dots
 * notational form into its binary representation in network  byte
 * order. The result is then stored in `*INP'
 * Accepted notations are:
 *     a.b.c.d (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd     (1.564)
 *     abcd (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123 (hex)
 *     0123  (oct)
 * @return: 0: Bad input format
 * @return: 1: Success */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,inet_aton,(char const *__restrict __cp, struct in_addr *__restrict __inp),(__cp,__inp))
#else /* __CRT_HAVE_inet_aton */
#include <libc/local/arpa.inet/inet_aton.h>
/* >> inet_aton(3)
 * Convert an Internet host address `CP' from its numbers-and-dots
 * notational form into its binary representation in network  byte
 * order. The result is then stored in `*INP'
 * Accepted notations are:
 *     a.b.c.d (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd     (1.564)
 *     abcd (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123 (hex)
 *     0123  (oct)
 * @return: 0: Bad input format
 * @return: 1: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_aton, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL inet_aton)(char const *__restrict __cp, struct in_addr *__restrict __inp) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_aton))(__cp, __inp); })
#endif /* !__CRT_HAVE_inet_aton */
#ifdef __USE_KOS
#ifdef __CRT_HAVE_inet_paton
/* >> inet_paton(3)
 * Same as `inet_aton()', but update `*pcp' to point past the address
 * Accepted notations are:
 *     a.b.c.d (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd     (1.564)
 *     abcd (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123 (hex)
 *     0123  (oct)
 * @param: network_addr: When non-zero, `*pcp' is a network address
 * @return: 0: Bad input format
 * @return: 1: Success */
__CDECLARE(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_NCX,inet_paton,(char const **__restrict __pcp, struct in_addr *__restrict __inp, int __network_addr),(__pcp,__inp,__network_addr))
#else /* __CRT_HAVE_inet_paton */
#include <libc/local/arpa.inet/inet_paton.h>
/* >> inet_paton(3)
 * Same as `inet_aton()', but update `*pcp' to point past the address
 * Accepted notations are:
 *     a.b.c.d (1.2.3.4)
 *     a.b.cd   (1.2.52)
 *     a.bcd     (1.564)
 *     abcd (4660)
 * With each number allowed to be written in as one of:
 *     123      (decimal)
 *     0x123 (hex)
 *     0123  (oct)
 * @param: network_addr: When non-zero, `*pcp' is a network address
 * @return: 0: Bad input format
 * @return: 1: Success */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_paton, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL inet_paton)(char const **__restrict __pcp, struct in_addr *__restrict __inp, int __network_addr) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_paton))(__pcp, __inp, __network_addr); })
#endif /* !__CRT_HAVE_inet_paton */
#endif /* __USE_KOS */
#ifdef __CRT_HAVE_inet_neta
/* >> inet_neta(3)
 * Similar to `inet_ntoa_r(3)', but use smaller formats if possible:
 *     0.0.0.0      For net = 0
 *     %u           For net <= 255
 *     %u.%u        For net <= 65535
 *     %u.%u.%u     For net <= 16777215
 *     %u.%u.%u.%u  For everything else
 * @return: buf:  Success
 * @return: NULL: [errno=EMSGSIZE]: The given `len' is too small */
__CDECLARE(__ATTR_OUTS(2, 3),char *,__NOTHROW_NCX,inet_neta,(__UINT32_TYPE__ __net, char *__buf, __SIZE_TYPE__ __len),(__net,__buf,__len))
#else /* __CRT_HAVE_inet_neta */
#include <libc/local/arpa.inet/inet_neta.h>
/* >> inet_neta(3)
 * Similar to `inet_ntoa_r(3)', but use smaller formats if possible:
 *     0.0.0.0      For net = 0
 *     %u           For net <= 255
 *     %u.%u        For net <= 65535
 *     %u.%u.%u     For net <= 16777215
 *     %u.%u.%u.%u  For everything else
 * @return: buf:  Success
 * @return: NULL: [errno=EMSGSIZE]: The given `len' is too small */
__NAMESPACE_LOCAL_USING_OR_IMPL(inet_neta, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUTS(2, 3) char *__NOTHROW_NCX(__LIBCCALL inet_neta)(__UINT32_TYPE__ __net, char *__buf, __SIZE_TYPE__ __len) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_neta))(__net, __buf, __len); })
#endif /* !__CRT_HAVE_inet_neta */
/* >> inet_net_ntop(3)
 * TODO: Implement & document */
__CDECLARE_OPT(,char *,__NOTHROW_RPC_KOS,inet_net_ntop,(int __af, void const *__cp, int __bits, char *__buf, __SIZE_TYPE__ __len),(__af,__cp,__bits,__buf,__len))
/* >> inet_net_pton(3)
 * TODO: Implement & document */
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,inet_net_pton,(int __af, char const *__cp, void *__buf, __SIZE_TYPE__ __len),(__af,__cp,__buf,__len))
/* >> inet_nsap_addr(3)
 * TODO: Implement & document */
__CDECLARE_OPT(,unsigned int,__NOTHROW_RPC_KOS,inet_nsap_addr,(char const *__cp, unsigned char *__buf, int __len),(__cp,__buf,__len))
/* >> inet_nsap_ntoa(3)
 * TODO: Implement & document */
__CDECLARE_OPT(,char *,__NOTHROW_RPC_KOS,inet_nsap_ntoa,(int __len, unsigned char const *__cp, char *__buf),(__len,__cp,__buf))
#endif /* __USE_MISC */
/* >> inet_pton(3)
 * TODO: Implement & document */
__CDECLARE_OPT(,int,__NOTHROW_RPC_KOS,inet_pton,(int __af, char const *__restrict __cp, void *__restrict __buf),(__af,__cp,__buf))
/* >> inet_ntop(3)
 * TODO: Implement & document */
__CDECLARE_OPT(,char const *,__NOTHROW_RPC_KOS,inet_ntop,(int __af, void const *__restrict __cp, char *__restrict __buf, socklen_t __len),(__af,__cp,__buf,__len))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ARPA_INET_H */
