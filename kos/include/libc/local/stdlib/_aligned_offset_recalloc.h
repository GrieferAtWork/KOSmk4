/* HASH CRC-32:0xfde9f7d1 */
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
#ifndef __local__aligned_offset_recalloc_defined
#define __local__aligned_offset_recalloc_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE__aligned_offset_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _aligned_free from stdlib */
#ifndef __local___localdep__aligned_free_defined
#define __local___localdep__aligned_free_defined 1
#ifdef __CRT_HAVE__aligned_free
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep__aligned_free,(void *__aligned_mallptr),_aligned_free,(__aligned_mallptr))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/_aligned_free.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__aligned_free __LIBC_LOCAL_NAME(_aligned_free)
#else /* ... */
#undef __local___localdep__aligned_free_defined
#endif /* !... */
#endif /* !__local___localdep__aligned_free_defined */
/* Dependency: _aligned_msize from stdlib */
#ifndef __local___localdep__aligned_msize_defined
#define __local___localdep__aligned_msize_defined 1
#ifdef __CRT_HAVE__aligned_msize
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep__aligned_msize,(void *__aligned_mallptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),_aligned_msize,(__aligned_mallptr,__min_alignment,__offset))
#else /* __CRT_HAVE__aligned_msize */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/_aligned_msize.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__aligned_msize __LIBC_LOCAL_NAME(_aligned_msize)
#endif /* !__CRT_HAVE__aligned_msize */
#endif /* !__local___localdep__aligned_msize_defined */
/* Dependency: _aligned_offset_malloc from stdlib */
#ifndef __local___localdep__aligned_offset_malloc_defined
#define __local___localdep__aligned_offset_malloc_defined 1
#ifdef __CRT_HAVE__aligned_offset_malloc
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__localdep__aligned_offset_malloc,(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),_aligned_offset_malloc,(__num_bytes,__min_alignment,__offset))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/_aligned_offset_malloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__aligned_offset_malloc __LIBC_LOCAL_NAME(_aligned_offset_malloc)
#else /* ... */
#undef __local___localdep__aligned_offset_malloc_defined
#endif /* !... */
#endif /* !__local___localdep__aligned_offset_malloc_defined */
/* Dependency: memcpy from string */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined 1
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memcpy(3)
 * Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
/* Dependency: memset from string */
#ifndef __local___localdep_memset_defined
#define __local___localdep_memset_defined 1
#ifdef __CRT_HAVE_memset
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_memset */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memset(3)
 * Fill memory with a given byte
 * @return: * : Always re-returns `dst' */
#define __localdep_memset __LIBC_LOCAL_NAME(memset)
#endif /* !__CRT_HAVE_memset */
#endif /* !__local___localdep_memset_defined */
__LOCAL_LIBC(_aligned_offset_recalloc) __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_aligned_offset_recalloc))(void *__aligned_mallptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) {
	void *__result;
	__num_bytes *= __count;
	__result = __localdep__aligned_offset_malloc(__num_bytes, __min_alignment, __offset);
	if (__result) {
		__SIZE_TYPE__ __temp = __localdep__aligned_msize(__aligned_mallptr, __min_alignment, __offset);
		if (__temp > __num_bytes)
			__temp = __num_bytes;
		__localdep_memcpy(__result, __aligned_mallptr, __temp);
		__localdep_memset((__BYTE_TYPE__ *)__result + __temp, 0, __num_bytes - __temp);
		__localdep__aligned_free(__aligned_mallptr);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__aligned_offset_recalloc_defined
#define __local___localdep__aligned_offset_recalloc_defined 1
#define __localdep__aligned_offset_recalloc __LIBC_LOCAL_NAME(_aligned_offset_recalloc)
#endif /* !__local___localdep__aligned_offset_recalloc_defined */
#else /* (__CRT_HAVE__aligned_offset_malloc || __CRT_HAVE_malloc || __CRT_HAVE_calloc || __CRT_HAVE_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE_posix_memalign) && (__CRT_HAVE__aligned_free || __CRT_HAVE_free || __CRT_HAVE_cfree) */
#undef __local__aligned_offset_recalloc_defined
#endif /* (!__CRT_HAVE__aligned_offset_malloc && !__CRT_HAVE_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE__aligned_free && !__CRT_HAVE_free && !__CRT_HAVE_cfree) */
#endif /* !__local__aligned_offset_recalloc_defined */
