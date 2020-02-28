/* HASH CRC-32:0x69b178df */
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
#ifndef __local_inet_ntoa_defined
#define __local_inet_ntoa_defined 1
/* Dependency: "inet_ntoa_r" from "arpa.inet" */
#ifndef ____localdep_inet_ntoa_r_defined
#define ____localdep_inet_ntoa_r_defined 1
#ifdef __CRT_HAVE_inet_ntoa_r
/* Re-entrant version of `inet_ntoa()' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((2)),char *,__NOTHROW_NCX,__localdep_inet_ntoa_r,(struct in_addr __inaddr, char __buf[16]),inet_ntoa_r,(__inaddr,__buf))
#else /* LIBC: inet_ntoa_r */
#include <local/arpa.inet/inet_ntoa_r.h>
/* Re-entrant version of `inet_ntoa()' */
#define __localdep_inet_ntoa_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(inet_ntoa_r))
#endif /* inet_ntoa_r... */
#endif /* !____localdep_inet_ntoa_r_defined */

__NAMESPACE_LOCAL_BEGIN
/* Convert Internet number in IN to ASCII representation. The return
 * value is a pointer to an internal array containing the string */
__LOCAL_LIBC(inet_ntoa) __ATTR_RETNONNULL __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(inet_ntoa))(struct in_addr __inaddr) {
#line 134 "kos/src/libc/magic/arpa.inet.c"
	static char __buf[16];
	return __localdep_inet_ntoa_r(__inaddr, __buf);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_inet_ntoa_defined */
