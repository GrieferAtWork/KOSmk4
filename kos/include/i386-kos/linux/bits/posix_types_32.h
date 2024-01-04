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
#ifndef _I386_KOS_LINUX_BITS_POSIX_TYPES_32_H
#define _I386_KOS_LINUX_BITS_POSIX_TYPES_32_H 1

#include <hybrid/typecore.h>

/* NOTE: Types in here are not actually used by the kernel!
 *       This header only mirrors what GLibC does for API compatibility. */

#ifdef __CC__
#define __kernel_mode_t    __UINT16_TYPE__
#define __kernel_ipc_pid_t __UINT16_TYPE__
#define __kernel_uid_t     __UINT16_TYPE__
#define __kernel_gid_t     __UINT16_TYPE__
#define __kernel_old_dev_t __UINT16_TYPE__
#endif /* __CC__ */

#endif /* _I386_KOS_LINUX_BITS_POSIX_TYPES_32_H */
