/* HASH CRC-32:0xe662ceec */
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
#ifndef __local__aligned_offset_recalloc_dbg_defined
#define __local__aligned_offset_recalloc_dbg_defined
#include <__crt.h>
#if defined(__CRT_HAVE__aligned_offset_recalloc) || ((defined(__CRT_HAVE__aligned_offset_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__aligned_offset_recalloc_defined
#define __local___localdep__aligned_offset_recalloc_defined
#ifdef __CRT_HAVE__aligned_offset_recalloc
__CREDIRECT(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,__localdep__aligned_offset_recalloc,(void *__aligned_mallptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),_aligned_offset_recalloc,(__aligned_mallptr,__count,__num_bytes,__min_alignment,__offset))
#elif (defined(__CRT_HAVE__aligned_offset_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_malloc/_aligned_offset_recalloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__aligned_offset_recalloc __LIBC_LOCAL_NAME(_aligned_offset_recalloc)
#else /* ... */
#undef __local___localdep__aligned_offset_recalloc_defined
#endif /* !... */
#endif /* !__local___localdep__aligned_offset_recalloc_defined */
__LOCAL_LIBC(_aligned_offset_recalloc_dbg) __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_aligned_offset_recalloc_dbg))(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset, char const *__filename, int __line) {
	(void)__filename;
	(void)__line;
	return (__NAMESPACE_LOCAL_SYM __localdep__aligned_offset_recalloc)(__ptr, __count, __num_bytes, __min_alignment, __offset);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__aligned_offset_recalloc_dbg_defined
#define __local___localdep__aligned_offset_recalloc_dbg_defined
#define __localdep__aligned_offset_recalloc_dbg __LIBC_LOCAL_NAME(_aligned_offset_recalloc_dbg)
#endif /* !__local___localdep__aligned_offset_recalloc_dbg_defined */
#else /* __CRT_HAVE__aligned_offset_recalloc || ((__CRT_HAVE__aligned_offset_malloc || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && (__CRT_HAVE__aligned_free || __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free)) */
#undef __local__aligned_offset_recalloc_dbg_defined
#endif /* !__CRT_HAVE__aligned_offset_recalloc && ((!__CRT_HAVE__aligned_offset_malloc && !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE__aligned_free && !__CRT_HAVE_free && !__CRT_HAVE_cfree && !__CRT_HAVE___libc_free)) */
#endif /* !__local__aligned_offset_recalloc_dbg_defined */
