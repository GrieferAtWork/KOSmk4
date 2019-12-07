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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_DEBUGGER_ARCH_RT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_DEBUGGER_ARCH_RT_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <kernel/except.h>
#include <kernel/types.h>
#include <sched/rwlock-intern.h>
#include <sched/signal-intern.h>

#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>
#include <kos/kernel/segment.h>

DECL_BEGIN

/* The System state on x86 while inside of the builtin debugger:
 *
 *  - %pax, %pcx, %pdx, %pbx, %pbp, %pdi, %psi, [%r8-15], %pflags:
 *                All general purpose registers can be used just like usual
 *  - %psp:       Points somewhere into `dbg_stack'.
 *                If this stack should ever overflow, the debugger will reset itself.
 *  - %pflags.IF: Always enabled.
 *
 *  - %idtr:      Always points to `x86_dbgidt', where `x86_dbgidt' is pretty much
 *                a carbon copy of `x86_idt', though with a couple of changes made
 *                to allow the handling of HID-related interrupts.
 *
 *  - %gdtr:      Always points to `x86_dbggdt', where `x86_dbggdt' is a carbon
 *                copy of the unmodified base-state of the original GDT.
 *  - %ds:        Always `SEGMENT_USER_DATA_RPL'
 *  - %es:        Always `SEGMENT_USER_DATA_RPL'
 *  - %fs:        Always [i386:`SEGMENT_KERNEL_FSBASE', x86_64:`SEGMENT_USER_DATA_RPL']
 *  - %gs:        Always [i386:`SEGMENT_USER_GSBASE_RPL', x86_64:`SEGMENT_USER_DATA_RPL']
 *  - %ss:        Always `SEGMENT_KERNEL_DATA'
 *  - %cs:        Always `SEGMENT_KERNEL_CODE'
 *  - %tr:        Always `SEGMENT_CPU_TSS'
 *  - %ldtr:      Always `SEGMENT_CPU_LDT'
 *  - %cr0:       1:CR0_PE, CR0_PG; 0:CR0_TS
 *  - %cr3:       Always points to `pagedir_kernel_phys'
 *
 *  - THIS_TASK:  Points to the task-structure of the thread that originally entered the
 *                debugger. If during debugger entry, it is found that this pointer is
 *                invalid, or unset, this will instead point to `FORCPU(THIS_CPU, thiscpu_idle)'
 *                instead.
 *
 *  - THIS_TASK->t_cpu->c_override: Set to `THIS_TASK'
 *
 *  - Hosting CPU:
 *    The hosting CPU in general is undefined, but currently the boot
 *    is always being used (though this may change in the future)
 *
 *  - Other CPUs:
 *    All other CPUs are suspended and will resume execution when
 *    debugger mode is exited.
 *
 *  - While in debugger mode, `dbg_active' is non-zero.
 *    Care is taken that no secondary CPU will see this value being
 *    non-zero while debugger mode is being entered on another CPU.
 *
 *  - Exiting debugger mode:
 *    To exit debugger mode, `dbg_exit()' should be called, which will proceed to:
 *     - Call `x86_dbg_fini()'
 *     - Restore saved data fields from `x86_dbg_exitstate'
 *     - Resume execution with the CPU state described by `x86_dbg_exitstate'
 *
 */


#ifdef __CC__

struct task;

/* Arch-specific backups for context data of
 * the current thread whilst in debugger mode. */
struct x86_dbg_hoststate {
	struct exception_info   dhs_except;    /* Saved exception info. */
	struct task            *dhs_taskself;  /* Saved `this_task.t_self' */
	uintptr_t               dhs_taskflags; /* Saved `this_task.t_flags' */
	uintptr_t               dhs_psp0;      /* Saved `this_x86_kernel_psp0' */
	struct task            *dhs_override;  /* Saved `THIS_CPU->c_override' */
	struct read_locks       dhs_readlocks; /* Saved `this_read_locks' */
	struct task_connections dhs_signals;   /* Saved signal connections. */
	bool                    dhs_pint;      /* Set to true if preemptive interrupts were enabled. */
};

/* Host-thread special-state backup data. (saved/restored by `dbg_init()' and `dbg_fini()') */
DATDEF struct x86_dbg_hoststate x86_dbg_hostbackup;

/* DBG trap state information. */
/* [valid_if(x86_dbg_trapstatekind != X86_DBG_STATEKIND_NONE)]
 * This is a `struct Xcpustate *' (depending on `x86_dbg_trapstatekind') */
DATDEF void *x86_dbg_trapstate;
/* The kind of state stored in `x86_dbg_trapstate' (one of `X86_DBG_STATEKIND_*') */
DATDEF unsigned int x86_dbg_trapstatekind;


/* The CPU state that gets loaded when `dbg_exit()' is called. */
DATDEF struct fcpustate x86_dbg_exitstate;

/* TODO: Get rid of the following two functions! */
DATDEF struct fcpustate x86_dbg_origstate; /* The CPU state originally loaded by the current thread. */
DATDEF struct fcpustate x86_dbg_viewstate; /* The CPU state currently being viewed by the debugger (for walking the stack...). */



/* 1 + the LAPIC ID of the CPU currently holding the debugger lock.
 * This value is used with `lock cmpxchgw' to describe the primary
 * lock used to ensure that only a single thread can ever be the
 * controller of debugger mode. */
DATDEF WEAK u16 x86_dbg_owner_lapicid;

/* The GDT and IDT used by the debugger. */
DATDEF struct segment x86_dbggdt[SEGMENT_COUNT];
DATDEF struct desctab const x86_dbggdt_ptr;

#ifndef __x86_dbgidt_defined
#define __x86_dbgidt_defined 1
DATDEF struct idt_segment x86_dbgidt[256];
DATDEF struct desctab const x86_dbgidt_ptr;
#endif /* !__x86_dbgidt_defined */


/* Get/set a register, given its ID
 * NOTE: When `return > buflen', then
 *       dbg_getregbyname: The contents of `buf' are undefined.
 *       dbg_setregbyname: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: id:  One of `X86_REGISTER_*' (from <asm/registers.h>) or one of `X86_DBGREGISTER_*'
 * @return: * : The required buffer size, or 0 when `name' isn't recognized. */
FUNDEF size_t NOTHROW(KCALL x86_dbg_getregbyid)(unsigned int level, unsigned int id, void *__restrict buf, size_t buflen);
FUNDEF size_t NOTHROW(KCALL x86_dbg_setregbyid)(unsigned int level, unsigned int id, void const *__restrict buf, size_t buflen);

/* Return the ID (one of `X86_REGISTER_*' from <asm/registers.h>,
 * or one of `X86_DBGREGISTER_*') from a given register name. */
FUNDEF WUNUSED ATTR_PURE NONNULL((1)) unsigned int
NOTHROW(KCALL x86_dbg_regfromname)(char const *__restrict name, size_t namelen);

#endif /* __CC__ */

/*[[[enum]]]*/
#ifdef __CC__
enum {
	X86_DBGREGISTER_FEXCEPTREGISTER = 0x80000000, /* FLAG: Lookup the register in the thread's exception-context.
	                                               *       Written as `%x.eax' or `%except.eax' */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define X86_DBGREGISTER_FEXCEPTREGISTER X86_DBGREGISTER_FEXCEPTREGISTER /* FLAG: Lookup the register in the thread's exception-context. */
#else /* __COMPILER_PREFERR_ENUMS */
#define X86_DBGREGISTER_FEXCEPTREGISTER 0x80000000 /* FLAG: Lookup the register in the thread's exception-context. */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/



/* CPU state kind codes. */
#define X86_DBG_STATEKIND_NONE 0 /* No DBG_REGLEVEL_TRAP-level CPU state */
#define X86_DBG_STATEKIND_FCPU 1 /* `struct fcpustate' */
#define X86_DBG_STATEKIND_UCPU 2 /* `struct ucpustate' */
#define X86_DBG_STATEKIND_LCPU 3 /* `struct lcpustate' */
#define X86_DBG_STATEKIND_KCPU 4 /* `struct kcpustate' */
#define X86_DBG_STATEKIND_ICPU 5 /* `struct icpustate' */
#define X86_DBG_STATEKIND_SCPU 6 /* `struct scpustate' */

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_DEBUGGER_ARCH_RT_H */
