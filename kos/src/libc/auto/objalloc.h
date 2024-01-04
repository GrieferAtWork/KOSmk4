/* HASH CRC-32:0x9cd8ef7b */
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
#ifndef GUARD_LIBC_AUTO_OBJALLOC_H
#define GUARD_LIBC_AUTO_OBJALLOC_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <objalloc.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> objalloc_create(3)
 * Allocate and initialize a new objalloc object.
 * @return: * :   The new objalloc object
 * @return: NULL: Out of memory */
INTDEF struct objalloc *NOTHROW_NCX(LIBCCALL libc_objalloc_create)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> _objalloc_alloc(3)
 * Allocate `num_bytes' of memory from `self'
 * @return: * :   The `num_bytes'-large data-blob
 * @return: NULL: Out of memory */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INOUT(1) void *NOTHROW_NCX(LIBDCALL libd__objalloc_alloc)(struct objalloc *self, __ULONGPTR_TYPE__ num_bytes);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> _objalloc_alloc(3)
 * Allocate `num_bytes' of memory from `self'
 * @return: * :   The `num_bytes'-large data-blob
 * @return: NULL: Out of memory */
INTDEF ATTR_MALLOC ATTR_MALL_DEFAULT_ALIGNED WUNUSED ATTR_ALLOC_SIZE((2)) ATTR_INOUT(1) void *NOTHROW_NCX(LIBCCALL libc__objalloc_alloc)(struct objalloc *self, __ULONGPTR_TYPE__ num_bytes);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> objalloc_free(3)
 * Free all memory allocated by `self', before also freeing `self' */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBDCALL libd_objalloc_free)(struct objalloc *self);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> objalloc_free(3)
 * Free all memory allocated by `self', before also freeing `self' */
INTDEF ATTR_INOUT(1) void NOTHROW_NCX(LIBCCALL libc_objalloc_free)(struct objalloc *self);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> objalloc_free_block(3)
 * Free a given `ptr', as well as everything allocated since. */
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW_NCX(LIBDCALL libd_objalloc_free_block)(struct objalloc *self, void *ptr);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> objalloc_free_block(3)
 * Free a given `ptr', as well as everything allocated since. */
INTDEF ATTR_INOUT(1) NONNULL((2)) void NOTHROW_NCX(LIBCCALL libc_objalloc_free_block)(struct objalloc *self, void *ptr);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_OBJALLOC_H */
