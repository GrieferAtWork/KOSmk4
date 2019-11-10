/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_IDT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_IDT_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <kos/kernel/segment.h>

DECL_BEGIN

/* Special interrupt numbers. */
#define X86_INTERRUPT_APIC_IPI      0xee
#define X86_INTERRUPT_APIC_SPURIOUS 0xef

/* ISR pushes-error-code selector */
#define IDT_CONFIG_PUSHESERRORS(vector_id)                       \
	((vector_id) == 0x08 /* #DF  Double Fault. */ ||             \
	 (vector_id) == 0x0a /* #TS  Invalid TSS. */ ||              \
	 (vector_id) == 0x0b /* #NP  Segment Not Present. */ ||      \
	 (vector_id) == 0x0c /* #SS  Stack-Segment Fault. */ ||      \
	 (vector_id) == 0x0d /* #GP  General Protection Fault. */ || \
	 (vector_id) == 0x0e /* #PF  Page Fault. */ ||               \
	 (vector_id) == 0x11 /* #AC  Alignment Check. */ ||          \
	 (vector_id) == 0x1e /* #SX  Security Exception. */)

/* ISR user-space access selector */
#define IDT_CONFIG_ALLOWUSER(vector_id)                     \
	((vector_id) == 0x80 /* Syscall */ ||                   \
	 (vector_id) == 0x29 /* __fastfail() */ ||              \
	 (vector_id) == 0x05 /* #BR  Bound Range Exceeded */ || \
	 (vector_id) == 0x04 /* #OF  Overflow */ ||             \
	 (vector_id) == 0x03 /* #BP  Breakpoint */)

/* Return the DPL to-be configured for a given ISR vector. */
#define IDT_CONFIG_GETDPL(vector_id) \
	(IDT_CONFIG_ALLOWUSER(vector_id) ? 3 : 0)


#ifdef __CC__

struct idt_segment; /* From <kos/kernel/segment.h> */
struct desctab;     /* From <kos/kernel/cpu-state.h> */

DATDEF struct idt_segment x86_idt[256];
DATDEF struct desctab const x86_idt_ptr;
#ifndef CONFIG_NO_DEBUGGER
DATDEF struct idt_segment x86_dbgidt[256];
DATDEF struct desctab const x86_dbgidt_ptr;
#endif /* !CONFIG_NO_DEBUGGER */


//FUNDEF void KCALL x86_;


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_IDT_H */
