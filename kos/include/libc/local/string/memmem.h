/* HASH CRC-32:0xed0348b8 */
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
#ifndef __local_memmem_defined
#define __local_memmem_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bcmp_defined
#define __local___localdep_bcmp_defined
#ifdef __CRT_HAVE_bcmp
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_memcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_bcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bcmp __LIBC_LOCAL_NAME(memcmp)
#endif /* !... */
#endif /* !__local___localdep_bcmp_defined */
#ifndef __local___localdep_memchr_defined
#define __local___localdep_memchr_defined
#ifdef __CRT_HAVE_memchr
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memchr */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memchr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memchr __LIBC_LOCAL_NAME(memchr)
#endif /* !__CRT_HAVE_memchr */
#endif /* !__local___localdep_memchr_defined */
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memmem) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memmem))(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) {
	__BYTE_TYPE__ *__candidate, __marker;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if __unlikely(!__needlelen || __needlelen > __haystacklen)
		return __NULLPTR;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if __unlikely(!__needlelen)
		return (void *)__haystack;
	if __unlikely(__needlelen > __haystacklen)
		return __NULLPTR;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	__haystacklen -= (__needlelen - 1);
	__marker       = *(__BYTE_TYPE__ *)__needle;
	while ((__candidate = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_memchr)(__haystack, __marker, __haystacklen)) != __NULLPTR) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_bcmp)(__candidate, __needle, __needlelen) == 0)
			return (void *)__candidate;
		++__candidate;
		__haystacklen = ((__BYTE_TYPE__ *)__haystack + __haystacklen) - __candidate;
		__haystack    = (void const *)__candidate;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memmem_defined
#define __local___localdep_memmem_defined
#define __localdep_memmem __LIBC_LOCAL_NAME(memmem)
#endif /* !__local___localdep_memmem_defined */
#endif /* !__local_memmem_defined */
