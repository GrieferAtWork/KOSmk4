/* HASH CRC-32:0x522e5313 */
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
#ifndef __local_inet_addr_defined
#define __local_inet_addr_defined
#include <__crt.h>
#include <net/bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_inet_paton_defined
#define __local___localdep_inet_paton_defined
#ifdef __CRT_HAVE_inet_paton
__NAMESPACE_LOCAL_END
#include <netinet/bits/in.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_inet_paton,(char const **__restrict __pcp, struct in_addr *__restrict __inp, int __network_addr),inet_paton,(__pcp,__inp,__network_addr))
#else /* __CRT_HAVE_inet_paton */
__NAMESPACE_LOCAL_END
#include <libc/local/arpa.inet/inet_paton.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_inet_paton __LIBC_LOCAL_NAME(inet_paton)
#endif /* !__CRT_HAVE_inet_paton */
#endif /* !__local___localdep_inet_paton_defined */
__NAMESPACE_LOCAL_END
#include <netinet/in.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(inet_addr) __ATTR_PURE __ATTR_IN(1) __u_net32_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(inet_addr))(char const *__restrict __cp) {
	struct in_addr __addr;
	if (!(__NAMESPACE_LOCAL_SYM __localdep_inet_paton)((char const **)&__cp, &__addr, 0) || *__cp)
		return INADDR_NONE;
	return __addr.s_addr;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_inet_addr_defined
#define __local___localdep_inet_addr_defined
#define __localdep_inet_addr __LIBC_LOCAL_NAME(inet_addr)
#endif /* !__local___localdep_inet_addr_defined */
#endif /* !__local_inet_addr_defined */
