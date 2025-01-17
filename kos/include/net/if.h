/* HASH CRC-32:0xb196c0b6 */
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
/* (>) Standard: POSIX.1-2004 (Issue 6, IEEE Std 1003.1-2004) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/net/if.h) */
/* (#) Portability: DragonFly BSD (/sys/net/if.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/net/if.h) */
/* (#) Portability: FreeBSD       (/sys/net/if.h) */
/* (#) Portability: GNU C Library (/sysdeps/[...]/net/if.h) */
/* (#) Portability: GNU Hurd      (/usr/include/net/if.h) */
/* (#) Portability: NetBSD        (/sys/net/if.h) */
/* (#) Portability: OpenBSD       (/sys/net/if.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/net/if.h) */
/* (#) Portability: diet libc     (/include/net/if.h) */
/* (#) Portability: libc4/5       (/include/net/if.h) */
/* (#) Portability: libc6         (/include/net/if.h) */
/* (#) Portability: mintlib       (/include/net/if.h) */
/* (#) Portability: musl libc     (/include/net/if.h) */
/* (#) Portability: uClibc        (/include/net/if.h) */
#ifndef _NET_IF_H
#define _NET_IF_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/os/net-if.h>

#ifdef __USE_MISC
#include <bits/crt/if_nameindex.h>
#include <bits/crt/ifaddr.h>
#include <bits/os/ifconf.h>
#include <bits/os/ifmap.h>
#include <bits/os/ifreq.h>
#include <bits/os/sockaddr.h>
#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#include <sys/socket.h>
#endif /* __USE_GLIBC_BLOAT */
#endif /* __USE_MISC */

/* Max length of an interface name. */
#if !defined(IF_NAMESIZE) && defined(__IF_NAMESIZE)
#define IF_NAMESIZE __IF_NAMESIZE
#endif /* !IF_NAMESIZE && __IF_NAMESIZE */

#ifdef __USE_MISC
/* Standard interface flags. */
#if !defined(IFF_UP) && defined(__IFF_UP)
#define IFF_UP          __IFF_UP          /* ??? */
#endif /* !IFF_UP && __IFF_UP */
#if !defined(IFF_BROADCAST) && defined(__IFF_BROADCAST)
#define IFF_BROADCAST   __IFF_BROADCAST   /* ??? */
#endif /* !IFF_BROADCAST && __IFF_BROADCAST */
#if !defined(IFF_DEBUG) && defined(__IFF_DEBUG)
#define IFF_DEBUG       __IFF_DEBUG       /* ??? */
#endif /* !IFF_DEBUG && __IFF_DEBUG */
#if !defined(IFF_LOOPBACK) && defined(__IFF_LOOPBACK)
#define IFF_LOOPBACK    __IFF_LOOPBACK    /* ??? */
#endif /* !IFF_LOOPBACK && __IFF_LOOPBACK */
#if !defined(IFF_POINTOPOINT) && defined(__IFF_POINTOPOINT)
#define IFF_POINTOPOINT __IFF_POINTOPOINT /* ??? */
#endif /* !IFF_POINTOPOINT && __IFF_POINTOPOINT */
#if !defined(IFF_NOTRAILERS) && defined(__IFF_NOTRAILERS)
#define IFF_NOTRAILERS  __IFF_NOTRAILERS  /* ??? */
#endif /* !IFF_NOTRAILERS && __IFF_NOTRAILERS */
#if !defined(IFF_RUNNING) && defined(__IFF_RUNNING)
#define IFF_RUNNING     __IFF_RUNNING     /* ??? */
#endif /* !IFF_RUNNING && __IFF_RUNNING */
#if !defined(IFF_NOARP) && defined(__IFF_NOARP)
#define IFF_NOARP       __IFF_NOARP       /* ??? */
#endif /* !IFF_NOARP && __IFF_NOARP */
#if !defined(IFF_PROMISC) && defined(__IFF_PROMISC)
#define IFF_PROMISC     __IFF_PROMISC     /* ??? */
#endif /* !IFF_PROMISC && __IFF_PROMISC */
#if !defined(IFF_ALLMULTI) && defined(__IFF_ALLMULTI)
#define IFF_ALLMULTI    __IFF_ALLMULTI    /* ??? */
#endif /* !IFF_ALLMULTI && __IFF_ALLMULTI */
#if !defined(IFF_MASTER) && defined(__IFF_MASTER)
#define IFF_MASTER      __IFF_MASTER      /* ??? */
#endif /* !IFF_MASTER && __IFF_MASTER */
#if !defined(IFF_SLAVE) && defined(__IFF_SLAVE)
#define IFF_SLAVE       __IFF_SLAVE       /* ??? */
#endif /* !IFF_SLAVE && __IFF_SLAVE */
#if !defined(IFF_MULTICAST) && defined(__IFF_MULTICAST)
#define IFF_MULTICAST   __IFF_MULTICAST   /* ??? */
#endif /* !IFF_MULTICAST && __IFF_MULTICAST */
#if !defined(IFF_PORTSEL) && defined(__IFF_PORTSEL)
#define IFF_PORTSEL     __IFF_PORTSEL     /* ??? */
#endif /* !IFF_PORTSEL && __IFF_PORTSEL */
#if !defined(IFF_AUTOMEDIA) && defined(__IFF_AUTOMEDIA)
#define IFF_AUTOMEDIA   __IFF_AUTOMEDIA   /* ??? */
#endif /* !IFF_AUTOMEDIA && __IFF_AUTOMEDIA */
#if !defined(IFF_DYNAMIC) && defined(__IFF_DYNAMIC)
#define IFF_DYNAMIC     __IFF_DYNAMIC     /* ??? */
#endif /* !IFF_DYNAMIC && __IFF_DYNAMIC */

#ifndef IFHWADDRLEN
#define IFHWADDRLEN 6 /* == ETH_ALEN */
#endif /* !IFHWADDRLEN */

/* Max length of an interface name. */
#if !defined(IFNAMSIZ) && defined(__IF_NAMESIZE)
#define IFNAMSIZ __IF_NAMESIZE
#endif /* !IFNAMSIZ && __IF_NAMESIZE */

/* ??? */
#define _IOT_ifreq        _IOT(_IOTS(char), __IF_NAMESIZE, _IOTS(char), 16, 0, 0)
#define _IOT_ifreq_short  _IOT(_IOTS(char), __IF_NAMESIZE, _IOTS(short), 1, 0, 0)
#define _IOT_ifreq_int    _IOT(_IOTS(char), __IF_NAMESIZE, _IOTS(int), 1, 0, 0)
#define _IOT_ifconf       _IOT(_IOTS(struct ifconf), 1, 0, 0, 0, 0)
#endif /* __USE_MISC */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_if_nametoindex
/* >> if_nametoindex(3)
 * Lookup the index of the interface with the given `ifname'
 * @return: * : Index of the interface
 * @return: 0 : [errno=ENODEV] No interface matching `ifname'
 * @return: 0 : [errno=*] Error */
__CDECLARE(__ATTR_IN(1),__STDC_UINT_AS_SIZE_T,__NOTHROW_RPC_KOS,if_nametoindex,(char const *__ifname),(__ifname))
#else /* __CRT_HAVE_if_nametoindex */
#include <asm/os/socket-ioctls.h>
#include <asm/os/socket.h>
#include <bits/types.h>
#if ((defined(__CRT_HAVE_socket) || defined(__CRT_HAVE___socket)) && defined(__SOCK_DGRAM) && (defined(__AF_LOCAL) || defined(__AF_INET) || defined(__AF_INET6)) && (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)) && defined(__SIOCGIFINDEX)) || defined(__CRT_HAVE_if_nameindex)
#include <libc/local/net.if/if_nametoindex.h>
/* >> if_nametoindex(3)
 * Lookup the index of the interface with the given `ifname'
 * @return: * : Index of the interface
 * @return: 0 : [errno=ENODEV] No interface matching `ifname'
 * @return: 0 : [errno=*] Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(if_nametoindex, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __STDC_UINT_AS_SIZE_T __NOTHROW_RPC_KOS(__LIBCCALL if_nametoindex)(char const *__ifname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(if_nametoindex))(__ifname); })
#endif /* ((__CRT_HAVE_socket || __CRT_HAVE___socket) && __SOCK_DGRAM && (__AF_LOCAL || __AF_INET || __AF_INET6) && (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl || __CRT_HAVE___ioctl_time64) && __SIOCGIFINDEX) || __CRT_HAVE_if_nameindex */
#endif /* !__CRT_HAVE_if_nametoindex */
#ifdef __CRT_HAVE_if_indextoname
/* >> if_indextoname(3)
 * Lookup the name of the interface with the given `ifindex'
 * @return: ifname : Success (up to `IF_NAMESIZE' characters were written to `ifname')
 * @return: NULL   : [errno=ENXIO] No interface with index `ifindex'
 * @return: NULL   : [errno=*] Error */
__CDECLARE(__ATTR_OUT(2),char *,__NOTHROW_RPC_KOS,if_indextoname,(__STDC_UINT_AS_SIZE_T __ifindex, char *__ifname),(__ifindex,__ifname))
#else /* __CRT_HAVE_if_indextoname */
#include <asm/os/socket-ioctls.h>
#include <asm/os/socket.h>
#include <bits/types.h>
#if ((defined(__CRT_HAVE_socket) || defined(__CRT_HAVE___socket)) && defined(__SOCK_DGRAM) && (defined(__AF_LOCAL) || defined(__AF_INET) || defined(__AF_INET6)) && (defined(__CRT_HAVE_ioctl) || defined(__CRT_HAVE___ioctl) || defined(__CRT_HAVE___libc_ioctl) || defined(__CRT_HAVE___ioctl_time64)) && defined(__SIOCGIFNAME)) || defined(__CRT_HAVE_if_nameindex)
#include <libc/local/net.if/if_indextoname.h>
/* >> if_indextoname(3)
 * Lookup the name of the interface with the given `ifindex'
 * @return: ifname : Success (up to `IF_NAMESIZE' characters were written to `ifname')
 * @return: NULL   : [errno=ENXIO] No interface with index `ifindex'
 * @return: NULL   : [errno=*] Error */
__NAMESPACE_LOCAL_USING_OR_IMPL(if_indextoname, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(2) char *__NOTHROW_RPC_KOS(__LIBCCALL if_indextoname)(__STDC_UINT_AS_SIZE_T __ifindex, char *__ifname) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(if_indextoname))(__ifindex, __ifname); })
#endif /* ((__CRT_HAVE_socket || __CRT_HAVE___socket) && __SOCK_DGRAM && (__AF_LOCAL || __AF_INET || __AF_INET6) && (__CRT_HAVE_ioctl || __CRT_HAVE___ioctl || __CRT_HAVE___libc_ioctl || __CRT_HAVE___ioctl_time64) && __SIOCGIFNAME) || __CRT_HAVE_if_nameindex */
#endif /* !__CRT_HAVE_if_indextoname */
/* >> if_indextoname(3)
 * Allocate and return a listing of all interface names. The list is
 * allocated dynamically and is terminated by a NULL-if_name  entry.
 *
 * Once done, the caller must dispose the list using `if_freenameindex(3)'
 * @return: *   : Success (base-pointer of the allocated interface-list)
 * @return: NULL: Error (s.a. `errno') */
__CDECLARE_OPT(__ATTR_WUNUSED,struct if_nameindex *,__NOTHROW_RPC_KOS,if_nameindex,(void),())
#ifdef __CRT_HAVE_if_freenameindex
/* >> if_freenameindex(3)
 * Free an interface-list previously allocated by `if_nameindex(3)' */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,if_freenameindex,(struct if_nameindex *__ptr),(__ptr))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/net.if/if_freenameindex.h>
/* >> if_freenameindex(3)
 * Free an interface-list previously allocated by `if_nameindex(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(if_freenameindex, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) void __NOTHROW_NCX(__LIBCCALL if_freenameindex)(struct if_nameindex *__ptr) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(if_freenameindex))(__ptr); })
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NET_IF_H */
