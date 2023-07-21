/* HASH CRC-32:0xb5bbb5f4 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_xmalloc_defined
#define __local_xmalloc_defined
#include <__crt.h>
#if defined(__CRT_HAVE_xrealloc) || defined(__CRT_HAVE_xcalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_crt_xcalloc_defined) && defined(__CRT_HAVE_xcalloc)
#define __local___localdep_crt_xcalloc_defined
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_crt_xcalloc,(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),xcalloc,(__elem_count,__elem_size))
#endif /* !__local___localdep_crt_xcalloc_defined && __CRT_HAVE_xcalloc */
#if !defined(__local___localdep_crt_xrealloc_defined) && defined(__CRT_HAVE_xrealloc)
#define __local___localdep_crt_xrealloc_defined
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_crt_xrealloc,(void *__ptr, __SIZE_TYPE__ __num_bytes),xrealloc,(__ptr,__num_bytes))
#endif /* !__local___localdep_crt_xrealloc_defined && __CRT_HAVE_xrealloc */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),__libc_malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#else /* ... */
#undef __local___localdep_malloc_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_defined */
#if !defined(__local___localdep_xmalloc_failed_defined) && defined(__CRT_HAVE_xmalloc_failed)
#define __local___localdep_xmalloc_failed_defined
__CREDIRECT_VOID(__ATTR_NORETURN,,__localdep_xmalloc_failed,(__SIZE_TYPE__ __num_bytes),xmalloc_failed,(__num_bytes))
#endif /* !__local___localdep_xmalloc_failed_defined && __CRT_HAVE_xmalloc_failed */
__NAMESPACE_LOCAL_END
#include <asm/crt/malloc.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(xmalloc) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(xmalloc))(__SIZE_TYPE__ __num_bytes) {
#ifdef __CRT_HAVE_xrealloc
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_xrealloc)(__NULLPTR, __num_bytes);
#elif defined(__CRT_HAVE_xcalloc)
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_xcalloc)(1, __num_bytes);
#else /* ... */
	void *__result = (__NAMESPACE_LOCAL_SYM __localdep_malloc)(__num_bytes);
	if (__result == __NULLPTR) {
#ifndef __MALLOC_ZERO_IS_NONNULL
		if (__num_bytes != 0 || ((__result = (__NAMESPACE_LOCAL_SYM __localdep_malloc)(1)) == __NULLPTR))
#endif /* !__MALLOC_ZERO_IS_NONNULL */
		{
			(__NAMESPACE_LOCAL_SYM __localdep_xmalloc_failed)(__num_bytes);
		}
	}
	return __result;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_xmalloc_defined
#define __local___localdep_xmalloc_defined
#define __localdep_xmalloc __LIBC_LOCAL_NAME(xmalloc)
#endif /* !__local___localdep_xmalloc_defined */
#else /* __CRT_HAVE_xrealloc || __CRT_HAVE_xcalloc || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_xmalloc_failed) */
#undef __local_xmalloc_defined
#endif /* !__CRT_HAVE_xrealloc && !__CRT_HAVE_xcalloc && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_xmalloc_failed) */
#endif /* !__local_xmalloc_defined */
