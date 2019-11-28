/* HASH CRC-32:0x7a02405c */
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
#ifndef __local_fuzzy_memcmp_defined
#if !defined(__NO_MALLOCA)
#define __local_fuzzy_memcmp_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <parts/malloca.h>
/* Dependency: "memcpyq" from "string" */
#ifndef ____localdep_memcpyq_defined
#define ____localdep_memcpyq_defined 1
#ifdef __fast_memcpyq_defined
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyq (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyq))
#elif defined(__CRT_HAVE_memcpyq)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyq,(/*aligned(8)*/ void *__restrict __dst, /*aligned(8)*/ void const *__restrict __src, __SIZE_TYPE__ __n_qwords),memcpyq,(__dst,__src,__n_qwords))
#else /* LIBC: memcpyq */
#include <local/string/memcpyq.h>
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyq))
#endif /* memcpyq... */
#endif /* !____localdep_memcpyq_defined */

/* Dependency: "memcpyl" from "string" */
#ifndef ____localdep_memcpyl_defined
#define ____localdep_memcpyl_defined 1
#ifdef __fast_memcpyl_defined
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyl (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyl))
#elif defined(__CRT_HAVE_memcpyl)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyl,(/*aligned(4)*/ void *__restrict __dst, /*aligned(4)*/ void const *__restrict __src, __SIZE_TYPE__ __n_dwords),memcpyl,(__dst,__src,__n_dwords))
#elif defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 4)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyl,(/*aligned(4)*/ void *__restrict __dst, /*aligned(4)*/ void const *__restrict __src, __SIZE_TYPE__ __n_dwords),wmemcpy,(__dst,__src,__n_dwords))
#else /* LIBC: memcpyl */
#include <local/string/memcpyl.h>
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyl (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyl))
#endif /* memcpyl... */
#endif /* !____localdep_memcpyl_defined */

/* Dependency: "memcpyw" from "string" */
#ifndef ____localdep_memcpyw_defined
#define ____localdep_memcpyw_defined 1
#ifdef __fast_memcpyw_defined
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyw (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyw))
#elif defined(__CRT_HAVE_memcpyw)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(/*aligned(2)*/ void *__restrict __dst, /*aligned(2)*/ void const *__restrict __src, __SIZE_TYPE__ __n_words),memcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(/*aligned(2)*/ void *__restrict __dst, /*aligned(2)*/ void const *__restrict __src, __SIZE_TYPE__ __n_words),wmemcpy,(__dst,__src,__n_words))
#else /* LIBC: memcpyw */
#include <local/string/memcpyw.h>
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyw (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyw))
#endif /* memcpyw... */
#endif /* !____localdep_memcpyw_defined */

/* Dependency: "memcpy" from "string" */
#ifndef ____localdep_memcpy_defined
#define ____localdep_memcpy_defined 1
#ifdef __fast_memcpy_defined
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* LIBC: memcpy */
#include <local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))
#endif /* memcpy... */
#endif /* !____localdep_memcpy_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fuzzy_memcmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 3)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fuzzy_memcmp))(void const *__s1,
                                                          __SIZE_TYPE__ __s1_bytes,
                                                          void const *__s2,
                                                          __SIZE_TYPE__ __s2_bytes) {
#line 4221 "kos/src/libc/magic/string.c"
	__SIZE_TYPE__ *__v0, *__v1, __i, __j, __cost, __temp;
	if __unlikely(!__s1_bytes)
		return __s2_bytes;
	if __unlikely(!__s2_bytes)
		return __s1_bytes;
	if (__s2_bytes > __s1_bytes) {
		{ void const *__temp = __s1; __s1 = __s2; __s2 = __temp; }
		{ __SIZE_TYPE__ __temp = __s1_bytes; __s1_bytes = __s2_bytes; __s2_bytes = __temp; }
	}
	__malloca_tryhard(__v0, (__s2_bytes+1) * sizeof(__SIZE_TYPE__));
#ifdef __malloca_tryhard_mayfail
	if __unlikely(!__v0)
		return (__SIZE_TYPE__)-1;
#endif /* __malloca_tryhard_mayfail */
	__malloca_tryhard(__v1, (__s2_bytes+1) * sizeof(__SIZE_TYPE__));
#ifdef __malloca_tryhard_mayfail
	if __unlikely(!__v1) {
		__freea(__v0);
		return (__SIZE_TYPE__)-1;
	}
#endif /* __malloca_tryhard_mayfail */
	for (__i = 0; __i < __s2_bytes; ++__i)
		__v0[__i] = __i;
	for (__i = 0; __i < __s1_bytes; ++__i) {
		__v1[0] = __i+1;
		for (__j = 0; __j < __s2_bytes; __j++) {
			__cost  = ((__BYTE_TYPE__ *)__s1)[__i] != ((__BYTE_TYPE__ *)__s2)[__j];
			__cost += __v0[__j];
			__temp  = __v1[__j]+1;
			if (__cost > __temp) __cost = __temp;
			__temp  = __v0[__j+1]+1;
			if (__cost > __temp) __cost = __temp;
			__v1[__j+1] = __cost;
		}
#if __SIZEOF_SIZE_T__ == 8
		__localdep_memcpyq((__UINT64_TYPE__ *)__v0, (__UINT64_TYPE__ *)__v1, __s2_bytes);
#elif __SIZEOF_SIZE_T__ == 4
		__localdep_memcpyl((__UINT32_TYPE__ *)__v0, (__UINT32_TYPE__ *)__v1, __s2_bytes);
#elif __SIZEOF_SIZE_T__ == 2
		__localdep_memcpyw((__UINT16_TYPE__ *)__v0, (__UINT16_TYPE__ *)__v1, __s2_bytes);
#else
		__localdep_memcpy((__UINT8_TYPE__ *)__v0, (__UINT8_TYPE__ *)__v1, __s2_bytes*sizeof(__SIZE_TYPE__));
#endif
	}
	__temp = __v1[__s2_bytes];
	__freea(__v1);
	__freea(__v0);
	return __temp;
}
__NAMESPACE_LOCAL_END
#endif /* !__NO_MALLOCA */
#endif /* !__local_fuzzy_memcmp_defined */
