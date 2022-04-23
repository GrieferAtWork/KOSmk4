/* HASH CRC-32:0x10a9d7a3 */
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
#ifndef __local_C_alloca_defined
#define __local_C_alloca_defined
#include <__crt.h>
#if defined(__CRT_HAVE_xmalloc) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed))
__NAMESPACE_LOCAL_BEGIN
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
#ifndef __local___localdep_xmalloc_defined
#define __local___localdep_xmalloc_defined
#ifdef __CRT_HAVE_xmalloc
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep_xmalloc,(__SIZE_TYPE__ __num_bytes),xmalloc,(__num_bytes))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && defined(__CRT_HAVE_xmalloc_failed)
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/xmalloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_xmalloc __LIBC_LOCAL_NAME(xmalloc)
#else /* ... */
#undef __local___localdep_xmalloc_defined
#endif /* !... */
#endif /* !__local___localdep_xmalloc_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/host.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(C_alloca) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(C_alloca))(__SIZE_TYPE__ __num_bytes) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	struct C_alloca_header {
		struct C_alloca_header *__cah_prev; /* [0..1] Previous chunk */
		void                   *__cah_sp;   /* Stack pointer during allocation */
#if (__LIBC_MALLOC_ALIGNMENT % (2 * __SIZEOF_POINTER__)) != 0
		/* Pad to ensure that user-pointers are properly aligned. */
		__BYTE_TYPE__ __cah_ad[__LIBC_MALLOC_ALIGNMENT - (__LIBC_MALLOC_ALIGNMENT % (2 * __SIZEOF_POINTER__))];
#endif /* (__LIBC_MALLOC_ALIGNMENT % (2 * __SIZEOF_POINTER__)) != 0 */
	};

	/* [0..n] Old allocations. */
	static struct C_alloca_header *__old = __NULLPTR;
	struct C_alloca_header *__result;
	void *__sp = &__num_bytes; /* Stack position probe. */

	/* Reclaim old allocations. */
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
	while (__old && __old->__cah_sp < __sp)
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
	while (__old && __old->__cah_sp > __sp)
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
	{
		struct C_alloca_header *__prev;
		__prev = __old->__cah_prev;
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__old);
		__old = __prev;
	}

	/* Special case: C_alloca() must return NULL for 0-byte requests. */
	if (__num_bytes == 0)
		return __NULLPTR;
	__result = (struct C_alloca_header *)(__NAMESPACE_LOCAL_SYM __localdep_xmalloc)(sizeof(struct C_alloca_header) + __num_bytes);

	/* Remember this allocation */
	__result->__cah_sp   = __sp;
	__result->__cah_prev = __old;
	__old = __result;

	/* Return a pointer to the user payload. */
	return (__result + 1);
#else /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	if (__num_bytes == 0)
		return __NULLPTR;
	return (__NAMESPACE_LOCAL_SYM __localdep_xmalloc)(__num_bytes);
#endif /* !__CRT_HAVE_free && !__CRT_HAVE_cfree && !__CRT_HAVE___libc_free */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_C_alloca_defined
#define __local___localdep_C_alloca_defined
#define __localdep_C_alloca __LIBC_LOCAL_NAME(C_alloca)
#endif /* !__local___localdep_C_alloca_defined */
#else /* __CRT_HAVE_xmalloc || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && __CRT_HAVE_xmalloc_failed) */
#undef __local_C_alloca_defined
#endif /* !__CRT_HAVE_xmalloc && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || !__CRT_HAVE_xmalloc_failed) */
#endif /* !__local_C_alloca_defined */
