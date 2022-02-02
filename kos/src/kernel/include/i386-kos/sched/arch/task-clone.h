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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TASK_CLONE_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TASK_CLONE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

/* Arch-specific parameters for `task_clone()' */
#define ARCH_CLONE__PARAMS              \
	,                                   \
	USER UNCHECKED void *x86_child_psp, \
	uintptr_t x86_child_gsbase,         \
	uintptr_t x86_child_fsbase
#define ARCH_CLONE__ARGS \
	, x86_child_psp, x86_child_gsbase, x86_child_fsbase

/* The per-task value written to `t_psp0' during scheduler preemption. */
DATDEF ATTR_PERTASK uintptr_t _this_x86_kernel_psp0 ASMNAME("this_x86_kernel_psp0");
#define _task_init_arch_sstate(child, caller, p_sstate) \
	(void)(FORTASK(child, _this_x86_kernel_psp0) = (uintptr_t)mnode_getendaddr(&FORTASK(child, this_kernel_stacknode)))

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TASK_CLONE_H */
