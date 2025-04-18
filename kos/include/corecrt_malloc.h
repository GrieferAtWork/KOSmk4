/* HASH CRC-32:0x72c36602 */
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
/* (#) Portability: Windows Kits (/ucrt/corecrt_malloc.h) */
/*!always_includes <crtdefs.h>*/
#ifndef _CORECRT_MALLOC_H
#define _CORECRT_MALLOC_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <crtdefs.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

__NAMESPACE_STD_BEGIN
#ifndef __std_malloc_defined
#define __std_malloc_defined
#ifdef __malloc_defined
__NAMESPACE_GLB_USING_OR_IMPL(malloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL malloc)(size_t __num_bytes) { return :: malloc(__num_bytes); })
#elif __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__CEIDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,malloc,(size_t __num_bytes),{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__CDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,malloc,(size_t __num_bytes),(__num_bytes))
#elif defined(__CRT_HAVE___libc_malloc)
__CREDIRECT_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,malloc,(size_t __num_bytes),__libc_malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_STD_END
#include <libc/local/stdlib/malloc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(malloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL malloc)(size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc))(__num_bytes); })
#else /* ... */
#undef __std_malloc_defined
#endif /* !... */
#endif /* !__std_malloc_defined */
#ifndef __std_calloc_defined
#define __std_calloc_defined
#ifdef __calloc_defined
__NAMESPACE_GLB_USING_OR_IMPL(calloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBCCALL calloc)(size_t __count, size_t __num_bytes) { return :: calloc(__count, __num_bytes); })
#elif __has_builtin(__builtin_calloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_calloc)
__CEIDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,calloc,(size_t __count, size_t __num_bytes),{ return __builtin_calloc(__count, __num_bytes); })
#elif defined(__CRT_HAVE_calloc)
__CDECLARE_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,calloc,(size_t __count, size_t __num_bytes),(__count,__num_bytes))
#elif defined(__CRT_HAVE___libc_calloc)
__CREDIRECT_GCCNCX(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,calloc,(size_t __count, size_t __num_bytes),__libc_calloc,(__count,__num_bytes))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_STD_END
#include <libc/local/stdlib/calloc.h>
__NAMESPACE_STD_BEGIN
__NAMESPACE_LOCAL_USING_OR_IMPL(calloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBCCALL calloc)(size_t __count, size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(calloc))(__count, __num_bytes); })
#else /* ... */
#undef __std_calloc_defined
#endif /* !... */
#endif /* !__std_calloc_defined */
#ifndef __std_realloc_defined
#define __std_realloc_defined
#ifdef __realloc_defined
__NAMESPACE_GLB_USING_OR_IMPL(realloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL realloc)(void *__mallptr, size_t __num_bytes) { return :: realloc(__mallptr, __num_bytes); })
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIDECLARE_GCCNCX(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc,(void *__mallptr, size_t __num_bytes),{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CDECLARE_GCCNCX(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc,(void *__mallptr, size_t __num_bytes),(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__CREDIRECT_GCCNCX(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc,(void *__mallptr, size_t __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __std_realloc_defined
#endif /* !... */
#endif /* !__std_realloc_defined */
#ifndef __std_free_defined
#define __std_free_defined
#ifdef __free_defined
__NAMESPACE_GLB_USING_OR_IMPL(free, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL free)(void *__mallptr) { :: free(__mallptr); })
#elif __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIDECLARE_GCCNCX(,void,__NOTHROW_NCX,free,(void *__mallptr),{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CDECLARE_VOID_GCCNCX(,__NOTHROW_NCX,free,(void *__mallptr),(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID_GCCNCX(,__NOTHROW_NCX,free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID_GCCNCX(,__NOTHROW_NCX,free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __std_free_defined
#endif /* !... */
#endif /* !__std_free_defined */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
#if !defined(__malloc_defined) && defined(__std_malloc_defined)
#define __malloc_defined
__NAMESPACE_STD_USING(malloc)
#endif /* !__malloc_defined && __std_malloc_defined */
#if !defined(__calloc_defined) && defined(__std_calloc_defined)
#define __calloc_defined
__NAMESPACE_STD_USING(calloc)
#endif /* !__calloc_defined && __std_calloc_defined */
#if !defined(__realloc_defined) && defined(__std_realloc_defined)
#define __realloc_defined
__NAMESPACE_STD_USING(realloc)
#endif /* !__realloc_defined && __std_realloc_defined */
#if !defined(__free_defined) && defined(__std_free_defined)
#define __free_defined
__NAMESPACE_STD_USING(free)
#endif /* !__free_defined && __std_free_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __CRT_HAVE_recallocv
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,_recalloc,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),recallocv,(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE__recalloc)
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,_recalloc,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__mallptr,__elem_count,__elem_size))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <libc/local/malloc/recallocv.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL _recalloc)(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recallocv))(__mallptr, __elem_count, __elem_size); }
#endif /* ... */
#ifdef __CRT_HAVE__aligned_malloc
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,_aligned_malloc,(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment),(__num_bytes,__min_alignment))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/corecrt_malloc/_aligned_malloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_malloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(2) __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL _aligned_malloc)(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_malloc))(__num_bytes, __min_alignment); })
#endif /* ... */
#ifdef __CRT_HAVE__aligned_offset_malloc
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,_aligned_offset_malloc,(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),(__num_bytes,__min_alignment,__offset))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/corecrt_malloc/_aligned_offset_malloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_malloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL _aligned_offset_malloc)(__SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_malloc))(__num_bytes, __min_alignment, __offset); })
#endif /* ... */
#ifdef __CRT_HAVE__aligned_realloc
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_ALIGN(3) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,_aligned_realloc,(void *__aligned_mallptr, __SIZE_TYPE__ __newsize, __SIZE_TYPE__ __min_alignment),(__aligned_mallptr,__newsize,__min_alignment))
#elif (defined(__CRT_HAVE__aligned_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))
#include <libc/local/corecrt_malloc/_aligned_realloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_realloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(3) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL _aligned_realloc)(void *__aligned_mallptr, __SIZE_TYPE__ __newsize, __SIZE_TYPE__ __min_alignment) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_realloc))(__aligned_mallptr, __newsize, __min_alignment); })
#endif /* ... */
#ifdef __CRT_HAVE__aligned_recalloc
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_ALIGN(4) __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,_aligned_recalloc,(void *__aligned_mallptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment),(__aligned_mallptr,__count,__num_bytes,__min_alignment))
#elif (defined(__CRT_HAVE__aligned_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))
#include <libc/local/corecrt_malloc/_aligned_recalloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_recalloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(4) __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL _aligned_recalloc)(void *__aligned_mallptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_recalloc))(__aligned_mallptr, __count, __num_bytes, __min_alignment); })
#endif /* ... */
#ifdef __CRT_HAVE__aligned_offset_realloc
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,_aligned_offset_realloc,(void *__aligned_mallptr, __SIZE_TYPE__ __newsize, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),(__aligned_mallptr,__newsize,__min_alignment,__offset))
#elif (defined(__CRT_HAVE__aligned_offset_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))
#include <libc/local/corecrt_malloc/_aligned_offset_realloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_realloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL _aligned_offset_realloc)(void *__aligned_mallptr, __SIZE_TYPE__ __newsize, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_realloc))(__aligned_mallptr, __newsize, __min_alignment, __offset); })
#endif /* ... */
#ifdef __CRT_HAVE__aligned_offset_recalloc
__CDECLARE(__ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,_aligned_offset_recalloc,(void *__aligned_mallptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),(__aligned_mallptr,__count,__num_bytes,__min_alignment,__offset))
#elif (defined(__CRT_HAVE__aligned_offset_malloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && (defined(__CRT_HAVE__aligned_free) || defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))
#include <libc/local/corecrt_malloc/_aligned_offset_recalloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_offset_recalloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL _aligned_offset_recalloc)(void *__aligned_mallptr, __SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_offset_recalloc))(__aligned_mallptr, __count, __num_bytes, __min_alignment, __offset); })
#endif /* ... */
#ifdef __CRT_HAVE__aligned_msize
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,_aligned_msize,(void *__aligned_mallptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset),(__aligned_mallptr,__min_alignment,__offset))
#else /* __CRT_HAVE__aligned_msize */
#include <libc/local/corecrt_malloc/_aligned_msize.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_msize, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL _aligned_msize)(void *__aligned_mallptr, __SIZE_TYPE__ __min_alignment, __SIZE_TYPE__ __offset) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_msize))(__aligned_mallptr, __min_alignment, __offset); })
#endif /* !__CRT_HAVE__aligned_msize */
#ifdef __CRT_HAVE__aligned_free
__CDECLARE_VOID(,__NOTHROW_NCX,_aligned_free,(void *__aligned_mallptr),(__aligned_mallptr))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/corecrt_malloc/_aligned_free.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_aligned_free, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL _aligned_free)(void *__aligned_mallptr) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_aligned_free))(__aligned_mallptr); })
#endif /* ... */
#ifdef __CRT_HAVE_realloc_in_place
/* >> realloc_in_place(3)
 * `realloc_in_place(3)' will return `NULL' if the reallocation isn't
 * possible due to the requested memory above `mallptr' already being
 * in use. However, NULL is also returned (and `errno=ENOMEM' is set)
 * if  insufficient  memory  (for  internal  control  structures)  is
 * available to complete the operation. */
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,_expand,(void *__restrict __mallptr, size_t __n_bytes),realloc_in_place,(__mallptr,__n_bytes))
#elif defined(__CRT_HAVE__expand)
/* >> realloc_in_place(3)
 * `realloc_in_place(3)' will return `NULL' if the reallocation isn't
 * possible due to the requested memory above `mallptr' already being
 * in use. However, NULL is also returned (and `errno=ENOMEM' is set)
 * if  insufficient  memory  (for  internal  control  structures)  is
 * available to complete the operation. */
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,_expand,(void *__restrict __mallptr, size_t __n_bytes),(__mallptr,__n_bytes))
#endif /* ... */
#ifdef __CRT_HAVE_malloc_usable_size
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,size_t,__NOTHROW_NCX,_msize,(void *__restrict __mallptr),malloc_usable_size,(__mallptr))
#elif defined(__CRT_HAVE__msize)
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,size_t,__NOTHROW_NCX,_msize,(void *__restrict __mallptr),(__mallptr))
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_CORECRT_MALLOC_H */
