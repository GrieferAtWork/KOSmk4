/* HASH CRC-32:0xb1e41d80 */
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
#ifndef __local_memcasemem_defined
#define __local_memcasemem_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: tolower from ctype */
#ifndef __local___localdep_tolower_defined
#define __local___localdep_tolower_defined 1
#if __has_builtin(__builtin_tolower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tolower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,{ return __builtin_tolower(__ch); })
#elif defined(__CRT_HAVE_tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,(__ch))
#elif defined(__CRT_HAVE__tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),_tolower,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/ctype/tolower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower __LIBC_LOCAL_NAME(tolower)
#endif /* !... */
#endif /* !__local___localdep_tolower_defined */
/* Dependency: memcasecmp from string */
#ifndef __local___localdep_memcasecmp_defined
#define __local___localdep_memcasecmp_defined 1
#ifdef __CRT_HAVE_memcasecmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcasecmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memicmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE__memicmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcasecmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),_memicmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memcasecmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcasecmp __LIBC_LOCAL_NAME(memcasecmp)
#endif /* !... */
#endif /* !__local___localdep_memcasecmp_defined */
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * During comprisons, casing of character is ignored (s.a. `memmem()')
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack + haystacklen' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__LOCAL_LIBC(memcasemem) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memcasemem))(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) {
	__BYTE_TYPE__ *__candidate, __marker;
	__BYTE_TYPE__ *__hayend;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if __unlikely(!__needlelen || __needlelen > __haystacklen)
		return __NULLPTR;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if __unlikely(!__needlelen)
		return (__BYTE_TYPE__ *)__haystack + __haystacklen;
	if __unlikely(__needlelen > __haystacklen)
		return __NULLPTR;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	__haystacklen -= (__needlelen - 1);
	__marker       = __localdep_tolower(*(__BYTE_TYPE__ *)__needle);
	__hayend       = (__BYTE_TYPE__ *)__haystack + __haystacklen;
	for (;;) {
		for (__candidate = (__BYTE_TYPE__ *)__haystack; __candidate < __hayend; ++__candidate) {
			__BYTE_TYPE__ __b = *__candidate;
			if (__b == __marker || __localdep_tolower(__b) == __marker)
				goto __got_candidate;
		}
		break;
__got_candidate:
		if (__localdep_memcasecmp(__candidate, __needle, __needlelen) == 0)
			return (void *)__candidate;
		++__candidate;
		__haystacklen = ((__BYTE_TYPE__ *)__haystack + __haystacklen) - __candidate;
		__haystack    = (void const *)__candidate;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memcasemem_defined
#define __local___localdep_memcasemem_defined 1
#define __localdep_memcasemem __LIBC_LOCAL_NAME(memcasemem)
#endif /* !__local___localdep_memcasemem_defined */
#endif /* !__local_memcasemem_defined */
