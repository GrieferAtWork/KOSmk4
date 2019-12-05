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


#ifdef ENTER_AT_FCPUSTATE
#    define FUNCNAM      dbg_enter_fcpustate
#    define L(x)         .L##x##f
#elif defined(ENTER_AT_UCPUSTATE)
#    define FUNCNAM      dbg_enter_ucpustate
#    define L(x)         .L##x##u
#elif defined(ENTER_AT_LCPUSTATE)
#    define FUNCNAM      dbg_enter_lcpustate
#    define L(x)         .L##x##l
#elif defined(ENTER_AT_KCPUSTATE)
#    define FUNCNAM      dbg_enter_kcpustate
#    define L(x)         .L##x##k
#elif defined(ENTER_AT_ICPUSTATE)
#    define FUNCNAM      dbg_enter_icpustate
#    define L(x)         .L##x##i
#elif defined(ENTER_AT_SCPUSTATE)
#    define FUNCNAM      dbg_enter_scpustate
#    define L(x)         .L##x##s
#endif

#include <libunwind/cfi.h>

.section .text.cold
PUBLIC_FUNCTION(FUNCNAM)
	.cfi_startproc simple
	.cfi_signal_frame
	.cfi_def_cfa %esp, 0

	/* struct [fulkis]cpustate *state = %ecx */
	/* void (KCALL *main)(void *arg)  = %edx */
	/* void *arg                      = 4(%esp) */
	/* void *return_pc                = 0(%esp) */
#ifdef ENTER_AT_FCPUSTATE

	.cfi_reg_offset %edi, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI, %ecx
	.cfi_reg_offset %esi, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESI, %ecx
	.cfi_reg_offset %ebp, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBP, %ecx
	.cfi_reg_offset %esp, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP, %ecx
	.cfi_reg_offset %ebx, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBX, %ecx
	.cfi_reg_offset %edx, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDX, %ecx
	.cfi_reg_offset %ecx, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ECX, %ecx
	.cfi_reg_offset %eax, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX, %ecx
	.cfi_reg_offset %gs, OFFSET_FCPUSTATE_GS, %ecx
	.cfi_reg_offset %fs, OFFSET_FCPUSTATE_FS, %ecx
	.cfi_reg_offset %es, OFFSET_FCPUSTATE_ES, %ecx
	.cfi_reg_offset %ds, OFFSET_FCPUSTATE_DS, %ecx
	.cfi_reg_offset %cs, OFFSET_FCPUSTATE_CS, %ecx
	.cfi_reg_offset %ss, OFFSET_FCPUSTATE_SS, %ecx
	.cfi_reg_offset %eflags, OFFSET_FCPUSTATE_EFLAGS, %ecx
	.cfi_reg_offset %eip, OFFSET_FCPUSTATE_EIP, %ecx

#elif defined(ENTER_AT_UCPUSTATE)

	.cfi_reg_offset %edi, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EDI, %ecx
	.cfi_reg_offset %esi, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESI, %ecx
	.cfi_reg_offset %ebp, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EBP, %ecx
	.cfi_reg_offset %esp, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESP, %ecx
	.cfi_reg_offset %ebx, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EBX, %ecx
	.cfi_reg_offset %edx, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EDX, %ecx
	.cfi_reg_offset %ecx, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ECX, %ecx
	.cfi_reg_offset %eax, OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EAX, %ecx
	.cfi_reg_offset %gs, OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_GS, %ecx
	.cfi_reg_offset %fs, OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_FS, %ecx
	.cfi_reg_offset %es, OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_ES, %ecx
	.cfi_reg_offset %ds, OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_DS, %ecx
	.cfi_reg_offset %cs, OFFSET_UCPUSTATE_CS, %ecx
	.cfi_reg_offset %ss, OFFSET_UCPUSTATE_SS, %ecx
	.cfi_reg_offset %eflags, OFFSET_UCPUSTATE_EFLAGS, %ecx
	.cfi_reg_offset %eip, OFFSET_UCPUSTATE_EIP, %ecx

#elif defined(ENTER_AT_LCPUSTATE)

	.cfi_reg_offset %edi, OFFSET_LCPUSTATE_EDI, %ecx
	.cfi_reg_offset %esi, OFFSET_LCPUSTATE_ESI, %ecx
	.cfi_reg_offset %ebp, OFFSET_LCPUSTATE_EBP, %ecx
	.cfi_reg_offset %esp, OFFSET_LCPUSTATE_ESP, %ecx
	.cfi_reg_offset %ebx, OFFSET_LCPUSTATE_EBX, %ecx
	.cfi_reg_offset %eip, OFFSET_LCPUSTATE_EIP, %ecx

#elif defined(ENTER_AT_KCPUSTATE)

	.cfi_reg_offset %ecx, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ECX, %ecx
	.cfi_reg_offset %edi, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EDI, %ecx
	.cfi_reg_offset %esi, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ESI, %ecx
	.cfi_reg_offset %ebp, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EBP, %ecx
	.cfi_reg_offset %esp, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ESP, %ecx
	.cfi_reg_offset %ebx, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EBX, %ecx
	.cfi_reg_offset %edx, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EDX, %ecx
	.cfi_reg_offset %eax, OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EAX, %ecx
	.cfi_reg_offset %eflags, OFFSET_KCPUSTATE_EFLAGS, %ecx
	.cfi_reg_offset %eip, OFFSET_KCPUSTATE_EIP, %ecx

#elif defined(ENTER_AT_ICPUSTATE)
#define CFA_OFFSET     OFFSET_ICPUSTATE_IRREGS

	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss

	.cfi_def_cfa %ecx, OFFSET_ICPUSTATE_IRREGS
	.cfi_rel_offset %edi, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EBP
/*	.cfi_rel_offset %esp, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_ESP */
	.cfi_rel_offset %ebx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_ICPUSTATE_GPREGS+OFFSET_GPREGS_EAX
	.cfi_restore_iret_gs
	.cfi_restore_iret_fs_or_offset (OFFSET_ICPUSTATE_FS - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_es_or_offset (OFFSET_ICPUSTATE_ES - OFFSET_ICPUSTATE_IRREGS)
	.cfi_restore_iret_ds_or_offset (OFFSET_ICPUSTATE_DS - OFFSET_ICPUSTATE_IRREGS)

#elif defined(ENTER_AT_SCPUSTATE)
#define CFA_OFFSET     OFFSET_SCPUSTATE_IRREGS

	.cfi_restore_iret_eip
	.cfi_restore_iret_cs
	.cfi_restore_iret_eflags
	.cfi_restore_iret_esp
	.cfi_restore_iret_ss

	.cfi_def_cfa %ecx, OFFSET_SCPUSTATE_IRREGS
	.cfi_rel_offset %edi, OFFSET_SCPUSTATE_GPREGS+OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_SCPUSTATE_GPREGS+OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_SCPUSTATE_GPREGS+OFFSET_GPREGS_EBP
/*	.cfi_rel_offset %esp, OFFSET_SCPUSTATE_GPREGS+OFFSET_GPREGS_ESP */
	.cfi_rel_offset %ebx, OFFSET_SCPUSTATE_GPREGS+OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_SCPUSTATE_GPREGS+OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_SCPUSTATE_GPREGS+OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_SCPUSTATE_GPREGS+OFFSET_GPREGS_EAX

	.cfi_restore_iret_gs_or_offset ((OFFSET_SCPUSTATE_SGREGS+OFFSET_SGREGS_GS) - OFFSET_SCPUSTATE_IRREGS)
	.cfi_restore_iret_fs_or_offset ((OFFSET_SCPUSTATE_SGREGS+OFFSET_SGREGS_FS) - OFFSET_SCPUSTATE_IRREGS)
	.cfi_restore_iret_es_or_offset ((OFFSET_SCPUSTATE_SGREGS+OFFSET_SGREGS_ES) - OFFSET_SCPUSTATE_IRREGS)
	.cfi_restore_iret_ds_or_offset ((OFFSET_SCPUSTATE_SGREGS+OFFSET_SGREGS_DS) - OFFSET_SCPUSTATE_IRREGS)
#endif

	/* Disable interrupts */
	cli

#ifndef CONFIG_NO_SMP
	/* Figure out our LAPIC ID so we can try to acquire `dbg_activator_lapic_id',
	 * and check if the debugger was invoked recursively. */
L(acquire_lapic_lock):
	movl   %ss:x86_lapicbase, %eax
	testl  %eax, %eax
	jz     1f  /* No LAPIC --> We're the only CPU! */
	movl   %ss:APIC_ID(%eax), %eax
	andl   $APIC_ID_FMASK, %eax
	shrl   $APIC_ID_FSHIFT, %eax
	movl   %ecx, %ss:dbg_cpu_temporary(,%eax,4)
	EXTERN(__x86_dbg_cpu_temporary_b0)
	EXTERN(__x86_dbg_cpu_temporary_b1)
	EXTERN(__x86_dbg_cpu_temporary_b2)
	EXTERN(__x86_dbg_cpu_temporary_b3)
#ifdef CFA_OFFSET
	/* Encode an expression to load the new CFA */
	.cfi_escape DW_CFA_def_cfa_expression
	.cfi_escape 12
	.cfi_escape DW_OP_addr
	.cfi_escape __x86_dbg_cpu_temporary_b0
	.cfi_escape __x86_dbg_cpu_temporary_b1
	.cfi_escape __x86_dbg_cpu_temporary_b2
	.cfi_escape __x86_dbg_cpu_temporary_b3
	.cfi_escape DW_OP_reg0 + CFI_386_UNWIND_REGISTER_EAX /* dbg_cpu_temporary, %eax */
	.cfi_escape DW_OP_lit4  /* dbg_cpu_temporary, %eax, 4 */
	.cfi_escape DW_OP_mul   /* dbg_cpu_temporary, %eax * 4 */
	.cfi_escape DW_OP_plus  /* dbg_cpu_temporary + (%eax * 4) */
	.cfi_escape DW_OP_deref /* *(dbg_cpu_temporary + (%eax * 4)) */
	.cfi_escape DW_OP_plus_uconst
	.cfi_escape CFA_OFFSET  /* *(dbg_cpu_temporary + (%eax * 4)) + CFA_OFFSET */
#else /* CFA_OFFSET */
#define ENCODE_REGISTER(regid,offset) \
	.cfi_escape DW_CFA_expression; \
	.cfi_escape regid; \
	.cfi_escape 12; \
	.cfi_escape DW_OP_addr; \
	.cfi_escape __x86_dbg_cpu_temporary_b0; \
	.cfi_escape __x86_dbg_cpu_temporary_b1; \
	.cfi_escape __x86_dbg_cpu_temporary_b2; \
	.cfi_escape __x86_dbg_cpu_temporary_b3; /* dbg_cpu_temporary */ \
	.cfi_escape DW_OP_reg0 + CFI_386_UNWIND_REGISTER_EAX; /* dbg_cpu_temporary, %eax */ \
	.cfi_escape DW_OP_lit4;  /* dbg_cpu_temporary, %eax, 4 */ \
	.cfi_escape DW_OP_mul;   /* dbg_cpu_temporary, %eax * 4 */ \
	.cfi_escape DW_OP_plus;  /* dbg_cpu_temporary + (%eax * 4) */ \
	.cfi_escape DW_OP_deref; /* *(dbg_cpu_temporary + (%eax * 4)) */ \
	.cfi_escape DW_OP_plus_uconst; \
	.cfi_escape offset;      /* *(dbg_cpu_temporary + (%eax * 4)) + offset */ \
/**/

#ifdef ENTER_AT_FCPUSTATE
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EAX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EDI,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_ESI,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESI)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EBP,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBP)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_ESP,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EBX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBX)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EDX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDX)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_ECX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ECX)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_GS,OFFSET_FCPUSTATE_GS)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_FS,OFFSET_FCPUSTATE_FS)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_ES,OFFSET_FCPUSTATE_ES)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_DS,OFFSET_FCPUSTATE_DS)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_CS,OFFSET_FCPUSTATE_CS)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_SS,OFFSET_FCPUSTATE_SS)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EFLAGS,OFFSET_FCPUSTATE_EFLAGS)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EIP,OFFSET_FCPUSTATE_EIP)
#elif defined(ENTER_AT_UCPUSTATE)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EAX,OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EAX)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EDI,OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EDI)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_ESI,OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESI)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EBP,OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EBP)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_ESP,OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESP)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EBX,OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EBX)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EDX,OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EDX)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_ECX,OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ECX)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_GS,OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_GS)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_FS,OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_FS)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_ES,OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_ES)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_DS,OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_DS)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_CS,OFFSET_UCPUSTATE_CS)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_SS,OFFSET_UCPUSTATE_SS)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EFLAGS,OFFSET_UCPUSTATE_EFLAGS)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EIP,OFFSET_UCPUSTATE_EIP)
#elif defined(ENTER_AT_LCPUSTATE)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EDI,OFFSET_LCPUSTATE_EDI)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_ESI,OFFSET_LCPUSTATE_ESI)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EBP,OFFSET_LCPUSTATE_EBP)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_ESP,OFFSET_LCPUSTATE_ESP)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EBX,OFFSET_LCPUSTATE_EBX)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EIP,OFFSET_LCPUSTATE_EIP)
#elif defined(ENTER_AT_KCPUSTATE)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EAX,OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EAX)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_ECX,OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ECX)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EDI,OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EDI)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_ESI,OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ESI)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EBP,OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EBP)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_ESP,OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ESP)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EBX,OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EBX)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EDX,OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EDX)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EFLAGS,OFFSET_KCPUSTATE_EFLAGS)
	ENCODE_REGISTER(CFI_386_UNWIND_REGISTER_EIP,OFFSET_KCPUSTATE_EIP)
#else
#error "Unsupported register mode"
#endif
#undef ENCODE_REGISTER
#endif /* !CFA_OFFSET */

	leal   1(%eax), %ecx
	xorl   %eax, %eax
	lock;  cmpxchgl %ecx, %ss:dbg_activator_lapic_id
	jz     2f             /* First time the debugger is entered. */
	/* Check if this is a recursive entry? */
	cmpl   %eax, %ecx     /* PREVIOUS_LAPIC_ID == MY_LAPIC_ID */
	je     2f             /* Recursive debugger entry */
	movl   %ss:dbg_cpu_temporary-4(,%ecx,4), %ecx
	.cfi_remember_state
	.cfi_def_cfa %ecx, 0
	/* This is where we get if some other CPU is currently inside the debugger...
	 * At this point, either re-enable interrupts (if they were enabled before),
	 * and hlt to wait for the locking core to exit debugger mode, at which point
	 * it should send an IPI to let us know that our turn has come, or keep on
	 * idling (only using pause) if we're not allowed to turn on interrupts. */
	pause
	testl  $(EFLAGS_IF), %ss:0(%esp)
	jz     L(acquire_lapic_lock) /* Not allowed to block... */
	sti
	hlt
	cli
	jmp    L(acquire_lapic_lock)
	.cfi_restore_state
2:	movl   %ss:dbg_cpu_temporary-4(,%ecx,4), %ecx
1:	.cfi_def_cfa %ecx, 0
#endif /* !CONFIG_NO_SMP */

	/* We're now in debugger mode! (or at least: we're now holding the debugger mode lock)
	 * At this point, we must check if the caller was already in debugger mode (as is the
	 * case when `dbg_active' is already non-zero), in which case we musn't override the
	 * currently saved `dbg_exitstate' or `dbg_viewstate', but simply re-set the debugger
	 * stack and re-initialize the debugger CPU context, but not change anything about
	 * where to return (this is what happens when the user pressed CTRL+C when the debugger
	 * command-line driver is active, allowing them to soft-reset the debugger commandline
	 * in case the current command gets into a loop) */
	EXTERN(dbg_active)
	cmpl   $(0), %ss:dbg_active
	jne    .Lcommon_recursive_debugger

#define COPYWORD(src_offset,dst_offset) \
	movl   %ss:(src_offset)(%ecx), %eax; \
	movl   %eax, %ss:dbg_exitstate+(dst_offset)
#define COPYSEG(src_reg,dst_offset) \
	movl   src_reg, %eax; \
	movl   %eax, %ss:dbg_exitstate+(dst_offset)
#define NULLREG(dst_offset) \
	movl   $(0), %ss:dbg_exitstate+(dst_offset)
#define FIXEDREG(value,dst_offset) \
	movl   $value, %ss:dbg_exitstate+(dst_offset)



	/* Copy (and convert) the given cpustate into `dbg_exitstate' */
#ifdef ENTER_AT_FCPUSTATE
.Lindex = 0
.rept SIZEOF_FCPUSTATE/4
	/* Simple case: We can just to a 1-on-1 copy! */
	COPYWORD(.Lindex,.Lindex)
	.Lindex = .Lindex + 4
.endr
#else
#if defined(ENTER_AT_UCPUSTATE)
	COPYWORD(OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EDI,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI)
	COPYWORD(OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESI,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESI)
	COPYWORD(OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EBP,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBP)
	COPYWORD(OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ESP,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP)
	COPYWORD(OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EBX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBX)
	COPYWORD(OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EDX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDX)
	COPYWORD(OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_ECX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ECX)
	COPYWORD(OFFSET_UCPUSTATE_GPREGS+OFFSET_GPREGS_EAX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX)
	COPYWORD(OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_GS,OFFSET_FCPUSTATE_GS)
	COPYWORD(OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_FS,OFFSET_FCPUSTATE_FS)
	COPYWORD(OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_ES,OFFSET_FCPUSTATE_ES)
	COPYWORD(OFFSET_UCPUSTATE_SGREGS+OFFSET_SGREGS_DS,OFFSET_FCPUSTATE_DS)
	COPYWORD(OFFSET_UCPUSTATE_CS,OFFSET_FCPUSTATE_CS)
	COPYWORD(OFFSET_UCPUSTATE_SS,OFFSET_FCPUSTATE_SS)
	COPYWORD(OFFSET_UCPUSTATE_EFLAGS,OFFSET_FCPUSTATE_EFLAGS)
	COPYWORD(OFFSET_UCPUSTATE_EIP,OFFSET_FCPUSTATE_EIP)
#elif defined(ENTER_AT_LCPUSTATE)
	COPYWORD(OFFSET_LCPUSTATE_EDI,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI)
	COPYWORD(OFFSET_LCPUSTATE_ESI,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESI)
	COPYWORD(OFFSET_LCPUSTATE_EBP,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBP)
	COPYWORD(OFFSET_LCPUSTATE_ESP,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP)
	COPYWORD(OFFSET_LCPUSTATE_EBX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBX)
	COPYWORD(OFFSET_LCPUSTATE_EIP,OFFSET_FCPUSTATE_EIP)
	NULLREG(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX)
	NULLREG(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ECX)
	NULLREG(OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDX)
	COPYSEG(%gs,OFFSET_FCPUSTATE_GS)
	FIXEDREG(SEGMENT_KERNEL_FSBASE,OFFSET_FCPUSTATE_FS)
	FIXEDREG(SEGMENT_USER_DATA_RPL,OFFSET_FCPUSTATE_ES)
	FIXEDREG(SEGMENT_USER_DATA_RPL,OFFSET_FCPUSTATE_DS)
	FIXEDREG(SEGMENT_KERNEL_CODE,OFFSET_FCPUSTATE_CS)
	FIXEDREG(SEGMENT_KERNEL_DATA,OFFSET_FCPUSTATE_SS)
	pushfl
	popl   %ss:dbg_exitstate+OFFSET_FCPUSTATE_EFLAGS
#elif defined(ENTER_AT_KCPUSTATE)
	COPYWORD(OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EDI,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI)
	COPYWORD(OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ESI,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESI)
	COPYWORD(OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EBP,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBP)
	COPYWORD(OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ESP,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP)
	COPYWORD(OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EBX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBX)
	COPYWORD(OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EDX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDX)
	COPYWORD(OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_ECX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ECX)
	COPYWORD(OFFSET_KCPUSTATE_GPREGS+OFFSET_GPREGS_EAX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX)
	COPYWORD(OFFSET_KCPUSTATE_EFLAGS,OFFSET_FCPUSTATE_EFLAGS)
	COPYWORD(OFFSET_KCPUSTATE_EIP,OFFSET_FCPUSTATE_EIP)
	COPYSEG(%gs,OFFSET_FCPUSTATE_GS)
	FIXEDREG(SEGMENT_KERNEL_FSBASE,OFFSET_FCPUSTATE_FS)
	FIXEDREG(SEGMENT_USER_DATA_RPL,OFFSET_FCPUSTATE_ES)
	FIXEDREG(SEGMENT_USER_DATA_RPL,OFFSET_FCPUSTATE_DS)
	FIXEDREG(SEGMENT_KERNEL_CODE,OFFSET_FCPUSTATE_CS)
	FIXEDREG(SEGMENT_KERNEL_DATA,OFFSET_FCPUSTATE_SS)
#elif defined(ENTER_AT_ICPUSTATE) || defined(ENTER_AT_SCPUSTATE)
	/* icpustate or scpustate */
#ifdef ENTER_AT_ICPUSTATE
	COPYWORD(OFFSET_ICPUSTATE_IRREGS+OFFSET_GPREGS_EDI,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI)
	COPYWORD(OFFSET_ICPUSTATE_IRREGS+OFFSET_GPREGS_ESI,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESI)
	COPYWORD(OFFSET_ICPUSTATE_IRREGS+OFFSET_GPREGS_EBP,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBP)
/*	COPYWORD(OFFSET_ICPUSTATE_IRREGS+OFFSET_GPREGS_ESP,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP) */
	COPYWORD(OFFSET_ICPUSTATE_IRREGS+OFFSET_GPREGS_EBX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBX)
	COPYWORD(OFFSET_ICPUSTATE_IRREGS+OFFSET_GPREGS_EDX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDX)
	COPYWORD(OFFSET_ICPUSTATE_IRREGS+OFFSET_GPREGS_ECX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ECX)
	COPYWORD(OFFSET_ICPUSTATE_IRREGS+OFFSET_GPREGS_EAX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX)
	COPYSEG(%gs,OFFSET_FCPUSTATE_GS)
	COPYWORD(OFFSET_ICPUSTATE_FS,OFFSET_FCPUSTATE_FS)
	COPYWORD(OFFSET_ICPUSTATE_ES,OFFSET_FCPUSTATE_ES)
	COPYWORD(OFFSET_ICPUSTATE_DS,OFFSET_FCPUSTATE_DS)
#define IRREGS_OFFSET   OFFSET_ICPUSTATE_IRREGS
#else /* ENTER_AT_ICPUSTATE */
	COPYWORD(OFFSET_SCPUSTATE_IRREGS+OFFSET_GPREGS_EDI,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI)
	COPYWORD(OFFSET_SCPUSTATE_IRREGS+OFFSET_GPREGS_ESI,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESI)
	COPYWORD(OFFSET_SCPUSTATE_IRREGS+OFFSET_GPREGS_EBP,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBP)
/*	COPYWORD(OFFSET_SCPUSTATE_IRREGS+OFFSET_GPREGS_ESP,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP) */
	COPYWORD(OFFSET_SCPUSTATE_IRREGS+OFFSET_GPREGS_EBX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBX)
	COPYWORD(OFFSET_SCPUSTATE_IRREGS+OFFSET_GPREGS_EDX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDX)
	COPYWORD(OFFSET_SCPUSTATE_IRREGS+OFFSET_GPREGS_ECX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ECX)
	COPYWORD(OFFSET_SCPUSTATE_IRREGS+OFFSET_GPREGS_EAX,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX)
	COPYWORD(OFFSET_SCPUSTATE_SGREGS+OFFSET_SGREGS_GS,OFFSET_FCPUSTATE_GS)
	COPYWORD(OFFSET_SCPUSTATE_SGREGS+OFFSET_SGREGS_FS,OFFSET_FCPUSTATE_FS)
	COPYWORD(OFFSET_SCPUSTATE_SGREGS+OFFSET_SGREGS_ES,OFFSET_FCPUSTATE_ES)
	COPYWORD(OFFSET_SCPUSTATE_SGREGS+OFFSET_SGREGS_DS,OFFSET_FCPUSTATE_DS)
#define IRREGS_OFFSET   OFFSET_SCPUSTATE_IRREGS
#endif /* !ENTER_AT_ICPUSTATE */
	/* Load information from the IRET tail. */

	/* Check for a VM86 IRET tail. */
#define IRET(offset)  (IRREGS_OFFSET+(offset))(%ecx)
	testl  $(EFLAGS_VM), IRET(OFFSET_IRREGS_EFLAGS)
	jz     L(no_vm86_iret)
	/* VM86 IRET */
	COPYWORD(IRREGS_OFFSET+OFFSET_IRREGS_ES,OFFSET_FCPUSTATE_ES)
	COPYWORD(IRREGS_OFFSET+OFFSET_IRREGS_DS,OFFSET_FCPUSTATE_DS)
	COPYWORD(IRREGS_OFFSET+OFFSET_IRREGS_FS,OFFSET_FCPUSTATE_FS)
	COPYWORD(IRREGS_OFFSET+OFFSET_IRREGS_GS,OFFSET_FCPUSTATE_GS)
	jmp    L(copy_user_iret_regs)
L(no_vm86_iret):
	/* Check for a user-space IRET tail. */
	testl  $(3), IRET(OFFSET_IRREGS_CS)
	jz     L(no_user_iret)
L(copy_user_iret_regs):
	COPYWORD(IRREGS_OFFSET+OFFSET_IRREGS_SS,OFFSET_FCPUSTATE_SS)
	COPYWORD(IRREGS_OFFSET+OFFSET_IRREGS_ESP,OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP)
	jmp    L(copy_common_iret_regs)
L(no_user_iret):
	/* Kernel-space IRET tail */
	FIXEDREG(SEGMENT_KERNEL_DATA,OFFSET_FCPUSTATE_SS)
	/* The return-SP is the end-address of the IRREGS structure. */
	leal   IRREGS_OFFSET+SIZEOF_IRREGS_KERNEL(%ecx), %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP
L(copy_common_iret_regs):
	COPYWORD(IRREGS_OFFSET+OFFSET_IRREGS_CS,OFFSET_FCPUSTATE_CS)
	COPYWORD(IRREGS_OFFSET+OFFSET_IRREGS_EFLAGS,OFFSET_FCPUSTATE_EFLAGS)
	COPYWORD(IRREGS_OFFSET+OFFSET_IRREGS_EIP,OFFSET_FCPUSTATE_EIP)
#undef IRET
#undef IRREGS_OFFSET
#endif

	movl   $(0), %ss:dbg_exitstate+OFFSET_FCPUSTATE_TR
	str    %ss:dbg_exitstate+OFFSET_FCPUSTATE_TR
	movl   $(0), %ss:dbg_exitstate+OFFSET_FCPUSTATE_LDT
	sldt   %ss:dbg_exitstate+OFFSET_FCPUSTATE_LDT
	movl   %cr0, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR0
	movl   %cr2, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR2
	movl   %cr3, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR3
	movl   %cr4, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_COREGS+OFFSET_COREGS_CR4
	movl   %dr0, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR0
	movl   %dr1, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR1
	movl   %dr2, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR2
	movl   %dr3, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR3
	movl   %dr6, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR6
	movl   %dr7, %eax
	movl   %eax, %ss:dbg_exitstate+OFFSET_FCPUSTATE_DRREGS+OFFSET_DRREGS_DR7
	sgdtl  %ss:dbg_exitstate+OFFSET_FCPUSTATE_GDT
	sidtl  %ss:dbg_exitstate+OFFSET_FCPUSTATE_IDT
#endif
#undef FIXEDREG
#undef NULLREG
#undef COPYSEG
#undef COPYWORD



#ifdef DEFINED_Lcommon_recursive_debugger
	jmp    .Lcommon_recursive_debugger
	.cfi_endproc
#else /* DEFINED_Lcommon_recursive_debugger */
#define DEFINED_Lcommon_recursive_debugger 1
.Lcommon_recursive_debugger:
	/* Setup CFI to restore from `dbg_exitstate' */
	movl   $(dbg_exitstate), %esi
	.cfi_endproc
	.cfi_startproc simple
	.cfi_iret_signal_frame
	.cfi_def_cfa %esi, 0
	.cfi_rel_offset %edi, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDI
	.cfi_rel_offset %esi, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESI
	.cfi_rel_offset %ebp, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBP
	.cfi_rel_offset %esp, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ESP
	.cfi_rel_offset %ebx, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EBX
	.cfi_rel_offset %edx, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EDX
	.cfi_rel_offset %ecx, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_ECX
	.cfi_rel_offset %eax, OFFSET_FCPUSTATE_GPREGS+OFFSET_GPREGS_EAX
	.cfi_rel_offset %eflags, OFFSET_FCPUSTATE_EFLAGS
	.cfi_rel_offset %eip, OFFSET_FCPUSTATE_EIP
	.cfi_rel_offset %es, OFFSET_FCPUSTATE_ES
	.cfi_rel_offset %cs, OFFSET_FCPUSTATE_CS
	.cfi_rel_offset %ss, OFFSET_FCPUSTATE_SS
	.cfi_rel_offset %ds, OFFSET_FCPUSTATE_DS
	.cfi_rel_offset %fs, OFFSET_FCPUSTATE_FS
	.cfi_rel_offset %gs, OFFSET_FCPUSTATE_GS

	/* The debugger was entered recursively!
	 * Reset parts of the debugger control state,
	 * and restore the expected debugger CPU context. */
	movl   $(pagedir_kernel_phys), %eax
	movl   %eax, %cr3
	movl   %cr0, %eax
	orl    $(CR0_PE|CR0_PG), %eax
	andl   $~(CR0_TS|CR0_WP), %eax
	movl   %eax, %cr0

	/* Load the debugger-specific GDT / IDT */
	lgdtl  %ss:dbg_gdt_pointer
	lidtl  %ss:dbg_idt_pointer

	/* Load segment registers. */
	movl   $(SEGMENT_USER_DATA_RPL), %eax
	movl   %eax, %ds
	movl   %eax, %es
	movl   $(SEGMENT_KERNEL_FSBASE), %eax
	movl   %eax, %fs
	movl   $(SEGMENT_USER_GSBASE_RPL), %eax
	movl   %eax, %gs
	movl   $(SEGMENT_KERNEL_DATA), %eax
	movl   %eax, %ss
	ljmpl  $(SEGMENT_KERNEL_CODE), $(1f) /* movl $(SEGMENT_KERNEL_CODE), %cs */
1:

	/* x86_debug_gdt[SEGMENT_CPU_TSS].busy = 0; */
	andb   $(0b11111101), x86_debug_gdt+SEGMENT_CPU_TSS+5
	movw   $(SEGMENT_CPU_TSS), %ax
	ltrw   %ax

	movw   $(SEGMENT_CPU_LDT), %ax
	lldtw  %ax

	movl   4(%esp), %eax  /* void *arg = 4(%esp) */

	EXTERN(__kernel_debug_stack)
	movl   $(__kernel_debug_stack + KERNEL_DEBUG_STACKSIZE), %esp

	pushl  %eax           /* void *arg */
	pushl  $(dbg_exit)    /* Return address... */
	pushl  %edx           /* void (KCALL *main)(void *arg) */

	/* Check if we need to initialize the debugger? */
	cmpl   $(0), dbg_active
	jne    1f
	movl   $(1), dbg_active /* Indicate that the debugger is now active */
	EXTERN(dbg_init)
	call   dbg_init       /* Initialize first time around */
1:
	/* Reset the current debugger state. */
	EXTERN(dbg_reset)
	call   dbg_reset

	/* Enable interrupts while in debugger-mode */
	sti

	ret                   /* (*main)(arg) --> return to `dbg_exit()' */
	.cfi_endproc
#endif /* !DEFINED_Lcommon_recursive_debugger */
END(FUNCNAM)

#undef CFA_OFFSET
#undef L
#undef FUNCNAM
#undef ENTER_AT_FCPUSTATE
#undef ENTER_AT_UCPUSTATE
#undef ENTER_AT_LCPUSTATE
#undef ENTER_AT_KCPUSTATE
#undef ENTER_AT_ICPUSTATE
#undef ENTER_AT_SCPUSTATE


