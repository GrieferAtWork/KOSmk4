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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_COMPAT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_COMPAT_H 1

#include <kernel/compiler.h>

#include <hybrid/host.h>

#if defined(__x86_64__) && defined(__CC__) && !defined(syscall_iscompat)
#include <sched/pertask.h> /* PERTASK_GET() */
#include <sched/task.h>    /* _this_kernel_stack */

#include <kos/kernel/cpu-state-helpers64.h> /* irregs_iscompat() */
#define syscall_irregs() \
	((struct irregs64 *)VM_PAGE2ADDR(PERTASK_GET((*(struct vm_node *)&_this_kernel_stack).vn_node.a_vmax) + 1) - 1)
#define syscall_iscompat() irregs_iscompat(syscall_irregs())
#endif /* __x86_64__ && __CC__ && !syscall_iscompat */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_COMPAT_H */
