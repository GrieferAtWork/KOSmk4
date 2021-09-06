/* HASH CRC-32:0xca0c38b6 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ether_paton_r_defined
#define __local_ether_paton_r_defined 1
#include <__crt.h>
struct ether_addr;
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isspace_defined
#define __local___localdep_isspace_defined 1
#if __has_builtin(__builtin_isspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,{ return __builtin_isspace(__ch); })
#elif defined(__CRT_HAVE_isspace)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isspace.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isspace __LIBC_LOCAL_NAME(isspace)
#endif /* !... */
#endif /* !__local___localdep_isspace_defined */
__NAMESPACE_LOCAL_END
#include <net/ethernet.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ether_paton_r) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) struct ether_addr *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ether_paton_r))(char const **__restrict __pasc, struct ether_addr *__restrict __addr) {
	unsigned int __i;
	char const *__asc = *__pasc;
	for (__i = 0; __i < 6; ++__i) {
		__UINT8_TYPE__ __octet;
		char __c;
		__c = *__asc++;
		if (__c >= '0' && __c <= '9')
			__octet = __c - '0';
		else if (__c >= 'a' && __c <= 'f')
			__octet = 10 + __c - 'a';
		else if (__c >= 'A' && __c <= 'F')
			__octet = 10 + __c - 'A';
		else {
			return __NULLPTR;
		}
		__c = *__asc++;
		__octet <<= 4;
		if (__c >= '0' && __c <= '9')
			__octet |= __c - '0';
		else if (__c >= 'a' && __c <= 'f')
			__octet |= 10 + __c - 'a';
		else if (__c >= 'A' && __c <= 'F')
			__octet |= 10 + __c - 'A';
		else {
			return __NULLPTR;
		}
		__c = *__asc++;
		if (__c == ':') {
			if (__i >= 5)
				return __NULLPTR;
		} else if (!__c || __localdep_isspace(__c)) {
			if (__i < 5)
				return __NULLPTR;
		} else {
			return __NULLPTR;
		}
		__addr->ether_addr_octet[__i] = __octet;
	}
	*__pasc = __asc;
	return __addr;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ether_paton_r_defined
#define __local___localdep_ether_paton_r_defined 1
#define __localdep_ether_paton_r __LIBC_LOCAL_NAME(ether_paton_r)
#endif /* !__local___localdep_ether_paton_r_defined */
#endif /* !__local_ether_paton_r_defined */
