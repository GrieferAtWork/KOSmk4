/* HASH CRC-32:0xe66e62da */
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
#ifndef _KOS_MALLOC_H
#define _KOS_MALLOC_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <kos/anno.h>

#include <malloc.h>

#ifdef __CC__
__SYSDECL_BEGIN

__CDECLARE_OPT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__THROWING,Malloc,(size_t __num_bytes),(__num_bytes))
__CDECLARE_OPT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__THROWING,Calloc,(size_t __count, size_t __num_bytes),(__count,__num_bytes))
__CDECLARE_OPT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__THROWING,Realloc,(void *__mallptr, size_t __num_bytes),(__mallptr,__num_bytes))
__CDECLARE_OPT(__ATTR_MALLOC __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)),void *,__THROWING,Memalign,(size_t __alignment, size_t __num_bytes),(__alignment,__num_bytes))
__CDECLARE_OPT(__ATTR_MALLOC __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_MALL_PAGEALIGNED __ATTR_ALLOC_SIZE((1)),void *,__THROWING,PValloc,(size_t __num_bytes),(__num_bytes))
#ifdef __CRT_HAVE_Valloc
__CDECLARE(__ATTR_MALLOC __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_MALL_PAGEALIGNED __ATTR_ALLOC_SIZE((1)),void *,__THROWING,Valloc,(size_t __num_bytes),(__num_bytes))
#elif defined(__CRT_HAVE_Memalign)
#include <libc/local/kos.malloc/Valloc.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(Valloc, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_MALL_PAGEALIGNED __ATTR_ALLOC_SIZE((1)) void *(__LIBCCALL Valloc)(size_t __num_bytes) __THROWS(__E_BADALLOC) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Valloc))(__num_bytes); })
#endif /* ... */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_Memdup
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 2) __ATTR_ALLOC_SIZE((2)),void *,__THROWING,Memdup,(void const *__restrict __ptr, size_t __num_bytes),(__ptr,__num_bytes))
#elif defined(__CRT_HAVE_Malloc)
#include <libc/local/kos.malloc/Memdup.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(Memdup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 2) __ATTR_ALLOC_SIZE((2)) void *(__LIBCCALL Memdup)(void const *__restrict __ptr, size_t __num_bytes) __THROWS(__E_BADALLOC) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Memdup))(__ptr, __num_bytes); })
#endif /* ... */
#ifdef __CRT_HAVE_Memcdup
/* @throws: E_BADALLOC: ... */
__CDECLARE(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 3),void *,__THROWING,Memcdup,(void const *__restrict __ptr, int __needle, size_t __num_bytes),(__ptr,__needle,__num_bytes))
#elif defined(__CRT_HAVE_Memdup) || defined(__CRT_HAVE_Malloc)
#include <libc/local/kos.malloc/Memcdup.h>
/* @throws: E_BADALLOC: ... */
__NAMESPACE_LOCAL_USING_OR_IMPL(Memcdup, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ACCESS_ROS(1, 3) void *(__LIBCCALL Memcdup)(void const *__restrict __ptr, int __needle, size_t __num_bytes) __THROWS(__E_BADALLOC) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Memcdup))(__ptr, __needle, __num_bytes); })
#endif /* ... */
#endif /* __USE_KOS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_MALLOC_H */
