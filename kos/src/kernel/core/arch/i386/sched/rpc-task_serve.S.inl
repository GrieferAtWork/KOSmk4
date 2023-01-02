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
#ifdef __INTELLISENSE__
#include "rpc.S"
//#define    DEFINE_task_serve
//#define DEFINE_task_serve_nx
#define DEFINE_task_serve_with_sigmask
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_task_serve) +    \
     defined(DEFINE_task_serve_nx) + \
     defined(DEFINE_task_serve_with_sigmask)) != 1
#error "Must #define exactly one of these"
#endif /* ... */


#ifdef DEFINE_task_serve

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
 * @return: true:  RPC  functions  may  have  been  been  executed, and
 *                 preemption was re-enabled if it was disabled before.
 * @return: false: No  RPC needed to be served, and preemption
 *                 remains disabled if it was disabled before. */
/* FUNDEF bool KCALL task_serve(void) THROWS(E_INTERRUPT_USER_RPC, ...); */
#define LOCAL_task_serve                task_serve
#define LOCAL_task_serve_with_icpustate task_serve_with_icpustate

#elif defined(DEFINE_task_serve_nx)

/* Arch-specific function:
 * Same as `task_serve()', but only sevice RPCs that were scheduled as no-throw.
 * @return: * : Set of `TASK_SERVE_*' */
/* FUNDEF WUNUSED unsigned int NOTHROW(KCALL task_serve_nx)(void); */
#define LOCAL_task_serve                task_serve_nx
#define LOCAL_task_serve_with_icpustate task_serve_with_icpustate_nx

#elif defined(DEFINE_task_serve_with_sigmask)

/* Same as `task_serve()', but use the given `sigmask'
 * instead of the  calling thread's thread-local  one.
 * Used for the implementation of `sigsuspend(2)' */
/* >> FUNDEF NONNULL((1)) bool FCALL
 * >> task_serve_with_sigmask(sigset_t const *__restrict sigmask)
 * >>         THROWS(E_INTERRUPT_USER_RPC, ...); */
#define LOCAL_task_serve                task_serve_with_sigmask
#define LOCAL_task_serve_with_icpustate task_serve_with_icpustate_and_sigmask

#endif /* ... */



.section .text
PUBLIC_FUNCTION(LOCAL_task_serve)
	.cfi_startproc
	.cfi_signal_frame
	.cfi_def_cfa %Psp, SIZEOF_POINTER

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

#ifdef DEFINE_task_serve_with_sigmask
	movP   %R_fcall0P, %R_fcall1P /* sigset_t const *sigmask */
#endif /* DEFINE_task_serve_with_sigmask */

	movP   %Psp, %R_fcall0P
	EXTERN(LOCAL_task_serve_with_icpustate)
	call   LOCAL_task_serve_with_icpustate
	movP   %Pax, %Psp

	/* Load the newly updated cpustate. */
	EXTERN(cpu_apply_icpustate_Psp)
	jmp    cpu_apply_icpustate_Psp
	.cfi_endproc
END(LOCAL_task_serve)

#undef LOCAL_task_serve_with_icpustate
#undef LOCAL_task_serve


#undef DEFINE_task_serve_with_sigmask
#undef DEFINE_task_serve_nx
#undef DEFINE_task_serve
