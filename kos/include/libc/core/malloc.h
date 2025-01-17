/* HASH CRC-32:0x9d5e29c8 */
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
#ifndef _LIBC_CORE_MALLOC_H
#define _LIBC_CORE_MALLOC_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifndef ____libc_core_realloc_in_place_defined
#define ____libc_core_realloc_in_place_defined
#ifdef __CRT_HAVE_realloc_in_place
#include <hybrid/typecore.h>
/* >> realloc_in_place(3)
 * `realloc_in_place(3)' will return `NULL' if the reallocation isn't
 * possible due to the requested memory above `mallptr' already being
 * in use. However, NULL is also returned (and `errno=ENOMEM' is set)
 * if  insufficient  memory  (for  internal  control  structures)  is
 * available to complete the operation. */
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__libc_core_realloc_in_place,(void *__restrict __mallptr, __SIZE_TYPE__ __n_bytes),realloc_in_place,(__mallptr,__n_bytes))
#elif defined(__CRT_HAVE__expand)
#include <hybrid/typecore.h>
/* >> realloc_in_place(3)
 * `realloc_in_place(3)' will return `NULL' if the reallocation isn't
 * possible due to the requested memory above `mallptr' already being
 * in use. However, NULL is also returned (and `errno=ENOMEM' is set)
 * if  insufficient  memory  (for  internal  control  structures)  is
 * available to complete the operation. */
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__libc_core_realloc_in_place,(void *__restrict __mallptr, __SIZE_TYPE__ __n_bytes),_expand,(__mallptr,__n_bytes))
#else /* ... */
#undef ____libc_core_realloc_in_place_defined
#endif /* !... */
#endif /* !____libc_core_realloc_in_place_defined */
#ifndef ____libc_core_malloc_usable_size_defined
#define ____libc_core_malloc_usable_size_defined
#ifdef __CRT_HAVE_malloc_usable_size
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_malloc_usable_size,(void *__restrict __mallptr),malloc_usable_size,(__mallptr))
#elif defined(__CRT_HAVE__msize)
#include <hybrid/typecore.h>
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__SIZE_TYPE__,__NOTHROW_NCX,__libc_core_malloc_usable_size,(void *__restrict __mallptr),_msize,(__mallptr))
#else /* ... */
#undef ____libc_core_malloc_usable_size_defined
#endif /* !... */
#endif /* !____libc_core_malloc_usable_size_defined */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_MALLOC_H */
