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
#ifndef _ARM_KOS_ASM_CFI_H
#define _ARM_KOS_ASM_CFI_H 1

#include <__stdinc.h>

#include <hybrid/__asm.h>

#ifndef __COMPILER_NO_GCC_ASM_MACROS
__ASM_BEGIN

/* Decode register names and invoke `func' with the effective CFI register ID. */
__ASM_L(.macro __cfi_decode_register func:req, reg:req)
#define __REGISTER_CASE(name,id) __ASM_L(.ifc __ASM_ARG(\reg),name; __ASM_ARG(\func) id; .else)
	/* core registers */
	__REGISTER_CASE(r0,0) __REGISTER_CASE(a1,0)
	__REGISTER_CASE(r1,1) __REGISTER_CASE(a2,1)
	__REGISTER_CASE(r2,2) __REGISTER_CASE(a3,2)
	__REGISTER_CASE(r3,3) __REGISTER_CASE(a4,3)
	__REGISTER_CASE(r4,4) __REGISTER_CASE(v1,4)
	__REGISTER_CASE(r5,5) __REGISTER_CASE(v2,5)
	__REGISTER_CASE(r6,6) __REGISTER_CASE(v3,6)
	__REGISTER_CASE(r7,7) __REGISTER_CASE(v4,7) __REGISTER_CASE(WR,9)
	__REGISTER_CASE(r8,8) __REGISTER_CASE(v5,8)
	__REGISTER_CASE(r9,9) __REGISTER_CASE(v6,9) __REGISTER_CASE(SB,9)
	__REGISTER_CASE(r10,10) __REGISTER_CASE(sl,10) __REGISTER_CASE(v7,10) __REGISTER_CASE(SL,10)
	__REGISTER_CASE(r11,11) __REGISTER_CASE(fp,11) __REGISTER_CASE(v8,11) __REGISTER_CASE(FP,11)
	__REGISTER_CASE(r12,12) __REGISTER_CASE(ip,12) __REGISTER_CASE(IP,12)
	__REGISTER_CASE(r13,13) __REGISTER_CASE(sp,13) __REGISTER_CASE(SP,13)
	__REGISTER_CASE(r14,14) __REGISTER_CASE(lr,14) __REGISTER_CASE(LR,14)
	__REGISTER_CASE(r15,15) __REGISTER_CASE(pc,15) __REGISTER_CASE(PC,15)

	/* Extended registers */
	__REGISTER_CASE(apsr,128) __REGISTER_CASE(cpsr,128)
	__REGISTER_CASE(SPSR_fiq,129) __REGISTER_CASE(spsr_fiq,129)
	__REGISTER_CASE(SPSR_irq,130) __REGISTER_CASE(spsr_irq,130)
	__REGISTER_CASE(SPSR_abt,131) __REGISTER_CASE(spsr_abt,131)
	__REGISTER_CASE(SPSR_und,132) __REGISTER_CASE(spsr_und,132)
	__REGISTER_CASE(SPSR_svc,133) __REGISTER_CASE(spsr_svc,133)
	__REGISTER_CASE(R8_usr,144) __REGISTER_CASE(r8_usr,144)
	__REGISTER_CASE(R9_usr,145) __REGISTER_CASE(r9_usr,145)
	__REGISTER_CASE(R10_usr,146) __REGISTER_CASE(r10_usr,146)
	__REGISTER_CASE(R11_usr,147) __REGISTER_CASE(r11_usr,147)
	__REGISTER_CASE(R12_usr,148) __REGISTER_CASE(r12_usr,148)
	__REGISTER_CASE(SP_usr,149) __REGISTER_CASE(sp_usr,149) __REGISTER_CASE(R13_usr,149) __REGISTER_CASE(r13_usr,149)
	__REGISTER_CASE(LR_usr,150) __REGISTER_CASE(lr_usr,150) __REGISTER_CASE(R14_usr,150) __REGISTER_CASE(r14_usr,150)
	__REGISTER_CASE(R8_fiq,151) __REGISTER_CASE(r8_fiq,151)
	__REGISTER_CASE(R9_fiq,152) __REGISTER_CASE(r9_fiq,152)
	__REGISTER_CASE(R10_fiq,153) __REGISTER_CASE(r10_fiq,153)
	__REGISTER_CASE(R11_fiq,154) __REGISTER_CASE(r11_fiq,154)
	__REGISTER_CASE(R12_fiq,155) __REGISTER_CASE(r12_fiq,155)
	__REGISTER_CASE(SP_fiq,156) __REGISTER_CASE(sp_fiq,156) __REGISTER_CASE(R13_fiq,156) __REGISTER_CASE(r13_fiq,156)
	__REGISTER_CASE(LR_fiq,157) __REGISTER_CASE(lr_fiq,157) __REGISTER_CASE(R14_fiq,157) __REGISTER_CASE(r14_fiq,157)
	__REGISTER_CASE(SP_irq,158) __REGISTER_CASE(sp_irq,158) __REGISTER_CASE(R13_irq,158) __REGISTER_CASE(r13_irq,158)
	__REGISTER_CASE(LR_irq,159) __REGISTER_CASE(lr_irq,159) __REGISTER_CASE(R14_irq,159) __REGISTER_CASE(r14_irq,159)
	__REGISTER_CASE(SP_abt,160) __REGISTER_CASE(sp_abt,160) __REGISTER_CASE(R13_abt,160) __REGISTER_CASE(r13_abt,160)
	__REGISTER_CASE(LR_abt,161) __REGISTER_CASE(lr_abt,161) __REGISTER_CASE(R14_abt,161) __REGISTER_CASE(r14_abt,161)
	__REGISTER_CASE(SP_und,162) __REGISTER_CASE(sp_und,162) __REGISTER_CASE(R13_und,162) __REGISTER_CASE(r13_und,162)
	__REGISTER_CASE(LR_und,163) __REGISTER_CASE(lr_und,163) __REGISTER_CASE(R14_und,163) __REGISTER_CASE(r14_und,163)
	__REGISTER_CASE(SP_svc,164) __REGISTER_CASE(sp_svc,164) __REGISTER_CASE(R13_svc,164) __REGISTER_CASE(r13_svc,164)
	__REGISTER_CASE(LR_svc,165) __REGISTER_CASE(lr_svc,165) __REGISTER_CASE(R14_svc,165) __REGISTER_CASE(r14_svc,165)
__ASM_L(	__ASM_ARG(\func) __ASM_ARG(\reg))
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif;.endif)
__ASM_L(	.endif;.endif)
#undef __REGISTER_CASE
__ASM_L(.endm)


/* >> .cfi_pushregs {r0, r1, r2, ...}
 * Encode  CFI instrumentation for saving registers to-stack.
 * Only canonical register name may be used (though those are
 * allowed to be case-insensitive) */
__ASM_L(.macro .cfi_pushregs args:vararg)
__ASM_L(	.ifnc_startswith "\args","{";.error ".cfi_pushregs: register list '\args' doesn't start '{'";.endif)
__ASM_L(	.ifnc_endswith "\args","}";.error ".cfi_pushregs: register list '\args' doesn't end '}'";.endif)
__ASM_L(	.ifc_contains "\args","-";.error ".cfi_pushregs: register list '\args' must not contain '-'";.endif)
__ASM_L(	.Lcfi_pushregs_offset = 0)
/*[[[deemon
local REGS = {
	("r0", 0), ("r1", 1), ("r2", 2), ("r3", 3),
	("r4", 4), ("r5", 5), ("r6", 6), ("r7", 7),
	("r8", 8), ("r9", 9), ("r10", 10), ("r11", 11),
	("r12", 12), ("sp", 13), ("lr", 14), ("pc", 15)
};
for (local name, id: REGS) {
	print('__ASM_L(	.ifc_ibcontains "\\args",', name, ')');
	print('__ASM_L(		.cfi_rel_offset ', id, ', .Lcfi_pushregs_offset)');
	print('__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)');
	print('__ASM_L(	.endif)');
}
]]]*/
__ASM_L(	.ifc_ibcontains "\args",r0)
__ASM_L(		.cfi_rel_offset 0, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r1)
__ASM_L(		.cfi_rel_offset 1, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r2)
__ASM_L(		.cfi_rel_offset 2, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r3)
__ASM_L(		.cfi_rel_offset 3, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r4)
__ASM_L(		.cfi_rel_offset 4, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r5)
__ASM_L(		.cfi_rel_offset 5, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r6)
__ASM_L(		.cfi_rel_offset 6, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r7)
__ASM_L(		.cfi_rel_offset 7, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r8)
__ASM_L(		.cfi_rel_offset 8, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r9)
__ASM_L(		.cfi_rel_offset 9, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r10)
__ASM_L(		.cfi_rel_offset 10, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r11)
__ASM_L(		.cfi_rel_offset 11, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r12)
__ASM_L(		.cfi_rel_offset 12, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",sp)
__ASM_L(		.cfi_rel_offset 13, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",lr)
__ASM_L(		.cfi_rel_offset 14, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",pc)
__ASM_L(		.cfi_rel_offset 15, .Lcfi_pushregs_offset)
__ASM_L(		.Lcfi_pushregs_offset = .Lcfi_pushregs_offset + 4)
__ASM_L(	.endif)
/*[[[end]]]*/
__ASM_L(	.if .Lcfi_pushregs_offset != 0)
__ASM_L(		.cfi_adjust_cfa_offset .Lcfi_pushregs_offset)
__ASM_L(	.endif)
__ASM_L(.endm)


/* >> .cfi_popregs {r0, r1, r2, ...}
 * Encode  CFI  instrumentation for  restoring  registers from-stack.
 * Only canonical register name may be used (though those are allowed
 * to be case-insensitive) */
__ASM_L(.macro .cfi_popregs args:vararg)
__ASM_L(	.ifnc_startswith "\args","{";.error ".cfi_popregs: register list '\args' doesn't start '{'";.endif)
__ASM_L(	.ifnc_endswith "\args","}";.error ".cfi_popregs: register list '\args' doesn't end '}'";.endif)
__ASM_L(	.ifc_contains "\args","-";.error ".cfi_popregs: register list '\args' must not contain '-'";.endif)
__ASM_L(	.Lcfi_popregs_offset = 0)
/*[[[deemon
local REGS = {
	("r0", 0), ("r1", 1), ("r2", 2), ("r3", 3),
	("r4", 4), ("r5", 5), ("r6", 6), ("r7", 7),
	("r8", 8), ("r9", 9), ("r10", 10), ("r11", 11),
	("r12", 12), ("sp", 13), ("lr", 14), ("pc", 15)
};
for (local name, id: REGS) {
	print('__ASM_L(	.ifc_ibcontains "\\args",', name, ')');
	print('__ASM_L(		.cfi_restore ', id, ')');
	print('__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)');
	print('__ASM_L(	.endif)');
}
]]]*/
__ASM_L(	.ifc_ibcontains "\args",r0)
__ASM_L(		.cfi_restore 0)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r1)
__ASM_L(		.cfi_restore 1)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r2)
__ASM_L(		.cfi_restore 2)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r3)
__ASM_L(		.cfi_restore 3)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r4)
__ASM_L(		.cfi_restore 4)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r5)
__ASM_L(		.cfi_restore 5)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r6)
__ASM_L(		.cfi_restore 6)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r7)
__ASM_L(		.cfi_restore 7)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r8)
__ASM_L(		.cfi_restore 8)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r9)
__ASM_L(		.cfi_restore 9)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r10)
__ASM_L(		.cfi_restore 10)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r11)
__ASM_L(		.cfi_restore 11)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",r12)
__ASM_L(		.cfi_restore 12)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",sp)
__ASM_L(		.cfi_restore 13)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",lr)
__ASM_L(		.cfi_restore 14)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
__ASM_L(	.ifc_ibcontains "\args",pc)
__ASM_L(		.cfi_restore 15)
__ASM_L(		.Lcfi_popregs_offset = .Lcfi_popregs_offset - 4)
__ASM_L(	.endif)
/*[[[end]]]*/
__ASM_L(	.if .Lcfi_popregs_offset != 0)
__ASM_L(		.cfi_adjust_cfa_offset .Lcfi_popregs_offset)
__ASM_L(	.endif)
__ASM_L(.endm)

/* >> push_cfi_r {r0, r1, r2, ...}
 * Combination of `push' + `.cfi_pushregs' */
__ASM_L(.macro push_cfi_r args:vararg)
__ASM_L(	push __ASM_ARG(\args))
__ASM_L(	.cfi_pushregs __ASM_ARG(\args))
__ASM_L(.endm)

/* >> pop_cfi_r {r0, r1, r2, ...}
 * Combination of `pop' + `.cfi_popregs' */
__ASM_L(.macro pop_cfi_r args:vararg)
__ASM_L(	pop __ASM_ARG(\args))
__ASM_L(	.cfi_popregs __ASM_ARG(\args))
__ASM_L(.endm)


__ASM_END
#endif /* !__COMPILER_NO_GCC_ASM_MACROS */

#endif /* !_ARM_KOS_ASM_CFI_H */
