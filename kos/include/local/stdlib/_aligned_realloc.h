/* HASH CRC-32:0xe57dd9b7 */
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
#ifndef __local__aligned_realloc_defined
#if ((defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_malloc)) && ((__has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free)) && 1
#define __local__aligned_realloc_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "_aligned_malloc" from "stdlib" */
#ifndef ____localdep__aligned_malloc_defined
#define ____localdep__aligned_malloc_defined 1
#if defined(__CRT_HAVE__aligned_malloc)
__CREDIRECT(__ATTR_WUNUSED __ATTR_MALLOC __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep__aligned_malloc,(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment),_aligned_malloc,(__num_bytes,__min_alignment))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc)
#include <local/stdlib/_aligned_malloc.h>
#define __localdep__aligned_malloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_malloc))
#else /* CUSTOM: _aligned_malloc */
#undef ____localdep__aligned_malloc_defined
#endif /* _aligned_malloc... */
#endif /* !____localdep__aligned_malloc_defined */

/* Dependency: "_aligned_msize" from "stdlib" */
#ifndef ____localdep__aligned_msize_defined
#define ____localdep__aligned_msize_defined 1
#if defined(__CRT_HAVE__aligned_msize)
__CREDIRECT(__ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep__aligned_msize,(void *__mptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),_aligned_msize,(__mptr,__min_alignment,__offset))
#else /* LIBC: _aligned_msize */
#include <local/stdlib/_aligned_msize.h>
#define __localdep__aligned_msize (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_msize))
#endif /* _aligned_msize... */
#endif /* !____localdep__aligned_msize_defined */

/* Dependency: "memcpy" from "string" */
#ifndef ____localdep_memcpy_defined
#define ____localdep_memcpy_defined 1
#if defined(__fast_memcpy_defined)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* LIBC: memcpy */
#include <local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))
#endif /* memcpy... */
#endif /* !____localdep_memcpy_defined */

/* Dependency: "_aligned_free" from "stdlib" */
#ifndef ____localdep__aligned_free_defined
#define ____localdep__aligned_free_defined 1
#if defined(__CRT_HAVE__aligned_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep__aligned_free,(void *__mptr),_aligned_free,(__mptr))
#elif (__has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
#include <local/stdlib/_aligned_free.h>
#define __localdep__aligned_free (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_free))
#else /* CUSTOM: _aligned_free */
#undef ____localdep__aligned_free_defined
#endif /* _aligned_free... */
#endif /* !____localdep__aligned_free_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_aligned_realloc) __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(3) __ATTR_ALLOC_SIZE((2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_aligned_realloc))(void *__mptr,
                                                              __SIZE_TYPE__ __newsize,
                                                              __SIZE_TYPE__ __min_alignment) {
#line 2353 "kos/src/libc/magic/stdlib.c"
	void *__result;
	__result = __localdep__aligned_malloc(__newsize, __min_alignment);
	if (__result && __mptr) {
		__SIZE_TYPE__ __temp = __localdep__aligned_msize(__mptr, __min_alignment, 0);
		if (__temp > __newsize)
			__temp = __newsize;
		__localdep_memcpy(__result, __mptr, __temp);
		__localdep__aligned_free(__mptr);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* ((defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE__aligned_malloc)) && ((__has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE__aligned_free)) && 1 */
#endif /* !__local__aligned_realloc_defined */
