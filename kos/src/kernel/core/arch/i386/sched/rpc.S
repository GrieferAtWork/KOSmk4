/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_S
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_S 1
#define __ASSEMBLER__ 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_RPC
#include <kernel/rt/except-handler.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/host.h>

#include <asm/cfi.h>
#include <asm/instr/compat.h>
#include <kos/kernel/cpu-state-asm.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/rpc.h>

#ifdef __x86_64__
#define cpu_apply_icpustate_Psp cpu_apply_icpustate_rsp
#else /* __x86_64__ */
#define cpu_apply_icpustate_Psp cpu_apply_icpustate_esp
#endif /* !__x86_64__ */

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
	.cfi_signal_frame
/*[[[cfi{register='%cfa'}
	push   %Psp                        # `(struct rpc_context *)%Psp'
	add    $SIZEOF_POINTER             # `&((struct rpc_context *)%Psp)->rc_state'
	deref                              # `((struct rpc_context *)%Psp)->rc_state'
	add    $OFFSET_ICPUSTATE_IRREGS    # `&((struct rpc_context *)%Psp)->rc_state->ics_irregs'
]]]*/
#ifdef __x86_64__
	.cfi_escape 15,7,119,0,35,8,6,35,120
#else /* __x86_64__ */
	.cfi_escape 15,7,116,0,35,4,6,35,44
#endif /* !__x86_64__ */
/*[[[end]]]*/
	ASM_CFI_OFFSET_RESTORE_ICPUSTATE(-OFFSET_ICPUSTATE_IRREGS)

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
	.cfi_signal_frame
	.cfi_def_cfa %esp, 0
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


/* Arch-specific function:
 * Serve pending, synchronous (and asynchronous) RPCs.
 * NOTE: If the caller was previously  disabled preemption, it will  remain
 *       disabled  if  there  were no  RPC  functions had  to  be executed.
 *       Otherwise, preemption will become enabled, and `true' is returned,
 *       or an exception thrown by an RPC function gets propagated.
 * WARNING: Do not call this function unconditionally!
 *          Only call it if you're certain to be about to start  blocking
 *          in a context where a reset of your current context would have
 *          the potential to resolve the  block. (Reset here meaning  the
 *          current system call being restarted)
 * @return: true:  At   least  one  RPC   function  was  executed,  and
 *                 preemption was re-enabled if it was disabled before.
 * @return: false: No  RPC needed to be served, and preemption
 *                 remains disabled if it was disabled before. */
/* FUNDEF bool KCALL task_serve(void) THROWS(...); */
.section .text
PUBLIC_FUNCTION(task_serve)
	.cfi_startproc
	.cfi_signal_frame
	.cfi_def_cfa %esp, 0
	/* Quick check: is there anything to do? */
	ttest  mask=TASK_FRPC, loc=task__t_flags, seg=%segtls
	jnz    1f
	xorP   %Pax, %Pax
	ret
1:	/* Yes, there are pending RPCs which need to be serviced */
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

	movP   %Psp, %R_fcall0P
	EXTERN(task_serve_with_icpustate)
	call   task_serve_with_icpustate
	movP   %Pax, %Psp

	/* Load the newly updated cpustate. */
	EXTERN(cpu_apply_icpustate_Psp)
	jmp    cpu_apply_icpustate_Psp
	.cfi_endproc
END(task_serve)



/* Arch-specific function:
 * Same as `task_serve()', but only sevice RPCs that were scheduled as no-throw.
 * @return: * : Set of `TASK_SERVE_*' */
/* FUNDEF WUNUSED unsigned int NOTHROW(KCALL task_serve_nx)(void); */
.section .text
PUBLIC_FUNCTION(task_serve_nx)
	.cfi_startproc
	.cfi_signal_frame
	.cfi_def_cfa %esp, 0
	/* Quick check: is there anything to do? */
	ttest  mask=TASK_FRPC, loc=task__t_flags, seg=%segtls
	jnz    1f
	xorP   %Pax, %Pax
	ret
1:	/* Yes, there are pending RPCs which need to be serviced */
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

	movP   %Psp, %R_fcall0P
	EXTERN(task_serve_with_icpustate_nx)
	call   task_serve_with_icpustate_nx
	movP   %Pax, %Psp

	/* Load the newly updated cpustate. */
	EXTERN(cpu_apply_icpustate_Psp)
	jmp    cpu_apply_icpustate_Psp
	.cfi_endproc
END(task_serve_nx)



/* Entry point for IRET tails that have been re-directed for sysret.
 * Used to  redirect  how  the kernel  will  return  to  user-space:
 * >> redirect_iret_for_sysret() {
 * >>     struct irregs_kernel *irr;
 * >>     PREEMPTION_DISABLE(); // Redirection is only
 * >>     if (IS_VM86_TASK) {
 * >>         irr = GET_KERNEL_STACK_BASE() - sizeof(struct irregs_vm86);
 * >>     } else {
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
	.cfi_signal_frame
	EXTERN(x86_userexcept_sysret_personality)
	/* NOTE: `x86_userexcept_sysret_personality'  handles
	 *       exceptions by calling `userexcept_handler()' */
	.cfi_personality 0, x86_userexcept_sysret_personality

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
print("#else /* __x86_64__ *" "/");
for (local reg: ["eip", "cs", "eflags"])
	restoreSimpleRegister('i386', reg);
for (local reg: { "es", "ds", "fs", "gs" })
	restoreVm86Register(reg);
print("#endif /* !__x86_64__ *" "/");
]]]*/
#ifdef __x86_64__
__ASM_L(	.cfi_escape 22,16,18,47,3,0,75,79,83,47,7,0,8,this_x86_sysret_iret + OFFSET_IRREGS_RIP,155,6)
__ASM_L(	.cfi_escape 47,2,0,128,0)
__ASM_L(	.cfi_escape 22,51,19,47,3,0,75,79,83,47,7,0,8,this_x86_sysret_iret + OFFSET_IRREGS_CS,155,6)
__ASM_L(	.cfi_escape 47,3,0,146,51,0)
__ASM_L(	.cfi_escape 22,49,19,47,3,0,75,79,83,47,7,0,8,this_x86_sysret_iret + OFFSET_IRREGS_RFLAGS,155,6)
__ASM_L(	.cfi_escape 47,3,0,146,49,0)
__ASM_L(	.cfi_escape 22,7,18,47,3,0,75,79,83,47,7,0,8,this_x86_sysret_iret + OFFSET_IRREGS_RSP,155,6)
__ASM_L(	.cfi_escape 47,2,0,119,0)
__ASM_L(	.cfi_escape 22,52,19,47,3,0,75,79,83,47,7,0,8,this_x86_sysret_iret + OFFSET_IRREGS_SS,155,6)
__ASM_L(	.cfi_escape 47,3,0,146,52,0)
#else /* __x86_64__ */
__ASM_L(	.cfi_escape 22,8,18,47,3,0,75,79,83,47,7,0,8,this_x86_sysret_iret + OFFSET_IRREGS_EIP,155,6)
__ASM_L(	.cfi_escape 47,2,0,120,0)
__ASM_L(	.cfi_escape 22,41,19,47,3,0,75,79,83,47,7,0,8,this_x86_sysret_iret + OFFSET_IRREGS_CS,155,6)
__ASM_L(	.cfi_escape 47,3,0,146,41,0)
__ASM_L(	.cfi_escape 22,9,18,47,3,0,75,79,83,47,7,0,8,this_x86_sysret_iret + OFFSET_IRREGS_EFLAGS,155,6)
__ASM_L(	.cfi_escape 47,2,0,121,0)
__ASM_L(	.cfi_escape 22,40,31,47,3,0,75,79,83,47,19,0,8,this_x86_sysret_iret + OFFSET_IRREGS_EFLAGS,155,6)
__ASM_L(	.cfi_escape 16,128,128,8,26,32,40,6,0,116,8,6,47,3,0,146)
__ASM_L(	.cfi_escape 40,0)
__ASM_L(	.cfi_escape 22,43,31,47,3,0,75,79,83,47,19,0,8,this_x86_sysret_iret + OFFSET_IRREGS_EFLAGS,155,6)
__ASM_L(	.cfi_escape 16,128,128,8,26,32,40,6,0,116,12,6,47,3,0,146)
__ASM_L(	.cfi_escape 43,0)
__ASM_L(	.cfi_escape 22,44,31,47,3,0,75,79,83,47,19,0,8,this_x86_sysret_iret + OFFSET_IRREGS_EFLAGS,155,6)
__ASM_L(	.cfi_escape 16,128,128,8,26,32,40,6,0,116,16,6,47,3,0,146)
__ASM_L(	.cfi_escape 44,0)
__ASM_L(	.cfi_escape 22,45,31,47,3,0,75,79,83,47,19,0,8,this_x86_sysret_iret + OFFSET_IRREGS_EFLAGS,155,6)
__ASM_L(	.cfi_escape 16,128,128,8,26,32,40,6,0,116,20,6,47,3,0,146)
__ASM_L(	.cfi_escape 45,0)
#endif /* !__x86_64__ */
/*[[[end]]]*/
	.cfi_def_cfa %rsp, 0
#ifndef __x86_64__
	/* Correctly unwind  */
	.cfi_restore_iret_esp -SIZEOF_IRREGS_KERNEL
	.cfi_restore_iret_ss  -SIZEOF_IRREGS_KERNEL
#endif /* !__x86_64__ */

	nop /* Required to allow for detection during unwinding. */
PUBLIC_FUNCTION(x86_userexcept_sysret)

	/* Entry point for redirected system return paths */

	/* Construct an IRET tail with information from `this_x86_sysret_iret' */
#ifdef __x86_64__
	/* Note that our current %gs.base still points to kernel-space. */
	pushP_cfi  %segtls:(this_x86_sysret_iret + OFFSET_IRREGS_SS)
	.cfi_rel_offset %ss, 0
	pushP_cfi  %segtls:(this_x86_sysret_iret + OFFSET_IRREGS_PSP)
	.cfi_rel_offset %Psp, 0
#else /* __x86_64__ */
#define SPOFFSETOF_GPREGS (OFFSET_ICPUSTATE_GPREGS - (OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL))
	movP   %Pax, %ss:SPOFFSETOF_GPREGS + OFFSET_GPREGS_PAX(%Psp)
	.cfi_rel_offset %eax, SPOFFSETOF_GPREGS + OFFSET_GPREGS_PAX
	movP   %fs, %Pax
	movP   %Pax, %ss:SPOFFSETOF_GPREGS + OFFSET_ICPUSTATE_FS(%Psp)
	.cfi_rel_offset %fs, SPOFFSETOF_GPREGS + OFFSET_ICPUSTATE_FS
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
#define CFAOFFSETOF_ICPUSTATE (-(OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL))
	pushP_cfi  %ds   /* ir_ds */
	.cfi_restore_iret_ds_or_offset CFAOFFSETOF_ICPUSTATE + OFFSET_ICPUSTATE_DS, CFAOFFSETOF_ICPUSTATE + OFFSET_ICPUSTATE_IRREGS
	pushP_cfi  %es   /* ir_es */
	.cfi_restore_iret_es_or_offset CFAOFFSETOF_ICPUSTATE + OFFSET_ICPUSTATE_ES, CFAOFFSETOF_ICPUSTATE + OFFSET_ICPUSTATE_IRREGS
	subP   $(8), %Psp /* NOTE: `%fs' and `%eax' were already saved earlier! */
	.cfi_adjust_cfa_offset 8
	pushP_cfi  %fs   /* ir_fs */
	.cfi_restore_iret_fs_or_offset CFAOFFSETOF_ICPUSTATE + OFFSET_ICPUSTATE_FS, CFAOFFSETOF_ICPUSTATE + OFFSET_ICPUSTATE_IRREGS
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
	 * now ready to make the call to `userexcept_sysret()'! */
	movP   %Psp, %R_fcall0P
	EXTERN(userexcept_sysret)
	call   userexcept_sysret

	/* Load the newly updated cpustate. */
	movP   %Pax, %Psp
	EXTERN(cpu_apply_icpustate_Psp)
	jmp    cpu_apply_icpustate_Psp
	.cfi_endproc
END(x86_userexcept_sysret)

#endif /* !CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_RPC_S */
