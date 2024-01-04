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
%(c_prefix){
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
}

%[default:section(".text.crt{|.dos}.net.interface")]

%[define_decl_include("<bits/crt/if_nameindex.h>": ["struct if_nameindex"])]
%[define_decl_include("<bits/crt/ifaddr.h>": ["struct ifaddr"])]
%[define_decl_include("<bits/os/ifconf.h>": ["struct ifconf"])]
%[define_decl_include("<bits/os/ifmap.h>": ["struct ifmap"])]
%[define_decl_include("<bits/os/ifreq.h>": ["struct ifreq"])]
%[define_decl_include("<bits/os/sockaddr.h>": ["struct sockaddr"])]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/os/net-if.h>
)]%{

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

}


@@>> if_nametoindex(3)
@@Lookup the index of the interface with the given `ifname'
@@@return: * : Index of the interface
@@@return: 0 : [errno=ENODEV] No interface matching `ifname'
@@@return: 0 : [errno=*] Error
[[cp_kos, decl_include("<features.h>")]]
[[requires_include("<asm/os/socket-ioctls.h>")]]
[[requires(($has_function(opensock, ioctl) && defined(__SIOCGIFINDEX)) ||
           $has_function(if_nameindex))]]
[[impl_include("<asm/os/net-if.h>", "<bits/crt/if_nameindex.h>", "<hybrid/typecore.h>")]]
[[impl_include("<bits/os/ifreq.h>", "<libc/errno.h>")]]
__STDC_UINT_AS_SIZE_T if_nametoindex([[in]] char const *ifname) {
@@pp_if $has_function(opensock, ioctl) && defined(__SIOCGIFINDEX)@@
	int ok;
	fd_t sockfd;
	@struct ifreq@ req;
	if unlikely(strlen(ifname) >= __IF_NAMESIZE) {
@@pp_ifdef ENODEV@@
		(void)__libc_seterrno(ENODEV);
@@pp_else@@
		(void)__libc_seterrno(1);
@@pp_endif@@
		goto err;
	}
	sockfd = opensock();
	if unlikely(sockfd < 0)
		goto err;
	strncpy(req.@ifr_name@, ifname, __IF_NAMESIZE);
	ok = ioctl(sockfd, __SIOCGIFINDEX, &req);
@@pp_if $has_function(close)@@
	(void)close(sockfd);
@@pp_endif@@
	if unlikely(ok < 0)
		goto err;
	return req.@ifr_ifindex@;
@@pp_else@@
	size_t i;
	@struct if_nameindex@ *index = if_nameindex();
	if unlikely(!index)
		goto err;
	for (i = 0; index[i].@if_name@; ++i) {
		if (strcmp(index[i].@if_name@, ifname) == 0) {
			__STDC_UINT_AS_SIZE_T result = index[i].@if_index@;
@@pp_if $has_function(if_freenameindex)@@
			if_freenameindex(index);
@@pp_endif@@
			return result;
		}
	}
@@pp_ifdef ENODEV@@
	(void)__libc_seterrno(ENODEV);
@@pp_else@@
	(void)__libc_seterrno(1);
@@pp_endif@@
err_index:
@@pp_if $has_function(if_freenameindex)@@
	if_freenameindex(index);
@@pp_endif@@
@@pp_endif@@
err:
	return 0;
}

@@>> if_indextoname(3)
@@Lookup the name of the interface with the given `ifindex'
@@@return: ifname : Success (up to `IF_NAMESIZE' characters were written to `ifname')
@@@return: NULL   : [errno=ENXIO] No interface with index `ifindex'
@@@return: NULL   : [errno=*] Error
[[cp_kos, decl_include("<features.h>")]]
[[requires_include("<asm/os/socket-ioctls.h>")]]
[[requires(($has_function(opensock, ioctl) && defined(__SIOCGIFNAME)) ||
           $has_function(if_nameindex))]]
[[impl_include("<asm/os/net-if.h>", "<bits/crt/if_nameindex.h>", "<hybrid/typecore.h>")]]
[[impl_include("<bits/os/ifreq.h>", "<libc/errno.h>")]]
char *if_indextoname(__STDC_UINT_AS_SIZE_T ifindex, [[out]] char *ifname/*[IF_NAMESIZE]*/) {
@@pp_if $has_function(opensock, ioctl) && defined(__SIOCGIFNAME)@@
	int ok;
	fd_t sockfd;
	@struct ifreq@ req;
	sockfd = opensock();
	if unlikely(sockfd < 0)
		goto err;
	req.@ifr_ifindex@ = ifindex;
	ok = ioctl(sockfd, __SIOCGIFNAME, &req);
@@pp_if $has_function(close)@@
	(void)close(sockfd);
@@pp_endif@@
	if unlikely(ok < 0) {
@@pp_if defined(__libc_geterrno) && defined(ENODEV) && defined(ENXIO)@@
		if (__libc_geterrno() == ENODEV)
			__libc_seterrno(ENXIO);
@@pp_endif@@
		goto err;
	}
	return strncpy(ifname, req.@ifr_name@, __IF_NAMESIZE);
@@pp_else@@
	size_t i;
	@struct if_nameindex@ *index = if_nameindex();
	if unlikely(!index)
		goto err;
	for (i = 0; index[i].@if_name@; ++i) {
		if (index[i].@if_index@ == ifindex) {
			strncpy(ifname, index[i].@if_name@, __IF_NAMESIZE);
@@pp_if $has_function(if_freenameindex)@@
			if_freenameindex(index);
@@pp_endif@@
			return ifname;
		}
	}
@@pp_ifdef ENXIO@@
	(void)__libc_seterrno(ENXIO);
@@pp_else@@
	(void)__libc_seterrno(1);
@@pp_endif@@
err_index:
@@pp_if $has_function(if_freenameindex)@@
	if_freenameindex(index);
@@pp_endif@@
@@pp_endif@@
err:
	return 0;
}

@@>> if_indextoname(3)
@@Allocate and return a listing of all interface names. The list is
@@allocated dynamically and is terminated by a NULL-if_name  entry.
@@
@@Once done, the caller must dispose the list using `if_freenameindex(3)'
@@@return: *   : Success (base-pointer of the allocated interface-list)
@@@return: NULL: Error (s.a. `errno')
[[cp_kos, wunused]]
[[decl_include("<bits/crt/if_nameindex.h>")]]
struct if_nameindex *if_nameindex();

@@>> if_freenameindex(3)
@@Free an interface-list previously allocated by `if_nameindex(3)'
[[decl_include("<bits/crt/if_nameindex.h>", "<hybrid/typecore.h>")]]
[[requires_function(free)]]
void if_freenameindex([[nonnull]] struct if_nameindex *ptr) {
	size_t i;
	for (i = 0; ptr[i].@if_name@; ++i)
		free(ptr[i].@if_name@);
	free(ptr);
}


@@Construct  and return a socket of arbitrary
@@typing (for use with talking to the kernel)
[[decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/socket.h>")]]
[[requires($has_function(socket) && defined(__SOCK_DGRAM) &&
           (defined(__AF_LOCAL) || defined(__AF_INET) || defined(__AF_INET6)))]]
[[impl_include("<asm/os/socket.h>", "<hybrid/typecore.h>", "<libc/errno.h>")]]
[[static, wunused]] $fd_t opensock() {
	size_t i;
	static unsigned int const domains[] = {
@@pp_ifdef __AF_LOCAL@@
		__AF_LOCAL,
@@pp_endif@@
@@pp_ifdef __AF_INET@@
		__AF_INET,
@@pp_endif@@
@@pp_ifdef __AF_INET6@@
		__AF_INET6,
@@pp_endif@@
	};
	for (i = 0; i < lengthof(domains); ++i) {
		fd_t result;
@@pp_ifdef __SOCK_CLOEXEC@@
		result = socket(domains[i], __SOCK_DGRAM | __SOCK_CLOEXEC, 0);
@@pp_else@@
		result = socket(domains[i], __SOCK_DGRAM, 0);
@@pp_endif@@
		if likely(result >= 0)
			return result;
	}
@@pp_ifdef ENOENT@@
	return __libc_seterrno(ENOENT);
@@pp_else@@
	return __libc_seterrno(1);
@@pp_endif@@
}


%{

__SYSDECL_END
#endif /* __CC__ */

}
