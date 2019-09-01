/* HASH 0x77689ec0 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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
ATTR_WEAK ATTR_SECTION(".text.crt.net.convert.ntohl") uint32_t
NOTHROW_NCX(LIBCCALL libc_ntohl)(uint32_t netlong) {
#line 290 "kos/src/libc/magic/netinet.in.c"
	return (uint32_t)__hybrid_beswap32(netlong);
}

#include <hybrid/__byteswap.h>
INTERN ATTR_CONST
ATTR_WEAK ATTR_SECTION(".text.crt.net.convert.ntohs") uint16_t
NOTHROW_NCX(LIBCCALL libc_ntohs)(uint16_t netshort) {
#line 296 "kos/src/libc/magic/netinet.in.c"
	return (uint16_t)__hybrid_beswap16(netshort);
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(ntohl, libc_ntohl);
DEFINE_PUBLIC_WEAK_ALIAS(htonl, libc_ntohl);
DEFINE_PUBLIC_WEAK_ALIAS(ntohs, libc_ntohs);
DEFINE_PUBLIC_WEAK_ALIAS(htons, libc_ntohs);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_NETINET_IN_C */
