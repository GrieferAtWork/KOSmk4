/* HASH CRC-32:0xc9f3b11e */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_NETINET_IN_C
#define GUARD_LIBC_AUTO_NETINET_IN_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/netinet.in.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.net.convert") ATTR_CONST uint16_t
NOTHROW_NCX(LIBCCALL libc_htons)(uint16_t hostword) {
	return (uint16_t)__hybrid_htobe32(hostword);
}
#ifdef __HYBRID_HTOBE_IS_BETOH
DEFINE_INTERN_ALIAS(libc_ntohs, libc_htons);
#else /* __HYBRID_HTOBE_IS_BETOH */
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.net.convert") ATTR_CONST uint16_t
NOTHROW_NCX(LIBCCALL libc_ntohs)(uint16_t netshort) {
	return (uint16_t)__hybrid_betoh16(netshort);
}
#endif /* !__HYBRID_HTOBE_IS_BETOH */
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.net.convert") ATTR_CONST uint32_t
NOTHROW_NCX(LIBCCALL libc_htonl)(uint32_t hostlong) {
	return (uint32_t)__hybrid_htobe32(hostlong);
}
#ifdef __HYBRID_HTOBE_IS_BETOH
DEFINE_INTERN_ALIAS(libc_ntohl, libc_htonl);
#else /* __HYBRID_HTOBE_IS_BETOH */
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.net.convert") ATTR_CONST uint32_t
NOTHROW_NCX(LIBCCALL libc_ntohl)(uint32_t netlong) {
	return (uint32_t)__hybrid_betoh32(netlong);
}
#endif /* !__HYBRID_HTOBE_IS_BETOH */
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.net.convert") ATTR_CONST uint64_t
NOTHROW_NCX(LIBCCALL libc_htonq)(uint64_t hostquad) {
	return (uint64_t)__hybrid_htobe64(hostquad);
}
#ifdef __HYBRID_HTOBE_IS_BETOH
DEFINE_INTERN_ALIAS(libc_ntohq, libc_htonq);
#else /* __HYBRID_HTOBE_IS_BETOH */
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.net.convert") ATTR_CONST uint64_t
NOTHROW_NCX(LIBCCALL libc_ntohq)(uint64_t netquad) {
	return (uint64_t)__hybrid_betoh64(netquad);
}
#endif /* !__HYBRID_HTOBE_IS_BETOH */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(htons, libc_htons);
DEFINE_PUBLIC_WEAK_ALIAS(ntohs, libc_ntohs);
DEFINE_PUBLIC_WEAK_ALIAS(htonl, libc_htonl);
DEFINE_PUBLIC_WEAK_ALIAS(ntohl, libc_ntohl);
DEFINE_PUBLIC_WEAK_ALIAS(htonq, libc_htonq);
DEFINE_PUBLIC_WEAK_ALIAS(ntohq, libc_ntohq);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_NETINET_IN_C */
