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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_BREAKPOINT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_BREAKPOINT_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <asm/cpu-flags.h>

#ifdef __CC__
DECL_BEGIN

/* Per-MMan debug registers. (lazily loaded during task switches)
 * NOTE: When  setting  a debug  register (using  __wrdrN()), you
 *       must  also update these fields accordingly. - Otherwise,
 *       any changes made will become lost the next time the mman
 *       is changed.
 * NOTE: These fields are _NOT_ inherited during `mman_fork()'! */
DATDEF ATTR_PERMMAN void *thismman_x86_dr0;
DATDEF ATTR_PERMMAN void *thismman_x86_dr1;
DATDEF ATTR_PERMMAN void *thismman_x86_dr2;
DATDEF ATTR_PERMMAN void *thismman_x86_dr3;
DATDEF ATTR_PERMMAN uintptr_t thismman_x86_dr7;

struct mman;

/* Add/Remove a local hardware breakpoint to the given VM.
 * @param: br_size: Breakpoint size (One of `DR_S(1|2|4|8)')
 * @param: br_cond: Breakpoint condition (One of `DR_C(EXEC|WRITE|READWRITE|IO)')
 * @return: true:   Successfully added/deleted the breakpoint.
 * @return: false:  No unused breakpoints exist / the given breakpoint doesn't exist * */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(KCALL mman_addhwbreak)(struct mman *__restrict self, void *addr,
                               unsigned int br_cond DFL(DR_CEXEC),
                               unsigned int br_size DFL(DR_S1));
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(KCALL mman_delhwbreak)(struct mman *__restrict self, void *addr,
                               unsigned int br_cond DFL(DR_CEXEC),
                               unsigned int br_size DFL(DR_S1));

/* Clear all hardware breakpoints from `self' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL mman_clrhwbreak)(struct mman *__restrict self);

DECL_END
#endif /* __CC__ */


#ifdef __ASSEMBLER__
.macro reload_x86_debug_registers this_mman_reg:req, scratch_reg1:req, scratch_reg2:req, disable_local:req
	mov    thismman_x86_dr7(\this_mman_reg), \scratch_reg1
	test   $(DR7_L0|DR7_G0|DR7_L1|DR7_G1|DR7_L2|DR7_G2|DR7_L3|DR7_G3), \scratch_reg1
	jz     991f
	test   $(DR7_L0|DR7_G0), \scratch_reg1
	jz     992f
	mov    thismman_x86_dr0(\this_mman_reg), \scratch_reg2
	mov    \scratch_reg2, %dr0
992:
	test   $(DR7_L1|DR7_G1), \scratch_reg1
	jz     992f
	mov    thismman_x86_dr1(\this_mman_reg), \scratch_reg2
	mov    \scratch_reg2, %dr1
992:
	test   $(DR7_L2|DR7_G2), \scratch_reg1
	jz     992f
	mov    thismman_x86_dr2(\this_mman_reg), \scratch_reg2
	mov    \scratch_reg2, %dr2
992:
	test   $(DR7_L3|DR7_G3), \scratch_reg1
	jz     992f
	mov    thismman_x86_dr2(\this_mman_reg), \scratch_reg2
	mov    \scratch_reg2, %dr3
992:
	mov    \scratch_reg1, %dr7
.if \disable_local
	jmp    993f
991: /* Disable local breakpoints */
	mov    %dr7, \scratch_reg1
	and    $(DR7_L0|DR7_L1|DR7_L2|DR7_L3), \scratch_reg1
	mov    \scratch_reg1, %dr7
993:
.else
991:
.endif
.endm
#endif /* __ASSEMBLER__ */


#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_BREAKPOINT_H */
