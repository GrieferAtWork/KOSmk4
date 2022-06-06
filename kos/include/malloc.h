/* HASH CRC-32:0xf5985d96 */
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
/* (#) Portability: Cygwin        (/newlib/libc/include/malloc.h) */
/* (#) Portability: DJGPP         (/include/malloc.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/malloc.h) */
/* (#) Portability: FreeBSD       (/include/malloc.h) */
/* (#) Portability: GNU C Library (/malloc/malloc.h) */
/* (#) Portability: MSVC          (/include/malloc.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/malloc.h) */
/* (#) Portability: NetBSD        (/include/malloc.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/malloc.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/malloc.h) */
/* (#) Portability: Windows Kits  (/ucrt/malloc.h) */
/* (#) Portability: diet libc     (/include/malloc.h) */
/* (#) Portability: libc4/5       (/include/malloc.h) */
/* (#) Portability: libc6         (/include/malloc.h) */
/* (#) Portability: mintlib       (/include/malloc.h) */
/* (#) Portability: musl libc     (/include/malloc.h) */
/* (#) Portability: uClibc        (/include/malloc.h) */
#ifndef _MALLOC_H
#define _MALLOC_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/crt/malloc.h>
#include <bits/types.h>
#if defined(__USE_KOS) && defined(__USE_STRING_OVERLOADS)
#include <hybrid/__overflow.h>
#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */
#endif /* __USE_KOS && __USE_STRING_OVERLOADS */


#ifdef __M_TRIM_THRESHOLD
#define M_TRIM_THRESHOLD __M_TRIM_THRESHOLD
#endif /* __M_TRIM_THRESHOLD */
#ifdef __M_GRANULARITY
#define M_GRANULARITY __M_GRANULARITY
#endif /* __M_GRANULARITY */
#ifdef __M_MMAP_THRESHOLD
#define M_MMAP_THRESHOLD __M_MMAP_THRESHOLD
#endif /* __M_MMAP_THRESHOLD */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
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
#ifndef __realloc_in_place_defined
#define __realloc_in_place_defined
#ifdef __CRT_HAVE_realloc_in_place
/* >> realloc_in_place(3)
 * `realloc_in_place(3)' will return `NULL' if the reallocation isn't
 * possible due to the requested memory above `mallptr' already being
 * in use. However, NULL is also returned (and `errno=ENOMEM' is set)
 * if  insufficient  memory  (for  internal  control  structures)  is
 * available to complete the operation. */
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc_in_place,(void *__restrict __mallptr, size_t __n_bytes),(__mallptr,__n_bytes))
#elif defined(__CRT_HAVE__expand)
/* >> realloc_in_place(3)
 * `realloc_in_place(3)' will return `NULL' if the reallocation isn't
 * possible due to the requested memory above `mallptr' already being
 * in use. However, NULL is also returned (and `errno=ENOMEM' is set)
 * if  insufficient  memory  (for  internal  control  structures)  is
 * available to complete the operation. */
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc_in_place,(void *__restrict __mallptr, size_t __n_bytes),_expand,(__mallptr,__n_bytes))
#else /* ... */
#undef __realloc_in_place_defined
#endif /* !... */
#endif /* !__realloc_in_place_defined */
#ifndef __memalign_defined
#define __memalign_defined
#if __has_builtin(__builtin_aligned_alloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_aligned_alloc)
__CEIREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memalign,(size_t __alignment, size_t __n_bytes),aligned_alloc,{ return __builtin_aligned_alloc(__alignment, __n_bytes); })
#elif defined(__CRT_HAVE_memalign)
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memalign,(size_t __alignment, size_t __n_bytes),(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_aligned_alloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memalign,(size_t __alignment, size_t __n_bytes),aligned_alloc,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE___libc_memalign)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memalign,(size_t __alignment, size_t __n_bytes),__libc_memalign,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
#include <libc/local/malloc/memalign.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memalign, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL memalign)(size_t __alignment, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memalign))(__alignment, __n_bytes); })
#else /* ... */
#undef __memalign_defined
#endif /* !... */
#endif /* !__memalign_defined */
__CDECLARE_OPT(__ATTR_MALLOC __ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,pvalloc,(size_t __n_bytes),(__n_bytes))
#ifndef __valloc_defined
#define __valloc_defined
#ifdef __CRT_HAVE_valloc
__CDECLARE(__ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,valloc,(__SIZE_TYPE__ __n_bytes),(__n_bytes))
#elif defined(__CRT_HAVE___libc_valloc)
__CREDIRECT(__ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,valloc,(__SIZE_TYPE__ __n_bytes),__libc_valloc,(__n_bytes))
#elif defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/malloc/valloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(valloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL valloc)(__SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(valloc))(__n_bytes); })
#else /* ... */
#undef __valloc_defined
#endif /* !... */
#endif /* !__valloc_defined */
#ifndef __posix_memalign_defined
#define __posix_memalign_defined
#if __has_builtin(__builtin_posix_memalign) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_posix_memalign)
__CEIDECLARE_GCCNCX(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,posix_memalign,(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),{ return __builtin_posix_memalign(__pp, __alignment, __n_bytes); })
#elif defined(__CRT_HAVE_posix_memalign)
__CDECLARE_GCCNCX(__ATTR_OUT(1),__errno_t,__NOTHROW_NCX,posix_memalign,(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),(__pp,__alignment,__n_bytes))
#elif defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign)
#include <libc/local/malloc/posix_memalign.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_memalign, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_OUT(1) __errno_t __NOTHROW_NCX(__LIBCCALL posix_memalign)(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_memalign))(__pp, __alignment, __n_bytes); })
#else /* ... */
#undef __posix_memalign_defined
#endif /* !... */
#endif /* !__posix_memalign_defined */
#ifndef __cfree_defined
#define __cfree_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,cfree,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,cfree,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CDECLARE_VOID(,__NOTHROW_NCX,cfree,(void *__mallptr),(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,cfree,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __cfree_defined
#endif /* !... */
#endif /* !__cfree_defined */
#ifdef __CRT_HAVE_malloc_trim
__CDECLARE(,int,__NOTHROW_NCX,malloc_trim,(size_t __pad),(__pad))
#else /* __CRT_HAVE_malloc_trim */
#include <libc/local/malloc/malloc_trim.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(malloc_trim, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL malloc_trim)(size_t __pad) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc_trim))(__pad); })
#endif /* !__CRT_HAVE_malloc_trim */
#ifndef __malloc_usable_size_defined
#define __malloc_usable_size_defined
#ifdef __CRT_HAVE_malloc_usable_size
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,size_t,__NOTHROW_NCX,malloc_usable_size,(void *__restrict __mallptr),(__mallptr))
#elif defined(__CRT_HAVE__msize)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,size_t,__NOTHROW_NCX,malloc_usable_size,(void *__restrict __mallptr),_msize,(__mallptr))
#else /* ... */
#undef __malloc_usable_size_defined
#endif /* !... */
#endif /* !__malloc_usable_size_defined */
#ifdef __CRT_HAVE_mallopt
__CDECLARE(,int,__NOTHROW_NCX,mallopt,(int __parameter_number, int __parameter_value),(__parameter_number,__parameter_value))
#else /* __CRT_HAVE_mallopt */
#include <libc/local/malloc/mallopt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mallopt, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL mallopt)(int __parameter_number, int __parameter_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mallopt))(__parameter_number, __parameter_value); })
#endif /* !__CRT_HAVE_mallopt */
#ifdef __CRT_HAVE_memdup
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INS(1, 2),void *,__NOTHROW_NCX,__memdup,(void const *__restrict __ptr, size_t __n_bytes),memdup,(__ptr,__n_bytes))
#elif defined(__CRT_HAVE___memdup)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INS(1, 2),void *,__NOTHROW_NCX,__memdup,(void const *__restrict __ptr, size_t __n_bytes),(__ptr,__n_bytes))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/malloc/memdup.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INS(1, 2) void *__NOTHROW_NCX(__LIBCCALL __memdup)(void const *__restrict __ptr, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memdup))(__ptr, __n_bytes); }
#endif /* ... */
#ifdef __CRT_HAVE_memcdup
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INS(1, 3),void *,__NOTHROW_NCX,__memcdup,(void const *__restrict __ptr, int __needle, size_t __n_bytes),memcdup,(__ptr,__needle,__n_bytes))
#elif defined(__CRT_HAVE___memcdup)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INS(1, 3),void *,__NOTHROW_NCX,__memcdup,(void const *__restrict __ptr, int __needle, size_t __n_bytes),(__ptr,__needle,__n_bytes))
#elif defined(__CRT_HAVE_memdup) || defined(__CRT_HAVE___memdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/malloc/memcdup.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INS(1, 3) void *__NOTHROW_NCX(__LIBCCALL __memcdup)(void const *__restrict __ptr, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcdup))(__ptr, __needle, __n_bytes); }
#endif /* ... */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_memdup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INS(1, 2),void *,__NOTHROW_NCX,memdup,(void const *__restrict __ptr, size_t __n_bytes),(__ptr,__n_bytes))
#elif defined(__CRT_HAVE___memdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INS(1, 2),void *,__NOTHROW_NCX,memdup,(void const *__restrict __ptr, size_t __n_bytes),__memdup,(__ptr,__n_bytes))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/malloc/memdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memdup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INS(1, 2) void *__NOTHROW_NCX(__LIBCCALL memdup)(void const *__restrict __ptr, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memdup))(__ptr, __n_bytes); })
#endif /* ... */
#ifdef __CRT_HAVE_memcdup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INS(1, 3),void *,__NOTHROW_NCX,memcdup,(void const *__restrict __ptr, int __needle, size_t __n_bytes),(__ptr,__needle,__n_bytes))
#elif defined(__CRT_HAVE___memcdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INS(1, 3),void *,__NOTHROW_NCX,memcdup,(void const *__restrict __ptr, int __needle, size_t __n_bytes),__memcdup,(__ptr,__needle,__n_bytes))
#elif defined(__CRT_HAVE_memdup) || defined(__CRT_HAVE___memdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#include <libc/local/malloc/memcdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memcdup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_INS(1, 3) void *__NOTHROW_NCX(__LIBCCALL memcdup)(void const *__restrict __ptr, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcdup))(__ptr, __needle, __n_bytes); })
#endif /* ... */
#ifndef __reallocarray_defined
#define __reallocarray_defined
#ifdef __CRT_HAVE_reallocarray
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocarray,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_reallocarr)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocarray,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarr,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/malloc/reallocarray.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(reallocarray, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL reallocarray)(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocarray))(__ptr, __elem_count, __elem_size); })
#else /* ... */
#undef __reallocarray_defined
#endif /* !... */
#endif /* !__reallocarray_defined */
#ifndef __reallocv_defined
#define __reallocv_defined
#ifdef __CRT_HAVE_reallocarray
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocv,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarray,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_reallocarr)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,reallocv,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarr,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <libc/local/malloc/reallocarray.h>
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL reallocv)(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocarray))(__ptr, __elem_count, __elem_size); }
#else /* ... */
#undef __reallocv_defined
#endif /* !... */
#endif /* !__reallocv_defined */
#ifndef __recalloc_defined
#define __recalloc_defined
#ifdef __CRT_HAVE_recalloc
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,recalloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),(__mallptr,__num_bytes))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <libc/local/malloc/recalloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(recalloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL recalloc)(void *__mallptr, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recalloc))(__mallptr, __num_bytes); })
#else /* ... */
#undef __recalloc_defined
#endif /* !... */
#endif /* !__recalloc_defined */
#ifndef __recallocv_defined
#define __recallocv_defined
#ifdef __CRT_HAVE_recallocv
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,recallocv,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE__recalloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,recallocv,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),_recalloc,(__mallptr,__elem_count,__elem_size))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
#include <libc/local/malloc/recallocv.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(recallocv, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL recallocv)(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recallocv))(__mallptr, __elem_count, __elem_size); })
#else /* ... */
#undef __recallocv_defined
#endif /* !... */
#endif /* !__recallocv_defined */

#ifdef __USE_STRING_OVERLOADS
#ifndef __MALLOC_OVERLOADS_DEFINED
#define __MALLOC_OVERLOADS_DEFINED 1
#ifdef __malloc_defined
__NAMESPACE_LOCAL_BEGIN
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2))
void *__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mallocv))(size_t __elem_count, size_t __elem_size) {
	size_t __total_size;
	if __unlikely(__hybrid_overflow_umul(__elem_count, __elem_size, &__total_size))
		__total_size = (size_t)-1; /* Force down-stream failure */
	return (malloc)(__total_size);
}
__NAMESPACE_LOCAL_END
#endif /* __malloc_defined */
#ifdef __cplusplus
extern "C++" {
#ifdef __malloc_defined
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2))
void *__NOTHROW_NCX(__LIBCCALL malloc)(size_t __elem_count, size_t __elem_size) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mallocv)(__elem_count, __elem_size); }
#endif /* __malloc_defined */
#ifdef __calloc_defined
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1))
void *__NOTHROW_NCX(__LIBCCALL calloc)(size_t __num_bytes) { return (calloc)(1, __num_bytes); }
#endif /* __calloc_defined */
} /* extern "C++" */
extern "C++" {
#ifdef __CRT_HAVE_reallocarray
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,realloc,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarray,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_reallocarr)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,realloc,(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),reallocarr,(__ptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
} /* extern "C++" */
#include <libc/local/malloc/reallocarray.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL realloc)(void *__ptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(reallocarray))(__ptr, __elem_count, __elem_size); }
#endif /* ... */
#ifdef __CRT_HAVE_recallocv
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,recalloc,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),recallocv,(__mallptr,__elem_count,__elem_size))
#elif defined(__CRT_HAVE__recalloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)),void *,__NOTHROW_NCX,recalloc,(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),_recalloc,(__mallptr,__elem_count,__elem_size))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_malloc_usable_size) || defined(__CRT_HAVE__msize))
} /* extern "C++" */
#include <libc/local/malloc/recallocv.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2, 3)) void *__NOTHROW_NCX(__LIBCCALL recalloc)(void *__mallptr, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(recallocv))(__mallptr, __elem_count, __elem_size); }
#endif /* ... */
} /* extern "C++" */
#elif defined(__HYBRID_PP_VA_OVERLOAD)
#ifdef __malloc_defined
#define __PRIVATE_malloc_1 (malloc)
#define __PRIVATE_malloc_2 __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mallocv)
#undef malloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define malloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_malloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define malloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_malloc_, (args))(args)
#endif /* ... */
#endif /* __malloc_defined */
#ifdef __calloc_defined
#define __PRIVATE_calloc_1(num_bytes) (calloc)(1, num_bytes)
#define __PRIVATE_calloc_2            (calloc)
#undef calloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define calloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_calloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define calloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_calloc_, (args))(args)
#endif /* ... */
#endif /* __calloc_defined */
#if defined(__realloc_defined) && defined(__reallocarray_defined)
#define __PRIVATE_realloc_2 (realloc)
#define __PRIVATE_realloc_3 (reallocarray)
#undef realloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define realloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_realloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define realloc(args...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_realloc_, (args))(args)
#endif /* ... */
#endif /* __realloc_defined && __reallocarray_defined */
#if defined(__recalloc_defined) && defined(__recallocv_defined)
#define __PRIVATE_recalloc_2 (recalloc)
#define __PRIVATE_recalloc_3 (recallocv)
#undef recalloc
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define recalloc(...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_recalloc_, (__VA_ARGS__))(__VA_ARGS__)
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define recalloc(aargs...) __HYBRID_PP_VA_OVERLOAD(__PRIVATE_recalloc_, (args))(args)
#endif /* ... */
#endif /* __recalloc_defined && __recallocv_defined */
#endif /* ... */
#endif /* !__MALLOC_OVERLOADS_DEFINED */
#endif /* __USE_STRING_OVERLOADS */
#endif /* __USE_KOS */
#ifdef __clang_tidy__
#ifdef __memalign_defined
#undef memalign
#define memalign(alignment, n_bytes) __builtin_memalign(alignment, n_bytes)
#endif /* __memalign_defined */
#ifdef __pvalloc_defined
#undef pvalloc
#define pvalloc(n_bytes) __builtin_pvalloc(n_bytes)
#endif /* __pvalloc_defined */
#ifdef __valloc_defined
#undef valloc
#define valloc(n_bytes) __builtin_valloc(n_bytes)
#endif /* __valloc_defined */
#ifdef __posix_memalign_defined
#include <asm/os/errno.h>
#undef posix_memalign
#define posix_memalign(pp, alignment, n_bytes) ((*(pp) = __builtin_memalign(alignment, n_bytes)) != 0 ? 0 : __ENOMEM)
#endif /* __posix_memalign_defined */
#if defined(__CRT_HAVE_memdup) || defined(__CRT_HAVE___memdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
#undef memdup
#define memdup(ptr, n_bytes) __builtin_memdup(ptr, n_bytes)
#endif /* __CRT_HAVE_memdup || __CRT_HAVE___memdup || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign */
#ifdef __reallocarray_defined
#undef reallocarray
#define reallocarray(ptr, elem_count, elem_size) __builtin_reallocarray(ptr, elem_count, elem_size)
#undef recallocv
#define recallocv reallocarray
#endif /* __reallocarray_defined */
#ifdef __realloc_defined
#undef recalloc
#define recalloc realloc
#endif /* __realloc_defined */
#endif /* __clang_tidy__ */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_DOS
#include <corecrt_malloc.h>
#endif /* __USE_DOS */

#endif /* !_MALLOC_H */
