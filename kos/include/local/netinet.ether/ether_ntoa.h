/* HASH CRC-32:0xd61dded3 */
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
#ifndef __local_ether_ntoa_defined
#define __local_ether_ntoa_defined 1
#include <__crt.h>
#include <net/ethernet.h>
/* Dependency: "ether_ntoa_r" from "netinet.ether" */
#ifndef ____localdep_ether_ntoa_r_defined
#define ____localdep_ether_ntoa_r_defined 1
#ifdef __CRT_HAVE_ether_ntoa_r
/* Convert 48 bit Ethernet ADDRess to ASCII */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_ether_ntoa_r,(struct ether_addr const *__restrict __addr, char *__restrict __buf),ether_ntoa_r,(__addr,__buf))
#else /* LIBC: ether_ntoa_r */
#include <local/netinet.ether/ether_ntoa_r.h>
/* Convert 48 bit Ethernet ADDRess to ASCII */
#define __localdep_ether_ntoa_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_ntoa_r))
#endif /* ether_ntoa_r... */
#endif /* !____localdep_ether_ntoa_r_defined */

__NAMESPACE_LOCAL_BEGIN
/* Convert 48 bit Ethernet ADDRess to ASCII */
__LOCAL_LIBC(ether_ntoa) __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ether_ntoa))(struct ether_addr const *__restrict __addr) {
#line 54 "kos/src/libc/magic/netinet.ether.c"
	static char __buf[21];
	return __localdep_ether_ntoa_r(__addr, __buf);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_ether_ntoa_defined */
