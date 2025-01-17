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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_COMPAT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_COMPAT_H 1

#include <kernel/compiler.h>

#include <hybrid/host.h>

#if defined(__x86_64__) && defined(__CC__) && !defined(syscall_iscompat)
#include <sched/pertask.h> /* PERTASK_GET() */
#include <sched/task.h>    /* this_kernel_stacknode */

#include <kos/kernel/bits/cpu-state-helpers64.h> /* irregs_iscompat() */

DECL_BEGIN

#ifndef ___this_x86_kernel_psp0_defined
#define ___this_x86_kernel_psp0_defined
/* [== mnode_getendaddr(THIS_KERNEL_STACK)]
 * The per-task value written to `t_psp0' during scheduler preemption. */
DATDEF ATTR_PERTASK uintptr_t const this_x86_kernel_psp0;
#endif /* !___this_x86_kernel_psp0_defined */

#define x86_syscall_irregs() \
	((struct irregs64 *)PERTASK_GET(this_x86_kernel_psp0) - 1)
#define syscall_iscompat() irregs_iscompat(x86_syscall_irregs())

DECL_END
#endif /* __x86_64__ && __CC__ && !syscall_iscompat */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_COMPAT_H */
