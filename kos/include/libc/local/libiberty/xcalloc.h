/* HASH CRC-32:0xe6a59f4 */
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
#ifndef __local_xcalloc_defined
#define __local_xcalloc_defined
#include <__crt.h>
#if defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bzero_defined
#define __local___localdep_bzero_defined
#ifdef __CRT_HAVE_bzero
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzero.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzero __LIBC_LOCAL_NAME(bzero)
#endif /* !... */
#endif /* !__local___localdep_bzero_defined */
#ifndef __local___localdep_calloc_defined
#define __local___localdep_calloc_defined
#if __has_builtin(__builtin_calloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_calloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),calloc,{ return __builtin_calloc(__count, __num_bytes); })
#elif defined(__CRT_HAVE_calloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),calloc,(__count,__num_bytes))
#elif defined(__CRT_HAVE___libc_calloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),__libc_calloc,(__count,__num_bytes))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/calloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_calloc __LIBC_LOCAL_NAME(calloc)
#else /* ... */
#undef __local___localdep_calloc_defined
#endif /* !... */
#endif /* !__local___localdep_calloc_defined */
#if !defined(__local___localdep_crt_xmalloc_defined) && defined(__CRT_HAVE_xmalloc)
#define __local___localdep_crt_xmalloc_defined
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_crt_xmalloc,(__SIZE_TYPE__ __num_bytes),xmalloc,(__num_bytes))
#endif /* !__local___localdep_crt_xmalloc_defined && __CRT_HAVE_xmalloc */
#if !defined(__local___localdep_crt_xrealloc_defined) && defined(__CRT_HAVE_xrealloc)
#define __local___localdep_crt_xrealloc_defined
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_crt_xrealloc,(void *__ptr, __SIZE_TYPE__ __num_bytes),xrealloc,(__ptr,__num_bytes))
#endif /* !__local___localdep_crt_xrealloc_defined && __CRT_HAVE_xrealloc */
#if !defined(__local___localdep_xmalloc_failed_defined) && defined(__CRT_HAVE_xmalloc_failed)
#define __local___localdep_xmalloc_failed_defined
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep_xmalloc_failed,(__SIZE_TYPE__ __num_bytes),xmalloc_failed,(__num_bytes))
#endif /* !__local___localdep_xmalloc_failed_defined && __CRT_HAVE_xmalloc_failed */
__NAMESPACE_LOCAL_END
#include <asm/crt/malloc.h>
#include <hybrid/__overflow.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(xcalloc) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(xcalloc))(__SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) {
#if defined(__CRT_HAVE_xmalloc) || defined(__CRT_HAVE_xrealloc)
	void *__result;
	__SIZE_TYPE__ __total;
	if (__hybrid_overflow_umul(__elem_count, __elem_size, &__total))
		__total = (__SIZE_TYPE__)-1;
#ifdef __CRT_HAVE_xmalloc
	__result = (__NAMESPACE_LOCAL_SYM __localdep_crt_xmalloc)(__total);
#else /* __CRT_HAVE_xmalloc */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_crt_xrealloc)(__NULLPTR, __total);
#endif /* !__CRT_HAVE_xmalloc */
	(__NAMESPACE_LOCAL_SYM __localdep_bzero)(__result, __total);
	return __result;
#else /* __CRT_HAVE_xmalloc || __CRT_HAVE_xrealloc */
	void *__result = (__NAMESPACE_LOCAL_SYM __localdep_calloc)(__elem_count, __elem_size);
	if (__result == __NULLPTR) {
#ifndef __MALLOC_ZERO_IS_NONNULL
		if ((__elem_count != 0 && __elem_size != 0) || ((__result = (__NAMESPACE_LOCAL_SYM __localdep_calloc)(1, 1)) == __NULLPTR))
#endif /* !__MALLOC_ZERO_IS_NONNULL */
		{
			__SIZE_TYPE__ __total;
			if (__hybrid_overflow_umul(__elem_count, __elem_size, &__total))
				__total = (__SIZE_TYPE__)-1;
			(__NAMESPACE_LOCAL_SYM __localdep_xmalloc_failed)(__total);
		}
	}
	return __result;
#endif /* !__CRT_HAVE_xmalloc && !__CRT_HAVE_xrealloc */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_xcalloc_defined
#define __local___localdep_xcalloc_defined
#define __localdep_xcalloc __LIBC_LOCAL_NAME(xcalloc)
#endif /* !__local___localdep_xcalloc_defined */
#else /* __CRT_HAVE_xmalloc || __CRT_HAVE_xrealloc || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_xmalloc_failed) */
#undef __local_xcalloc_defined
#endif /* !__CRT_HAVE_xmalloc && !__CRT_HAVE_xrealloc && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_xmalloc_failed) */
#endif /* !__local_xcalloc_defined */
