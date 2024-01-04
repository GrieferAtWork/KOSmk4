/* HASH CRC-32:0x91ea6020 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
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

#ifndef __KERNEL__
/* >> realloc_in_place(3)
 * `realloc_in_place(3)' will return `NULL' if the reallocation isn't
 * possible due to the requested memory above `mallptr' already being
 * in use. However, NULL is also returned (and `errno=ENOMEM' is set)
 * if  insufficient  memory  (for  internal  control  structures)  is
 * available to complete the operation. */
INTDEF ATTR_MALL_DEFAULT_ALIGNED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc_realloc_in_place)(void *__restrict mallptr, size_t n_bytes);
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(1) ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc_memalign)(size_t alignment, size_t n_bytes);
INTDEF ATTR_MALLOC ATTR_MALL_PAGEALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc_pvalloc)(size_t n_bytes);
INTDEF ATTR_MALL_PAGEALIGNED WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc_valloc)(size_t n_bytes);
INTDEF ATTR_OUT(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_memalign)(void **__restrict pp, size_t alignment, size_t n_bytes);
INTDEF int NOTHROW_NCX(LIBCCALL libc_malloc_trim)(size_t pad);
INTDEF ATTR_PURE WUNUSED size_t NOTHROW_NCX(LIBCCALL libc_malloc_usable_size)(void *__restrict mallptr);
INTDEF int NOTHROW_NCX(LIBCCALL libc_mallopt)(int parameter_number, int parameter_value);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INS(1, 2) void *NOTHROW_NCX(LIBCCALL libc_memdup)(void const *__restrict ptr, size_t n_bytes);
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INS(1, 3) void *NOTHROW_NCX(LIBCCALL libc_memcdup)(void const *__restrict ptr, int needle, size_t n_bytes);
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBCCALL libc_reallocarray)(void *ptr, size_t elem_count, size_t elem_size);
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc_recalloc)(void *mallptr, size_t num_bytes);
INTDEF ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBCCALL libc_recallocv)(void *mallptr, size_t elem_count, size_t elem_size);
INTDEF struct mallinfo NOTHROW_NCX(LIBCCALL libc_mallinfo)(void);
INTDEF struct mallinfo2 NOTHROW_NCX(LIBCCALL libc_mallinfo2)(void);
#endif /* !__KERNEL__ */
#ifdef __clang_tidy__
#define libc_realloc_in_place(mallptr, n_bytes)        __builtin_realloc_in_place(mallptr, n_bytes)
#define libc_memalign(alignment, n_bytes)              __builtin_memalign(alignment, n_bytes)
#define libc_pvalloc(n_bytes)                          __builtin_pvalloc(n_bytes)
#define libc_valloc(n_bytes)                           __builtin_valloc(n_bytes)
#define libc_posix_memalign(pp, alignment, n_bytes)    ((*(pp) = __builtin_memalign(alignment, n_bytes)) != 0 ? 0 : ENOMEM)
#define libc_malloc_usable_size(ptr)                   __builtin_malloc_usable_size(ptr)
#define libc_memdup(ptr, n_bytes)                      __builtin_memdup(ptr, n_bytes)
#define libc_reallocarray(ptr, elem_count, elem_size)  __builtin_reallocarray(ptr, elem_count, elem_size)
#define libc_recalloc(mallptr, num_bytes)              __builtin_recalloc(mallptr, num_bytes)
#define libc_recallocv(mallptr, elem_count, elem_size) __builtin_recallocv(mallptr, elem_count, elem_size)
#endif /* __clang_tidy__ */

DECL_END

#endif /* !GUARD_LIBC_USER_MALLOC_H */
