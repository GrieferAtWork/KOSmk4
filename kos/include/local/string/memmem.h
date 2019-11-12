/* HASH CRC-32:0x4d0b8a2f */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_memmem_defined
#define __local_memmem_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memchr" from "string" */
#ifndef ____localdep_memchr_defined
#define ____localdep_memchr_defined 1
#ifdef __fast_memchr_defined
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memchr (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))
#elif defined(__CRT_HAVE_memchr)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__needle,__n_bytes))
#else /* LIBC: memchr */
#include <local/string/memchr.h>
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memchr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))
#endif /* memchr... */
#endif /* !____localdep_memchr_defined */

/* Dependency: "memcmp" from "string" */
#ifndef ____localdep_memcmp_defined
#define ____localdep_memcmp_defined 1
#ifdef __fast_memcmp_defined
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __localdep_memcmp (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcmp))
#elif defined(__CRT_HAVE_memcmp)
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#else /* LIBC: memcmp */
#include <local/string/memcmp.h>
/* Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __localdep_memcmp (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcmp))
#endif /* memcmp... */
#endif /* !____localdep_memcmp_defined */

__NAMESPACE_LOCAL_BEGIN
#include <features.h>
/* Return the first address of a sub-string `needle...+=needlelen' stored within `haystack...+=haystacklen'
 * If no such sub-string exists, return `NULL' instead.
 * #ifdef _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), also return `NULL' unconditionally.
 * #else // _MEMMEM_EMPTY_NEEDLE_NULL_SOURCE
 * When `needlelen' is ZERO(0), re-return `haystack' unconditionally.
 * #endif // !_MEMMEM_EMPTY_NEEDLE_NULL_SOURCE */
__LOCAL_LIBC(memmem) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memmem))(void const *__haystack,
                                                    __SIZE_TYPE__ __haystacklen,
                                                    void const *__needle,
                                                    __SIZE_TYPE__ __needlelen) {
#line 650 "kos/src/libc/magic/string.c"
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
	while ((__candidate = (__BYTE_TYPE__ *)__localdep_memchr(__haystack, __marker, __haystacklen)) != __NULLPTR) {
		if (__localdep_memcmp(__candidate, __needle, __needlelen) == 0)
			return (void *)__candidate;
		++__candidate;
		__haystacklen = ((__BYTE_TYPE__ *)__haystack + __haystacklen) - __candidate;
		__haystack    = (void const *)__candidate;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_memmem_defined */
