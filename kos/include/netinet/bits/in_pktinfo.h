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
#ifndef _NETINET_BITS_IN_PKTINFO_H
#define _NETINET_BITS_IN_PKTINFO_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <netinet/bits/in_addr.h>

#ifdef __CC__
__SYSDECL_BEGIN

/* Structure used for IP_PKTINFO. */
struct in_pktinfo {
	__INT32_TYPE__ ipi_ifindex;  /* Interface index. */
	struct in_addr ipi_spec_dst; /* Routing destination address. */
	struct in_addr ipi_addr;     /* Header destination address. */
};

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NETINET_BITS_IN_PKTINFO_H */
