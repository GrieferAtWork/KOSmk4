/* HASH CRC-32:0x784e9d36 */
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
#ifndef __local_memcdup_defined
#define __local_memcdup_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_memdup) || defined(__CRT_HAVE___memdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memchr from string */
#ifndef __local___localdep_memchr_defined
#define __local___localdep_memchr_defined 1
#ifdef __CRT_HAVE_memchr
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__needle,__n_bytes))
#else /* __CRT_HAVE_memchr */
__NAMESPACE_LOCAL_END
#include <local/string/memchr.h>
__NAMESPACE_LOCAL_BEGIN
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memchr __LIBC_LOCAL_NAME(memchr)
#endif /* !__CRT_HAVE_memchr */
#endif /* !__local___localdep_memchr_defined */
/* Dependency: memdup from malloc */
#ifndef __local___localdep_memdup_defined
#define __local___localdep_memdup_defined 1
#ifdef __CRT_HAVE_memdup
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memdup,(void const *__restrict __ptr, __SIZE_TYPE__ __n_bytes),memdup,(__ptr,__n_bytes))
#elif defined(__CRT_HAVE___memdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memdup,(void const *__restrict __ptr, __SIZE_TYPE__ __n_bytes),__memdup,(__ptr,__n_bytes))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <local/malloc/memdup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memdup __LIBC_LOCAL_NAME(memdup)
#else /* ... */
#undef __local___localdep_memdup_defined
#endif /* !... */
#endif /* !__local___localdep_memdup_defined */
__LOCAL_LIBC(memcdup) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memcdup))(void const *__restrict __ptr, int __needle, __SIZE_TYPE__ __n_bytes) {
	if __likely(__n_bytes) {
		void const *__endaddr;
		__endaddr = __localdep_memchr(__ptr, __needle, __n_bytes - 1);
		if (__endaddr)
			__n_bytes = ((__UINTPTR_TYPE__)__endaddr - (__UINTPTR_TYPE__)__ptr) + 1;
	}
	return __localdep_memdup(__ptr, __n_bytes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memcdup_defined
#define __local___localdep_memcdup_defined 1
#define __localdep_memcdup __LIBC_LOCAL_NAME(memcdup)
#endif /* !__local___localdep_memcdup_defined */
#else /* __CRT_HAVE_memdup || __CRT_HAVE___memdup || __CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign */
#undef __local_memcdup_defined
#endif /* !__CRT_HAVE_memdup && !__CRT_HAVE___memdup && !__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign */
#endif /* !__local_memcdup_defined */
