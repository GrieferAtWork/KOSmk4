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
#ifndef _NETINET_BITS_IP_MREQ_H
#define _NETINET_BITS_IP_MREQ_H 1

#include <__stdinc.h>

#include <netinet/bits/in_addr.h>

#ifdef __CC__
__SYSDECL_BEGIN

/* IPv4 multicast request. */
struct ip_mreq {
	struct in_addr imr_multiaddr; /* IP multicast address of group. */
	struct in_addr imr_interface; /* Local IP address of interface. */
};
struct ip_mreq_source {
	struct in_addr imr_multiaddr;  /* IP multicast address of group. */
	struct in_addr imr_interface;  /* IP address of source. */
	struct in_addr imr_sourceaddr; /* IP address of interface. */
};

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NETINET_BITS_IP_MREQ_H */
