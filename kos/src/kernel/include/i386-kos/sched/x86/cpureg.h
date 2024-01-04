/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_CPUREG_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_CPUREG_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/cpu.h> /* CONFIG_NO_SMP */

#include <kos/kernel/cpu-state.h>

DECL_BEGIN

#ifdef __CC__
#ifndef CONFIG_NO_SMP

/* Per-cpu storage space for internal registers that are (normally)
 * not altered, but (for obvious reasons) have to be re-loaded when
 * the CPU returns from deep sleep.
 * s.a. "/kos/src/kernel/core/arch/i386/sched/smp.S" */



/* Saved GDT register.
 * usually: { (SEGMENT_COUNT * SIZEOF_SEGMENT_DESCRIPTOR) - 1, thiscpu_x86_gdt } */
DATDEF ATTR_PERCPU struct desctab thiscpu_x86_saved_gdtr;

/* Saved IDT register. (usually `x86_idt_ptr') */
DATDEF ATTR_PERCPU struct desctab thiscpu_x86_saved_idtr;

/* Saved LDT register. (usually `SEGMENT_CPU_LDT') */
DATDEF ATTR_PERCPU u16 thiscpu_x86_saved_ldtr;

/* Saved Task register. (usually `SEGMENT_CPU_TSS') */
DATDEF ATTR_PERCPU u16 thiscpu_x86_saved_tr;

/* Saved %cr0 and %cr4 registers. Loaded during late CPU
 * bootstrap, and saved when a CPU goes into deep sleep.
 *
 * First initialized alongside cpuid information. */
DATDEF ATTR_PERCPU uintptr_t thiscpu_x86_saved_cr0;
DATDEF ATTR_PERCPU uintptr_t thiscpu_x86_saved_cr4;


/* Other (feature-dependent) registers exist that may be added here, such as:
 *   - %cr0 (certain bits only)
 *   - %cr3 (certain bits only)
 *   - IA32_SYSENTER_CS
 *   - IA32_SYSENTER_ESP
 *   - IA32_SYSENTER_EIP
 *   - x86_64-only: IA32_EFER (certain bits only)
 *   - x86_64-only: IA32_STAR
 *   - x86_64-only: IA32_FMASK
 *   - x86_64-only: IA32_LSTAR
 * However,  (currently)  these  registers are  never  modified at  all,  or only
 * modified in very controlled environments, such that the default initialization
 * done by the SMP startup code is sufficient to deal with them properly. */

#endif /* !CONFIG_NO_SMP */
#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_X86_CPUREG_H */
