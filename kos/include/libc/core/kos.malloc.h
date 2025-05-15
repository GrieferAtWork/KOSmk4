/* HASH CRC-32:0x1dd26b88 */
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
#ifndef _LIBC_CORE_KOS_MALLOC_H
#define _LIBC_CORE_KOS_MALLOC_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#if !defined(____libc_core_Malloc_defined) && defined(__CRT_HAVE_Malloc)
#define ____libc_core_Malloc_defined
#include <kos/anno.h>
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1)),void *,__THROWING(E_BADALLOC),__libc_core_Malloc,(__SIZE_TYPE__ __num_bytes),Malloc,(__num_bytes))
#endif /* !____libc_core_Malloc_defined && __CRT_HAVE_Malloc */
#if !defined(____libc_core_Calloc_defined) && defined(__CRT_HAVE_Calloc)
#define ____libc_core_Calloc_defined
#include <kos/anno.h>
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((1, 2)),void *,__THROWING(E_BADALLOC),__libc_core_Calloc,(__SIZE_TYPE__ __count, __SIZE_TYPE__ __num_bytes),Calloc,(__count,__num_bytes))
#endif /* !____libc_core_Calloc_defined && __CRT_HAVE_Calloc */
#if !defined(____libc_core_Realloc_defined) && defined(__CRT_HAVE_Realloc)
#define ____libc_core_Realloc_defined
#include <kos/anno.h>
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__THROWING(E_BADALLOC),__libc_core_Realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),Realloc,(__mallptr,__num_bytes))
#endif /* !____libc_core_Realloc_defined && __CRT_HAVE_Realloc */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_KOS_MALLOC_H */
