/* HASH CRC-32:0xeed9429a */
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
#ifndef GUARD_LIBC_AUTO_CORECRT_MALLOC_H
#define GUARD_LIBC_AUTO_CORECRT_MALLOC_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_malloc.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(2) ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBDCALL libd__aligned_malloc)(size_t num_bytes, size_t min_alignment);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_ALIGN(2) ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc__aligned_malloc)(size_t num_bytes, size_t min_alignment);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBDCALL libd__aligned_offset_malloc)(size_t num_bytes, size_t min_alignment, size_t offset);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_MALLOC WUNUSED ATTR_ALLOC_SIZE((1)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_malloc)(size_t num_bytes, size_t min_alignment, size_t offset);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_ALLOC_ALIGN(3) ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBDCALL libd__aligned_realloc)(void *aligned_mallptr, size_t newsize, size_t min_alignment);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_ALLOC_ALIGN(3) ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc__aligned_realloc)(void *aligned_mallptr, size_t newsize, size_t min_alignment);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_ALLOC_ALIGN(4) ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBDCALL libd__aligned_recalloc)(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_ALLOC_ALIGN(4) ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBCCALL libc__aligned_recalloc)(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBDCALL libd__aligned_offset_realloc)(void *aligned_mallptr, size_t newsize, size_t min_alignment, size_t offset);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_ALLOC_SIZE((2)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_realloc)(void *aligned_mallptr, size_t newsize, size_t min_alignment, size_t offset);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBDCALL libd__aligned_offset_recalloc)(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment, size_t offset);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_ALLOC_SIZE((2, 3)) void *NOTHROW_NCX(LIBCCALL libc__aligned_offset_recalloc)(void *aligned_mallptr, size_t count, size_t num_bytes, size_t min_alignment, size_t offset);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_PURE WUNUSED size_t NOTHROW_NCX(LIBDCALL libd__aligned_msize)(void *aligned_mallptr, size_t min_alignment, size_t offset);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED size_t NOTHROW_NCX(LIBCCALL libc__aligned_msize)(void *aligned_mallptr, size_t min_alignment, size_t offset);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF void NOTHROW_NCX(LIBDCALL libd__aligned_free)(void *aligned_mallptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF void NOTHROW_NCX(LIBCCALL libc__aligned_free)(void *aligned_mallptr);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CORECRT_MALLOC_H */
