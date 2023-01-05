/* HASH CRC-32:0x664eceb1 */
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
#ifndef __local_stravis_defined
#define __local_stravis_defined
#include <__crt.h>
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
#ifndef __local___localdep_strnvisx_defined
#define __local___localdep_strnvisx_defined
#ifdef __CRT_HAVE_strnvisx
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INS(3, 4) __ATTR_OUTS(1, 2),int,__NOTHROW_NCX,__localdep_strnvisx,(char *__dst, __SIZE_TYPE__ __dstsize, char const *__src, __SIZE_TYPE__ __srclen, int __flags),strnvisx,(__dst,__dstsize,__src,__srclen,__flags))
#else /* __CRT_HAVE_strnvisx */
__NAMESPACE_LOCAL_END
#include <libc/local/vis/strnvisx.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strnvisx __LIBC_LOCAL_NAME(strnvisx)
#endif /* !__CRT_HAVE_strnvisx */
#endif /* !__local___localdep_strnvisx_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(stravis) __ATTR_IN_OPT(2) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(stravis))(char **__p_resstr, char const *__src, int __flags) {
	int __result;
	char *__dst;
	__SIZE_TYPE__ __srclen, __dstsize;
	if __unlikely(!__src || *__src) {
		if __unlikely((*__p_resstr = (char *)(__NAMESPACE_LOCAL_SYM __localdep_calloc)(1, sizeof(char))) == __NULLPTR)
			return -1;
		return 0;
	}
	__srclen  = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__src);
	__dstsize = (__srclen * 4) + 1;
	__dst     = (char *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__dstsize);
	if __unlikely(!__dst)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_strnvisx)(__dst, __dstsize, __src, __srclen, __flags);
	if __unlikely(__result == -1) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__dst);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
		return -1;
	}

	/* Free unused trailing memory. */
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
	{
		char *__trimmed_dst;
		__trimmed_dst = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__dst, ((__SIZE_TYPE__)__result + 1) * sizeof(char));
		if __likely(__trimmed_dst)
			__dst = __trimmed_dst;
	}
#endif /* __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
	*__p_resstr = __dst;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_stravis_defined
#define __local___localdep_stravis_defined
#define __localdep_stravis __LIBC_LOCAL_NAME(stravis)
#endif /* !__local___localdep_stravis_defined */
#else /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
#undef __local_stravis_defined
#endif /* !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
#endif /* !__local_stravis_defined */
