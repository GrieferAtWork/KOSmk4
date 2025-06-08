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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_IDT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_IDT_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/types.h>

#include <kos/kernel/x86/segment.h>

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

/* ISR pushed PC points *at* faulting instruction (requires a signal frame):
 * [BEFORE] 00 divide_by_zero         #DE  Divide-by-zero           -- Points at `div' or `idiv'
 * [???   ] 01 debugtrap              #DB  Debug                    -- (Its complicated; can be both a trap and a fault)
 * [BEFORE] 02 non_maskable_interrupt #NMI Non-maskable Interrupt
 * [AFTER ] 03 breakpoint             #BP  Breakpoint               -- Points after `int3' or `int $3'
 * [AFTER ] 04 overflow               #OF  Overflow                 -- Points after `into' or `int $4'
 * [BEFORE] 05 bound_range            #BR  Bound Range Exceeded     -- Points at `bound'
 * [BEFORE] 06 illegal_instruction    #UD  Invalid Opcode           -- Points at start of illop
 * [BEFORE] 07 device_not_available   #NM  Device Not Available     -- Points at start of fpu instr
 * [???   ] 08 double_fault           #DF  Double Fault             -- Saved PC is undefined
 * [BEFORE] 09 coprocessor_fault      #CSO Coprocessor Segment Overrun (unused on 486+)
 * [BEFORE] 0a invalid_tss            #TS  Invalid TSS              -- Points at start-of-task / faulting instr
 * [BEFORE] 0b segment_not_present    #NP  Segment Not Present      -- Points at faulting instr
 * [BEFORE] 0c stackfault             #SS  Stack-Segment Fault      -- Points at start-of-task / faulting instr
 * [BEFORE] 0d gpf                    #GP  General Protection Fault -- Points at faulting instr
 * [BEFORE] 0e pagefault              #PF  Page Fault               -- Points at faulting instr
 * [      ] 0f 0fh                    Reserved (exception)...
 * [BEFORE] 10 fpu_x87                #MF  x87 Floating-Point Exception -- Points at unrelated instr (x87 IP points at faulting instr)
 * [BEFORE] 11 bad_alignment          #AC  Alignment Check          -- Points at faulting instr
 * [???   ] 12 machine_check          #MC  Machine Check            -- Saved PC is undefined
 * [BEFORE] 13 fpu_simd               #XM  SIMD Floating-Point Exception -- Points at faulting instr
 * [BEFORE] 14 virtualization_error   #VE  Virtualization Exception
 * [???   ] 15
 * [???   ] 16
 * [???   ] 17
 * [???   ] 18
 * [???   ] 19
 * [???   ] 1a
 * [???   ] 1b
 * [???   ] 1c
 * [???   ] 1d
 * [???   ] 1e security_exception     #SX  Security Exception.
 * [???   ] 1f
 *
 * NOTE: Everything "???" we treat as "BEFORE" */
#define IDT_CONFIG_POINTS_AT_PC(vector_id)                        \
	((vector_id) < 0x20  /* All exceptions, except... */ &&       \
	 (vector_id) != 0x03 /* #BP  Breakpoint  (int3, int $3) */ && \
	 (vector_id) != 0x04 /* #OF  Overflow    (into, int $4) */)

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

/* Returns non-zero if `vector_id' should behave as a TRAP, i.e.:
 * call its C-level handler  with interrupts enabled, so-long  as
 * the interrupted program location had them enabled, too.
 * WARNING: This  macro  is  only used  for  vectors 00h...2fh!
 *          All other vectors are handled as non-trapping, with
 *          the exception of vector 80h (which is a trap) */
#define IDT_CONFIG_ISTRAP(vector_id)                            \
	((vector_id) == 0x00 /* #DE  Divide by zero */ ||           \
	 (vector_id) == 0x04 /* #OF  Overflow */ ||                 \
	 (vector_id) == 0x05 /* #BR  Bound Range */ ||              \
	 (vector_id) == 0x06 /* #UD  Illegal Instruction */ ||      \
	 (vector_id) == 0x0b /* #NP  Segment not present */ ||      \
	 (vector_id) == 0x0c /* #SS  Stack segment fault */ ||      \
	 (vector_id) == 0x0d /* #GP  General Protection Fault */ || \
	 ((vector_id) >= 0x20 && (vector_id) <= 0x2f) /* MS services */)


#ifdef __CC__

struct idt_segment; /* From <kos/kernel/x86/segment.h> */
struct desctab;     /* From <kos/kernel/cpu-state.h> */

DATDEF struct idt_segment x86_idt[256];
DATDEF struct desctab const x86_idt_ptr;

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#ifndef __x86_dbgidt_defined
#define __x86_dbgidt_defined
DATDEF struct idt_segment x86_dbgidt[256];
DATDEF struct desctab const x86_dbgidt_ptr;
#ifndef CONFIG_NO_SMP
DATDEF struct idt_segment x86_dbgaltcoreidt[256];
DATDEF struct desctab const x86_dbgaltcoreidt_ptr;
#endif /* !CONFIG_NO_SMP */
#endif /* !__x86_dbgidt_defined */

#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

/* Start modifying `x86_idt'
 * This function must be called prior to making modifications to `x86_idt'.
 * Doing this  is required  to prevent  other CPUs/threads  from  servicing
 * interrupts   with   IDT   segments   that   aren't   fully  initialized.
 * As  such,  any  modifications  made  to  `x86_idt'  after  this function
 * is called  will only  come into  effect once  `x86_idt_modify_end()'  is
 * called. These functions are implemented as:
 *   x86_idt_modify_begin():
 *     - Acquire an internal mutex
 *     - Allocate an internal copy of the IDT
 *     - Copy `x86_idt' into the internal copy
 *     - Broadcast an IPI, telling all CPUs to lidt() the internal copy
 *   x86_idt_modify_end():
 *     - if (discard_changes) x86_idt = <INTERNAL_COPY>;
 *     - Broadcast an IPI, telling all CPUs to `lidt(&x86_idt_ptr)'
 *     - Free the internal copy previously allocated by `x86_idt_modify_begin()'
 *     - Release the internal mutex
 * Using this method, changes can be staged for eventual use in  `x86_idt',
 * without running the risk of any CPU/thread ever accessing an incomplete/
 * corrupt IDT entry.
 * When calling  `x86_idt_modify_end()', the  caller is  responsible to  ensure
 * that the call was preceded by `x86_idt_modify_begin()', as well as to ensure
 * that any call to `x86_idt_modify_begin()' is eventually followed by  another
 * call to `x86_idt_modify_end()'
 * Also note that these  functions must not be  called recursively from the  same
 * thread. - A call to `x86_idt_modify_begin()' must _NOT_ be followed by another
 * call to `x86_idt_modify_begin()' from the same thread!
 * @param: nx:     When true, don't do anything that could throw an exception, or block.
 * @return: true:  Success (always returned when `nx == false')
 * @return: false: Failure (only ever returned when `nx == true') */
FUNDEF bool FCALL x86_idt_modify_begin(bool nx)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INTERRUPT);
FUNDEF NOBLOCK void
NOTHROW(FCALL x86_idt_modify_end)(bool discard_changes DFL(false));


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_IDT_H */
