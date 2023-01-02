/* HASH CRC-32:0x476f98fa */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
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

#ifndef __KERNEL__
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1)) void *(LIBCCALL libc_Malloc)(size_t num_bytes) THROWS(E_BADALLOC);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((1, 2)) void *(LIBCCALL libc_Calloc)(size_t count, size_t num_bytes) THROWS(E_BADALLOC);
INTDEF ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((2)) void *(LIBCCALL libc_Realloc)(void *mallptr, size_t num_bytes) THROWS(E_BADALLOC);
INTDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED ATTR_ALLOC_ALIGN(1) ATTR_ALLOC_SIZE((2)) void *(LIBCCALL libc_Memalign)(size_t alignment, size_t num_bytes) THROWS(E_BADALLOC);
INTDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED __ATTR_MALL_PAGEALIGNED ATTR_ALLOC_SIZE((1)) void *(LIBCCALL libc_PValloc)(size_t num_bytes) THROWS(E_BADALLOC);
INTDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED __ATTR_MALL_PAGEALIGNED ATTR_ALLOC_SIZE((1)) void *(LIBCCALL libc_Valloc)(size_t num_bytes) THROWS(E_BADALLOC);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INS(1, 2) void *(LIBCCALL libc_Memdup)(void const *__restrict ptr, size_t num_bytes) THROWS(E_BADALLOC);
/* @throws: E_BADALLOC: ... */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED ATTR_RETNONNULL WUNUSED ATTR_INS(1, 3) void *(LIBCCALL libc_Memcdup)(void const *__restrict ptr, int needle, size_t num_bytes) THROWS(E_BADALLOC);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_MALLOC_H */
