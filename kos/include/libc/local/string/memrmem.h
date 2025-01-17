/* HASH CRC-32:0xc15dc6d7 */
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
#ifndef __local_memrmem_defined
#define __local_memrmem_defined
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
#ifndef __local___localdep_memrchr_defined
#define __local___localdep_memrchr_defined
#ifdef __CRT_HAVE_memrchr
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memrchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memrchr,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memrchr */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memrchr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrchr __LIBC_LOCAL_NAME(memrchr)
#endif /* !__CRT_HAVE_memrchr */
#endif /* !__local___localdep_memrchr_defined */
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memrmem) __ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_INS(3, 4) __ATTR_NONNULL((1, 3)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memrmem))(void const *__haystack, __SIZE_TYPE__ __haystacklen, void const *__needle, __SIZE_TYPE__ __needlelen) {
	__BYTE_TYPE__ *__candidate, __marker;
#if defined(__USE_MEMMEM_EMPTY_NEEDLE_NULL) && !defined(__BUILDING_LIBC)
	if __unlikely(!__needlelen || __needlelen > __haystacklen)
		return __NULLPTR;
#else /* __USE_MEMMEM_EMPTY_NEEDLE_NULL && !__BUILDING_LIBC */
	if __unlikely(!__needlelen)
		return (__BYTE_TYPE__ *)__haystack + __haystacklen;
	if __unlikely(__needlelen > __haystacklen)
		return __NULLPTR;
#endif /* !__USE_MEMMEM_EMPTY_NEEDLE_NULL || __BUILDING_LIBC */
	__haystacklen -= __needlelen - 1;
	__marker = *(__UINT8_TYPE__ const *)__needle;
	while ((__candidate = (__BYTE_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_memrchr)(__haystack, __marker, __haystacklen)) != __NULLPTR) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_bcmp)(__candidate, __needle, __needlelen) == 0)
			return (void *)__candidate;
		__haystacklen = (__SIZE_TYPE__)(__candidate - (__BYTE_TYPE__ *)__haystack);
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memrmem_defined
#define __local___localdep_memrmem_defined
#define __localdep_memrmem __LIBC_LOCAL_NAME(memrmem)
#endif /* !__local___localdep_memrmem_defined */
#endif /* !__local_memrmem_defined */
