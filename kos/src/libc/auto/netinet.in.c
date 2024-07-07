/* HASH CRC-32:0x9a609e9 */
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
#ifndef GUARD_LIBC_AUTO_NETINET_IN_C
#define GUARD_LIBC_AUTO_NETINET_IN_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/netinet.in.h"

DECL_BEGIN

#ifndef __KERNEL__
INTDEF struct in6_addr const libc_in6addr_any;
INTDEF struct in6_addr const libc_in6addr_loopback;
INTERN_CONST ATTR_SECTION(".rodata.crt.net.inet.6") struct in6_addr const libc_in6addr_any = IN6ADDR_ANY_INIT;
INTERN_CONST ATTR_SECTION(".rodata.crt.net.inet.6") struct in6_addr const libc_in6addr_loopback = IN6ADDR_LOOPBACK_INIT;
DEFINE_PUBLIC_ALIAS(in6addr_any, libc_in6addr_any);
DEFINE_PUBLIC_ALIAS(in6addr_loopback, libc_in6addr_loopback);
#endif /* !__KERNEL__ */
#ifndef __KERNEL__
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.net.convert") ATTR_CONST uint16_t
NOTHROW(LIBCCALL libc_htons)(uint16_t hostword) {
	return (uint16_t)__hybrid_htobe32(hostword);
}
#include <hybrid/__byteswap.h>
#ifdef __HYBRID_HTOBE_IS_BETOH
DEFINE_INTERN_ALIAS_P(libc_ntohs,libc_htons,ATTR_CONST,uint16_t,NOTHROW,LIBCCALL,(uint16_t netshort),(netshort));
#else /* __HYBRID_HTOBE_IS_BETOH */
INTERN ATTR_SECTION(".text.crt.net.convert") ATTR_CONST uint16_t
NOTHROW(LIBCCALL libc_ntohs)(uint16_t netshort) {
	return (uint16_t)__hybrid_betoh16(netshort);
}
#endif /* !__HYBRID_HTOBE_IS_BETOH */
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.net.convert") ATTR_CONST uint32_t
NOTHROW(LIBCCALL libc_htonl)(uint32_t hostlong) {
	return (uint32_t)__hybrid_htobe32(hostlong);
}
#include <hybrid/__byteswap.h>
#ifdef __HYBRID_HTOBE_IS_BETOH
DEFINE_INTERN_ALIAS_P(libc_ntohl,libc_htonl,ATTR_CONST,uint32_t,NOTHROW,LIBCCALL,(uint32_t netlong),(netlong));
#else /* __HYBRID_HTOBE_IS_BETOH */
INTERN ATTR_SECTION(".text.crt.net.convert") ATTR_CONST uint32_t
NOTHROW(LIBCCALL libc_ntohl)(uint32_t netlong) {
	return (uint32_t)__hybrid_betoh32(netlong);
}
#endif /* !__HYBRID_HTOBE_IS_BETOH */
#include <hybrid/__byteswap.h>
INTERN ATTR_SECTION(".text.crt.net.convert") ATTR_CONST WUNUSED uint64_t
NOTHROW(LIBCCALL libc_htonq)(uint64_t hostquad) {
	return (uint64_t)__hybrid_htobe64(hostquad);
}
#include <hybrid/__byteswap.h>
#ifdef __HYBRID_HTOBE_IS_BETOH
DEFINE_INTERN_ALIAS_P(libc_ntohq,libc_htonq,ATTR_CONST WUNUSED,uint64_t,NOTHROW,LIBCCALL,(uint64_t netquad),(netquad));
#else /* __HYBRID_HTOBE_IS_BETOH */
INTERN ATTR_SECTION(".text.crt.net.convert") ATTR_CONST WUNUSED uint64_t
NOTHROW(LIBCCALL libc_ntohq)(uint64_t netquad) {
	return (uint64_t)__hybrid_betoh64(netquad);
}
#endif /* !__HYBRID_HTOBE_IS_BETOH */
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(__htons,libc_htons,ATTR_CONST,uint16_t,NOTHROW,LIBCCALL,(uint16_t hostword),(hostword));
DEFINE_PUBLIC_ALIAS_P(htons,libc_htons,ATTR_CONST,uint16_t,NOTHROW,LIBCCALL,(uint16_t hostword),(hostword));
DEFINE_PUBLIC_ALIAS_P(__ntohs,libc_ntohs,ATTR_CONST,uint16_t,NOTHROW,LIBCCALL,(uint16_t netshort),(netshort));
DEFINE_PUBLIC_ALIAS_P(ntohs,libc_ntohs,ATTR_CONST,uint16_t,NOTHROW,LIBCCALL,(uint16_t netshort),(netshort));
DEFINE_PUBLIC_ALIAS_P(__htonl,libc_htonl,ATTR_CONST,uint32_t,NOTHROW,LIBCCALL,(uint32_t hostlong),(hostlong));
DEFINE_PUBLIC_ALIAS_P(htonl,libc_htonl,ATTR_CONST,uint32_t,NOTHROW,LIBCCALL,(uint32_t hostlong),(hostlong));
DEFINE_PUBLIC_ALIAS_P(__ntohl,libc_ntohl,ATTR_CONST,uint32_t,NOTHROW,LIBCCALL,(uint32_t netlong),(netlong));
DEFINE_PUBLIC_ALIAS_P(ntohl,libc_ntohl,ATTR_CONST,uint32_t,NOTHROW,LIBCCALL,(uint32_t netlong),(netlong));
DEFINE_PUBLIC_ALIAS_P(htonq,libc_htonq,ATTR_CONST WUNUSED,uint64_t,NOTHROW,LIBCCALL,(uint64_t hostquad),(hostquad));
DEFINE_PUBLIC_ALIAS_P(ntohq,libc_ntohq,ATTR_CONST WUNUSED,uint64_t,NOTHROW,LIBCCALL,(uint64_t netquad),(netquad));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_NETINET_IN_C */
