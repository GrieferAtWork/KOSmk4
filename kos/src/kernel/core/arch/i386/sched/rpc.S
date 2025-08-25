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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#include <kernel/rt/except-handler.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/host.h>

#include <cfi.h>
#include <asm/cpu-flags.h>
#include <asm/instr/compat.h>
#include <asm/instr/ttest.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/rpc.h>

#ifdef __x86_64__
#include <asm/instr/fsgsbase.h>
#include <asm/instr/kgsbase.h>
#endif /* __x86_64__ */

#ifdef __x86_64__
#define cpu_apply_icpustate_Psp cpu_apply_icpustate_rsp
#else /* __x86_64__ */
#define cpu_apply_icpustate_Psp cpu_apply_icpustate_esp
#endif /* !__x86_64__ */

#define SIZEOF_POINTER              __SIZEOF_POINTER__
#define rpc_context__rc_state       __SIZEOF_POINTER__
#define task__t_self                OFFSET_TASK_SELF
#define task__t_refcnt              OFFSET_TASK_REFCNT
#define task__t_flags               OFFSET_TASK_FLAGS
#define task__t_cpu                 OFFSET_TASK_CPU
#define task__t_mman                OFFSET_TASK_MMAN
#define task__t_mman_tasks__le_next OFFSET_TASK_MMAN_TASKS_NEXT
#define task__t_mman_tasks__le_prev OFFSET_TASK_MMAN_TASKS_PREV
#define task__t_heapsz              OFFSET_TASK_HEAPSZ
#define task__t_state               OFFSET_TASK_STATE
#define task___t_next               OFFSET_TASK__NEXT



/* Restore function for functions pushed by `task_asyncrpc_push()'
 * This  function   is   entered   with  the   stack   set   like:
 *   0(%Psp): struct rpc_context */
.section .text
INTERN_FUNCTION(x86_task_asyncrpc_restore)
	.cfi_startproc simple
	.cfi_signal_frame__rpc
/*[[[cfi{register='%cfa'}
	push   %Psp            # `(struct rpc_context *)%Psp'
	add    $SIZEOF_POINTER # `&((struct rpc_context *)%Psp)->rc_state'
	deref                  # `((struct rpc_context *)%Psp)->rc_state'
]]]*/
#ifdef __x86_64__
	.cfi_escape 15,5,119,0,35,8,6
#else /* __x86_64__ */
	.cfi_escape 15,5,116,0,35,4,6
#endif /* !__x86_64__ */
/*[[[end]]]*/
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(0)

	/* Load the return-icpustate into `%Psp' */
	movP   rpc_context__rc_state(%Psp), %Psp
	.cfi_def_cfa_register %Psp

	/* Load the newly updated cpustate. */
	EXTERN(cpu_apply_icpustate_Psp)
	jmp    cpu_apply_icpustate_Psp
	.cfi_endproc
END(x86_task_asyncrpc_restore)




/* >> PUBLIC NOBLOCK NONNULL((1, 2)) void FCALL
 * >> task_asyncrpc_execnow(struct rpc_context *__restrict context,
 * >>                       prpc_exec_callback_t func, void *cookie);
 * Arch-specific function:
 * Execute the given `func' using the register state at the time of
 * the call to this function,  whilst passing the given  `context'. */
.section .text
PUBLIC_FUNCTION(task_asyncrpc_execnow)
	.cfi_startproc
	.cfi_def_cfa %Psp, 0
	popP_cfi %Pax
	.cfi_register %Pip, %Pax
#ifdef __x86_64__
	movq   %rsp, %rcx
	pushq_cfi $(SEGMENT_KERNEL_DATA0) /* %ss */
	.cfi_rel_offset %ss, 0
	pushq_cfi %rcx                    /* %Psp */
	.cfi_rel_offset %rsp, 0
#endif /* __x86_64__ */
	pushfP_cfi_r                      /* %Pflags */
	pushP_cfi $(SEGMENT_KERNEL_CODE)  /* %cs */
	.cfi_rel_offset %cs, 0
	pushP_cfi  %Pax                   /* %Pip */
	.cfi_rel_offset %Pip, 0
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R

	/* Save the register state in `context->rc_state' */
	movP   %R_fcall0P, %Pbx
	movP   %Psp, rpc_context__rc_state(%Pbx)

	/* Load arguments */
	movP   %R_fcall1P, %Pax
#ifdef __x86_64__
	movP   %Pdx, %R_fcall1P
#else /* __x86_64__ */
	movP   (OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL)(%Psp), %R_fcall1P
#endif /* !__x86_64__ */

	/* Invoke the given `func' */
	callP  *%Pax
	movP   rpc_context__rc_state(%Pbx), %Psp

	/* Load the newly updated cpustate. */
	EXTERN(cpu_apply_icpustate_Psp)
	jmp    cpu_apply_icpustate_Psp
	.cfi_endproc
END(task_asyncrpc_execnow)


/* Define low-level implementations for `task_serve()' */
#ifndef __INTELLISENSE__
#define DEFINE_task_serve
#include "rpc-task_serve.S.inl"
#define DEFINE_task_serve_nx
#include "rpc-task_serve.S.inl"
#define DEFINE_task_serve_with_sigmask
#include "rpc-task_serve.S.inl"
#endif /* !__INTELLISENSE__ */



/* Entry point for IRET tails that have been re-directed for sysret.
 * Used to  redirect  how  the kernel  will  return  to  user-space:
 * >> redirect_iret_for_sysret() {
 * >>     struct irregs_kernel *irr;
 * >>     PREEMPTION_DISABLE(); // Redirection is only
 * >> #ifndef __I386_NO_VM86
 * >>     if (IS_VM86_TASK) {
 * >>         irr = GET_KERNEL_STACK_BASE() - sizeof(struct irregs_vm86);
 * >>     } else
 * >> #endif // !__I386_NO_VM86
 * >>     {
 * >>         irr = GET_KERNEL_STACK_BASE() - sizeof(struct irregs_user);
 * >>     }
 * >>     memcpy(&PERTASK(this_x86_sysret_iret),irr,
 * >>            sizeof(struct irregs_kernel));
 * >>     irr->ir_eip    = &x86_userexcept_sysret;
 * >>     irr->ir_cs     = SEGMENT_KERNEL_CS;
 * >>     irr->ir_eflags = 0; // Most importantly: disable interrupts
 * >> }
 * WARNING:
 *    Because of the redirection, in order to get/set any of the kernel  IRET
 *    registers when inside of an interrupt/syscall with preemption  enabled,
 *    you must always use the functions below, so-as to ensure that you don't
 *    re-override  the sysret redirection, but modify the saved state when it
 *    comes to the IRET tail. */
/* FUNDEF void ASMCALL x86_userexcept_sysret(void); */
.section .text
	.cfi_startproc simple
	/* NOTE: No personality function is defined  here, because the only  thing
	 *       it could ever do is  silently try to use `userexcept_handler'  in
	 *       order to push the  exception into user-space. However,  knowledge
	 *       of how to  restart the current  syscall/interrupt isn't  present,
	 *       as that would have had to be implemented somewhere higher on  the
	 *       call-stack, meaning that  we should  only ever get  here with  an
	 *       exception set when the current kernel function's not restartable.
	 *
	 * As such, we can also just let the regular fallback exception propagation
	 * take hold, which is already capable of this scenario. */


	/* CFI instrumentation to restore registers from the correct locations.
	 * Note the use of `ifnotimpl "KOS"', since GDB p00ps itself if we  let
	 * it see our `form_tls_address' instruction... */
	EXTERN(this_x86_sysret_iret)
/*[[[deemon
import outputForAssembly from .......misc.libgen.cfi.comp;
function restoreSimpleRegister(arch, reg) {
	outputForAssembly(arch, '%' + reg, r'
		ifnotimpl "KOS", 1f
		const1u @(this_x86_sysret_iret + OFFSET_IRREGS_' + reg.upper() + r')
		form_tls_address
		deref
		ret
	1:	push   %' + reg);
}
function restoreVm86Register(reg) {
	outputForAssembly('i386', '%' + reg, r'
		ifnotimpl "KOS", 1f
		const1u @(this_x86_sysret_iret + OFFSET_IRREGS_EFLAGS)
		form_tls_address
		deref
		and    $EFLAGS_VM
		jz     pop, 1f                   # Not a vm86 thread
		breg   %esp, $OFFSET_IRREGS_' + reg.upper() + r' - $SIZEOF_IRREGS_KERNEL
		deref                            # Load from the vm86 IRET tail
		ret
	1:	push   %' + reg + r'             # Unchanged');
}
print("#ifdef __x86_64__");
for (local reg: ["rip", "cs", "rflags", "rsp", "ss"])
	restoreSimpleRegister('x86_64', reg);
print("#else /" "* __x86_64__ *" "/");
for (local reg: ["eip", "cs", "eflags"])
	restoreSimpleRegister('i386', reg);
print("#ifndef __I386_NO_VM86");
for (local reg: { "es", "ds", "fs", "gs" })
	restoreVm86Register(reg);
print("#endif /" "* __I386_NO_VM86 *" "/");
print("#endif /" "* !__x86_64__ *" "/");
]]]*/
#ifdef __x86_64__
__ASM_L(	.cfi_escape 22,16,18,47,3,0,75,79,83,47,7,0,8,(this_x86_sysret_iret + OFFSET_IRREGS_RIP),155,6)
__ASM_L(	.cfi_escape 47,2,0,128,0)
__ASM_L(	.cfi_escape 22,51,19,47,3,0,75,79,83,47,7,0,8,(this_x86_sysret_iret + OFFSET_IRREGS_CS),155,6)
__ASM_L(	.cfi_escape 47,3,0,146,51,0)
__ASM_L(	.cfi_escape 22,49,19,47,3,0,75,79,83,47,7,0,8,(this_x86_sysret_iret + OFFSET_IRREGS_RFLAGS),155,6)
__ASM_L(	.cfi_escape 47,3,0,146,49,0)
__ASM_L(	.cfi_escape 22,7,18,47,3,0,75,79,83,47,7,0,8,(this_x86_sysret_iret + OFFSET_IRREGS_RSP),155,6)
__ASM_L(	.cfi_escape 47,2,0,119,0)
__ASM_L(	.cfi_escape 22,52,19,47,3,0,75,79,83,47,7,0,8,(this_x86_sysret_iret + OFFSET_IRREGS_SS),155,6)
__ASM_L(	.cfi_escape 47,3,0,146,52,0)
#else /* __x86_64__ */
__ASM_L(	.cfi_escape 22,8,18,47,3,0,75,79,83,47,7,0,8,(this_x86_sysret_iret + OFFSET_IRREGS_EIP),155,6)
__ASM_L(	.cfi_escape 47,2,0,120,0)
__ASM_L(	.cfi_escape 22,41,19,47,3,0,75,79,83,47,7,0,8,(this_x86_sysret_iret + OFFSET_IRREGS_CS),155,6)
__ASM_L(	.cfi_escape 47,3,0,146,41,0)
__ASM_L(	.cfi_escape 22,9,18,47,3,0,75,79,83,47,7,0,8,(this_x86_sysret_iret + OFFSET_IRREGS_EFLAGS),155,6)
__ASM_L(	.cfi_escape 47,2,0,121,0)
#ifndef __I386_NO_VM86
__ASM_L(	.cfi_escape 22,40,31,47,3,0,75,79,83,47,19,0,8,(this_x86_sysret_iret + OFFSET_IRREGS_EFLAGS),155,6)
__ASM_L(	.cfi_escape 16,128,128,8,26,32,40,6,0,116,8,6,47,3,0,146)
__ASM_L(	.cfi_escape 40,0)
__ASM_L(	.cfi_escape 22,43,31,47,3,0,75,79,83,47,19,0,8,(this_x86_sysret_iret + OFFSET_IRREGS_EFLAGS),155,6)
__ASM_L(	.cfi_escape 16,128,128,8,26,32,40,6,0,116,12,6,47,3,0,146)
__ASM_L(	.cfi_escape 43,0)
__ASM_L(	.cfi_escape 22,44,31,47,3,0,75,79,83,47,19,0,8,(this_x86_sysret_iret + OFFSET_IRREGS_EFLAGS),155,6)
__ASM_L(	.cfi_escape 16,128,128,8,26,32,40,6,0,116,16,6,47,3,0,146)
__ASM_L(	.cfi_escape 44,0)
__ASM_L(	.cfi_escape 22,45,31,47,3,0,75,79,83,47,19,0,8,(this_x86_sysret_iret + OFFSET_IRREGS_EFLAGS),155,6)
__ASM_L(	.cfi_escape 16,128,128,8,26,32,40,6,0,116,20,6,47,3,0,146)
__ASM_L(	.cfi_escape 45,0)
#endif /* __I386_NO_VM86 */
#endif /* !__x86_64__ */
/*[[[end]]]*/
	.cfi_def_cfa %Psp, -SIZEOF_IRREGS_KERNEL
#ifndef __x86_64__
	/* Always unwind %esp and %ss from `irregs_user'.
	 * If we  used `cfi_restore_iret_(esp|ss)',  then
	 * incorrect  values  would be  unwound  after an
	 * IRET tail redirection. */
	.cfi_rel_offset %Psp, (OFFSET_IRREGS_PSP - SIZEOF_IRREGS_KERNEL)
	.cfi_rel_offset %ss,  (OFFSET_IRREGS_SS - SIZEOF_IRREGS_KERNEL)
#endif /* !__x86_64__ */

	nop /* Required to allow for detection during unwinding. */
PUBLIC_FUNCTION(x86_userexcept_sysret)

	/* Entry point for redirected syscall return paths */

	/* Construct an IRET tail with information from `this_x86_sysret_iret' */
#ifdef __x86_64__
	/* Note that our current %gs.base still points to kernel-space. */
	pushP_cfi  %segtls:(this_x86_sysret_iret + OFFSET_IRREGS_SS)
	.cfi_rel_offset %ss, 0
	pushP_cfi  %segtls:(this_x86_sysret_iret + OFFSET_IRREGS_PSP)
	.cfi_rel_offset %Psp, 0
#else /* __x86_64__ */
#define SPOFFSETOF_ICPUSTATE (-(OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL))
#define SPOFFSETOF_GPREGS    (SPOFFSETOF_ICPUSTATE + OFFSET_ICPUSTATE_GPREGS)
	movP   %Pax, %ss:SPOFFSETOF_GPREGS + OFFSET_GPREGS_PAX(%Psp)
	.cfi_rel_offset %eax, SPOFFSETOF_GPREGS + OFFSET_GPREGS_PAX
	movP   %fs, %Pax
	movP   %Pax, %ss:SPOFFSETOF_ICPUSTATE + OFFSET_ICPUSTATE_FS(%Psp)
	.cfi_restore_iret_fs_or_offset (-OFFSET_ICPUSTATE_IRREGS) + OFFSET_ICPUSTATE_FS, 0
#undef SPOFFSETOF_ICPUSTATE
#undef SPOFFSETOF_GPREGS
	/* EAX and FS have now been saved, so we can load the KERNEL_FSBASE segment. */
	movw   $(SEGMENT_KERNEL_FSBASE), %ax
	movw   %ax, %fs
#endif /* !__x86_64__ */
	pushP_cfi  %segtls:(this_x86_sysret_iret + OFFSET_IRREGS_PFLAGS)
	.cfi_rel_offset %Pflags, 0
	pushP_cfi  %segtls:(this_x86_sysret_iret + OFFSET_IRREGS_CS)
	.cfi_rel_offset %cs, 0
	pushP_cfi  %segtls:(this_x86_sysret_iret + OFFSET_IRREGS_PIP)
	.cfi_rel_offset %Pip, 0

#ifndef __x86_64__
#define CFAOFFSETOF_ICPUSTATE (-OFFSET_ICPUSTATE_IRREGS)
	pushP_cfi  %ds   /* ir_ds */
	.cfi_restore_iret_ds_or_offset CFAOFFSETOF_ICPUSTATE + OFFSET_ICPUSTATE_DS, CFAOFFSETOF_ICPUSTATE + OFFSET_ICPUSTATE_IRREGS
	pushP_cfi  %es   /* ir_es */
	.cfi_restore_iret_es_or_offset CFAOFFSETOF_ICPUSTATE + OFFSET_ICPUSTATE_ES, CFAOFFSETOF_ICPUSTATE + OFFSET_ICPUSTATE_IRREGS
	subP   $(8), %Psp /* NOTE: `%fs' and `%eax' were already saved earlier! */
	.cfi_adjust_cfa_offset 8
#undef CFAOFFSETOF_ICPUSTATE
#endif /* !__x86_64__ */

	/* Re-enable interrupts, now that everything important has been saved. */
	sti

	/* Now save all of the user-space GP registers to create an icpustate. */
#ifdef __x86_64__
	ASM_PUSH_ICPUSTATE_AFTER_IRET_CFI_R
#else /* __x86_64__ */
	pushP_cfi_r %Pcx
	pushP_cfi_r %Pdx
	pushP_cfi_r %Pbx
	pushP_cfi_r %Psp
	pushP_cfi_r %Pbp
	pushP_cfi_r %Psi
	pushP_cfi_r %Pdi

	/* Load missing segment registers. */
	movw   $(SEGMENT_USER_DATA_RPL), %ax
	movw   %ax, %ds
	movw   %ax, %es
#endif /* !__x86_64__ */

	/* With the return-to-userspace context fully loaded, we're
	 * now  ready  to make  the call  to `userexcept_sysret()'! */
	movP   %Psp, %R_fcall0P
	EXTERN(userexcept_sysret)
	call   userexcept_sysret

	/* Load the newly updated cpustate. */
	movP   %Pax, %Psp
	EXTERN(cpu_apply_icpustate_Psp)
	jmp    cpu_apply_icpustate_Psp
	.cfi_endproc
END(x86_userexcept_sysret)




/* >> FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1)) void
 * >> NOTHROW(FCALL userexcept_handler_ucpustate)(struct ucpustate *__restrict state,
 * >>                                             struct rpc_syscall_info *sc_info);
 * Arch-specific function:
 * Wrapper around `userexcept_handler()' for use in implementing `except_unwind()'.
 * This function will (safely) construct  a complete `struct icpustate' at the  far
 * end of the  calling thread's  stack and populate  with with  register info  from
 * `state'.  Afterwards,  it will  force-unwind the  kernel stack  such that  it is
 * located  immediately at the new state. Once that is done, a call to the portable
 * function `userexcept_handler(<state>, sc_info)' is  made, and  if that  function
 * returns  normally,  either  `syscall_emulate_r(..., sc_info)'  if  non-NULL,  or
 * directly load the associated state by means of `cpu_apply_icpustate()'. */
.section .text
INTERN_FUNCTION(userexcept_handler_ucpustate)
	.cfi_startproc simple
	.cfi_def_cfa %R_fcall0P, 0
	ASM_CFI_OFFSET_RESTORE_UCPUSTATE(0)

#ifdef __x86_64__
#define MAX_SIZEOF_ICPUSTATE (SIZEOF_ICPUSTATE64)
#elif defined(__I386_NO_VM86)
#define MAX_SIZEOF_ICPUSTATE (OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS32_USER)
#else /* __x86_64__ */
#define MAX_SIZEOF_ICPUSTATE (OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS32_VM86)
#endif /* !__x86_64__ */

#define MAX_USED_BYTES_AT_STACK_TOP \
	(MAX_SIZEOF_ICPUSTATE + SIZEOF_RPC_SYSCALL_INFO + SIZEOF_UCPUSTATE)

	/* Check if one of the  given arguments fall into  the
	 * region of the stack which we're about to overwrite:
	 * >> if ((uintptr_t)state >= this_x86_kernel_psp0 - MAX_USED_BYTES_AT_STACK_TOP)
	 * >>     goto .Lmust_copy_state; */
	.cfi_remember_state
	EXTERN(this_x86_kernel_psp0)
	movP   %segtls:this_x86_kernel_psp0, %Pbp
	leaP   -MAX_USED_BYTES_AT_STACK_TOP(%Pbp), %Pax
	cmpP   %Pax, %R_fcall0P
	jae    .Lmust_copy_state
.Ldid_copy_state:
	/* >> if ((uintptr_t)sc_info >= this_x86_kernel_psp0 - MAX_USED_BYTES_AT_STACK_TOP)
	 * >>     goto .Lmust_copy_sc_info; */
	cmpP   %Pax, %R_fcall1P
	jae    .Lmust_copy_sc_info
.Ldid_copy_sc_info:

	cli /* Disable interrupts to  prevent async-RPCs from  trying to redirect  the
	     * iret, especially given how we're about to modify/re-write it ourselves! */

	/* NOTE: The given `state' (%R_fcall0P) may represent one of 2 locations:
	 *  #1: It may point to `x86_userexcept_sysret'
	 *  #2: It may point into user-space. In this case, an IRET redirection
	 *      might  have still  happened, and  left `state'  pointing at the
	 *      original user-space state (as mirrored in this_x86_sysret_iret) */

	/* Set `%Psp' such that it points at the correct IRET tail. */
#ifdef __x86_64__
	leaP   -SIZEOF_IRREGS64(%Pbp), %Psp
#elif defined(__I386_NO_VM86)
	leaP   -SIZEOF_IRREGS32_USER(%Pbp), %Psp
#else /* ... */
	movP   %segtls:this_x86_sysret_iret+OFFSET_IRREGS_PFLAGS, %Psi
	movP   OFFSET_UCPUSTATE_PFLAGS(%R_fcall0P), %Pdi
	cmpP   $(x86_userexcept_sysret), OFFSET_UCPUSTATE_PIP(%R_fcall0P)
	cmoveP %Psi, %Pdi /* %Pdi is the actual user-space %Pflags */
	movP   $(-SIZEOF_IRREGS32_USER), %Pax
	movP   $(-SIZEOF_IRREGS32_VM86), %Psi
	ttest  mask=EFLAGS_VM, loc=%Pdi
	cmovnzP %Psi, %Pax /* if (%Pdi & EFLAGS_VM) %Pax = -SIZEOF_IRREGS32_VM86 */
	leaP   (%Pbp,%Pax,1), %Psp
#endif /* !... */

	/* Check if the current IRET location points to `x86_userexcept_sysret' */
	cmpP   $(x86_userexcept_sysret), OFFSET_IRREGS_PIP(%Psp)
	jne    .Lfill_iret_from_state
/*.Lfill_iret_from_sysret:*/

	/* Debug assertions. */
#ifndef NDEBUG
#define ASSERT_CC(cc) j##cc 991f; int3; 991:
	cmpP   $(x86_userexcept_sysret), %segtls:this_x86_sysret_iret+OFFSET_IRREGS_PIP
	ASSERT_CC(ne) /* assert(PERTASK_GET(this_x86_sysret_iret.ir_Pip) != (uintptr_t)&x86_userexcept_sysret); */
	cmpP   $(0), OFFSET_IRREGS_PFLAGS(%Psp)
	ASSERT_CC(e) /* assert(return_state->ics_irregs.ir_Pflags == 0); */
	cmpw   $(SEGMENT_KERNEL_CODE), OFFSET_IRREGS_CS(%Psp)
	ASSERT_CC(e) /* assert(SEGMENT_IS_VALID_KERNCODE(return_state->ics_irregs.ir_cs16)); */
#undef ASSERT_CC
#endif /* !NDEBUG */

	/* Copy registers back into our iret tail. */
	movP   %segtls:this_x86_sysret_iret+OFFSET_IRREGS_PIP, %Pax
	movP   %Pax, OFFSET_IRREGS_PIP(%Psp)
	movzwP %segtls:this_x86_sysret_iret+OFFSET_IRREGS_CS, %Pax
	movP   %Pax, OFFSET_IRREGS_CS(%Psp)
	movP   %segtls:this_x86_sysret_iret+OFFSET_IRREGS_PFLAGS, %Pax
	movP   %Pax, OFFSET_IRREGS_PFLAGS(%Psp)
#ifdef __x86_64__
	movP   %segtls:this_x86_sysret_iret+OFFSET_IRREGS_PSP, %Pax
	movP   %Pax, OFFSET_IRREGS_PSP(%Psp)
	movzwP %segtls:this_x86_sysret_iret+OFFSET_IRREGS_SS, %Pax
	movP   %Pax, OFFSET_IRREGS_SS(%Psp)
#else /* __x86_64__ */
	/* Still initialized correctly:
	 * >> return_state->ics_irregs_u.ir_ss  = ...;
	 * >> return_state->ics_irregs_u.ir_esp = ...; */
#endif /* !__x86_64__ */
	jmp    .Lfill_iret_done
.Lfill_iret_from_state:
	/* Copy from the caller-given `state' */
	movP   OFFSET_UCPUSTATE_PIP(%R_fcall0P), %Pax
#ifndef NDEBUG
#define ASSERT_CC(cc) j##cc 991f; int3; 991:
	cmpP   $(x86_userexcept_sysret), %Pax
	ASSERT_CC(ne) /* assert(state->ucs_Pip != (uintptr_t)&x86_userexcept_sysret); */
#undef ASSERT_CC
#endif /* !NDEBUG */
	movP   %Pax, OFFSET_IRREGS_PIP(%Psp)
	movzwP OFFSET_UCPUSTATE_CS(%R_fcall0P), %Pax
	movP   %Pax, OFFSET_IRREGS_CS(%Psp)
	movP   OFFSET_UCPUSTATE_PFLAGS(%R_fcall0P), %Pax
	movP   %Pax, OFFSET_IRREGS_PFLAGS(%Psp)
	movP   OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PSP(%R_fcall0P), %Pax
	movP   %Pax, OFFSET_IRREGS_PSP(%Psp)
	movzwP OFFSET_UCPUSTATE_SS(%R_fcall0P), %Pax
	movP   %Pax, OFFSET_IRREGS_SS(%Psp)
.Lfill_iret_done:

	/* And with that, the IRET tail has been initialized correctly!
	 * Time  to  construct  the  rest  of  the  `struct icpustate'! */

#ifndef __x86_64__
#ifndef __I386_NO_VM86
	ttest  mask=EFLAGS_VM, loc=OFFSET_UCPUSTATE_PFLAGS(%R_fcall0P)
	jz     .Lpush_icpustate_sgregs_novm86
	/* Copy vm86 segment registers into the IRET tail where they belong! */
	movzwP OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_ES(%R_fcall0P), %Pax
	movP   %Pax, OFFSET_IRREGS_ES(%Psp)
	movzwP OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_DS(%R_fcall0P), %Pax
	movP   %Pax, OFFSET_IRREGS_DS(%Psp)
	movzwP OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_FS(%R_fcall0P), %Pax
	movP   %Pax, OFFSET_IRREGS_FS(%Psp)
	movzwP OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_GS(%R_fcall0P), %Pax
	movP   %Pax, OFFSET_IRREGS_GS(%Psp)
	pushP  $(SEGMENT_USER_DATA_RPL)   /* ics_ds */
	pushP  $(SEGMENT_USER_DATA_RPL)   /* ics_es */
	pushP  $(SEGMENT_USER_FSBASE_RPL) /* ics_fs */
	jmp    .Lpush_icpustate_sgregs_done
#endif /* !__I386_NO_VM86 */
.Lpush_icpustate_sgregs_novm86:
	pushP  OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_DS(%R_fcall0P) /* ics_ds */
	pushP  OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_ES(%R_fcall0P) /* ics_es */
	pushP  OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_FS(%R_fcall0P) /* ics_fs */
	movw   OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_GS(%R_fcall0P), %ax
	movw   %ax, %gs /* Doesn't appear in `struct icpustate', so must set immediately! */
.Lpush_icpustate_sgregs_done:
#endif /* !__x86_64__ */

	/* Fill in `ics_gpregs' */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PAX(%R_fcall0P) /* gp_eax */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PCX(%R_fcall0P) /* gp_ecx */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PDX(%R_fcall0P) /* gp_edx */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PBX(%R_fcall0P) /* gp_ebx */
#ifndef __x86_64__ /* x86_64 uses `struct gpregsnsp' */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PSP(%R_fcall0P) /* gp_esp */
#endif /* !__x86_64__ */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PBP(%R_fcall0P) /* gp_ebp */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PSI(%R_fcall0P) /* gp_esi */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_PDI(%R_fcall0P) /* gp_edi */
#ifdef __x86_64__ /* x86_64 has a bunch more registers */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R8(%R_fcall0P)  /* gp_r8 */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R9(%R_fcall0P)  /* gp_r9 */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R10(%R_fcall0P) /* gp_r10 */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R11(%R_fcall0P) /* gp_r11 */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R12(%R_fcall0P) /* gp_r12 */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R13(%R_fcall0P) /* gp_r13 */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R14(%R_fcall0P) /* gp_r14 */
	pushP  OFFSET_UCPUSTATE_GPREGS + OFFSET_GPREGS_R15(%R_fcall0P) /* gp_r15 */
#endif /* __x86_64__ */

	/* And   with  that,  the  new  `icpustate'  is  complete.
	 * However, we can't re-enable interrupts yet, since there
	 * are still some registers which need to be filled in, as
	 * well as the caller-given `sc_info', which we also  have
	 * to copy in case it is present. */
#ifdef __x86_64__
	movw   OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_DS(%R_fcall0P), %ax
	movw   %ax, %ds
	movw   OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_ES(%R_fcall0P), %ax
	movw   %ax, %es
	movw   OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_FS(%R_fcall0P), %ax
	movw   %ax, %fs
	EXTERN(this_task)
	movP   %segtls:this_task, %Pbx
	movw   OFFSET_UCPUSTATE_SGREGS + OFFSET_SGREGS_GS(%R_fcall0P), %ax
	movw   %ax, %gs
	wrgsbaseq %Pbx
	wrkgsbaseq OFFSET_UCPUSTATE_SGBASE + OFFSET_SGBASE_GSBASE(%R_fcall0P)
	movP   OFFSET_UCPUSTATE_SGBASE + OFFSET_SGBASE_FSBASE(%R_fcall0P), %Pax
	wrfsbaseq %Pax
#endif /* __x86_64__ */

	/* With that, everything we could possibly need from `%R_fcall0P'
	 * has been  loaded, and  the `icpustate'  at %Psp  is  complete! */
	movP   %Psp, %Pbx
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(-OFFSET_ICPUSTATE_IRREGS)
	.cfi_def_cfa %Pbx, OFFSET_ICPUSTATE_IRREGS

	/* Check if we need to copy `sc_info' */
	testP  %R_fcall1P, %R_fcall1P
	jnz    .Lcopy_sc_info
.Lcopy_sc_info_return:

	/* With everything from high now copied, we can re-enable interrupts */
	sti

	movP   %Pbx, %R_fcall0P /* For `userexcept_handler()' */
	movP   %R_fcall1P, %Pbp /* Needed once again later. */
	EXTERN(userexcept_handler)
	call   userexcept_handler

	/* If system call information was given, restart the system call. */
	testP  %Pbp, %Pbp
	.cfi_def_cfa_register %Pax
	jz     1f
	movP   %Pax, %R_fcall0P
	movP   %Pbp, %R_fcall1P
	EXTERN(syscall_emulate_r)
	jmp    syscall_emulate_r
1:

	/* Normally when `userexcept_handler()' returns, it means that the
	 * current system call or interrupt should be restarted.  However,
	 * the only reason we ever  get here is because  `except_unwind()'
	 * tried  to unwind an exception into userspace in a context where
	 * no prior exception handler  claimed ownership of the  exception
	 * for the purpose of allowing restarts.
	 *
	 * This  sort of thing must be used with  care, as it may lead to a
	 * soft-lock where some RPCs keep on causing task_serve() to  throw
	 * an exception, only for `userexcept_handler()' to fail to restart
	 * the interrupt,  then return  to user-space  where the  interrupt
	 * happens again immediately, causing the loop to continue forever.
	 *
	 * The solution to this problem is to assign exception handling
	 * to the interrupt handler  that essentially looks like  this:
	 * >> struct icpustate *myinterrupt(struct icpustate *state) {
	 * >> again:
	 * >>     TRY {
	 * >>         ... // The actual intrrupt work
	 * >>         return state;
	 * >>     } EXCEPT {
	 * >>         // When `userexcept_handler()' returns normally, that
	 * >>         // means that the interrupt should be restarted without
	 * >>         // returning to user-space!
	 * >>         state = userexcept_handler(state);
	 * >>     }
	 * >>     goto again;
	 * >> }
	 *
	 * Note that this sort of wrapper should be implemented at the  lowest
	 * possible level (iow: not in actual C code), and also note that this
	 * only affects interrupt handlers capable of throwing exceptions,  as
	 * well as performing blocking operations (iow: device interrupts  are
	 * unaffected by this,  though any access  to lazily initialized  file
	 * mappings, and as a consequence, any user-space memory access,  must
	 * be considered as potentially blocking) */

	movP   %Pax, %Psp
	.cfi_def_cfa_register %Psp

	/* Load the newly updated cpustate. */
	EXTERN(cpu_apply_icpustate_Psp)
	jmp    cpu_apply_icpustate_Psp


/* Auxiliary helper sub-routine: copy sc_info to the correct location. */
.Lcopy_sc_info:
	cld
#ifndef __x86_64__ /* On x86_64, `%R_fcall1P == %Psi' */
	movP   %R_fcall1P, %Psi
#endif /* !__x86_64__ */
	subP   $(SIZEOF_RPC_SYSCALL_INFO),                  %Psp
	movP   %Psp,                                        %Pdi
	movP   $(SIZEOF_RPC_SYSCALL_INFO / SIZEOF_POINTER), %Pcx
	rep    movsP
	movP   %Psp, %R_fcall1P
	jmp    .Lcopy_sc_info_return


/* Auxiliary helper sub-routines to deal with the unlikely event of stack-overlap */
	.cfi_restore_state
.Lmust_copy_state:
#ifdef __x86_64__
	movP   %R_fcall1P, %Pbp /* This  would  save %Pdx  on i386,  which isn't
	                         * clobbered below, so doesn't need to be saved!
	                         * On x86_64, it's  %Psi, which _is_  clobbered! */
#endif /* __x86_64__ */

	movP   %R_fcall0P, %Pbx /* Only needed for unwinding... */
	.cfi_def_cfa_register %Pbx

	/* >> %Psp -= SIZEOF_UCPUSTATE;
	 * >> %R_fcall0P = memcpy(%Psp, %R_fcall0P, SIZEOF_UCPUSTATE); */
	cld
	subP   $(SIZEOF_UCPUSTATE),                  %Psp
	movP   %R_fcall0P,                           %Psi
	movP   %Psp,                                 %Pdi
	movP   $(SIZEOF_UCPUSTATE / SIZEOF_POINTER), %Pcx
	rep    movsP
	movP   %Psp, %R_fcall0P /* The new & improved `struct ucpustate *state' */

#ifdef __x86_64__
	movP   %Pbp, %R_fcall1P
	movP   %segtls:this_x86_kernel_psp0, %Pbp
#endif /* __x86_64__ */
	jmp    .Ldid_copy_state

.Lmust_copy_sc_info:
	movP   %R_fcall0P, %Pbx
	.cfi_def_cfa_register %Pbx

	/* >> %Psp -= SIZEOF_RPC_SYSCALL_INFO;
	 * >> %R_fcall1P = memcpy(%Psp, %R_fcall1P, SIZEOF_RPC_SYSCALL_INFO); */
	cld
	subP   $(SIZEOF_RPC_SYSCALL_INFO),                  %Psp
	movP   %R_fcall1P,                                  %Psi
	movP   %Psp,                                        %Pdi
	movP   $(SIZEOF_RPC_SYSCALL_INFO / SIZEOF_POINTER), %Pcx
	rep    movsP
	movP   %Psp, %R_fcall1P /* The new & improved `struct rpc_syscall_info *sc_info' */
	movP   %Pbx, %R_fcall0P
	jmp    .Ldid_copy_sc_info
	.cfi_endproc
END(userexcept_handler_ucpustate)

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_S */
