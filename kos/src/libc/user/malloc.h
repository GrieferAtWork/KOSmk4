/* HASH CRC-32:0x8f1b14e0 */
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
#ifndef GUARD_LIBC_USER_MALLOC_H
#define GUARD_LIBC_USER_MALLOC_H 1

#include "../api.h"
#include "../auto/malloc.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <malloc.h>

DECL_BEGIN

/* @EXCEPT: `realloc_in_place()' will return `NULL' if the reallocation isn't
 *           possible due to the requested memory above `MALLPTR' already being
 *           in use. However, an `E_BADALLOC' exception is thrown if insufficient
 *           memory (for internal control structures) is available to complete
 *           the operation */
INTDEF ATTR_MALL_DEFAULT_ALIGNED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc_realloc_in_place)(void *__restrict mallptr, size_t n_bytes);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_ALLOC_ALIGN(1) void *NOTHROW_NCX(LIBCCALL libc_memalign)(size_t alignment, size_t n_bytes);
INTDEF ATTR_MALLOC ATTR_MALL_PAGEALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc_pvalloc)(size_t n_bytes);
INTDEF ATTR_MALL_PAGEALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc_valloc)(size_t n_bytes);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_posix_memalign)(void **__restrict pp, size_t alignment, size_t n_bytes);
INTDEF void NOTHROW_NCX(LIBCCALL libc_cfree)(void *__restrict mallptr);
INTDEF int NOTHROW_NCX(LIBCCALL libc__heapmin)(void);
INTDEF ATTR_PURE WUNUSED size_t NOTHROW_NCX(LIBCCALL libc_malloc_usable_size)(void *__restrict mallptr);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc_memdup)(void const *__restrict ptr, size_t n_bytes);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED NONNULL((1)) ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc_memcdup)(void const *__restrict ptr, int needle, size_t n_bytes);

DECL_END

#endif /* !GUARD_LIBC_USER_MALLOC_H */
