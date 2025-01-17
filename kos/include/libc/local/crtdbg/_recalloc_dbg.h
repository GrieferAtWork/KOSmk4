/* HASH CRC-32:0x9a097687 */
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
#ifndef __local__recalloc_dbg_defined
#define __local__recalloc_dbg_defined
#include <__crt.h>
#if defined(__CRT_HAVE_recallocv) || defined(__CRT_HAVE__recalloc) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize)))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_recallocv_defined
#define __local___localdep_recallocv_defined
#ifdef __CRT_HAVE_recallocv
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,__localdep_recallocv,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),recallocv,(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE__recalloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,__localdep_recallocv,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),_recalloc,(__mallptr,__elem_count,__elem_size))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
__NAMESPACE_LOCAL_END
#include <libc/local/malloc/recallocv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_recallocv __LIBC_LOCAL_NAME(recallocv)
#else /* ... */
#undef __local___localdep_recallocv_defined
#endif /* !... */
#endif /* !__local___localdep_recallocv_defined */
__LOCAL_LIBC(_recalloc_dbg) __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_recalloc_dbg))(void *__ptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, int __block_type, char const *__filename, int __line) {
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return (__NAMESPACE_LOCAL_SYM __localdep_recallocv)(__ptr, __count, __num_bytes);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__recalloc_dbg_defined
#define __local___localdep__recalloc_dbg_defined
#define __localdep__recalloc_dbg __LIBC_LOCAL_NAME(_recalloc_dbg)
#endif /* !__local___localdep__recalloc_dbg_defined */
#else /* __CRT_HAVE_recallocv || __CRT_HAVE__recalloc || ((__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_malloc_usable_size || __CRT_HAVE__msize)) */
#undef __local__recalloc_dbg_defined
#endif /* !__CRT_HAVE_recallocv && !__CRT_HAVE__recalloc && ((!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_malloc_usable_size && !__CRT_HAVE__msize)) */
#endif /* !__local__recalloc_dbg_defined */
