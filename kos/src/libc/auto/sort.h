/* HASH CRC-32:0x4ae0676 */
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
#ifndef GUARD_LIBC_AUTO_SORT_H
#define GUARD_LIBC_AUTO_SORT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sort.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sort_pointers(3)
 * Sort an array of `count' pointers `sortme' in ascending order
 * @param: work: An  additional array of `count' elements that may
 *               be used as temporary storage by the implemenation
 *               The  contents  of this  array are  undefined upon
 *               return of this function. */
INTDEF ATTR_INOUTS(2, 1) ATTR_OUTS(3, 1) void NOTHROW_NCX(LIBDCALL libd_sort_pointers)(size_t count, void **sortme, void **work);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sort_pointers(3)
 * Sort an array of `count' pointers `sortme' in ascending order
 * @param: work: An  additional array of `count' elements that may
 *               be used as temporary storage by the implemenation
 *               The  contents  of this  array are  undefined upon
 *               return of this function. */
INTDEF ATTR_INOUTS(2, 1) ATTR_OUTS(3, 1) void NOTHROW_NCX(LIBCCALL libc_sort_pointers)(size_t count, void **sortme, void **work);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SORT_H */
