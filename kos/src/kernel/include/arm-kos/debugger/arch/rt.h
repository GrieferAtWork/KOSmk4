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
#ifndef GUARD_KERNEL_INCLUDE_ARM_KOS_DEBUGGER_ARCH_RT_H
#define GUARD_KERNEL_INCLUDE_ARM_KOS_DEBUGGER_ARCH_RT_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <kernel/types.h>

#include <asm/intrin.h>
#include <kos/kernel/paging.h>

#ifdef __CC__
DECL_BEGIN


#ifndef __dbg_stack_defined
#define __dbg_stack_defined
DATDEF byte_t dbg_stack[KERNEL_DEBUG_STACKSIZE];
#endif /* !__dbg_stack_defined */

FORCELOCAL WUNUSED bool
NOTHROW(FCALL dbg_onstack)(void) {
	void *sp = __rdsp();
	return sp >= dbg_stack &&
	       sp <= dbg_stack + KERNEL_DEBUG_STACKSIZE;
}

DECL_END
#endif /* __CC__ */

/* CPU state kind codes. */
#define ARM_DBG_STATEKIND_NONE 0 /* No DBG_REGLEVEL_TRAP-level CPU state */
#define ARM_DBG_STATEKIND_FCPU 1 /* `struct fcpustate' */
#define ARM_DBG_STATEKIND_UCPU 2 /* `struct ucpustate' */
#define ARM_DBG_STATEKIND_LCPU 3 /* `struct lcpustate' */

#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_ARM_KOS_DEBUGGER_ARCH_RT_H */
