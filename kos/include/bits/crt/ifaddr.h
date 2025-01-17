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
#ifndef _BITS_CRT_IFADDR_H
#define _BITS_CRT_IFADDR_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/sockaddr.h>

#ifdef __CC__
__DECL_BEGIN

struct iface;
struct ifaddr;

#undef ifa_broadaddr
#undef ifa_dstaddr
struct ifaddr {
	struct sockaddr     ifa_addr; /* ??? */
#ifdef __COMPILER_HAVE_TRANSPARENT_UNION
	union {
		struct sockaddr ifa_broadaddr; /* ??? */
		struct sockaddr ifa_dstaddr;   /* ??? */
#ifndef __USE_KOS_PURE
		union {
			struct sockaddr ifu_broadaddr; /* ??? */
			struct sockaddr ifu_dstaddr;   /* ??? */
		}                   ifa_ifu;
#endif /* !__USE_KOS_PURE */
	};
#else /* __COMPILER_HAVE_TRANSPARENT_UNION */
	union {
		struct sockaddr ifu_broadaddr; /* ??? */
		struct sockaddr ifu_dstaddr;   /* ??? */
	}                   ifa_ifu;
#define ifa_broadaddr ifa_ifu.ifu_broadaddr /* ??? */
#define ifa_dstaddr   ifa_ifu.ifu_dstaddr   /* ??? */
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
	struct iface       *ifa_ifp;  /* ??? */
	struct ifaddr      *ifa_next; /* ??? */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_IFADDR_H */
