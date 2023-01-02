/* HASH CRC-32:0xd7cae7ee */
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
#ifndef __local_reallocf_defined
#define __local_reallocf_defined
#include <__crt.h>
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <hybrid/typecore.h>
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
__NAMESPACE_LOCAL_END
#include <asm/crt/malloc.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(reallocf) __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(reallocf))(void *__mallptr, __SIZE_TYPE__ __num_bytes) {
	void *__result;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_realloc)(__mallptr, __num_bytes);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#ifdef __REALLOC_ZERO_IS_NONNULL
	if __unlikely(!__result)
#else /* __REALLOC_ZERO_IS_NONNULL */
	/* Must check that num_bytes != 0 because if it isn't
	 * (iow: num_bytes == 0), then realloc(mallptr, 0) may
	 * act  the same as  `free(mallptr)'. If that happens,
	 * then we mustn't double-free `mallptr'.
	 * Note that realloc(<non-NULL>, 0) can't possibly fail
	 * for  lack  of memory  if `__REALLOC_ZERO_IS_NONNULL'
	 * was guessed incorrectly, so we know that the realloc
	 * can only fail when  returning `NULL' for a  non-zero
	 * size argument! */
	if __unlikely(!__result && __num_bytes != 0)
#endif /* !__REALLOC_ZERO_IS_NONNULL */
	{
		(__NAMESPACE_LOCAL_SYM __localdep_free)(__mallptr);
	}
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_reallocf_defined
#define __local___localdep_reallocf_defined
#define __localdep_reallocf __LIBC_LOCAL_NAME(reallocf)
#endif /* !__local___localdep_reallocf_defined */
#else /* __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
#undef __local_reallocf_defined
#endif /* !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
#endif /* !__local_reallocf_defined */
