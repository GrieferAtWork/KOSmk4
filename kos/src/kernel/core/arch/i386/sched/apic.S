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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_APIC_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_APIC_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/x86/idt.h>
#include <kernel/x86/pic.h>

#include <asm/instr/compat.h>
#include <asm/instr/ttest.h>
#include <hw/ic/apic.h>
#include <hw/ic/pic.h>
#include <hw/timer/pit.h>


/************************************************************************/
/* APIC IMPLEMENTATION                                                  */
/************************************************************************/

/* >> FUNDEF NOBLOCK WUNUSED NOPREEMPT bool
 * >> NOTHROW(FCALL arch_cpu_hwipi_pending_nopr)(void);
 * Check  if IPIs are  pending to be executed  by the calling CPU,
 * returning  `true'  if  this is  the  case, or  `false'  it not.
 * In order to serve any pending IPIs, preemption must be enabled. */
.section .text
PUBLIC_FUNCTION(arch_cpu_hwipi_pending_nopr)
	.cfi_startproc
	/* >> u32 mask = lapic_read(APIC_IRR(APIC_IRR_INDEX(X86_INTERRUPT_APIC_IPI)));
	 * >> return (mask & APIC_IRR_MASK(X86_INTERRUPT_APIC_IPI)) != 0; */
	xorP   %Pax, %Pax
	EXTERN(x86_lapicbase)
	movP   x86_lapicbase, %Pcx
	movl   APIC_IRR(APIC_IRR_INDEX(X86_INTERRUPT_APIC_IPI))(%Pcx), %ecx
	ttest  mask=APIC_IRR_MASK(X86_INTERRUPT_APIC_IPI), loc=%ecx
	setnz  %al
	ret
	.cfi_endproc
END(arch_cpu_hwipi_pending_nopr)



#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_APIC_S */
