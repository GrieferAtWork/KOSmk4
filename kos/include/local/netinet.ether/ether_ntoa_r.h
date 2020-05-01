/* HASH CRC-32:0x65ebbdca */
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
#ifndef __local_ether_ntoa_r_defined
#define __local_ether_ntoa_r_defined 1
#include <__crt.h>
#include <net/ethernet.h>
/* Dependency: "sprintf" from "stdio" */
#ifndef ____localdep_sprintf_defined
#define ____localdep_sprintf_defined 1
#if __has_builtin(__builtin_sprintf) && __has_builtin(__builtin_va_arg_pack) && !defined(__NO_EXTERNINLINE) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_sprintf)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_sprintf,(char *__restrict __buf, char const *__restrict __format, ...),sprintf,{ return __builtin_sprintf(__buf, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_sprintf) && !defined(__NO_ASMNAME)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("sprintf");
#elif defined(__CRT_HAVE__IO_sprintf) && !defined(__NO_ASMNAME)
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
__LIBC __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_sprintf)(char *__restrict __buf, char const *__restrict __format, ...) __CASMNAME("_IO_sprintf");
#else /* LIBC: sprintf */
#include <local/stdio/sprintf.h>
/* Print a formatted string to a given in-member string buffer `BUF'
 * Return the number of written characters, excluding a trailing NUL-character */
#define __localdep_sprintf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sprintf))
#endif /* sprintf... */
#endif /* !____localdep_sprintf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Convert 48 bit Ethernet ADDRess to ASCII */
__LOCAL_LIBC(ether_ntoa_r) __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ether_ntoa_r))(struct ether_addr const *__restrict __addr,
                                                          char *__restrict __buf) {
#line 61 "kos/src/libc/magic/netinet.ether.c"
	__localdep_sprintf(__buf, "%x:%x:%x:%x:%x:%x",
	        __addr->ether_addr_octet[0], __addr->ether_addr_octet[1],
	        __addr->ether_addr_octet[2], __addr->ether_addr_octet[3],
	        __addr->ether_addr_octet[4], __addr->ether_addr_octet[5]);
	return __buf;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_ether_ntoa_r_defined */
