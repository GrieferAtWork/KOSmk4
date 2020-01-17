/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_BREAKPOINT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_BREAKPOINT_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <asm/cpu-flags.h>

DECL_BEGIN

#ifdef __CC__

/* Per-vm debug registers. (lazily loaded during VM switches)
 * NOTE: When setting a debug register (using __wrdrN()), you
 *       must also update these fields accordingly. - Otherwise,
 *       any changes made will become lost the next time the VM
 *       is changed.
 * NOTE: These fields are _NOT_ inherited during `vm_clone()'! */
DATDEF ATTR_PERVM void *thisvm_x86_dr0;
DATDEF ATTR_PERVM void *thisvm_x86_dr1;
DATDEF ATTR_PERVM void *thisvm_x86_dr2;
DATDEF ATTR_PERVM void *thisvm_x86_dr3;
DATDEF ATTR_PERVM uintptr_t thisvm_x86_dr7;

/* Add/Remove a local hardware breakpoint to the given VM.
 * @param: br_size: Breakpoint size (One of `DR_S(1|2|4|8)')
 * @param: br_cond: Breakpoint condition (One of `DR_C(EXEC|WRITE|READWRITE|IO)')
 * @return: true:   Successfully added/deleted the breakpoint.
 * @return: false:  No unused breakpoints exist / the given breakpoint doesn't exist * */
FUNDEF NOBLOCK bool
NOTHROW(KCALL vm_addhwbreak)(struct vm *__restrict self, void *addr,
                             unsigned int br_cond DFL(DR_CEXEC),
                             unsigned int br_size DFL(DR_S1));
FUNDEF NOBLOCK bool
NOTHROW(KCALL vm_delhwbreak)(struct vm *__restrict self, void *addr,
                             unsigned int br_cond DFL(DR_CEXEC),
                             unsigned int br_size DFL(DR_S1));

/* Clear all hardware breakpoints from `self' */
FUNDEF NOBLOCK void
NOTHROW(KCALL vm_clrhwbreak)(struct vm *__restrict self);

#endif /* __CC__ */


#ifdef __ASSEMBLER__
.macro reload_x86_debug_registers this_vm_reg:req, scratch_reg1:req, scratch_reg2:req, disable_local:req
	mov    thisvm_x86_dr7(\this_vm_reg), \scratch_reg1
	test   $(DR7_L0|DR7_G0|DR7_L1|DR7_G1|DR7_L2|DR7_G2|DR7_L3|DR7_G3), \scratch_reg1
	jz     991f
	test   $(DR7_L0|DR7_G0), \scratch_reg1
	jz     992f
	mov    thisvm_x86_dr0(\this_vm_reg), \scratch_reg2
	mov    \scratch_reg2, %dr0
992:
	test   $(DR7_L1|DR7_G1), \scratch_reg1
	jz     992f
	mov    thisvm_x86_dr1(\this_vm_reg), \scratch_reg2
	mov    \scratch_reg2, %dr1
992:
	test   $(DR7_L2|DR7_G2), \scratch_reg1
	jz     992f
	mov    thisvm_x86_dr2(\this_vm_reg), \scratch_reg2
	mov    \scratch_reg2, %dr2
992:
	test   $(DR7_L3|DR7_G3), \scratch_reg1
	jz     992f
	mov    thisvm_x86_dr2(\this_vm_reg), \scratch_reg2
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


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_BREAKPOINT_H */
