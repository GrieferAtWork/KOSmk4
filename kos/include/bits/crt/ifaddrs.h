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
/*!included_by <ifaddrs.h>*/
#ifndef _BITS_CRT_IFADDRS_H
#define _BITS_CRT_IFADDRS_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

struct ifaddrs;
struct sockaddr;

struct ifaddrs {
	struct ifaddrs  *ifa_next;    /* ??? */
	char            *ifa_name;    /* ??? */
	unsigned int     ifa_flags;   /* ??? */
#if __SIZEOF_POINTER__ > 4
	__BYTE_TYPE__ __ifa_pad[__SIZEOF_POINTER__ - 4];
#endif /* __SIZEOF_POINTER__ > 4 */
	struct sockaddr *ifa_addr;    /* ??? */
	struct sockaddr *ifa_netmask; /* ??? */
#undef ifa_broadaddr
#undef ifa_dstaddr
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		union {
			struct sockaddr *ifu_broadaddr; /* ??? */
			struct sockaddr *ifu_dstaddr;   /* ??? */
		} ifa_ifu;
		struct sockaddr *ifa_broadaddr; /* ??? */
		struct sockaddr *ifa_dstaddr;   /* ??? */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	union {
		struct sockaddr *ifu_broadaddr; /* ??? */
		struct sockaddr *ifu_dstaddr;   /* ??? */
	} ifa_ifu;
#define ifa_broadaddr ifa_ifu.ifu_broadaddr
#define ifa_dstaddr   ifa_ifu.ifu_dstaddr
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	void *ifa_data; /* ??? */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_IFADDRS_H */
