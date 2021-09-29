/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_RPC_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_RPC_H 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_RPC
#include <hybrid/host.h>

/* Helper for `task_serve_with_icpustate()': set the return boolean */
/* Helper for `task_serve_with_icpustate_nx()': set the return integer */
#ifdef __x86_64__
#define _task_serve_with_icpustate_arch_set_return_bool(state, value) \
	(void)((state)->ics_gpregs.gp_rax = (value) ? 1 : 0)
#define _task_serve_with_icpustate_nx_arch_set_return_uint(state, value) \
	(void)((state)->ics_gpregs.gp_rax = (value))
#else /* __x86_64__ */
#define _task_serve_with_icpustate_arch_set_return_bool(state, value) \
	(void)((state)->ics_gpregs.gp_eax = (value) ? 1 : 0)
#define _task_serve_with_icpustate_nx_arch_set_return_uint(state, value) \
	(void)((state)->ics_gpregs.gp_eax = (value))
#endif /* !__x86_64__ */

#endif /* CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_RPC_H */
