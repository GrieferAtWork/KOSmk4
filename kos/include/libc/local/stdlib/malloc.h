/* HASH CRC-32:0x16e7889c */
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
#ifndef __local_malloc_defined
#define __local_malloc_defined
#include <__crt.h>
#if defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_calloc_defined
#define __local___localdep_crt_calloc_defined
#ifdef __CRT_HAVE_calloc
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_crt_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),calloc,(__count,__num_bytes))
#elif defined(__CRT_HAVE___libc_calloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_crt_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),__libc_calloc,(__count,__num_bytes))
#else /* ... */
#undef __local___localdep_crt_calloc_defined
#endif /* !... */
#endif /* !__local___localdep_crt_calloc_defined */
#ifndef __local___localdep_memalign_defined
#define __local___localdep_memalign_defined
#if __has_builtin(__builtin_aligned_alloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_aligned_alloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_memalign,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),aligned_alloc,{ return __builtin_aligned_alloc(__alignment, __n_bytes); })
#elif defined(__CRT_HAVE_memalign)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_memalign,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_aligned_alloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_memalign,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),aligned_alloc,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE___libc_memalign)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_memalign,(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),__libc_memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/malloc/memalign.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memalign __LIBC_LOCAL_NAME(memalign)
#else /* ... */
#undef __local___localdep_memalign_defined
#endif /* !... */
#endif /* !__local___localdep_memalign_defined */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
__LOCAL_LIBC(malloc) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(malloc))(__SIZE_TYPE__ __num_bytes) {
#if defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc)
	return (__NAMESPACE_LOCAL_SYM __localdep_crt_calloc)(1, __num_bytes);
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
	return (__NAMESPACE_LOCAL_SYM __localdep_realloc)(__NULLPTR, __num_bytes);
#else /* ... */
	return (__NAMESPACE_LOCAL_SYM __localdep_memalign)(__LIBC_MALLOC_ALIGNMENT, __num_bytes);
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_malloc_defined
#define __local___localdep_malloc_defined
#define __localdep_malloc __LIBC_LOCAL_NAME(malloc)
#endif /* !__local___localdep_malloc_defined */
#else /* __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
#undef __local_malloc_defined
#endif /* !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
#endif /* !__local_malloc_defined */
