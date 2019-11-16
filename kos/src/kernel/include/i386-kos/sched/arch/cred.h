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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_CRED_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_CRED_H 1

#include <kernel/compiler.h>

DECL_BEGIN

/* Return true if the calling thread is allowed to modify EFLAGS.IOPERM */
#define cred_allow_hwio() 1 /* TODO */

/* Mask of eflags bits that a user-space process is allowed to modify.
 * Attempting to set any non-masked EFLAGS bit will cause an exception:
 *    E_INVALID_ARGUMENT_BAD_VALUE:
 *        E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER:
 *            X86_REGISTER_MISC_EFLAGS:
 *                value
 * to be thrown */
#define cred_allow_eflags_modify_mask()                                                                      \
	(cred_allow_hwio() ? (EFLAGS_CF | EFLAGS_PF | EFLAGS_AF | EFLAGS_ZF | EFLAGS_SF | EFLAGS_OF | EFLAGS_ID) \
	                   : (EFLAGS_CF | EFLAGS_PF | EFLAGS_AF | EFLAGS_ZF | EFLAGS_SF | EFLAGS_OF | EFLAGS_ID | EFLAGS_IOPLMASK))


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_CRED_H */
