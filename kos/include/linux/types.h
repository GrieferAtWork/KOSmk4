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
/* (#) Portability: Linux     (/usr/include/linux/types.h) */
/* (#) Portability: diet libc (/include/linux/types.h) */
#ifndef _LINUX_TYPES_H
#define _LINUX_TYPES_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "posix_types.h"

#ifdef __CC__
__DECL_BEGIN

typedef __UINT16_TYPE__ __sum16;
typedef __UINT32_TYPE__ __wsum;

#define __aligned_u64  __ATTR_ALIGNED(8) __u64
#define __aligned_be64 __ATTR_ALIGNED(8) __be64
#define __aligned_le64 __ATTR_ALIGNED(8) __le64

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

__DECL_END
#endif /* __CC__ */

#endif /* !_LINUX_TYPES_H */
