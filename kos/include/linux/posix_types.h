/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LINUX_POSIX_TYPES_H
#define _LINUX_POSIX_TYPES_H 1

#include "stddef.h"
#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <asm/posix_types.h>

__SYSDECL_BEGIN

/* NOTE: This stuff isn't actually used by the KOS kernel,
 *       which uses the same structures/types as userspace. */
#undef __FD_SETSIZE
#define __FD_SETSIZE  1024

#ifdef __CC__
typedef struct {
	__ULONGPTR_TYPE__ fds_bits[__FD_SETSIZE/(8*sizeof(__ULONGPTR_TYPE__))];
} __kernel_fd_set;

typedef void (*__kernel_sighandler_t)(int);
typedef int __kernel_key_t;
typedef int __kernel_mqd_t;
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_LINUX_POSIX_TYPES_H */
