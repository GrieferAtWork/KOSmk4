/* HASH CRC-32:0x1be7b797 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_memcasemem_defined
#define __local_memcasemem_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcasecmp_defined
#define __local___localdep_memcasecmp_defined
#ifdef __CRT_HAVE_memcasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),memcasecmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE_memicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),memicmp,(__s1,__s2,__num_chars))
#elif defined(__CRT_HAVE__memicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __num_chars),_memicmp,(__s1,__s2,__num_chars))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcasecmp __LIBC_LOCAL_NAME(memcasecmp)
#endif /* !... */
#endif /* !__local___localdep_memcasecmp_defined */
#ifndef __local___localdep_tolower_defined
#define __local___localdep_tolower_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_tolower) && defined(__CRT_HAVE_tolower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,{ return __crt_tolower(__ch); })
#elif defined(__crt_tolower)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_tolower)(int __ch) { return __crt_tolower(__ch); }
#elif __has_builtin(__builtin_tolower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tolower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,{ return __builtin_tolower(__ch); })
#elif defined(__CRT_HAVE_tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/tolower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower __LIBC_LOCAL_NAME(tolower)
#endif /* !... */
#endif /* !__local___localdep_tolower_defined */
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memcasemem) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memcasemem))(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) {
	__BYTE_TYPE__ *__candidate, __marker;
	__BYTE_TYPE__ const *__hayend;
	if __unlikely(!__needlelen)
		return (__BYTE_TYPE__ *)__haystack + __haystacklen;
	if __unlikely(__needlelen > __haystacklen)
		return __NULLPTR;
	__haystacklen -= (__needlelen - 1);
	__marker = *(__BYTE_TYPE__ const *)__needle;
	__marker = (__BYTE_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_tolower)(__marker);
	__hayend = (__BYTE_TYPE__ const *)__haystack + __haystacklen;
	for (;;) {
		for (__candidate = (__BYTE_TYPE__ *)__haystack; __candidate < __hayend; ++__candidate) {
			__BYTE_TYPE__ __b = *__candidate;
			if (__b == __marker || (__BYTE_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_tolower)(__b) == __marker)
				goto __got_candidate;
		}
		break;
__got_candidate:
		if ((__NAMESPACE_LOCAL_SYM __localdep_memcasecmp)(__candidate, __needle, __needlelen) == 0)
			return (void *)__candidate;
		++__candidate;
		__haystacklen = ((__BYTE_TYPE__ const *)__haystack + __haystacklen) - __candidate;
		__haystack    = (void const *)__candidate;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memcasemem_defined
#define __local___localdep_memcasemem_defined
#define __localdep_memcasemem __LIBC_LOCAL_NAME(memcasemem)
#endif /* !__local___localdep_memcasemem_defined */
#endif /* !__local_memcasemem_defined */
