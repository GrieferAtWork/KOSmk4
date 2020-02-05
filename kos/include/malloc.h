/* HASH CRC-32:0x95fd3fb6 */
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
#ifndef _MALLOC_H
#define _MALLOC_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

__SYSDECL_BEGIN

#ifdef __CRT_KOS
/* malloc behavior attributes. */
#define __MALLOC_ZERO_IS_NONNULL  1
#define __REALLOC_ZERO_IS_NONNULL 1
#endif

#define M_TRIM_THRESHOLD     (-1)
#define M_GRANULARITY        (-2)
#define M_MMAP_THRESHOLD     (-3)

#ifdef __CC__

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __malloc_defined
#define __malloc_defined 1
#ifdef __std_malloc_defined
__NAMESPACE_STD_USING(malloc)
#elif __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
__CEIDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,malloc,(size_t __num_bytes),{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,malloc,(size_t __num_bytes),(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)
#include <local/stdlib/malloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(malloc, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL malloc)(size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc))(__num_bytes); })
#else /* CUSTOM: malloc */
#undef __malloc_defined
#endif /* malloc... */
#endif /* !__malloc_defined */
#ifndef __calloc_defined
#define __calloc_defined 1
#ifdef __std_calloc_defined
__NAMESPACE_STD_USING(calloc)
#elif __has_builtin(__builtin_calloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_calloc)
__CEIDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,calloc,(size_t __count, size_t __num_bytes),{ return __builtin_calloc(__count, __num_bytes); })
#elif defined(__CRT_HAVE_calloc)
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,calloc,(size_t __count, size_t __num_bytes),(__count,__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/stdlib/calloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(calloc, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)) void *__NOTHROW_NCX(__LIBCCALL calloc)(size_t __count, size_t __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(calloc))(__count, __num_bytes); })
#else /* CUSTOM: calloc */
#undef __calloc_defined
#endif /* calloc... */
#endif /* !__calloc_defined */
#ifndef __realloc_defined
#define __realloc_defined 1
#ifdef __std_realloc_defined
__NAMESPACE_STD_USING(realloc)
#elif __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc,(void *__mallptr, size_t __num_bytes),{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc,(void *__mallptr, size_t __num_bytes),(__mallptr,__num_bytes))
#else /* LIBC: realloc */
#undef __realloc_defined
#endif /* realloc... */
#endif /* !__realloc_defined */
#ifndef __free_defined
#define __free_defined 1
#ifdef __std_free_defined
__NAMESPACE_STD_USING(free)
#elif __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIDECLARE(,void,__NOTHROW_NCX,free,(void *__mallptr),{ return __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CDECLARE_VOID(,__NOTHROW_NCX,free,(void *__mallptr),(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,free,(void *__mallptr),cfree,(__mallptr))
#else /* LIBC: free */
#undef __free_defined
#endif /* free... */
#endif /* !__free_defined */
#ifdef __CRT_HAVE_realloc_in_place
/* @EXCEPT: `realloc_in_place()' will return `NULL' if the reallocation isn't
 *           possible due to the requested memory above `MALLPTR' already being
 *           in use. However, an `E_BADALLOC' exception is thrown if insufficient
 *           memory (for internal control structures) is available to complete
 *           the operation */
__CDECLARE(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc_in_place,(void *__restrict __mallptr, size_t __n_bytes),(__mallptr,__n_bytes))
#elif defined(__CRT_HAVE__expand)
/* @EXCEPT: `realloc_in_place()' will return `NULL' if the reallocation isn't
 *           possible due to the requested memory above `MALLPTR' already being
 *           in use. However, an `E_BADALLOC' exception is thrown if insufficient
 *           memory (for internal control structures) is available to complete
 *           the operation */
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,realloc_in_place,(void *__restrict __mallptr, size_t __n_bytes),_expand,(__mallptr,__n_bytes))
#endif /* realloc_in_place... */
#ifdef __CRT_HAVE_posix_memalign
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,crt_posix_memalign,(void **__restrict __pp, size_t __alignment, size_t __n_bytes),posix_memalign,(__pp,__alignment,__n_bytes))
#endif /* crt_posix_memalign... */

#ifdef __CRT_HAVE_memalign
__CDECLARE(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1),void *,__NOTHROW_NCX,memalign,(size_t __alignment, size_t __n_bytes),(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_aligned_alloc)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1),void *,__NOTHROW_NCX,memalign,(size_t __alignment, size_t __n_bytes),aligned_alloc,(__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign)
#include <local/malloc/memalign.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memalign, __FORCELOCAL __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1) void *__NOTHROW_NCX(__LIBCCALL memalign)(size_t __alignment, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memalign))(__alignment, __n_bytes); })
#endif /* memalign... */

#ifdef __CRT_HAVE_pvalloc
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,pvalloc,(size_t __n_bytes),(__n_bytes))
#endif /* pvalloc... */
#ifndef __valloc_defined
#define __valloc_defined 1
#ifdef __CRT_HAVE_valloc
__CDECLARE(__ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,valloc,(__SIZE_TYPE__ __n_bytes),(__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)
#include <local/malloc/valloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(valloc, __FORCELOCAL __ATTR_MALL_PAGEALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL valloc)(__SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(valloc))(__n_bytes); })
#else /* CUSTOM: valloc */
#undef __valloc_defined
#endif /* valloc... */
#endif /* !__valloc_defined */
#ifndef __posix_memalign_defined
#define __posix_memalign_defined 1
#if __has_builtin(__builtin_posix_memalign) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_posix_memalign)
__CEIDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_memalign,(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),{ return __builtin_posix_memalign(__pp, __alignment, __n_bytes); })
#elif defined(__CRT_HAVE_posix_memalign)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_memalign,(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),(__pp,__alignment,__n_bytes))
#elif defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)
#include <local/malloc/posix_memalign.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_memalign, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL posix_memalign)(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_memalign))(__pp, __alignment, __n_bytes); })
#else /* CUSTOM: posix_memalign */
#undef __posix_memalign_defined
#endif /* posix_memalign... */
#endif /* !__posix_memalign_defined */
#ifndef __cfree_defined
#define __cfree_defined 1
#ifdef __CRT_HAVE_free
__CREDIRECT_VOID(,__NOTHROW_NCX,cfree,(void *__restrict __mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CDECLARE_VOID(,__NOTHROW_NCX,cfree,(void *__restrict __mallptr),(__mallptr))
#else /* LIBC: cfree */
#undef __cfree_defined
#endif /* cfree... */
#endif /* !__cfree_defined */

#ifdef __CRT_HAVE_malloc_trim
__CDECLARE(,int,__NOTHROW_NCX,malloc_trim,(size_t __pad),(__pad))
#else /* LIBC: malloc_trim */
#include <local/malloc/malloc_trim.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(malloc_trim, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL malloc_trim)(size_t __pad) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc_trim))(__pad); })
#endif /* malloc_trim... */

#ifdef __CRT_HAVE_malloc_usable_size
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,size_t,__NOTHROW_NCX,malloc_usable_size,(void *__restrict __mallptr),(__mallptr))
#elif defined(__CRT_HAVE__msize)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,size_t,__NOTHROW_NCX,malloc_usable_size,(void *__restrict __mallptr),_msize,(__mallptr))
#endif /* malloc_usable_size... */
#ifdef __CRT_HAVE_mallopt
__CDECLARE(,int,__NOTHROW_NCX,mallopt,(int __parameter_number, int __parameter_value),(__parameter_number,__parameter_value))
#else /* LIBC: mallopt */
#include <local/malloc/mallopt.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mallopt, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL mallopt)(int __parameter_number, int __parameter_value) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mallopt))(__parameter_number, __parameter_value); })
#endif /* mallopt... */
#ifdef __CRT_HAVE___memdup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__memdup,(void const *__restrict __ptr, size_t __n_bytes),(__ptr,__n_bytes))
#elif defined(__CRT_HAVE_memdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__memdup,(void const *__restrict __ptr, size_t __n_bytes),memdup,(__ptr,__n_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/malloc/memdup.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL __memdup)(void const *__restrict __ptr, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memdup))(__ptr, __n_bytes); }
#endif /* __memdup... */
#ifdef __CRT_HAVE___memcdup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__memcdup,(void const *__restrict __ptr, int __needle, size_t __n_bytes),(__ptr,__needle,__n_bytes))
#elif defined(__CRT_HAVE_memcdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__memcdup,(void const *__restrict __ptr, int __needle, size_t __n_bytes),memcdup,(__ptr,__needle,__n_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_memdup) || defined(__CRT_HAVE___memdup)
#include <local/malloc/memcdup.h>
__FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL __memcdup)(void const *__restrict __ptr, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcdup))(__ptr, __needle, __n_bytes); }
#endif /* __memcdup... */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_memdup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memdup,(void const *__restrict __ptr, size_t __n_bytes),(__ptr,__n_bytes))
#elif defined(__CRT_HAVE___memdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memdup,(void const *__restrict __ptr, size_t __n_bytes),__memdup,(__ptr,__n_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc)
#include <local/malloc/memdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memdup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL memdup)(void const *__restrict __ptr, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memdup))(__ptr, __n_bytes); })
#endif /* memdup... */
#ifdef __CRT_HAVE_memcdup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memcdup,(void const *__restrict __ptr, int __needle, size_t __n_bytes),(__ptr,__needle,__n_bytes))
#elif defined(__CRT_HAVE___memcdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,memcdup,(void const *__restrict __ptr, int __needle, size_t __n_bytes),__memcdup,(__ptr,__needle,__n_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_memdup) || defined(__CRT_HAVE___memdup)
#include <local/malloc/memcdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(memcdup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL memcdup)(void const *__restrict __ptr, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcdup))(__ptr, __needle, __n_bytes); })
#endif /* memcdup... */
#endif /* __USE_KOS */
#ifdef __USE_DOS
#ifdef __CRT_HAVE__msize
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,size_t,__NOTHROW_NCX,_msize,(void *__restrict __mallptr),(__mallptr))
#elif defined(__CRT_HAVE_malloc_usable_size)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,size_t,__NOTHROW_NCX,_msize,(void *__restrict __mallptr),malloc_usable_size,(__mallptr))
#endif /* _msize... */
#endif /* __USE_DOS */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_MALLOC_H */
