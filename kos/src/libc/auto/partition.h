/* HASH CRC-32:0x344e74f4 */
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
#ifndef GUARD_LIBC_AUTO_PARTITION_H
#define GUARD_LIBC_AUTO_PARTITION_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <partition.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> partition_new(3)
 * Create a new partition for `num_elements' elements.
 *  - Uses `xmalloc(3)', so never returns `NULL'! */
INTDEF ATTR_RETNONNULL struct partition_def *NOTHROW_NCX(LIBDCALL libd_partition_new)(__STDC_INT_AS_UINT_T num_elements);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> partition_new(3)
 * Create a new partition for `num_elements' elements.
 *  - Uses `xmalloc(3)', so never returns `NULL'! */
INTDEF ATTR_RETNONNULL struct partition_def *NOTHROW_NCX(LIBCCALL libc_partition_new)(__STDC_INT_AS_UINT_T num_elements);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> partition_delete(3)
 * Destroy a given partition */
INTDEF void NOTHROW_NCX(LIBDCALL libd_partition_delete)(struct partition_def *self);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> partition_delete(3)
 * Destroy a given partition */
INTDEF void NOTHROW_NCX(LIBCCALL libc_partition_delete)(struct partition_def *self);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> partition_union(3)
 * Join the classes containing elements `a' and `b' into the same class
 * For  this, choose one  of the class's canonical  elements as the new
 * canonical element of the total  class, which is then also  returned. */
INTDEF ATTR_INOUT(1) __STDC_INT_AS_UINT_T NOTHROW_NCX(LIBDCALL libd_partition_union)(struct partition_def *self, __STDC_INT_AS_UINT_T a, __STDC_INT_AS_UINT_T b);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> partition_union(3)
 * Join the classes containing elements `a' and `b' into the same class
 * For  this, choose one  of the class's canonical  elements as the new
 * canonical element of the total  class, which is then also  returned. */
INTDEF ATTR_INOUT(1) __STDC_INT_AS_UINT_T NOTHROW_NCX(LIBCCALL libc_partition_union)(struct partition_def *self, __STDC_INT_AS_UINT_T a, __STDC_INT_AS_UINT_T b);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> partition_print(3)
 * Print classes (and  their elements) of  `self' to  `fp'
 * The format used is: '[' ['(' [0 1 2 3 4]... ')']... ']'
 * Example: "[(0 1 2 4 8)(3 6)(5 7)]" */
INTDEF ATTR_IN(1) ATTR_INOUT(2) void NOTHROW_CB_NCX(LIBDCALL libd_partition_print)(struct partition_def __KOS_FIXED_CONST *self, FILE *fp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> partition_print(3)
 * Print classes (and  their elements) of  `self' to  `fp'
 * The format used is: '[' ['(' [0 1 2 3 4]... ')']... ']'
 * Example: "[(0 1 2 4 8)(3 6)(5 7)]" */
INTDEF ATTR_IN(1) ATTR_INOUT(2) void NOTHROW_CB_NCX(LIBCCALL libc_partition_print)(struct partition_def __KOS_FIXED_CONST *self, FILE *fp);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PARTITION_H */
