/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_RT_EXCEPT_HANDLER_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_RT_EXCEPT_HANDLER_H 1

#include <__stdinc.h>

#include <kernel/types.h>
#include <sched/arch/task.h>

#include <hybrid/host.h>

#define ARCH_HAVE_USEREXCEPT_SYSRET_INJECTED
#if !defined(__x86_64__) && !defined(__I386_NO_VM86)
#define ARCH_HAVE_USEREXCEPT_SYSRET_MAYBE_INJECTED
#endif /* !__x86_64__ && !__I386_NO_VM86 */


#ifdef __CC__
DECL_BEGIN

/* Check if the calling thread's IRET tail was redirected. */
#ifdef __x86_64__
#define userexcept_sysret_injected() \
	(x86_get_irregs(THIS_TASK)->ir_rip == (uintptr_t)&x86_userexcept_sysret)
#else /* __x86_64__ */
#define userexcept_sysret_injected() \
	(x86_get_irregs(THIS_TASK)->ir_eip == (uintptr_t)&x86_userexcept_sysret)
#endif /* !__x86_64__ */


#if !defined(__x86_64__) && !defined(__I386_NO_VM86)
#ifndef ___this_x86_kernel_psp0_defined
#define ___this_x86_kernel_psp0_defined
/* [== mnode_getendaddr(THIS_KERNEL_STACK)]
 * The per-task value written to `t_psp0' during scheduler preemption. */
DATDEF ATTR_PERTASK uintptr_t const this_x86_kernel_psp0;
#endif /* !___this_x86_kernel_psp0_defined */

/* Same as `userexcept_sysret_injected()', but allowed to given false
 * positives, though  is  _NOT_  allowed to  given  false  negatives. */
FORCELOCAL ATTR_PURE WUNUSED __BOOL
__NOTHROW(userexcept_sysret_maybe_injected)(void) {
	void **psp0 = (void **)PERTASK_GET(this_x86_kernel_psp0);
	return (psp0[-5] == (void *)&x86_userexcept_sysret) || /* 5 == sizeof(struct irregs_user) / 4 */
	       (psp0[-9] == (void *)&x86_userexcept_sysret);   /* 9 == sizeof(struct irregs_vm86) / 4 */
}
#endif /* !__x86_64__ && !__I386_NO_VM86 */

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_RT_EXCEPT_HANDLER_H */
