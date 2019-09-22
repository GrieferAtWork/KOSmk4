/* HASH CRC-32:0xc86ba7cc */
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
#ifndef __local_memcdup_defined
#if ((defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_memdup) || defined(__CRT_HAVE___memdup))
#define __local_memcdup_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "memchr" from "string" */
#ifndef ____localdep_memchr_defined
#define ____localdep_memchr_defined 1
#if defined(__fast_memchr_defined)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memchr (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memchr))
#elif defined(__CRT_HAVE_memchr)
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memchr,(void const *__restrict __haystack, int __needle, __SIZE_TYPE__ __n_bytes),memchr,(__haystack,__needle,__n_bytes))
#else /* LIBC: memchr */
#include <local/string/memchr.h>
/* Ascendingly search for `NEEDLE', starting at `HAYSTACK'. - Return `NULL' if `NEEDLE' wasn't found. */
#define __localdep_memchr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memchr))
#endif /* memchr... */
#endif /* !____localdep_memchr_defined */

/* Dependency: "memdup" from "malloc" */
#ifndef ____localdep_memdup_defined
#define ____localdep_memdup_defined 1
#if defined(__CRT_HAVE_memdup)
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)) __ATTR_MALLOC __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memdup,(void const *__restrict __ptr, __SIZE_TYPE__ __n_bytes),memdup,(__ptr,__n_bytes))
#elif defined(__CRT_HAVE___memdup)
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)) __ATTR_MALLOC __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memdup,(void const *__restrict __ptr, __SIZE_TYPE__ __n_bytes),__memdup,(__ptr,__n_bytes))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc)
#include <local/malloc/memdup.h>
#define __localdep_memdup (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memdup))
#else /* CUSTOM: memdup */
#undef ____localdep_memdup_defined
#endif /* memdup... */
#endif /* !____localdep_memdup_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(memcdup) __ATTR_WUNUSED __ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)) __ATTR_MALLOC __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memcdup))(void const *__restrict __ptr,
                                                     int __needle,
                                                     __SIZE_TYPE__ __n_bytes) {
#line 209 "kos/src/libc/magic/malloc.c"
	if __likely(__n_bytes) {
		void const *__endaddr;
		__endaddr = __localdep_memchr(__ptr, __needle, __n_bytes - 1);
		if (__endaddr)
			__n_bytes = ((__UINTPTR_TYPE__)__endaddr - (__UINTPTR_TYPE__)__ptr) + 1;
	}
	return __localdep_memdup(__ptr, __n_bytes);
}
__NAMESPACE_LOCAL_END
#endif /* ((defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_memdup) || defined(__CRT_HAVE___memdup)) */
#endif /* !__local_memcdup_defined */
