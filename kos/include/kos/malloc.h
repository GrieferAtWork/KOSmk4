/* HASH CRC-32:0x6aeaf289 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_MALLOC_H
#define _KOS_MALLOC_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <malloc.h>

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__CRT_HAVE_Malloc)
/* @throws: E_BADALLOC: ... */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,Malloc,(size_t __n_bytes),(__n_bytes))
#endif /* Malloc... */
#if defined(__CRT_HAVE_Calloc)
/* @throws: E_BADALLOC: ... */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,Calloc,(size_t __count, size_t __n_bytes),(__count,__n_bytes))
#endif /* Calloc... */
#if defined(__CRT_HAVE_Realloc)
/* @throws: E_BADALLOC: ... */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,Realloc,(void *__mallptr, size_t __n_bytes),(__mallptr,__n_bytes))
#endif /* Realloc... */
#if defined(__CRT_HAVE_Memalign)
/* @throws: E_BADALLOC: ... */
__CDECLARE(__ATTR_MALLOC __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)) __ATTR_ALLOC_ALIGN(1),void *,__NOTHROW_NCX,Memalign,(size_t __alignment, size_t __n_bytes),(__alignment,__n_bytes))
#endif /* Memalign... */
#if defined(__CRT_HAVE_PValloc)
/* @throws: E_BADALLOC: ... */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_PAGEALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,PValloc,(size_t __n_bytes),(__n_bytes))
#endif /* PValloc... */
#if defined(__CRT_HAVE_Valloc)
/* @throws: E_BADALLOC: ... */
__CDECLARE(__ATTR_MALL_PAGEALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,Valloc,(size_t __n_bytes),(__n_bytes))
#elif defined(__CRT_HAVE_Memalign)
#include <local/kos.malloc/Valloc.h>
/* @throws: E_BADALLOC: ... */
__NAMESPACE_LOCAL_USING_OR_IMPL(Valloc, __FORCELOCAL __ATTR_MALL_PAGEALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)) void *__NOTHROW_NCX(__LIBCCALL Valloc)(size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Valloc))(__n_bytes); })
#endif /* Valloc... */

#ifdef __USE_KOS
#if defined(__CRT_HAVE_Memdup)
/* @throws: E_BADALLOC: ... */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,Memdup,(void const *__restrict __ptr, size_t __n_bytes),(__ptr,__n_bytes))
#elif defined(__CRT_HAVE_Malloc)
#include <local/kos.malloc/Memdup.h>
/* @throws: E_BADALLOC: ... */
__NAMESPACE_LOCAL_USING_OR_IMPL(Memdup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL Memdup)(void const *__restrict __ptr, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Memdup))(__ptr, __n_bytes); })
#endif /* Memdup... */
#if defined(__CRT_HAVE_Memcdup)
/* @throws: E_BADALLOC: ... */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,Memcdup,(void const *__restrict __ptr, int __needle, size_t __n_bytes),(__ptr,__needle,__n_bytes))
#elif defined(__CRT_HAVE___memcdup)
/* @throws: E_BADALLOC: ... */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,Memcdup,(void const *__restrict __ptr, int __needle, size_t __n_bytes),__memcdup,(__ptr,__needle,__n_bytes))
#elif (defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_posix_memalign) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc)) || (__has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_memdup) || defined(__CRT_HAVE___memdup)
#include <local/kos.malloc/Memcdup.h>
/* @throws: E_BADALLOC: ... */
__NAMESPACE_LOCAL_USING_OR_IMPL(Memcdup, __FORCELOCAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) __ATTR_ALLOC_SIZE((2)) void *__NOTHROW_NCX(__LIBCCALL Memcdup)(void const *__restrict __ptr, int __needle, size_t __n_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Memcdup))(__ptr, __needle, __n_bytes); })
#endif /* Memcdup... */
#endif /* __USE_KOS */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_KOS_MALLOC_H */
