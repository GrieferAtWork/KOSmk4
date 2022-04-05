/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_KERNEL_TYPES_H
#define _KOS_KERNEL_TYPES_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <kos/types.h>

#if __SIZEOF_POINTER__ == 4
#define BITS_PER_POINTER 32
#elif __SIZEOF_POINTER__ == 8
#define BITS_PER_POINTER 64
#elif __SIZEOF_POINTER__ == 2
#define BITS_PER_POINTER 16
#elif __SIZEOF_POINTER__ == 1
#define BITS_PER_POINTER 8
#else /* __SIZEOF_POINTER__ == ... */
#error "Invalid `__SIZEOF_POINTER__'"
#endif /* __SIZEOF_POINTER__ != ... */

#ifdef __CC__
__DECL_BEGIN

#ifndef __s8_defined
#define __s8_defined
typedef __s8 s8;
typedef __u8 u8;
typedef __s16 s16;
typedef __u16 u16;
typedef __s32 s32;
typedef __u32 u32;
#ifdef __INT64_TYPE__
typedef __s64 s64;
#endif /* __INT64_TYPE__ */
#ifdef __UINT64_TYPE__
typedef __u64 u64;
#endif /* __UINT64_TYPE__ */
#endif /* !__s8_defined */

#ifndef __le8_defined
#define __le8_defined
typedef __le8 le8;
typedef __be8 be8;
typedef __be16 be16;
typedef __le16 le16;
typedef __be32 be32;
typedef __le32 le32;
#ifdef __UINT64_TYPE__
typedef __be64 be64;
typedef __le64 le64;
#endif /* __UINT64_TYPE__ */
#endif /* !__le8_defined */

#ifndef __refcnt_t_defined
#define __refcnt_t_defined
typedef __uintptr_t refcnt_t;
#endif /* !__refcnt_t_defined */

__DECL_END
#endif /* __CC__ */

#endif /* !_KOS_KERNEL_TYPES_H */
