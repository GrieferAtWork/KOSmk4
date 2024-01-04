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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_CRED_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_CRED_H 1

#include <kernel/compiler.h>

#include <asm/cpu-flags.h>
#include <kos/capability.h>

DECL_BEGIN

/* Mask of eflags bits that a user-space process is allowed to  modify.
 * Attempting to set any non-masked EFLAGS bit will cause an exception:
 *    E_INVALID_ARGUMENT_BAD_VALUE:
 *        E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER:
 *            X86_REGISTER_MISC_EFLAGS:
 *                value
 * to be thrown */
#define cred_allow_eflags_modify_mask()                        \
	(capable(CAP_SYS_RAWIO) ? (EFLAGS_UMASK | EFLAGS_IOPLMASK) \
	                        : (EFLAGS_UMASK))

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_CRED_H */
