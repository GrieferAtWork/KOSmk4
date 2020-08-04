/* HASH CRC-32:0xa120cf57 */
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
#ifndef _LIBC_CORE_STDLIB_H
#define _LIBC_CORE_STDLIB_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifndef ____libc_core_malloc_defined
#define ____libc_core_malloc_defined 1
#if __has_builtin(__builtin_malloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_malloc)
#include <hybrid/typecore.h>
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__libc_core_malloc,(__SIZE_TYPE__ __num_bytes),malloc,{ return __builtin_malloc(__num_bytes); })
#elif defined(__CRT_HAVE_malloc)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__NOTHROW_NCX,__libc_core_malloc,(__SIZE_TYPE__ __num_bytes),malloc,(__num_bytes))
#elif defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/stdlib/malloc.h>
#define __libc_core_malloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(malloc))
#else /* ... */
#undef ____libc_core_malloc_defined
#endif /* !... */
#endif /* !____libc_core_malloc_defined */
#ifndef ____libc_core_calloc_defined
#define ____libc_core_calloc_defined 1
#if __has_builtin(__builtin_calloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_calloc)
#include <hybrid/typecore.h>
__CEIREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__libc_core_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),calloc,{ return __builtin_calloc(__count, __num_bytes); })
#elif defined(__CRT_HAVE_calloc)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__NOTHROW_NCX,__libc_core_calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),calloc,(__count,__num_bytes))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE_posix_memalign)
#include <local/stdlib/calloc.h>
#define __libc_core_calloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(calloc))
#else /* ... */
#undef ____libc_core_calloc_defined
#endif /* !... */
#endif /* !____libc_core_calloc_defined */
#ifndef ____libc_core_realloc_defined
#define ____libc_core_realloc_defined 1
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
#include <hybrid/typecore.h>
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__libc_core_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__libc_core_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef ____libc_core_realloc_defined
#endif /* !... */
#endif /* !____libc_core_realloc_defined */
#ifndef ____libc_core_free_defined
#define ____libc_core_free_defined 1
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__libc_core_free,(void *__mallptr),free,{ return __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__libc_core_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__libc_core_free,(void *__mallptr),cfree,(__mallptr))
#else /* ... */
#undef ____libc_core_free_defined
#endif /* !... */
#endif /* !____libc_core_free_defined */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_STDLIB_H */
