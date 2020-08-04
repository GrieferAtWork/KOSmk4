/* HASH CRC-32:0xcd10e6bf */
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
#ifndef __local_recalloc_defined
#define __local_recalloc_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_realloc) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: malloc_usable_size from malloc */
#ifndef __local___localdep_malloc_usable_size_defined
#define __local___localdep_malloc_usable_size_defined 1
#ifdef __CRT_HAVE_malloc_usable_size
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),malloc_usable_size,(__mallptr))
#elif defined(__CRT_HAVE__msize)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),_msize,(__mallptr))
#else /* ... */
#undef __local___localdep_malloc_usable_size_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_usable_size_defined */
/* Dependency: memset from string */
#ifndef __local___localdep_memset_defined
#define __local___localdep_memset_defined 1
#ifdef __CRT_HAVE_memset
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_memset */
__NAMESPACE_LOCAL_END
#include <local/string/memset.h>
__NAMESPACE_LOCAL_BEGIN
/* Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset __LIBC_LOCAL_NAME(memset)
#endif /* !__CRT_HAVE_memset */
#endif /* !__local___localdep_memset_defined */
/* Dependency: realloc from stdlib */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined 1
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#else /* __has_builtin(__builtin_realloc) && __LIBC_BIND_CRTBUILTINS */
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#endif /* !__has_builtin(__builtin_realloc) || !__LIBC_BIND_CRTBUILTINS */
#endif /* !__local___localdep_realloc_defined */
__LOCAL_LIBC(recalloc) __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(recalloc))(void *__mallptr, __SIZE_TYPE__ __num_bytes) {
	void *__result;
	__SIZE_TYPE__ __oldsize;
	__oldsize = __localdep_malloc_usable_size(__mallptr);
	__result  = __localdep_realloc(__mallptr, __num_bytes);
	if __likely(__result) {
		if (__num_bytes > __oldsize)
			__localdep_memset((__BYTE_TYPE__ *)__result + __oldsize, 0, __num_bytes - __oldsize);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_recalloc_defined
#define __local___localdep_recalloc_defined 1
#define __localdep_recalloc __LIBC_LOCAL_NAME(recalloc)
#endif /* !__local___localdep_recalloc_defined */
#else /* __CRT_HAVE_realloc && (__CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize) */
#undef __local_recalloc_defined
#endif /* !__CRT_HAVE_realloc || (!__CRT_HAVE_malloc_usable_size && !__CRT_HAVE__msize) */
#endif /* !__local_recalloc_defined */
