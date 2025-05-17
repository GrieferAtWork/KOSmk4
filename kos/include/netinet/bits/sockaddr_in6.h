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
/*!included_by <netinet/in.h>*/
#ifndef _NETINET_BITS_SOCKADDR_IN6_H
#define _NETINET_BITS_SOCKADDR_IN6_H 1

#include <__stdinc.h>

#include <bits/os/sockaddr-common.h>
#include <bits/os/sockaddr.h>
#include <net/bits/types.h>
#include <netinet/bits/in6_addr.h>
#include <netinet/bits/in_addr.h>

/* Internet address. */
#ifdef __CC__
__SYSDECL_BEGIN

/* AF_INET6: Socket address */
struct sockaddr_in6 {
	__SOCKADDR_COMMON(sin6_);
	__in_port_t     sin6_port;     /* Port number. */
	__u_net32_t     sin6_flowinfo; /* IPv6 flow information */
	struct in6_addr sin6_addr;     /* IPv6 address */
	__u_net32_t     sin6_scope_id; /* IPv6 scope-id */
};

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NETINET_BITS_SOCKADDR_IN6_H */
