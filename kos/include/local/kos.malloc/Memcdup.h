/* HASH CRC-32:0xb8f1169 */
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
#ifndef __local_Memcdup_defined
#if defined(__CRT_HAVE_Malloc) || defined(__CRT_HAVE_Memdup)
#define __local_Memcdup_defined 1
#include <__crt.h>
#include <kos/anno.h>
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

/* Dependency: "Memdup" from "kos.malloc" */
#ifndef ____localdep_Memdup_defined
#define ____localdep_Memdup_defined 1
#ifdef __CRT_HAVE_Memdup
/* @throws: E_BADALLOC: ... */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_NONNULL((1)),void *,,__localdep_Memdup,(void const *__restrict __ptr, __SIZE_TYPE__ __num_bytes),Memdup,(__ptr,__num_bytes)) __THROWS(E_BADALLOC)
#elif defined(__CRT_HAVE_Malloc)
#include <local/kos.malloc/Memdup.h>
/* @throws: E_BADALLOC: ... */
#define __localdep_Memdup (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Memdup))
#else /* CUSTOM: Memdup */
#undef ____localdep_Memdup_defined
#endif /* Memdup... */
#endif /* !____localdep_Memdup_defined */

__NAMESPACE_LOCAL_BEGIN
/* @throws: E_BADALLOC: ... */
__LOCAL_LIBC(Memcdup) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
(__LIBCCALL __LIBC_LOCAL_NAME(Memcdup))(void const *__restrict __ptr,
                                        int __needle,
                                        __SIZE_TYPE__ __num_bytes) __THROWS(E_BADALLOC) {
#line 61 "kos/src/libc/magic/kos.malloc.c"
	if __likely(__num_bytes) {
		void const *__endaddr;
		__endaddr = __localdep_memchr(__ptr, __needle, __num_bytes - 1);
		if (__endaddr)
			__num_bytes = ((__UINTPTR_TYPE__)__endaddr - (__UINTPTR_TYPE__)__ptr) + 1;
	}
	return __localdep_Memdup(__ptr, __num_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_Malloc || __CRT_HAVE_Memdup */
#endif /* !__local_Memcdup_defined */
