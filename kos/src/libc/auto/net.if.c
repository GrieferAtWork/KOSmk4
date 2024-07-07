/* HASH CRC-32:0xed17c2c9 */
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
#ifndef GUARD_LIBC_AUTO_NET_IF_C
#define GUARD_LIBC_AUTO_NET_IF_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/net.if.h"
#include "../user/stdlib.h"
#include "string.h"
#include "../user/sys.ioctl.h"
#include "../user/sys.socket.h"
#include "../user/unistd.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/net-if.h>
#include <bits/crt/if_nameindex.h>
#include <hybrid/typecore.h>
#include <bits/os/ifreq.h>
#include <libc/errno.h>
/* >> if_nametoindex(3)
 * Lookup the index of the interface with the given `ifname'
 * @return: * : Index of the interface
 * @return: 0 : [errno=ENODEV] No interface matching `ifname'
 * @return: 0 : [errno=*] Error */
INTERN ATTR_SECTION(".text.crt.net.interface") ATTR_IN(1) __STDC_UINT_AS_SIZE_T
NOTHROW_RPC_KOS(LIBCCALL libc_if_nametoindex)(char const *ifname) {

	int ok;
	fd_t sockfd;
	struct ifreq req;
	if unlikely(libc_strlen(ifname) >= __IF_NAMESIZE) {

		(void)__libc_seterrno(ENODEV);



		goto err;
	}
	sockfd = libc_opensock();
	if unlikely(sockfd < 0)
		goto err;
	libc_strncpy(req.ifr_name, ifname, __IF_NAMESIZE);
	ok = libc_ioctl(sockfd, __SIOCGIFINDEX, &req);

	(void)libc_close(sockfd);

	if unlikely(ok < 0)
		goto err;
	return req.ifr_ifindex;
























err:
	return 0;
}
#include <asm/os/net-if.h>
#include <bits/crt/if_nameindex.h>
#include <hybrid/typecore.h>
#include <bits/os/ifreq.h>
#include <libc/errno.h>
/* >> if_indextoname(3)
 * Lookup the name of the interface with the given `ifindex'
 * @return: ifname : Success (up to `IF_NAMESIZE' characters were written to `ifname')
 * @return: NULL   : [errno=ENXIO] No interface with index `ifindex'
 * @return: NULL   : [errno=*] Error */
INTERN ATTR_SECTION(".text.crt.net.interface") ATTR_OUT(2) char *
NOTHROW_RPC_KOS(LIBCCALL libc_if_indextoname)(__STDC_UINT_AS_SIZE_T ifindex,
                                              char *ifname) {

	int ok;
	fd_t sockfd;
	struct ifreq req;
	sockfd = libc_opensock();
	if unlikely(sockfd < 0)
		goto err;
	req.ifr_ifindex = ifindex;
	ok = libc_ioctl(sockfd, __SIOCGIFNAME, &req);

	(void)libc_close(sockfd);

	if unlikely(ok < 0) {

		if (__libc_geterrno() == ENODEV)
			__libc_seterrno(ENXIO);

		goto err;
	}
	return libc_strncpy(ifname, req.ifr_name, __IF_NAMESIZE);
























err:
	return 0;
}
/* >> if_freenameindex(3)
 * Free an interface-list previously allocated by `if_nameindex(3)' */
INTERN ATTR_SECTION(".text.crt.net.interface") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_if_freenameindex)(struct if_nameindex *ptr) {
	size_t i;
	for (i = 0; ptr[i].if_name; ++i)
		libc_free(ptr[i].if_name);
	libc_free(ptr);
}
#include <asm/os/socket.h>
#include <hybrid/typecore.h>
#include <libc/errno.h>
/* Construct  and return a socket of arbitrary
 * typing (for use with talking to the kernel) */
INTERN ATTR_SECTION(".text.crt.net.interface") WUNUSED fd_t
NOTHROW_NCX(LIBCCALL libc_opensock)(void) {
	size_t i;
	static unsigned int const domains[] = {

		__AF_LOCAL,


		__AF_INET,


		__AF_INET6,

	};
	for (i = 0; i < lengthof(domains); ++i) {
		fd_t result;

		result = libc_socket(domains[i], __SOCK_DGRAM | __SOCK_CLOEXEC, 0);



		if likely(result >= 0)
			return result;
	}

	return __libc_seterrno(ENOENT);



}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(if_nametoindex,libc_if_nametoindex,ATTR_IN(1),__STDC_UINT_AS_SIZE_T,NOTHROW_RPC_KOS,LIBCCALL,(char const *ifname),(ifname));
DEFINE_PUBLIC_ALIAS_P(if_indextoname,libc_if_indextoname,ATTR_OUT(2),char *,NOTHROW_RPC_KOS,LIBCCALL,(__STDC_UINT_AS_SIZE_T ifindex, char *ifname),(ifindex,ifname));
DEFINE_PUBLIC_ALIAS_P_VOID(if_freenameindex,libc_if_freenameindex,NONNULL((1)),NOTHROW_NCX,LIBCCALL,(struct if_nameindex *ptr),(ptr));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_NET_IF_C */
