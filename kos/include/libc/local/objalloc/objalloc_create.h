/* HASH CRC-32:0xe2372b40 */
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
#ifndef __local_objalloc_create_defined
#define __local_objalloc_create_defined
#include <__crt.h>
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <bits/crt/objalloc.h>
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
__LOCAL_LIBC(objalloc_create) struct objalloc *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(objalloc_create))(void) {
	struct objalloc *__result;
	__result = (struct objalloc *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(sizeof(struct objalloc));
	if __likely(__result) {
		struct __objalloc_chunk *__first;
		__first = (struct __objalloc_chunk *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__OBJALLOC_CHUNK_SIZE);
		if __unlikely(__result->chunks == __NULLPTR) {
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
			(__NAMESPACE_LOCAL_SYM __localdep_free)(__result);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
			return __NULLPTR;
		}
		__result->chunks        = __first;
		__first->__oc_prev      = __NULLPTR;
		__first->__oc_curptr    = __NULLPTR;
		__result->current_ptr   = (char *)__first + __OBJALLOC_CHUNK_HEADER_SIZE;
		__result->current_space = __OBJALLOC_CHUNK_SIZE - __OBJALLOC_CHUNK_HEADER_SIZE;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_objalloc_create_defined
#define __local___localdep_objalloc_create_defined
#define __localdep_objalloc_create __LIBC_LOCAL_NAME(objalloc_create)
#endif /* !__local___localdep_objalloc_create_defined */
#else /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
#undef __local_objalloc_create_defined
#endif /* !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
#endif /* !__local_objalloc_create_defined */
