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


__ASM_L(.macro .cfi_pushregs args:vararg)
__ASM_L(	/* TODO: CFI */)
__ASM_L(.endm)

__ASM_L(.macro .cfi_popregs args:vararg)
__ASM_L(	/* TODO: CFI */)
__ASM_L(.endm)

__ASM_L(.macro push_cfi_r args:vararg)
__ASM_L(	push __ASM_ARG(\args))
__ASM_L(	.cfi_pushregs __ASM_ARG(\args))
__ASM_L(.endm)

__ASM_L(.macro pop_cfi_r args:vararg)
__ASM_L(	pop __ASM_ARG(\args))
__ASM_L(	.cfi_popregs __ASM_ARG(\args))
__ASM_L(.endm)


__ASM_END
#endif /* !__COMPILER_NO_GCC_ASM_MACROS */

#endif /* !_ARM_KOS_ASM_CFI_H */
