/* HASH CRC-32:0xcafa806c */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_inet_ntoa_defined
#define __local_inet_ntoa_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_inet_ntoa_r_defined
#define __local___localdep_inet_ntoa_r_defined
#ifdef __CRT_HAVE_inet_ntoa_r
__NAMESPACE_LOCAL_END
#include <netinet/bits/in.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_RETNONNULL __ATTR_OUT(2),char *,__NOTHROW_NCX,__localdep_inet_ntoa_r,(struct in_addr __inaddr, char __buf[16]),inet_ntoa_r,(__inaddr,__buf))
#else /* __CRT_HAVE_inet_ntoa_r */
__NAMESPACE_LOCAL_END
#include <libc/local/arpa.inet/inet_ntoa_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_inet_ntoa_r __LIBC_LOCAL_NAME(inet_ntoa_r)
#endif /* !__CRT_HAVE_inet_ntoa_r */
#endif /* !__local___localdep_inet_ntoa_r_defined */
__LOCAL_LIBC(inet_ntoa) __ATTR_RETNONNULL __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(inet_ntoa))(struct in_addr __inaddr) {
	static char __buf[16];
	return (__NAMESPACE_LOCAL_SYM __localdep_inet_ntoa_r)(__inaddr, __buf);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_inet_ntoa_defined
#define __local___localdep_inet_ntoa_defined
#define __localdep_inet_ntoa __LIBC_LOCAL_NAME(inet_ntoa)
#endif /* !__local___localdep_inet_ntoa_defined */
#endif /* !__local_inet_ntoa_defined */
