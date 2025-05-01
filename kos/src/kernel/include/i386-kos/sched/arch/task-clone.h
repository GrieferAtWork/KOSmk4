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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TASK_CLONE_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TASK_CLONE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <kernel/x86/gdt.h>

#include <hybrid/host.h>

#ifdef __x86_64__
#include <kernel/arch/compat.h>
#endif /* __x86_64__ */

#ifdef __CC__
DECL_BEGIN

#define ARCH_HAVE_ARCH_TASK_CLONE_ARGS
struct arch_task_clone_args {
	uintptr_t atca_x86_fsbase; /* Initial child %fs.base */
	uintptr_t atca_x86_gsbase; /* Initial child %gs.base */
};
#define arch_task_clone_args_initfork(self)                 \
	(void)((self)->atca_x86_fsbase = x86_get_user_fsbase(), \
	       (self)->atca_x86_gsbase = x86_get_user_gsbase())
#define __arch_task_clone_args_inittls32(self, clone_flags, tls)     \
	(void)((self)->atca_x86_fsbase = x86_get_user_fsbase(),          \
	       (self)->atca_x86_gsbase = (uintptr_t)(tls),               \
	       !((clone_flags) & CLONE_SETTLS)                           \
	       ? (void)((self)->atca_x86_gsbase = x86_get_user_gsbase()) \
	       : (void)0)
#ifdef __x86_64__
#define __arch_task_clone_args_inittls64(self, clone_flags, tls)     \
	(void)((self)->atca_x86_gsbase = x86_get_user_gsbase(),          \
	       (self)->atca_x86_fsbase = (uintptr_t)(tls),               \
	       !((clone_flags) & CLONE_SETTLS)                           \
	       ? (void)((self)->atca_x86_fsbase = x86_get_user_fsbase()) \
	       : (void)0)
#define arch_task_clone_args_inittls(self, clone_flags, tls)                       \
	(syscall_iscompat() ? __arch_task_clone_args_inittls32(self, clone_flags, tls) \
	                    : __arch_task_clone_args_inittls64(self, clone_flags, tls))
#else /* __x86_64__ */
#define arch_task_clone_args_inittls __arch_task_clone_args_inittls32
#endif /* !__x86_64__ */


/* The per-task value written to `t_psp0' during scheduler preemption. */
DATDEF ATTR_PERTASK uintptr_t _this_x86_kernel_psp0 ASMNAME("this_x86_kernel_psp0");
#define _task_init_arch_sstate(child, caller, p_sstate) \
	(void)(FORTASK(child, _this_x86_kernel_psp0) = (uintptr_t)mnode_getendaddr(&FORTASK(child, this_kernel_stacknode)))

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TASK_CLONE_H */
