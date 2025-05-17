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
#ifndef _NETINET_BITS_IP_MSFILTER_H
#define _NETINET_BITS_IP_MSFILTER_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/os/sockaddr_storage.h>
#include <bits/types.h>
#include <netinet/bits/in_addr.h>

#ifdef __CC__
__SYSDECL_BEGIN

/* Full-state filter operations. */
struct ip_msfilter {
	struct in_addr imsf_multiaddr; /* IP multicast address of group. */
	struct in_addr imsf_interface; /* Local IP address of interface. */
	__uint32_t     imsf_fmode;     /* Filter mode. */
	__uint32_t     imsf_numsrc;    /* Number of source addresses. */
	struct in_addr imsf_slist[1];  /* Source addresses. */
};
#define __IP_MSFILTER_SIZE(numsrc) \
	(sizeof(struct ip_msfilter) -  \
	 sizeof(struct in_addr) +      \
	 ((numsrc) * sizeof(struct in_addr)))

struct group_filter {
	__uint32_t              gf_interface; /* Interface index. */
	struct sockaddr_storage gf_group;     /* Group address. */
	__uint32_t              gf_fmode;     /* Filter mode. */
	__uint32_t              gf_numsrc;    /* Number of source addresses. */
	struct sockaddr_storage gf_slist[1];  /* Source addresses. */
};
#define __GROUP_FILTER_SIZE(numsrc)    \
	(sizeof(struct group_filter) -     \
	 sizeof(struct sockaddr_storage) + \
	 ((numsrc) * sizeof(struct sockaddr_storage)))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NETINET_BITS_IP_MSFILTER_H */
