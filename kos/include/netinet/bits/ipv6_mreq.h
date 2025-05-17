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
#ifndef _NETINET_BITS_IPV6_MREQ_H
#define _NETINET_BITS_IPV6_MREQ_H 1

#include <__stdinc.h>
#include <features.h>

#include <netinet/bits/in6_addr.h>

#ifdef __CC__
__SYSDECL_BEGIN

/* IPv6 multicast request. */
struct ipv6_mreq {
	struct in6_addr         ipv6mr_multiaddr; /* IPv6 multicast address of group. */
	__STDC_UINT32_AS_SIZE_T ipv6mr_interface; /* local interface. */
};

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NETINET_BITS_IPV6_MREQ_H */
