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
#ifndef _I386_KOS_ASM_POSIX_TYPES_64_H
#define _I386_KOS_ASM_POSIX_TYPES_64_H 1

/* NOTE: Types in here are not actually used by the kernel!
 *       This header only mirrors what GLibC does for API compatibility. */

#include <hybrid/typecore.h>

#ifdef __CC__
typedef __UINT16_TYPE__    __kernel_old_uid_t;
#define __kernel_old_uid_t __kernel_old_uid_t
typedef __UINT16_TYPE__    __kernel_old_gid_t;
#define __kernel_old_gid_t __kernel_old_gid_t
typedef __UINT64_TYPE__    __kernel_old_dev_t;
#define __kernel_old_dev_t __kernel_old_dev_t
#endif /* __CC__ */

#include "../../asm/posix_types.h"

#endif /* _I386_KOS_ASM_POSIX_TYPES_64_H */
