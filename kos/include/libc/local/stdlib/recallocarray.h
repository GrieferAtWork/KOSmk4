/* HASH CRC-32:0x463dc359 */
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
#ifndef __local_recallocarray_defined
#define __local_recallocarray_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_recallocv) || defined(__CRT_HAVE__recalloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_calloc_defined
#define __local___localdep_calloc_defined
#if __has_builtin(__builtin_calloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_calloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),calloc,{ return __builtin_calloc(__count, __num_bytes); })
#elif defined(__CRT_HAVE_calloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__localdep_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),calloc,(__count,__num_bytes))
#elif defined(__CRT_HAVE___libc_calloc)
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
#ifndef __local___localdep_explicit_bzero_defined
#define __local___localdep_explicit_bzero_defined
#ifdef __CRT_HAVE_bzero
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_explicit_bzero,(void *__dst, __SIZE_TYPE__ __n_bytes),bzero,(__dst,__n_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_explicit_bzero,(void *__dst, __SIZE_TYPE__ __n_bytes),explicit_bzero,(__dst,__n_bytes))
#elif defined(__CRT_HAVE___bzero)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_explicit_bzero,(void *__dst, __SIZE_TYPE__ __n_bytes),__bzero,(__dst,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/strings/explicit_bzero.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_explicit_bzero __LIBC_LOCAL_NAME(explicit_bzero)
#endif /* !... */
#endif /* !__local___localdep_explicit_bzero_defined */
#ifndef __local___localdep_freezero_defined
#define __local___localdep_freezero_defined
#ifdef __CRT_HAVE_freezero
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_freezero,(void *__mallptr, __SIZE_TYPE__ __num_bytes),freezero,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/freezero.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_freezero __LIBC_LOCAL_NAME(freezero)
#else /* ... */
#undef __local___localdep_freezero_defined
#endif /* !... */
#endif /* !__local___localdep_freezero_defined */
#ifndef __local___localdep_malloc_usable_size_defined
#define __local___localdep_malloc_usable_size_defined
#ifdef __CRT_HAVE_malloc_usable_size
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),malloc_usable_size,(__mallptr))
#elif defined(__CRT_HAVE__msize)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__localdep_malloc_usable_size,(void *__restrict __mallptr),_msize,(__mallptr))
#else /* ... */
#undef __local___localdep_malloc_usable_size_defined
#endif /* !... */
#endif /* !__local___localdep_malloc_usable_size_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_recallocv_defined
#define __local___localdep_recallocv_defined
#ifdef __CRT_HAVE_recallocv
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,__localdep_recallocv,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),recallocv,(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE__recalloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,__localdep_recallocv,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),_recalloc,(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/malloc/recallocv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_recallocv __LIBC_LOCAL_NAME(recallocv)
#else /* ... */
#undef __local___localdep_recallocv_defined
#endif /* !... */
#endif /* !__local___localdep_recallocv_defined */
__LOCAL_LIBC(recallocarray) __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((3, 4)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(recallocarray))(void *__mallptr, __SIZE_TYPE__ __old_elem_count, __SIZE_TYPE__ __new_elem_count, __SIZE_TYPE__ __elem_size) {
	if (__mallptr != __NULLPTR && __old_elem_count != 0) {
		void *__result;
		__SIZE_TYPE__ __oldusable, __newneeded;
		__oldusable = (__NAMESPACE_LOCAL_SYM __localdep_malloc_usable_size)(__mallptr);
		__newneeded = __new_elem_count * __elem_size;
		if (__oldusable >= __newneeded) {
			if (__old_elem_count > __new_elem_count) {
				__SIZE_TYPE__ __zero_bytes;
				__zero_bytes = (__old_elem_count - __new_elem_count) * __elem_size;
				(__NAMESPACE_LOCAL_SYM __localdep_explicit_bzero)((__BYTE_TYPE__ *)__mallptr + __newneeded, __zero_bytes);
			}
			return __mallptr;
		}
		/* Allocate a new block so we can ensure that  an
		 * existing block gets freezero()'ed in all cases */
		__result = (__NAMESPACE_LOCAL_SYM __localdep_calloc)(__new_elem_count, __elem_size);
		if (__result) {
			if (__oldusable > __newneeded)
				__oldusable = __newneeded;
			(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__result, __mallptr, __oldusable);
			(__NAMESPACE_LOCAL_SYM __localdep_freezero)(__mallptr, __old_elem_count * __elem_size);
		}
		return __result;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_recallocv)(__mallptr, __new_elem_count, __elem_size);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_recallocarray_defined
#define __local___localdep_recallocarray_defined
#define __localdep_recallocarray __LIBC_LOCAL_NAME(recallocarray)
#endif /* !__local___localdep_recallocarray_defined */
#else /* (__CRT_HAVE_recallocv || __CRT_HAVE__recalloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize) */
#undef __local_recallocarray_defined
#endif /* (!__CRT_HAVE_recallocv && !__CRT_HAVE__recalloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_malloc_usable_size && !__CRT_HAVE__msize) */
#endif /* !__local_recallocarray_defined */
