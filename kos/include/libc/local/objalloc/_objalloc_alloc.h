/* HASH CRC-32:0x4202faa5 */
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
#ifndef __local__objalloc_alloc_defined
#define __local__objalloc_alloc_defined
#include <__crt.h>
#if defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <bits/crt/objalloc.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
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
__LOCAL_LIBC(_objalloc_alloc) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INOUT(1) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_objalloc_alloc))(struct objalloc *__self, __ULONGPTR_TYPE__ __num_bytes) {
	struct __objalloc_chunk *__newchunk;
	__SIZE_TYPE__ __size = (__SIZE_TYPE__)__num_bytes;
	if __unlikely(__size == 0)
		__size = 1;

	/* Force alignment. */
	__size = (__size + __LIBC_MALLOC_ALIGNMENT - 1) & ~(__LIBC_MALLOC_ALIGNMENT - 1);

	/* Check if the current chunk still contains enough space. */
	if (__size <= __self->current_space) {
		void *__result;
__steal_from_current_chunk:
		__result = __self->current_ptr;
		__self->current_ptr += __size;
		__self->current_space -= __size;
		return __result;
	}

	/* Check if we should allocate a dedicated chunk for a large request. */
	if (__size >= __OBJALLOC_BIG_REQUEST) {
		__SIZE_TYPE__ __chunksize = __size + __OBJALLOC_CHUNK_HEADER_SIZE;
		if __unlikely(__chunksize < __num_bytes)
			return __NULLPTR; /* Overflow */
		__newchunk = (struct __objalloc_chunk *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__chunksize);
		if __unlikely(!__newchunk)
			return __NULLPTR;
		__newchunk->__oc_prev   = (struct __objalloc_chunk *)__self->chunks;
		__newchunk->__oc_curptr = __self->current_ptr;
		__self->chunks = __newchunk;
		return (__BYTE_TYPE__ *)__newchunk + __OBJALLOC_CHUNK_HEADER_SIZE;
	}

	/* Allocate a new chunk for "small objects" */
	__newchunk = (struct __objalloc_chunk *)(__NAMESPACE_LOCAL_SYM __localdep_malloc)(__OBJALLOC_CHUNK_SIZE);
	if __unlikely(!__newchunk)
		return __NULLPTR;
	__newchunk->__oc_prev   = (struct __objalloc_chunk *)__self->chunks;
	__newchunk->__oc_curptr = __NULLPTR; /* small-object chunk! */
	__self->current_ptr   = (char *)__newchunk + __OBJALLOC_CHUNK_HEADER_SIZE;
	__self->current_space = __OBJALLOC_CHUNK_SIZE - __OBJALLOC_CHUNK_HEADER_SIZE;
	__self->chunks        = __newchunk;
	goto __steal_from_current_chunk;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__objalloc_alloc_defined
#define __local___localdep__objalloc_alloc_defined
#define __localdep__objalloc_alloc __LIBC_LOCAL_NAME(_objalloc_alloc)
#endif /* !__local___localdep__objalloc_alloc_defined */
#else /* __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
#undef __local__objalloc_alloc_defined
#endif /* !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign */
#endif /* !__local__objalloc_alloc_defined */
