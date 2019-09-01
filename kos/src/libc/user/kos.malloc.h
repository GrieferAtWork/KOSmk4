/* HASH 0xa0983d28 */
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
#ifndef GUARD_LIBC_USER_KOS_MALLOC_H
#define GUARD_LIBC_USER_KOS_MALLOC_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/malloc.h>

DECL_BEGIN

/* @throws: E_BADALLOC: ... */
INTDEF WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC ATTR_RETNONNULL ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc_Malloc)(size_t n_bytes);
/* @throws: E_BADALLOC: ... */
INTDEF WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC ATTR_RETNONNULL ATTR_ALLOC_SIZE((1, 2)) void *NOTHROW_NCX(LIBCCALL libc_Calloc)(size_t count, size_t n_bytes);
/* @throws: E_BADALLOC: ... */
INTDEF WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_MALLOC ATTR_ALLOC_SIZE((2)) ATTR_RETNONNULL void *NOTHROW_NCX(LIBCCALL libc_Realloc)(void *mallptr, size_t n_bytes);
/* @throws: E_BADALLOC: ... */
INTDEF WUNUSED ATTR_ALLOC_ALIGN(1) ATTR_ALLOC_SIZE((2)) ATTR_MALLOC ATTR_RETNONNULL void *NOTHROW_NCX(LIBCCALL libc_Memalign)(size_t alignment, size_t n_bytes);
/* @throws: E_BADALLOC: ... */
INTDEF WUNUSED ATTR_MALL_PAGEALIGNED ATTR_ALLOC_SIZE((1)) ATTR_MALLOC ATTR_RETNONNULL void *NOTHROW_NCX(LIBCCALL libc_PValloc)(size_t n_bytes);
/* @throws: E_BADALLOC: ... */
INTDEF ATTR_RETNONNULL WUNUSED ATTR_MALL_PAGEALIGNED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc_Valloc)(size_t n_bytes);
/* @throws: E_BADALLOC: ... */
INTDEF WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_ALLOC_SIZE((2)) ATTR_MALLOC ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_Memdup)(void const *__restrict ptr, size_t n_bytes);
/* @throws: E_BADALLOC: ... */
INTDEF WUNUSED ATTR_MALL_DEFAULT_ALIGNED ATTR_ALLOC_SIZE((2)) ATTR_MALLOC ATTR_RETNONNULL NONNULL((1)) void *NOTHROW_NCX(LIBCCALL libc_Memcdup)(void const *__restrict ptr, int needle, size_t n_bytes);

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_MALLOC_H */
