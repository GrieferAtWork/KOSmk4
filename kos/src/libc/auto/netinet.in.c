/* HASH CRC-32:0x763c0bee */
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
#include "netinet.in.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <hybrid/__byteswap.h>
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.net.convert.htons") uint16_t
NOTHROW_NCX(LIBCCALL libc_htons)(uint16_t hostword) {
#line 240 "kos/src/libc/magic/netinet.in.c"
	return (uint16_t)__hybrid_htobe32(hostword);
}

#include <hybrid/__byteswap.h>
#if defined(__HYBRID_HTOBE_IS_BETOH)
DEFINE_INTERN_ALIAS(libc_ntohs, libc_htons);
#else
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.net.convert.ntohs") uint16_t
NOTHROW_NCX(LIBCCALL libc_ntohs)(uint16_t netshort) {
#line 246 "kos/src/libc/magic/netinet.in.c"
	return (uint16_t)__hybrid_betoh16(netshort);
}
#endif /* MAGIC:alias */

#include <hybrid/__byteswap.h>
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.net.convert.htonl") uint32_t
NOTHROW_NCX(LIBCCALL libc_htonl)(uint32_t hostlong) {
#line 252 "kos/src/libc/magic/netinet.in.c"
	return (uint32_t)__hybrid_htobe32(hostlong);
}

#include <hybrid/__byteswap.h>
#if defined(__HYBRID_HTOBE_IS_BETOH)
DEFINE_INTERN_ALIAS(libc_ntohl, libc_htonl);
#else
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.net.convert.ntohl") uint32_t
NOTHROW_NCX(LIBCCALL libc_ntohl)(uint32_t netlong) {
#line 258 "kos/src/libc/magic/netinet.in.c"
	return (uint32_t)__hybrid_betoh32(netlong);
}
#endif /* MAGIC:alias */

#include <hybrid/__byteswap.h>
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.net.convert.htonq") uint64_t
NOTHROW_NCX(LIBCCALL libc_htonq)(uint64_t hostlong) {
#line 265 "kos/src/libc/magic/netinet.in.c"
	return (uint64_t)__hybrid_htobe64(hostlong);
}

#include <hybrid/__byteswap.h>
#if defined(__HYBRID_HTOBE_IS_BETOH)
DEFINE_INTERN_ALIAS(libc_ntohq, libc_htonq);
#else
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.net.convert.ntohq") uint64_t
NOTHROW_NCX(LIBCCALL libc_ntohq)(uint64_t netlong) {
#line 271 "kos/src/libc/magic/netinet.in.c"
	return (uint64_t)__hybrid_betoh64(netlong);
}
#endif /* MAGIC:alias */

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(htons, libc_htons);
DEFINE_PUBLIC_WEAK_ALIAS(ntohs, libc_ntohs);
DEFINE_PUBLIC_WEAK_ALIAS(htonl, libc_htonl);
DEFINE_PUBLIC_WEAK_ALIAS(ntohl, libc_ntohl);
DEFINE_PUBLIC_WEAK_ALIAS(htonq, libc_htonq);
DEFINE_PUBLIC_WEAK_ALIAS(ntohq, libc_ntohq);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_NETINET_IN_C */
