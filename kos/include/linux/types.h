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
#ifndef _LINUX_TYPES_H
#define _LINUX_TYPES_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include "posix_types.h"

__DECL_BEGIN

#ifdef __CC__

#ifndef ____s8_defined
#define ____s8_defined 1
typedef __INT8_TYPE__ __s8;
typedef __UINT8_TYPE__ __u8;
typedef __INT16_TYPE__ __s16;
typedef __UINT16_TYPE__ __u16;
typedef __INT32_TYPE__ __s32;
typedef __UINT32_TYPE__ __u32;
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ __s64;
#endif /* __INT64_TYPE__ */
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ __u64;
#endif /* __UINT64_TYPE__ */
#endif /* !____s8_defined */

#ifndef ____le8_defined
#define ____le8_defined 1
#ifdef __INTELLISENSE__
#include <hybrid/__byteorder.h>
typedef __intern::____intellisense_endianint<__ORDER_LITTLE_ENDIAN__,__UINT8_TYPE__> __le8;
typedef __intern::____intellisense_endianint<__ORDER_BIG_ENDIAN__,__UINT8_TYPE__> __be8;
typedef __intern::____intellisense_endianint<__ORDER_LITTLE_ENDIAN__,__UINT16_TYPE__> __le16;
typedef __intern::____intellisense_endianint<__ORDER_BIG_ENDIAN__,__UINT16_TYPE__> __be16;
typedef __intern::____intellisense_endianint<__ORDER_LITTLE_ENDIAN__,__UINT32_TYPE__> __le32;
typedef __intern::____intellisense_endianint<__ORDER_BIG_ENDIAN__,__UINT32_TYPE__> __be32;
#ifdef __UINT64_TYPE__
typedef __intern::____intellisense_endianint<__ORDER_LITTLE_ENDIAN__,__UINT64_TYPE__> __le64;
typedef __intern::____intellisense_endianint<__ORDER_BIG_ENDIAN__,__UINT64_TYPE__> __be64;
#endif /* __UINT64_TYPE__ */
#else /* __INTELLISENSE__ */

#ifndef __bitwise__
#ifdef __CHECKER__
#   define __bitwise__ __attribute__((bitwise))
#else /* __CHECKER__ */
#   define __bitwise__
#endif /* !__CHECKER__ */
#endif /* !__bitwise__ */

#ifndef __bitwise
#ifdef __CHECK_ENDIAN__
#   define __bitwise __bitwise__
#else /* __CHECK_ENDIAN__ */
#   define __bitwise
#endif /* !__CHECK_ENDIAN__ */
#endif /* !__bitwise */

typedef __bitwise __UINT8_TYPE__ __le8;
typedef __bitwise __UINT8_TYPE__ __be8;
typedef __bitwise __UINT16_TYPE__ __le16;
typedef __bitwise __UINT16_TYPE__ __be16;
typedef __bitwise __UINT32_TYPE__ __le32;
typedef __bitwise __UINT32_TYPE__ __be32;
#ifdef __UINT64_TYPE__
typedef __bitwise __UINT64_TYPE__ __le64;
typedef __bitwise __UINT64_TYPE__ __be64;
#endif /* __UINT64_TYPE__ */
#endif /* !__INTELLISENSE__ */
#endif /* !____le8_defined */

typedef __UINT16_TYPE__ __sum16;
typedef __UINT32_TYPE__ __wsum;

#define __aligned_u64  __ATTR_ALIGNED(8) __u64
#define __aligned_be64 __ATTR_ALIGNED(8) __be64
#define __aligned_le64 __ATTR_ALIGNED(8) __le64

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */
#endif /* __CC__ */

__DECL_END

#endif /* !_LINUX_TYPES_H */
