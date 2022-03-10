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
#ifndef _I386_KOS_ASM_INSTR_INTERRUPT_H
#define _I386_KOS_ASM_INSTR_INTERRUPT_H 1

#include <__stdinc.h>
#include <hybrid/__asm.h>
#include <hybrid/host.h>

/* On x86_64, entering/exiting an interrupt requires some special actions to be
 * be performed in order to  safely load/restore %gs.base. Additionally,  iretq
 * must be used instead of `iret'
 * With all of this in mind, an interrupt handler on x86_64 should be written
 * using the macros in this file:
 * >> INTERN_FUNCTION(my_interrupt_handler)
 * >> 	.cfi_startproc simple
 * >> 	.cfi_iret_signal_frame
 * >> 	.cfi_def_cfa %rsp, 0
 * >> 	swapgs_if_user_iret
 * >>
 * >> 	...
 * >>
 * >> 	swapgs_if_user_iret
 * >> 	iretq
 * >> END(my_interrupt_handler)
 */

#ifndef __COMPILER_NO_GCC_ASM_MACROS
#ifdef __x86_64__
__ASM_BEGIN
__ASM_L(.macro swapgs_if_user_iret)
__ASM_L(	testb  $(3), 8(%rsp)) /* 8 == OFFSET_IRREGS64_CS */
__ASM_L(	jz     991f)
__ASM_L(	swapgs)
__ASM_L(991:)
__ASM_L(.endm)

/* Generate the mandatory prefix for an interrupt handler
 * @param: type: One of { TRAP, INTR }
 *               INTR: #IF is disabled after entry
 *               TRAP: #IF is left unchanged after entry */
__ASM_L(.macro intr_enter type:req)
__ASM_L(	swapgs_if_user_iret)
__ASM_L(.ifc __ASM_ARG(\type),TRAP)
#if 1
__ASM_L(	testb  $(0x2), 17(%rsp))   /* 16 == OFFSET_IRREGS64_RFLAGS */
#else
__ASM_L(	testq  $(0x200), 16(%rsp)) /* 16 == OFFSET_IRREGS64_RFLAGS */
#endif
__ASM_L(	jz     991f)
__ASM_L(	sti)
__ASM_L(991:)
__ASM_L(.else)
__ASM_L(.ifc __ASM_ARG(\type),INTR)
__ASM_L(.else)
__ASM_L(.error "Expected TRAP or INTR for `type`, but got `\type`";)
__ASM_L(.endif; .endif)
__ASM_L(.endm)


/* Generate the mandatory suffix for an interrupt handler
 * @param: intr_enabled: When non-zero, EFLAGS.IF may be set when this macro is reached */
__ASM_L(.macro intr_exit intr_enabled=1)
#ifdef __KERNEL__
__ASM_L(.if __ASM_ARG(\intr_enabled))
__ASM_L(	cli)
__ASM_L(.endif)
#endif /* __KERNEL__ */
__ASM_L(	swapgs_if_user_iret)
__ASM_L(	iretq)
__ASM_L(.endm)
__ASM_END
#endif /* __x86_64__ */
#endif /* !__COMPILER_NO_GCC_ASM_MACROS */

#endif /* !_I386_KOS_ASM_INSTR_INTERRUPT_H */
