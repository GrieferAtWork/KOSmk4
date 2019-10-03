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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_C
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_C 1
#define _KOS_SOURCE 1
#define __WANT_SYSCALL_ARGUMENT_COUNT 1
#define __WANT_SYSCALL_ARGUMENT_COUNT_386 1
#define __WANT_SYSCALL_RESTART_MODES 1
#define __WANT_SYSCALL_CANCELLATION_POINTS 1
#define __WANT_SYSCALL_DOUBLE_WIDE_RETURN_386 1

#include <kernel/compiler.h>

#include <kernel/coredump.h>
#include <kernel/cpuid.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/idt.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/tss.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/except-handler.h>
#include <sched/mutex.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/host.h>

#include <asm/cpu-cpuid.h>
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/intrin.h>
#include <kos/bits/exception_data32.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/cpu-state32.h>
#include <kos/kernel/gdt.h>
#include <sys/wait.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>

#include <librpc/rpc.h>
#include <libunwind/unwind.h>

#include "except.h"

#ifdef __x86_64__
#include <kos/bits/exception_data-convert.h>
#endif /* __x86_64__ */

DECL_BEGIN



/* Serve all user-space redirection RPCs
 * @return: * :   The new CPU state to restore
 * @param: prestart_system_call: If `reason == TASK_RPC_REASON_SYSCALL', whilst an `E_INTERRUPT_USER_RPC'
 *                               exception was handled, when `RPC_KIND_USER_SYNC' RPCs exist that cannot
 *                               be handled in the current context, then set to true. */
INTDEF struct icpustate *
NOTHROW(FCALL rpc_serve_user_redirection_all)(struct icpustate *__restrict state,
                                              unsigned int reason,
                                              struct rpc_syscall_info const *sc_info,
                                              bool *prestart_system_call);

LOCAL ATTR_NORETURN void
NOTHROW(FCALL process_exit)(int reason) {
	/* TODO: If the crashing application is critical, invoke kernel PANIC() */
	/* TODO: We need to terminate the _process_; not just this thread! */
	task_exit(reason);
}

LOCAL NOBLOCK void
NOTHROW(KCALL user_icpu_to_ucpu)(struct icpustate const *__restrict state,
                                 struct ucpustate *__restrict ust) {
#ifdef __x86_64__
#error TODO
#else /* __x86_64__ */
	ust->ucs_gpregs        = state->ics_gpregs;
	ust->ucs_sgregs.sg_ds  = state->ics_ds;
	ust->ucs_sgregs.sg_es  = state->ics_es;
	ust->ucs_sgregs.sg_fs  = state->ics_fs;
	ust->ucs_sgregs.sg_gs  = __rdgs();
	ust->ucs_cs            = irregs_rdcs(&state->ics_irregs);
	ust->ucs_ss            = state->ics_irregs_u.ir_ss;
	ust->ucs_eflags        = irregs_rdflags(&state->ics_irregs);
	ust->ucs_eip           = irregs_rdip(&state->ics_irregs);
	ust->ucs_gpregs.gp_esp = state->ics_irregs_u.ir_esp;
#endif /* !__x86_64__ */
}


/* Create a coredump because of the currently thrown exception */
PUBLIC ATTR_NOINLINE NONNULL((1)) void FCALL
coredump_create_for_exception(struct icpustate *__restrict state) {
	struct ucpustate ust;
	struct exception_data error;
	struct exception_info *info = error_info();
	siginfo_t si;
	bool has_si;
	memcpy(&error, &info->ei_data, sizeof(struct exception_data));
	user_icpu_to_ucpu(state, &ust);
	has_si = error_as_signal(&error, &si);
#if EXCEPT_BACKTRACE_SIZE != 0
	{
		size_t i;
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i) {
			if (info->ei_trace[i] == NULL)
				break;
		}
		coredump_create(&ust, NULL, 0, &ust,
		                info->ei_trace, i, &info->ei_state,
		                &error, has_si ? &si : NULL,
		                UNWIND_DISABLED);
	}
#else /* EXCEPT_BACKTRACE_SIZE != 0 */
	coredump_create(&ust, NULL, 0, &ust,
	                NULL, 0, &info->ei_state,
	                &error, has_si ? &si : NULL,
	                UNWIND_DISABLED);
#endif /* EXCEPT_BACKTRACE_SIZE == 0 */
}

/* Create a coredump because of the given signal `si' */
PUBLIC ATTR_NOINLINE NONNULL((1, 2)) void FCALL
coredump_create_for_signal(struct icpustate *__restrict state,
                           siginfo_t const *__restrict si) {
	struct ucpustate ust;
	user_icpu_to_ucpu(state, &ust);
	coredump_create(&ust, NULL, 0, &ust, NULL, 0,
	                NULL, NULL, si, UNWIND_DISABLED);
}

LOCAL ATTR_RETNONNULL struct icpustate *
NOTHROW(FCALL translate_exception_errno)(struct icpustate *__restrict state,
                                         unsigned int UNUSED(reason)) {
	errno_t errval;
	struct exception_data *data;
	data   = error_data();
	errval = -error_as_errno(data);
#if 1
	{
		unsigned int pointer_count = EXCEPTION_DATA_POINTERS;
		while (pointer_count != 0 &&
		       data->e_pointers[pointer_count - 1] == 0)
			--pointer_count;
		printk(KERN_TRACE "[except] Translate exception %#x:%#x",data->e_class, data->e_subclass);
		if (pointer_count != 0) {
			unsigned int i;
			for (i = 0; i < pointer_count; ++i) {
				printk(KERN_TRACE "%c%#Ix",
				       i == 0 ? '[' : ',',
				       data->e_pointers[i]);
			}
			printk(KERN_TRACE "]");
		}
		printk(KERN_TRACE " into errno=%d [tid=%u]\n",
		       errval, task_getroottid_s());
	}
#endif
#ifdef __x86_64__
	state->ics_gpregs.gp_rax = errval;
	if (SYSCALL32_DOUBLE_WIDE(state->ics_gpregs.gp_rax) &&
	    irregs_iscompat(&state->ics_irregs))
		state->ics_gpregs.gp_rdx = (u64)-1; /* sign-extend */
#else /* __x86_64__ */
	if (SYSCALL32_DOUBLE_WIDE(state->ics_gpregs.gp_eax))
		state->ics_gpregs.gp_edx = (u32)-1; /* sign-extend */
	state->ics_gpregs.gp_eax = errval;
#endif /* !__x86_64__ */
	//error_printf("Propagate to user-space\n");
	return state;
}

INTERN struct icpustate *FCALL
raise_user_signal(struct icpustate *__restrict state,
                  siginfo_t const *__restrict siginfo,
                  unsigned int reason,
                  bool derived_from_exception) {
	struct icpustate *new_state;
	struct sighand *hand;
	struct kernel_sigaction action;
	/* Raise a POSIX signal */
again_gethand:
	assert(siginfo->si_signo != 0);
	assert(siginfo->si_signo < NSIG);
	if (!THIS_SIGHAND_PTR) {
		action.sa_handler = KERNEL_SIG_DFL;
		action.sa_flags   = 0;
		action.sa_mask    = NULL;
	} else {
		hand   = sighand_ptr_lockread(THIS_SIGHAND_PTR);
		action = hand->sh_actions[siginfo->si_signo - 1];
		xincref(action.sa_mask);
		sync_endread(hand);
	}

	/* Check for special signal handlers. */
	if (action.sa_handler == KERNEL_SIG_DFL)
		action.sa_handler = sighand_default_action(siginfo->si_signo);
	switch ((uintptr_t)(void *)action.sa_handler) {

#undef __CCAST
#define __CCAST(T) /* nothing */

	case KERNEL_SIG_IGN:
		xdecref_unlikely(action.sa_mask);
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
		    unlikely(!sighand_reset_handler(siginfo->si_signo, &action)))
			goto again_gethand;
		if (reason == TASK_RPC_REASON_SYSCALL)
			state = translate_exception_errno(state, reason);
		return state;

	case KERNEL_SIG_CORE:
		xdecref_unlikely(action.sa_mask);
		if (derived_from_exception) {
			coredump_create_for_exception(state);
		} else {
			coredump_create_for_signal(state, siginfo);
		}
		process_exit(W_EXITCODE(1, siginfo->si_signo));

	case KERNEL_SIG_TERM:
		xdecref_unlikely(action.sa_mask);
		process_exit(W_EXITCODE(1, siginfo->si_signo));

	case KERNEL_SIG_EXIT:
		xdecref_unlikely(action.sa_mask);
		task_exit(W_EXITCODE(1, siginfo->si_signo));

	case KERNEL_SIG_CONT:
		xdecref_unlikely(action.sa_mask);
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
		    unlikely(!sighand_reset_handler(siginfo->si_signo, &action)))
			goto again_gethand;
		/* Continue execution. */
		task_sigcont(THIS_TASK);
		return state;

	case KERNEL_SIG_STOP:
		/* TODO: Mask additional signals by looking at `SIGACTION_SA_NODEFER' and `action.sa_mask' */
		xdecref_unlikely(action.sa_mask);
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
			unlikely(!sighand_reset_handler(siginfo->si_signo, &action)))
			goto again_gethand;
		/* Suspend execution. */
		task_sigstop(W_STOPCODE(siginfo->si_signo));
		return state;

#undef __CCAST
#define __CCAST(T) (T)
	default: break;
	}

	/* Invoke a regular, old signal handler. */
	FINALLY_XDECREF_UNLIKELY(action.sa_mask);
	new_state = sighand_raise_signal(state, &action, siginfo,
	                                 NULL /* Never restart a system call that threw an exception */);
	if unlikely(!new_state)
		goto again_gethand;
	return state;
}

LOCAL struct icpustate *FCALL
raise_excption_as_user_signal(struct icpustate *__restrict state,
                              unsigned int reason) {
	siginfo_t siginfo;
	if (!error_as_signal(error_data(), &siginfo))
		return NULL;
	switch (siginfo.si_signo) {
	case SIGSYS:
		siginfo.si_call_addr = (void *)irregs_rdip(&state->ics_irregs);
		break;
	default: break;
	}
	return raise_user_signal(state, &siginfo, reason, true);
}

#ifdef __x86_64__
PRIVATE struct icpustate *FCALL
call_user_exception_handler32(struct icpustate *__restrict state,
                              unsigned int reason) THROWS(E_SEGFAULT)
#else /* __x86_64__ */
PRIVATE struct icpustate *FCALL
call_user_exception_handler(struct icpustate *__restrict state,
                            unsigned int reason) THROWS(E_SEGFAULT)
#endif /* !__x86_64__ */
{
	uintptr_t mode;
	USER CHECKED void *stack;
	USER CHECKED except_handler_t handler;
	USER CHECKED struct kcpustate32 *user_state;
	USER CHECKED struct exception_data32 *user_error;
	struct exception_data *mydata;
	/* Call the user-space exception handler */
	mode    = PERTASK_GET(_this_user_except_handler.ueh_mode);
	handler = PERTASK_GET(_this_user_except_handler.ueh_handler);
	stack   = PERTASK_GET(_this_user_except_handler.ueh_stack);
	if unlikely(!(mode & EXCEPT_HANDLER_FLAG_SETHANDLER))
		return NULL; /* No handler defined */
	if (stack == EXCEPT_HANDLER_SP_CURRENT) {
#ifdef __x86_64__
		stack = (void *)irregs_rdsp(&state->ics_irregs);
#else /* __x86_64__ */
		stack = (void *)state->ics_irregs_u.ir_esp;
#endif /* !__x86_64__ */
	}
	/* Align the stack. */
	stack = (void *)((uintptr_t)stack & ~3);
	/* Allocate structures */
	user_state = (struct kcpustate32 *)((byte_t *)stack - sizeof(struct kcpustate32));
	user_error = (struct exception_data32 *)((byte_t *)user_state - sizeof(struct exception_data32));
	/* Ensure that we can write to the given stack. */
	validate_writable(user_error, sizeof(struct exception_data32) + sizeof(struct kcpustate32));
	COMPILER_WRITE_BARRIER();
	/* Fill in user-space context information */
#ifdef __x86_64__
	user_state->kcs_gpregs.gp_edi = (u32)state->ics_gpregs.gp_rdi;
	user_state->kcs_gpregs.gp_esi = (u32)state->ics_gpregs.gp_rsi;
	user_state->kcs_gpregs.gp_ebp = (u32)state->ics_gpregs.gp_rbp;
	user_state->kcs_gpregs.gp_esp = (u32)irregs_rdsp(&state->ics_irregs);
	user_state->kcs_gpregs.gp_ebx = (u32)state->ics_gpregs.gp_rbx;
	user_state->kcs_gpregs.gp_edx = (u32)state->ics_gpregs.gp_rdx;
	user_state->kcs_gpregs.gp_ecx = (u32)state->ics_gpregs.gp_rcx;
	user_state->kcs_gpregs.gp_eax = (u32)state->ics_gpregs.gp_rax;
#else /* __x86_64__ */
	user_state->kcs_gpregs.gp_edi = state->ics_gpregs.gp_edi;
	user_state->kcs_gpregs.gp_esi = state->ics_gpregs.gp_esi;
	user_state->kcs_gpregs.gp_ebp = state->ics_gpregs.gp_ebp;
	user_state->kcs_gpregs.gp_esp = state->ics_irregs_u.ir_esp;
	user_state->kcs_gpregs.gp_ebx = state->ics_gpregs.gp_ebx;
	user_state->kcs_gpregs.gp_edx = state->ics_gpregs.gp_edx;
	user_state->kcs_gpregs.gp_ecx = state->ics_gpregs.gp_ecx;
	user_state->kcs_gpregs.gp_eax = state->ics_gpregs.gp_eax;
#endif /* !__x86_64__ */
	user_state->kcs_eflags = (u32)irregs_rdflags(&state->ics_irregs);
	user_state->kcs_eip    = (u32)irregs_rdip(&state->ics_irregs);
	/* Copy exception data onto the user-space stack. */
	mydata = &THIS_EXCEPTION_INFO.ei_data;
#ifdef __x86_64__
	exception_data64_to_exception_data32(user_error, mydata);
#else /* __x86_64__ */
	memcpy(user_error, mydata, sizeof(struct exception_data32));
#endif /* !__x86_64__ */
	/* Redirect the given CPU state to return to the user-space handler. */
#ifdef __x86_64__
	state->ics_gpregs.gp_rcx   = (u32)(uintptr_t)user_state; /* struct kcpustate32 *__restrict state */
	state->ics_gpregs.gp_rdx   = (u32)(uintptr_t)user_error; /* struct exception_data32 *__restrict error */
	irregs_wrsp(&state->ics_irregs, (u32)(uintptr_t)user_error);
#else /* __x86_64__ */
	state->ics_gpregs.gp_ecx   = (u32)(uintptr_t)user_state; /* struct kcpustate32 *__restrict state */
	state->ics_gpregs.gp_edx   = (u32)(uintptr_t)user_error; /* struct exception_data32 *__restrict error */
	state->ics_irregs_u.ir_esp = (u32)(uintptr_t)user_error;
#endif /* !__x86_64__ */
	irregs_wrip(&state->ics_irregs, (uintptr_t)(void *)handler);
	COMPILER_WRITE_BARRIER();
	/* Disable exception handling on one-shot mode. */
	if (mode & EXCEPT_HANDLER_FLAG_ONESHOT)
		PERTASK_SET(_this_user_except_handler.ueh_mode,
		            (mode & ~EXCEPT_HANDLER_MODE_MASK) |
		            EXCEPT_HANDLER_MODE_DISABLED);
	return state;
}

#ifdef __x86_64__
LOCAL struct icpustate *FCALL
call_user_exception_handler(struct icpustate *__restrict state,
                            unsigned int reason) THROWS(E_SEGFAULT) {
	struct icpustate *result;
	if (irregs_iscompat(&state->ics_irregs)) {
		result = call_user_exception_handler32(state, reason);
	} else {
		kernel_panic("TODO");
	}
	return result;
}
#endif /* !__x86_64__ */



/* @param: reason: How is the exception being propagated?
 *                 One of { TASK_RPC_REASON_SYSCALL, TASK_RPC_REASON_ASYNCUSER }
 *                 Where `TASK_RPC_REASON_SYSCALL' refers to the exception being
 *                 propagated because it happened while inside of a system call,
 *                 and `TASK_RPC_REASON_ASYNCUSER' referring to any other reason.
 *           NOTE: In the first case, check EFLAGS.CF to see if userspace wants
 *                 to make use of kernel exceptions. - Otherwise, translate exceptions
 *                 that happened in system calls to errno codes, and exceptions that
 *                 happened during any other kind of interrupt into SIG* */
INTERN struct icpustate *
NOTHROW(FCALL x86_propagate_userspace_exception)(struct icpustate *__restrict state,
                                                 unsigned int reason) {
	struct icpustate *new_state;

	/* NOTE: This function only gets called when the exception is propagated
	 *       from a regular interrupt (i.e. not for system calls) */
	assert(reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_ASYNCUSER);
	switch (error_code()) {

	case ERROR_CODEOF(E_EXIT_PROCESS):
		process_exit(PERTASK_GET(_this_exception_info.ei_data.e_pointers[0]));
	case ERROR_CODEOF(E_EXIT_THREAD):
		task_exit(PERTASK_GET(_this_exception_info.ei_data.e_pointers[0]));

	default: break;
	}

	if (reason == TASK_RPC_REASON_SYSCALL) {
		//error_printf("Unwind to userspace");
		if (irregs_rdflags(&state->ics_irregs) & EFLAGS_CF) {
			/* System call exceptions are enabled. */
			TRY {
				/* Propagate the exception to user-space if handlers are enabled. */
				if ((PERTASK_GET(_this_user_except_handler.ueh_mode) &
				     EXCEPT_HANDLER_MODE_MASK) != EXCEPT_HANDLER_MODE_DISABLED) {
					new_state = call_user_exception_handler(state, reason);
					if likely(new_state)
						goto return_new_state;
				}
				/* If exceptions don't work, try to propagate a POSIX signal */
				new_state = raise_excption_as_user_signal(state, reason);
				if likely(new_state)
					goto return_new_state;
			} EXCEPT {
			}
			/* If the exception still cannot be handled, terminate the program. */
			goto terminate_app;
		}
		/* Translate the current exception into an errno. */
		new_state = translate_exception_errno(state, reason);
		goto return_new_state;
	}

	TRY {
		/* Check if signal exceptions should be propagated. */
		if ((PERTASK_GET(_this_user_except_handler.ueh_mode) &
		     EXCEPT_HANDLER_MODE_MASK) == EXCEPT_HANDLER_MODE_SIGHAND) {
			new_state = call_user_exception_handler(state, reason);
			if likely(new_state)
				goto return_new_state;
		}
		/* Deliver a signal to the calling user-space thread. */
		new_state = raise_excption_as_user_signal(state, reason);
		if likely(new_state)
			goto return_new_state;
	} EXCEPT {
	}
terminate_app:
	coredump_create_for_exception(state);
	process_exit(W_EXITCODE(1, 0));
return_new_state:
	/* Delete the currently set exception. */
	PERTASK_SET(_this_exception_info.ei_code,
	            (error_code_t)ERROR_CODEOF(E_OK));
	return new_state;
}

#ifdef __x86_64__
/* Emulate the `syscall' instruction */
INTDEF ATTR_NORETURN void FCALL x86_syscall_emulation(struct icpustate *__restrict state);
#endif /* __x86_64__ */

/* Emulate the `sysenter' instruction */
INTDEF ATTR_NORETURN void FCALL x86_sysenter_emulation(struct icpustate *__restrict state);
/* Emulate the `int 80h' instruction */
INTDEF ATTR_NORETURN void FCALL x86_int80_emulation(struct icpustate *__restrict state);



/* Given a user-space UCPUSTATE, load that state into the active IRET tail, whilst
 * accounting for additional user-space RPC redirection, before serving user-level
 * RPC functions as specified by `reason', before propagating the then set exception
 * (if any) into user-space, also according to `reason'.
 * Afterwards, load the set CPU context and resume execution within user-space. */
INTERN ATTR_NORETURN void
NOTHROW(FCALL x86_handle_except_before_userspace)(struct ucpustate *__restrict ustate,
                                                  unsigned int reason) {
	struct icpustate *return_state;
	assert(!(THIS_TASK->t_flags & TASK_FKERNTHREAD));
	assertf(TASK_RPC_REASON_GETREASON(reason) == TASK_RPC_REASON_SYSCALL ||
	        TASK_RPC_REASON_GETREASON(reason) == TASK_RPC_REASON_ASYNCUSER,
	        "Invalid reason (%u)", reason);
	/* Disable interrupts to prevent Async-RPCs from doing even more re-directions! */
	__cli();
	return_state = (struct icpustate *)((byte_t *)VM_PAGE2ADDR(PERTASK_GET((*(struct vm_node *)&_this_kernel_stack).vn_node.a_vmax) + 1) -
	                                    (
#ifdef __x86_64__
	                                    SIZEOF_ICPUSTATE
#elif !defined(CONFIG_NO_VM86)
	                                    task_isvm86(THIS_TASK)
	                                    ? COMPILER_OFFSETAFTER(struct icpustate, ics_irregs_v)
	                                    : COMPILER_OFFSETAFTER(struct icpustate, ics_irregs_u)
#else
	                                    COMPILER_OFFSETAFTER(struct icpustate, ics_irregs_u)
#endif
	                                    ));
	/* Check if user-space got redirected (if so, we need to follow some custom unwinding rules). */
	if (IRREGS_PC(return_state->ics_irregs) == (uintptr_t)&x86_rpc_user_redirection) {
		/* A re-direction may have happened whilst we were unwinding. - Adjust for that now!
		 * HINT: The actual user-space return location is stored in `x86_rpc_redirection_iret' */
		assert(PERTASK_GET(IRREGS_PC(x86_rpc_redirection_iret)) != (uintptr_t)&x86_rpc_user_redirection);
		assert(return_state->ics_irregs.ir_cs == SEGMENT_KERNEL_CODE);
#ifdef __x86_64__
		assert(return_state->ics_irregs.ir_rflags == 0);
#else /* __x86_64__ */
		assert(return_state->ics_irregs.ir_eflags == 0);
#endif /* !__x86_64__ */
		/* Manually unwind additional FLAGS registers.
		 * Because .cfi_iret_signal_frame perform a kernel-space unwind
		 * due to the redirection, we must manually complete the
		 * unwind to also include ESP and SS
		 *  - Right now, ESP points at &irregs_user::ir_esp / &irregs_vm86::ir_esp
		 */
#ifdef __x86_64__
		assertf(ustate->ucs_gpregs.gp_rsp == return_state->ics_irregs.ir_rsp,
		        "ustate->ucs_gpregs.gp_rsp       = %p\n"
		        "return_state->ics_irregs.ir_rsp = %p\n",
		        ustate->ucs_gpregs.gp_rsp,
		        return_state->ics_irregs.ir_rsp);
#else /* __x86_64__ */
		assertf(ustate->ucs_gpregs.gp_esp == (u32)&return_state->ics_irregs_u.ir_esp,
		        "ustate->ucs_gpregs.gp_esp = %p\n"
		        "&return_state->ics_irregs_u.ir_esp = %p\n",
		        ustate->ucs_gpregs.gp_esp,
		        &return_state->ics_irregs_u.ir_esp);
#endif /* !__x86_64__ */

#ifdef __x86_64__
		GPREGS_TO_GPREGSNSP(return_state->ics_gpregs, ustate->ucs_gpregs);
		return_state->ics_irregs.ir_rip    = PERTASK_GET(x86_rpc_redirection_iret.ir_rip);
		return_state->ics_irregs.ir_cs     = PERTASK_GET(x86_rpc_redirection_iret.ir_cs);
		return_state->ics_irregs.ir_rflags = PERTASK_GET(x86_rpc_redirection_iret.ir_rflags);
		return_state->ics_irregs.ir_rsp    = PERTASK_GET(x86_rpc_redirection_iret.ir_rsp);
		return_state->ics_irregs.ir_ss     = PERTASK_GET(x86_rpc_redirection_iret.ir_ss);
		__wrds(ustate->ucs_sgregs.sg_ds);
		__wres(ustate->ucs_sgregs.sg_es);
		__wrfs(ustate->ucs_sgregs.sg_fs);
		__wrgs(ustate->ucs_sgregs.sg_gs);
#else /* __x86_64__ */
		return_state->ics_gpregs             = ustate->ucs_gpregs;
		return_state->ics_irregs_u.ir_eip    = PERTASK_GET(x86_rpc_redirection_iret.ir_eip);
		return_state->ics_irregs_u.ir_cs     = PERTASK_GET(x86_rpc_redirection_iret.ir_cs);
		return_state->ics_irregs_u.ir_eflags = PERTASK_GET(x86_rpc_redirection_iret.ir_eflags);
#if 0 /* Still properly initialized... */
		return_state->ics_irregs_u.ir_ss     = return_state->ics_irregs_u.ir_ss;
		return_state->ics_irregs_u.ir_esp    = return_state->ics_irregs_u.ir_esp;
#endif
		if (ustate->ucs_eflags & EFLAGS_VM) {
			/* Special case: vm86 return state */
			return_state->ics_ds             = SEGMENT_USER_DATA_RPL;
			return_state->ics_es             = SEGMENT_USER_DATA_RPL;
			return_state->ics_fs             = SEGMENT_USER_FSBASE_RPL;
			return_state->ics_irregs_v.ir_es = ustate->ucs_sgregs.sg_es;
			return_state->ics_irregs_v.ir_ds = ustate->ucs_sgregs.sg_ds;
			return_state->ics_irregs_v.ir_fs = ustate->ucs_sgregs.sg_fs;
			return_state->ics_irregs_v.ir_gs = ustate->ucs_sgregs.sg_gs;
		} else {
			return_state->ics_ds = ustate->ucs_sgregs.sg_ds;
			return_state->ics_es = ustate->ucs_sgregs.sg_es;
			return_state->ics_fs = ustate->ucs_sgregs.sg_fs;
			__wrgs(ustate->ucs_sgregs.sg_gs);
		}
#endif /* !__x86_64__ */
	} else {
		/* Fill in the user-space return location to match `ustate' */
#ifdef __x86_64__
		GPREGS_TO_GPREGSNSP(return_state->ics_gpregs, ustate->ucs_gpregs);
		__wrgs(ustate->ucs_sgregs.sg_gs);
		__wrfs(ustate->ucs_sgregs.sg_fs);
		__wres(ustate->ucs_sgregs.sg_es);
		__wrds(ustate->ucs_sgregs.sg_ds);
		return_state->ics_irregs.ir_rip    = ustate->ucs_rip;
		return_state->ics_irregs.ir_cs     = ustate->ucs_cs;
		return_state->ics_irregs.ir_rflags = ustate->ucs_rflags;
		return_state->ics_irregs.ir_rsp    = ustate->ucs_gpregs.gp_rsp;
		return_state->ics_irregs.ir_ss     = ustate->ucs_ss;
#else /* __x86_64__ */
		return_state->ics_gpregs             = ustate->ucs_gpregs;
		return_state->ics_irregs_u.ir_eip    = ustate->ucs_eip;
		return_state->ics_irregs_u.ir_cs     = ustate->ucs_cs;
		return_state->ics_irregs_u.ir_eflags = ustate->ucs_eflags;
		return_state->ics_irregs_u.ir_esp    = ustate->ucs_gpregs.gp_esp;
		return_state->ics_irregs_u.ir_ss     = ustate->ucs_ss;
#ifndef CONFIG_NO_VM86
		if (ustate->ucs_eflags & EFLAGS_VM) {
			return_state->ics_fs = SEGMENT_USER_FSBASE_RPL;
			return_state->ics_es = SEGMENT_USER_DATA_RPL;
			return_state->ics_ds = SEGMENT_USER_DATA_RPL;
			return_state->ics_irregs_v.ir_es = ustate->ucs_sgregs.sg_es;
			return_state->ics_irregs_v.ir_ds = ustate->ucs_sgregs.sg_ds;
			return_state->ics_irregs_v.ir_fs = ustate->ucs_sgregs.sg_fs;
			return_state->ics_irregs_v.ir_gs = ustate->ucs_sgregs.sg_gs;
		} else
#endif
		{
			return_state->ics_fs = ustate->ucs_sgregs.sg_fs;
			return_state->ics_es = ustate->ucs_sgregs.sg_es;
			return_state->ics_ds = ustate->ucs_sgregs.sg_ds;
			/* Since %gs doesn't get restored by `return_state', set it now,
			 * thus allowing RPC functions to still manipulate it.
			 * NOTE: We can be sure that it has a valid value, since this is
			 *       still the original value that was set when user-space
			 *       originally entered the kernel. */
			__wrgs(ustate->ucs_sgregs.sg_gs);
		}
#endif /* !__x86_64__ */
	}
#ifdef __x86_64__
	set_user_fsbase(ustate->ucs_sgbase.sg_fsbase);
	set_user_gsbase(ustate->ucs_sgbase.sg_gsbase);
#endif /* __x86_64__ */


	/* Now that we've constructed an entirely valid ICPUSTATE at the base of our
	 * own stack, we can re-enable interrupts, as it will be this state which is
	 * (presumably) going to be restored when jumping back into user-space. */
	__sti();

	/* Service RPCs before returning to user-space. */
	if (TASK_RPC_REASON_GETREASON(reason) == TASK_RPC_REASON_SYSCALL) {
		struct rpc_syscall_info info;
		bool must_restart_syscall;
		/* Fill in system call information. */
#ifdef __x86_64__
		info.rsi_sysno = return_state->ics_gpregs.gp_rax;
#else /* __x86_64__ */
		info.rsi_sysno = return_state->ics_gpregs.gp_eax;
#endif /* !__x86_64__ */
		info.rsi_flags = (RPC_SYSCALL_INFO_FARGVALID(0) | RPC_SYSCALL_INFO_FARGVALID(1) |
		                  RPC_SYSCALL_INFO_FARGVALID(2) | RPC_SYSCALL_INFO_FARGVALID(3));
		if (irregs_rdflags(&return_state->ics_irregs) & EFLAGS_CF)
			info.rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
#ifdef __x86_64__
		if (!irregs_iscompat(&return_state->ics_irregs)) {
			/* Native 64-bit system call. */
			info.rsi_flags = (RPC_SYSCALL_INFO_FARGVALID(0) | RPC_SYSCALL_INFO_FARGVALID(1) |
			                  RPC_SYSCALL_INFO_FARGVALID(2) | RPC_SYSCALL_INFO_FARGVALID(3) |
			                  RPC_SYSCALL_INFO_FARGVALID(4) | RPC_SYSCALL_INFO_FARGVALID(5) |
			                  RPC_SYSCALL_INFO_METHOD_X86_64_SYSCALL);
			info.rsi_args[0] = return_state->ics_gpregs.gp_rdi;
			info.rsi_args[1] = return_state->ics_gpregs.gp_rsi;
			info.rsi_args[2] = return_state->ics_gpregs.gp_rdx;
			info.rsi_args[3] = return_state->ics_gpregs.gp_r10;
			info.rsi_args[4] = return_state->ics_gpregs.gp_r8;
			info.rsi_args[5] = return_state->ics_gpregs.gp_r9;
		} else
#endif /* __x86_64__ */
		{
			unsigned int method;
			method = TASK_RPC_REASON_GETMETHOD(reason);
			/* Load system call argument information. */
#ifdef __x86_64__
			info.rsi_args[0] = return_state->ics_gpregs.gp_rbx;
			info.rsi_args[1] = return_state->ics_gpregs.gp_rcx;
			info.rsi_args[2] = return_state->ics_gpregs.gp_rdx;
			info.rsi_args[3] = return_state->ics_gpregs.gp_rsi;
#else /* __x86_64__ */
			info.rsi_args[0] = return_state->ics_gpregs.gp_ebx;
			info.rsi_args[1] = return_state->ics_gpregs.gp_ecx;
			info.rsi_args[2] = return_state->ics_gpregs.gp_edx;
			info.rsi_args[3] = return_state->ics_gpregs.gp_esi;
#endif /* !__x86_64__ */
			if (method == TASK_RPC_REASON_SYSCALL_METHOD_SYSENTER) {
				unsigned int max_argc;
				info.rsi_flags |= RPC_SYSCALL_INFO_METHOD_SYSENTER;
				max_argc = SYSCALL_REGISTER_COUNT(info.rsi_sysno);
				assert(max_argc <= 6);
				if (max_argc > 4) {
					/* Try to load a 5th (and possibly 6th) argument. */
					USER syscall_ulong_t *argv;
#ifdef __x86_64__
					argv = (USER syscall_ulong_t *)return_state->ics_gpregs.gp_rbp;
#else /* __x86_64__ */
					argv = (USER syscall_ulong_t *)return_state->ics_gpregs.gp_ebp;
#endif /* !__x86_64__ */
					if likely(ADDR_IS_USER(argv)) {
						struct exception_data old_except;
						memcpy(&old_except, &THIS_EXCEPTION_INFO.ei_data, sizeof(old_except));
						TRY {
							/* Copy arguments from user-space. */
							info.rsi_args[4] = ATOMIC_READ(argv[0]);
							info.rsi_flags |= RPC_SYSCALL_INFO_FARGVALID(4);
							if (max_argc > 5) {
								info.rsi_args[5] = ATOMIC_READ(argv[1]);
								info.rsi_flags |= RPC_SYSCALL_INFO_FARGVALID(5);
							}
						} EXCEPT {
							if (!was_thrown(E_SEGFAULT))
								RETHROW();
							goto restore_old_except;
						}
						__IF0 {
restore_old_except:
							memcpy(&THIS_EXCEPTION_INFO.ei_data, &old_except, sizeof(old_except));
						}
					}
				}
			} else {
				info.rsi_flags |= (RPC_SYSCALL_INFO_FARGVALID(4) |
				                   RPC_SYSCALL_INFO_FARGVALID(5) |
				                   RPC_SYSCALL_INFO_METHOD_INT80);
#ifdef __x86_64__
				info.rsi_args[4] = return_state->ics_gpregs.gp_rdi;
				info.rsi_args[5] = return_state->ics_gpregs.gp_rbp;
#else /* __x86_64__ */
				info.rsi_args[4] = return_state->ics_gpregs.gp_edi;
				info.rsi_args[5] = return_state->ics_gpregs.gp_ebp;
#endif /* !__x86_64__ */
			}
		}
		must_restart_syscall = false;
		return_state = rpc_serve_user_redirection_all(return_state,
		                                              TASK_RPC_REASON_SYSCALL,
		                                              &info,
		                                              &must_restart_syscall);
		/* If there is still an active exception (i.e. RPC handling didn't resolve
		 * the exception, as would be the case for `E_INTERRUPT_USER_RPC'), then we
		 * must somehow propagate the exception into user-space. */
		if (error_code() != E_OK) {
			assert(!must_restart_syscall);
			return_state = x86_propagate_userspace_exception(return_state,
			                                                 TASK_RPC_REASON_SYSCALL);
		} else if unlikely(must_restart_syscall) {
			/* Must restart the current system call.
			 * -> We do this the same way that `sysenter' gets emulated in `hw_illegal_instruction.c',
			 *    while simply adding a secondary pass for `int 80h'
			 * -> These functions will reset the kernel stack to its base, load user-space registers,
			 *    and directly jump to the applicable int80 / sysenter entry points.
			 *    NOTE: During this process, the system call may get traced a second time. */
#ifdef __x86_64__
			if (!irregs_iscompat(&return_state->ics_irregs)) {
				x86_syscall_emulation(return_state);
			} else
#endif /* __x86_64__ */
			if (TASK_RPC_REASON_GETMETHOD(reason) == TASK_RPC_REASON_SYSCALL_METHOD_SYSENTER) {
				x86_sysenter_emulation(return_state);
			} else {
				x86_int80_emulation(return_state);
			}
		}
	} else {
		return_state = rpc_serve_user_redirection_all(return_state,
		                                              TASK_RPC_REASON_ASYNCUSER,
		                                              NULL,
		                                              NULL);
		/* If there is still an active exception (i.e. RPC handling didn't resolve
		 * the exception, as would be the case for `E_INTERRUPT_USER_RPC'), then we
		 * must somehow propagate the exception into user-space. */
		if (error_code() != E_OK)
			return_state = x86_propagate_userspace_exception(return_state,
			                                                 TASK_RPC_REASON_ASYNCUSER);
	}

	/* Unwind into to the target state, thus returning back to userspace, though
	 * with the associated target potentially changed. */
	x86_unwind_interrupt(return_state);
}


INTDEF void FCALL
halt_unhandled_exception(unsigned int error,
                         struct kcpustate *__restrict unwind_state);

#define X86_SYSCALL_PERSONALITY_LSDA_SYSENTER_FLAG   ((uintptr_t)UINT32_C(0x40000000))


/* The personality function used to handle exceptions propagated through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC as `rpc_serve_user_redirection_all' */
INTERN unsigned int
NOTHROW(KCALL x86_syscall_personality)(struct unwind_fde_struct *__restrict fde,
                                       struct kcpustate *__restrict state,
                                       byte_t *__restrict lsda) {
	struct ucpustate ustate;
	unsigned int error;
	KCPUSTATE_TO_UCPUSTATE(ustate, *state);
	{
		unwind_cfa_sigframe_state_t cfa;
		void *pc = (void *)(UCPUSTATE_PC(ustate) - 1);
		error = unwind_fde_sigframe_exec(fde, &cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
		error = unwind_cfa_sigframe_apply(&cfa, fde, pc,
		                                  &unwind_getreg_kcpustate, state,
		                                  &unwind_setreg_ucpustate, &ustate);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
	}
	/* Check if the return state actually points into user-space,
	 * or alternatively: indicates a user-space redirection. */
	if (!(ustate.ucs_cs & 3) &&
#ifndef __x86_64__
	    !(ustate.ucs_eflags & EFLAGS_VM) &&
#endif /* !__x86_64__ */
	    UCPUSTATE_PC(ustate) != (uintptr_t)&x86_rpc_user_redirection)
		goto err;
	/* System calls encode their vector number as the LSDA pointer, so that
	 * when unwinding we can reverse-engineer that number in order to decide
	 * on special actions to perform based on the called function, as well as
	 * inform user-space of which function caused the exception, as well as
	 * implement system call restarting. */
	if (((uintptr_t)lsda & ~X86_SYSCALL_PERSONALITY_LSDA_SYSENTER_FLAG) !=
	    ((uintptr_t)-1 & ~X86_SYSCALL_PERSONALITY_LSDA_SYSENTER_FLAG)) {
#ifdef __x86_64__
		ustate.ucs_gpregs.gp_rax = (uintptr_t)lsda & ~X86_SYSCALL_PERSONALITY_LSDA_SYSENTER_FLAG;
#else /* __x86_64__ */
		ustate.ucs_gpregs.gp_eax = (uintptr_t)lsda & ~X86_SYSCALL_PERSONALITY_LSDA_SYSENTER_FLAG;
#endif /* !__x86_64__ */
	}
	x86_handle_except_before_userspace(&ustate,
	                                   (uintptr_t)lsda & X86_SYSCALL_PERSONALITY_LSDA_SYSENTER_FLAG
	                                   ? TASK_RPC_REASON_SYSCALL | TASK_RPC_REASON_SYSCALL_METHOD_SYSENTER
	                                   : TASK_RPC_REASON_SYSCALL | TASK_RPC_REASON_SYSCALL_METHOD_INT80);
err:
	halt_unhandled_exception(error, state);
	return DWARF_PERSO_EXECUTE_HANDLER_NOW;
}


INTDEF byte_t x86_sysenter_main[];

#ifndef CONFIG_NO_SYSCALL_TRACING
PRIVATE ATTR_COLDBSS struct mutex syscall_tracing_lock = MUTEX_INIT;
INTERN ATTR_COLDBSS bool syscall_tracing_enabled = false;

DATDEF struct idt_segment x86_idt_start[256];
DATDEF struct idt_segment x86_idt_start_traced[256];

INTDEF byte_t x86_sysenter_main_traced[];


struct ATTR_PACKED idt_pointer {
	uint16_t ip_length; /* Length */
	void    *ip_base;   /* Base */
};

PRIVATE NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL syscall_tracing_ipi)(struct icpustate *__restrict state,
                                   void *args[CPU_IPI_ARGCOUNT]) {
	if (CPUID_FEATURES.ci_1d & CPUID_1D_SEP) {
		/* Also re-direct the `sysenter' instruction */
		__wrmsr(IA32_SYSENTER_EIP,
		        args[0] == x86_idt_start_traced ? (uintptr_t)x86_sysenter_main_traced
		                                        : (uintptr_t)x86_sysenter_main);
	}
	__lidt(sizeof(x86_idt_start) - 1, args[0]);
	return state;
}

/* Enable/disable system call tracing.
 * @return: true:  Successfully changed the current tracing state.
 * @return: false: Tracing was already enabled/disabled. */
PUBLIC bool KCALL syscall_tracing_setenabled(bool enable) {
	void *argv[CPU_IPI_ARGCOUNT];
	struct idt_pointer oldptr;
	SCOPED_WRITELOCK(&syscall_tracing_lock);
	argv[0] = enable
	          ? x86_idt_start_traced
	          : x86_idt_start;
	ATOMIC_WRITE(syscall_tracing_enabled, enable);
	cpu_broadcastipi_notthis(&syscall_tracing_ipi,
	                         argv,
#if 1
	                         CPU_IPI_FNORMAL
	                         /* NOTE: Don't wake up deep-sleep CPUs!
	                          *       When a CPU wakes up, it already has to go through all
	                          *       of the initialization that also contains the part where
	                          *       it needs to load its IDT according to tracing of syscalls
	                          *       currently being enabled. */
#else
	                         CPU_IPI_FWAKEUP
#endif
	                         );
	if (CPUID_FEATURES.ci_1d & CPUID_1D_SEP) {
		__wrmsr(IA32_SYSENTER_EIP,
		        enable ? (uintptr_t)x86_sysenter_main_traced
		               : (uintptr_t)x86_sysenter_main);
	}
	__sidt(&oldptr);
	__lidt(sizeof(x86_idt_start) - 1, argv[0]);
	return oldptr.ip_base != argv[0];
}
/* Check if system call tracing is enabled. */
PUBLIC WUNUSED bool
NOTHROW(KCALL syscall_tracing_getenabled)(void) {
#if 1
	return ATOMIC_READ(syscall_tracing_enabled);
#else
	struct idt_pointer ptr;
	__sidt(&ptr);
	return ptr.ip_base == x86_idt_start_traced;
#endif
}
#endif /* !CONFIG_NO_SYSCALL_TRACING */


#ifdef __x86_64__

/* TODO */

#else /* __x86_64__ */

/* The return address to which system calls will return when they
 * propagate exceptions through `syscall_emulate_callback()'.
 * If we encounter this address during unwinding, instead of the
 * normal unwind procedure, we instead check if exceptions should
 * be propagated as errno codes, in which case we do the translation
 * before resuming execution normally.
 */
INTDEF byte_t x86_syscall_emulate_callback_guard_begin[];
INTDEF byte_t x86_syscall_emulate_callback_guard_end[];

struct x86_syscall_emulate_callback_stack {
	/*   +24 : subl   $24, %esp
	 *   +4  : pushl_cfi_r %esi
	 *   +4  : pushl_cfi_r %edi
	 *   +4  : pushl_cfi   %ecx // Backup `regs' for unwinding (s.a. `x86_syscall_emulate_callback_personality')
	 *   +4  : pushl_cfi   %edx // Backup `sysno' for unwinding (s.a. `x86_syscall_emulate_callback_personality')
	 *   +4  : RETURN_ADDRESS */
	u32               syscall_args[6];
	u32               saved_esi;
	u32               saved_edi;
	struct icpustate *regs;
	u32               sysno;
	union {
		byte_t        entry_sp[1];
		void         *return_pc;
	};
	u32               enable_except;
	byte_t            return_sp[1];
};

/* Personality function for guarding against exceptions that
 * are being propagated through `syscall_emulate_callback()' */
INTERN unsigned int
NOTHROW(KCALL x86_syscall_emulate_callback_personality)(struct unwind_fde_struct *__restrict fde,
                                                        struct kcpustate *__restrict state,
                                                        byte_t *__restrict lsda) {
	struct rpc_syscall_info info;
	struct icpustate *regs;
	bool must_restart_syscall;
	struct x86_syscall_emulate_callback_stack *stack;

	/* Continue unwinding if the exception isn't being
	 * propagated through the actual system call invocation. */
	if (state->kcs_eip <= (uintptr_t)x86_syscall_emulate_callback_guard_begin ||
	    state->kcs_eip > (uintptr_t)x86_syscall_emulate_callback_guard_end)
		return DWARF_PERSO_CONTINUE_UNWIND;

	stack = (struct x86_syscall_emulate_callback_stack *)state->kcs_gpregs.gp_esp;
	regs           = stack->regs;
	info.rsi_sysno = stack->sysno;
	info.rsi_flags = RPC_SYSCALL_INFO_FNORMAL | RPC_SYSCALL_INFO_METHOD_CALLBACK;
	if (stack->enable_except)
		info.rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	/* Load system call arguments. */
	{
		USER syscall_ulong_t *argv;
		argv = (USER syscall_ulong_t *)regs->ics_irregs_u.ir_esp;
		if likely(ADDR_IS_USER(argv)) {
			struct exception_data old_except;
			memcpy(&old_except, &THIS_EXCEPTION_INFO.ei_data, sizeof(old_except));
			TRY {
				unsigned int i, max_argc;
				max_argc = SYSCALL_REGISTER_COUNT(info.rsi_sysno);
				assert(max_argc <= 6);
				/* Copy arguments from user-space. */
				for (i = 0; i < max_argc; ++i) {
					info.rsi_args[i] = ATOMIC_READ(argv[i]);
					info.rsi_flags |= RPC_SYSCALL_INFO_FARGVALID(i);
				}
			} EXCEPT {
				if (!was_thrown(E_SEGFAULT))
					RETHROW();
				goto restore_old_except;
			}
			__IF0 {
restore_old_except:
				memcpy(&THIS_EXCEPTION_INFO.ei_data, &old_except, sizeof(old_except));
			}
		}
	}

	/* Service user-redirection RPCs to try and resolve the problem. */
	must_restart_syscall = false;
	regs = rpc_serve_user_redirection_all(regs,
	                                      TASK_RPC_REASON_SYSCALL,
	                                      &info,
	                                      &must_restart_syscall);
	if (error_code() == E_OK) {
		if unlikely(must_restart_syscall) {
			/* Unwind to the start of `syscall_emulate_callback()',
			 * thus re-starting the system call. */
			state->kcs_gpregs.gp_esi = stack->saved_esi;
			state->kcs_gpregs.gp_edi = stack->saved_edi;
			state->kcs_gpregs.gp_ecx = (uintptr_t)regs;
			state->kcs_gpregs.gp_edx = (uintptr_t)info.rsi_sysno;
			state->kcs_gpregs.gp_esp = (uintptr_t)stack->entry_sp;
			state->kcs_eip = (uintptr_t)&syscall_emulate_callback;
			return DWARF_PERSO_EXECUTE_HANDLER_NOW;
		}
		/* RPCs were able to handle the error!
		 * -> Have `syscall_emulate_callback()' return normally */
		state->kcs_gpregs.gp_esi = stack->saved_esi;
		state->kcs_gpregs.gp_edi = stack->saved_edi;
		state->kcs_eip           = (uintptr_t)stack->return_pc;
		state->kcs_gpregs.gp_esp = (uintptr_t)stack->return_sp;
		/* Have the `syscall_emulate_callback()' function return the new register state. */
		state->kcs_gpregs.gp_eax = (u32)regs;
		return DWARF_PERSO_EXECUTE_HANDLER_NOW;
	}
	assert(!must_restart_syscall);
	*(struct icpustate **)(state->kcs_gpregs.gp_esp + (24 + 4 + 4)) = regs;

	/* Check if `enable_except' was true. */
	if (info.rsi_flags & RPC_SYSCALL_INFO_FEXCEPT)
		return DWARF_PERSO_CONTINUE_UNWIND; /* Propagate the exception */
	if (ERRORCODE_ISRTLPRIORITY(error_code()))
		return DWARF_PERSO_CONTINUE_UNWIND; /* Always propagate */

	/* Must handle the exception by translating it to an errno */
	state->kcs_gpregs.gp_esi = stack->saved_esi;
	state->kcs_gpregs.gp_edi = stack->saved_edi;
	assert(info.rsi_sysno == stack->sysno);
	state->kcs_eip           = (uintptr_t)stack->return_pc;
	state->kcs_gpregs.gp_esp = (uintptr_t)stack->return_sp;

	/* Have the `syscall_emulate_callback()' function return the new register state. */
	state->kcs_gpregs.gp_eax = (u32)regs;

	/* Store the errno variant of the current exception
	 * in the user-space register context. */
	if (SYSCALL32_DOUBLE_WIDE(info.rsi_sysno))
		regs->ics_gpregs.gp_edx = (u32)-1; /* sign-extend */
	regs->ics_gpregs.gp_eax = (u32)-error_as_errno(error_data());
	PERTASK_SET(_this_exception_info.ei_code, (error_code_t)ERROR_CODEOF(E_OK));

	/* With the unwinding now completed, resume normal execution. */
	return DWARF_PERSO_EXECUTE_HANDLER_NOW;
}




INTDEF byte_t x86_syscall_emulate_int80_guard[];

struct syscall_emulate_int80_stack {
	/* +24 : subl   $24, %esp
	 * +4  : pushl_cfi %ecx // Backup `regs' for unwinding (s.a. `syscall_emulate_int80_personality')
	 * +4  : RETURN_ADDRESS */
	u32               syscall_args[6];
	struct icpustate *regs;
	union {
		byte_t        entry_sp[1];
		void         *return_pc;
	};
	byte_t            return_sp[1];
};

INTERN unsigned int
NOTHROW(KCALL syscall_emulate_int80_personality)(struct unwind_fde_struct *__restrict fde,
                                                 struct kcpustate *__restrict state,
                                                 byte_t *__restrict lsda) {
	struct rpc_syscall_info info;
	struct icpustate *regs;
	bool must_restart_syscall;
	struct syscall_emulate_int80_stack *stack;

	/* Only guard the actual invocation of system calls. */
	if (state->kcs_eip != (uintptr_t)x86_syscall_emulate_int80_guard)
		return DWARF_PERSO_CONTINUE_UNWIND;

	/* Check if `enable_except' was true. */
	stack = (struct syscall_emulate_int80_stack *)state->kcs_gpregs.gp_esp;
	regs = stack->regs;

	/* Load system call information. */
	info.rsi_sysno = regs->ics_gpregs.gp_eax;
	info.rsi_flags = (RPC_SYSCALL_INFO_FNORMAL | RPC_SYSCALL_INFO_METHOD_INT80 |
	                  RPC_SYSCALL_INFO_FARGVALID(0) | RPC_SYSCALL_INFO_FARGVALID(1) |
	                  RPC_SYSCALL_INFO_FARGVALID(2) | RPC_SYSCALL_INFO_FARGVALID(3) |
	                  RPC_SYSCALL_INFO_FARGVALID(4) | RPC_SYSCALL_INFO_FARGVALID(5));
	if (irregs_rdflags(&regs->ics_irregs_k) & EFLAGS_CF)
		info.rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	info.rsi_args[0] = regs->ics_gpregs.gp_ebx;
	info.rsi_args[1] = regs->ics_gpregs.gp_ecx;
	info.rsi_args[2] = regs->ics_gpregs.gp_edx;
	info.rsi_args[3] = regs->ics_gpregs.gp_esi;
	info.rsi_args[4] = regs->ics_gpregs.gp_edi;
	info.rsi_args[5] = regs->ics_gpregs.gp_ebp;

	/* Service user-redirection RPCs to try and resolve the problem. */
	must_restart_syscall = false;
	regs = rpc_serve_user_redirection_all(regs,
	                                      TASK_RPC_REASON_SYSCALL,
	                                      &info,
	                                      &must_restart_syscall);

	if (error_code() == E_OK) {
		if unlikely(must_restart_syscall) {
			/* Unwind to the start of `syscall_emulate_int80()',
			 * thus restarting the system call. */
			state->kcs_gpregs.gp_ecx = (u32)regs;
			state->kcs_gpregs.gp_esp = (uintptr_t)stack->entry_sp;
			state->kcs_eip = (uintptr_t)&syscall_emulate_int80;
			return DWARF_PERSO_EXECUTE_HANDLER_NOW;
		}
		/* RPCs were able to handle the error!
		 * -> Have `syscall_emulate_int80()' return normally */
		state->kcs_eip           = (uintptr_t)stack->return_pc;
		state->kcs_gpregs.gp_esp = (uintptr_t)stack->return_sp;
		/* Have the `syscall_emulate_int80()' function return the new register state. */
		state->kcs_gpregs.gp_eax = (u32)regs;
		return DWARF_PERSO_EXECUTE_HANDLER_NOW;
	}
	assert(!must_restart_syscall);
	stack->regs = regs;

	if (info.rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) /* propagate exceptions */
		return DWARF_PERSO_CONTINUE_UNWIND;
	if (ERRORCODE_ISRTLPRIORITY(error_code()))
		return DWARF_PERSO_CONTINUE_UNWIND; /* Always propagate */

	/* Must handle the exception by translating it to an errno */
	state->kcs_eip           = (uintptr_t)stack->return_pc;
	state->kcs_gpregs.gp_esp = (uintptr_t)stack->return_sp;
	/* Have the `syscall_emulate_int80()' function return the new register state. */
	state->kcs_gpregs.gp_eax = (u32)regs;

	/* Store the errno variant of the current exception
	 * in the user-space register context. */
	if (SYSCALL32_DOUBLE_WIDE(info.rsi_sysno))
		regs->ics_gpregs.gp_edx = (u32)-1; /* sign-extend */
	regs->ics_gpregs.gp_eax = (u32)-error_as_errno(error_data());
	PERTASK_SET(_this_exception_info.ei_code, (error_code_t)ERROR_CODEOF(E_OK));

	/* With the unwinding now completed, resume normal execution. */
	return DWARF_PERSO_EXECUTE_HANDLER_NOW;
}


typedef syscall_ulong_t (__ARCH_SYSCALLCC *syscall_proto_t)(syscall_ulong_t arg0, syscall_ulong_t arg1,
                                                            syscall_ulong_t arg2, syscall_ulong_t arg3,
                                                            syscall_ulong_t arg4, syscall_ulong_t arg5);
typedef u64 (__ARCH_SYSCALLCC *syscall_proto64_t)(syscall_ulong_t arg0, syscall_ulong_t arg1,
                                                  syscall_ulong_t arg2, syscall_ulong_t arg3,
                                                  syscall_ulong_t arg4, syscall_ulong_t arg5);
INTDEF syscall_proto_t const __c32_syscallrouter[];
INTDEF syscall_proto_t const __c32_exsyscallrouter[];



/* GCC doesn't like our casts to `syscall_proto64_t' */
#pragma GCC diagnostic ignored "-Wcast-function-type"


/* Emulate a system call, given its all possible information about it.
 * @param: regs:          The user-space register context in which the
 *                        system call should be executed.
 * @param: sysno:         The system call ID that is being invoked.
 * @param: enable_except: When true, enable support for exceptions.
 *                        Otherwise, translate exceptions to errno codes,
 *                        and write them into the return register of `regs'.
 * @param: argN:          The Nth argument to-be passed to the system call. */
PUBLIC struct icpustate *FCALL
syscall_emulate(struct icpustate *__restrict regs,
                struct rpc_syscall_info *__restrict sc_info) {
	syscall_proto_t proto;
	syscall_ulong_t sysno;
	assertf((sc_info->rsi_flags & RPC_SYSCALL_INFO_FMETHOD) == RPC_SYSCALL_INFO_METHOD_EMULATE,
	        "Invalid `sc_info' passed to `syscall_emulate()' (syscall "
	        "method must be RPC_SYSCALL_INFO_METHOD_EMULATE, but is %#x)",
	        sc_info->rsi_flags & RPC_SYSCALL_INFO_FMETHOD);
again:
	sysno = sc_info->rsi_sysno;
	TRY {
		if (sysno < __NR_syscall_max) {
			/* Normal system call */
			proto = __c32_syscallrouter[sysno];
			if (x86_syscall_double_wide_get(x86_syscall_register_count, sysno)) {
				u64 result;
do_syscall64:
				result = (*(syscall_proto64_t)proto)(sc_info->rsi_args[0],
				                                     sc_info->rsi_args[1],
				                                     sc_info->rsi_args[2],
				                                     sc_info->rsi_args[3],
				                                     sc_info->rsi_args[4],
				                                     sc_info->rsi_args[5]);
				regs->ics_gpregs.gp_eax = (u32)(result);
				regs->ics_gpregs.gp_edx = (u32)(result >> 32);
			} else {
do_syscall32:
				regs->ics_gpregs.gp_eax = (*proto)(sc_info->rsi_args[0],
				                                   sc_info->rsi_args[1],
				                                   sc_info->rsi_args[2],
				                                   sc_info->rsi_args[3],
				                                   sc_info->rsi_args[4],
				                                   sc_info->rsi_args[5]);
			}
		} else if (sysno >= __NR_exsyscall_min && sysno <= __NR_exsyscall_max) {
			/* Extended system call */
			proto = __c32_exsyscallrouter[sysno - __NR_exsyscall_min];
			if (x86_syscall_double_wide_get(x86_exsyscall_register_count, sysno - __NR_exsyscall_min))
				goto do_syscall64;
			goto do_syscall32;
		} else {
			/* Invalid system call */
			if (sc_info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) {
				syscall_ulong_t args[6];
				unsigned int i;
				memcpy(args, sc_info->rsi_args, sizeof(args));
				for (i = 0; i < 6; ++i) {
					if (!(sc_info->rsi_flags & RPC_SYSCALL_INFO_FARGVALID(i)))
						args[i] = 0;
				}
				THROW(E_UNKNOWN_SYSTEMCALL,
				      sc_info->rsi_sysno,
				      args[0], args[1], args[2],
				      args[3], args[4], args[5]);
			}
			regs->ics_gpregs.gp_eax = (u32)-ENOSYS;
		}
	} EXCEPT {
		/* Service user-redirection RPCs to try and resolve the problem. */
		bool must_restart_syscall;
		must_restart_syscall = false;
		regs = rpc_serve_user_redirection_all(regs,
		                                      TASK_RPC_REASON_SYSCALL,
		                                      sc_info,
		                                      &must_restart_syscall);
		assert((sc_info->rsi_flags & RPC_SYSCALL_INFO_FMETHOD) == RPC_SYSCALL_INFO_METHOD_EMULATE);
		if (error_code() == E_OK) {
			if unlikely(must_restart_syscall)
				goto again; /* Do the restart */
			/* RPCs were able to handle the error!  -> return normally */
			goto done;
		}
		assert(!must_restart_syscall);
		if (sc_info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) /* propagate exceptions */
			RETHROW();
		if (ERRORCODE_ISRTLPRIORITY(error_code()))
			RETHROW(); /* Always propagate */
		/* Store the errno variant of the current exception
		 * in the user-space register context. */
		if (SYSCALL32_DOUBLE_WIDE(sysno))
			regs->ics_gpregs.gp_edx = (u32)-1; /* sign-extend */
		regs->ics_gpregs.gp_eax = (u32)-error_as_errno(error_data());
		PERTASK_SET(_this_exception_info.ei_code, (error_code_t)ERROR_CODEOF(E_OK));
	}
done:
	return regs;
}


struct x86_lcall7_syscall_data {
	uintptr_t          unwind_sysno;
	uintptr_t          saved_edx;
	uintptr_t          saved_ecx;
	uintptr_t          saved_fs;
	uintptr_t          saved_es;
	uintptr_t          saved_ds;
	struct irregs_user iret;
};

INTDEF byte_t x86_lcall7_syscall_guard[];

INTERN unsigned int
NOTHROW(KCALL x86_syscall_lcall7_personality)(struct unwind_fde_struct *__restrict UNUSED(fde),
                                              struct kcpustate *__restrict state,
                                              byte_t *__restrict UNUSED(lsda)) {
	struct x86_lcall7_syscall_data *data;
	if (KCPUSTATE_PC(*state) != (uintptr_t)x86_lcall7_syscall_guard)
		return DWARF_PERSO_CONTINUE_UNWIND;
	data = (struct x86_lcall7_syscall_data *)KCPUSTATE_SP(*state);
	assertf((uintptr_t)(data + 1) == (uintptr_t)VM_PAGE2ADDR(PERTASK_GET((*(struct vm_node *)&_this_kernel_stack).vn_node.a_vmax) + 1),
	        "%p != %p",
	        (uintptr_t)(data + 1),
	        (uintptr_t)VM_PAGE2ADDR(PERTASK_GET((*(struct vm_node *)&_this_kernel_stack).vn_node.a_vmax) + 1));

	/* TODO: Custom unwind handler. */

	return DWARF_PERSO_CONTINUE_UNWIND;
}

INTERN syscall_ulong_t FCALL
x86_lcall7_syscall_main(struct x86_lcall7_syscall_data *__restrict data,
                        syscall_ulong_t sysno) {
	unsigned int argc;
	syscall_ulong_t result;
	syscall_ulong_t argv[6];
	USER syscall_ulong_t *usp;
	bool double_wide;
	syscall_proto_t proto;
	memset(argv, 0, sizeof(argv));
	usp = (USER syscall_ulong_t *)data->iret.ir_esp;
	if (sysno <= __NR_syscall_max) {
		proto       = __c32_syscallrouter[sysno];
		argc        = x86_syscall_register_count_get(x86_syscall_register_count, sysno);
		double_wide = x86_syscall_double_wide_get(x86_syscall_register_count, sysno);
	} else if (sysno >= __NR_exsyscall_min && sysno <= __NR_exsyscall_max) {
		proto       = __c32_exsyscallrouter[sysno - __NR_exsyscall_min];
		argc        = x86_syscall_register_count_get(x86_exsyscall_register_count, sysno - __NR_exsyscall_min);
		double_wide = x86_syscall_double_wide_get(x86_exsyscall_register_count, sysno - __NR_exsyscall_min);
	} else {
		goto err_nosys;
	}
	if unlikely(!ADDR_IS_USER(usp)) {
		if (argc != 0)
			THROW(E_SEGFAULT_UNMAPPED, usp, E_SEGFAULT_CONTEXT_USERCODE);
	} else {
		switch (argc) {
		case 6:
			argv[5] = ATOMIC_READ(usp[5]);
			ATTR_FALLTHROUGH
		case 5:
			argv[4] = ATOMIC_READ(usp[4]);
			ATTR_FALLTHROUGH
		case 4:
			argv[3] = ATOMIC_READ(usp[3]);
			ATTR_FALLTHROUGH
		case 3:
			argv[2] = ATOMIC_READ(usp[2]);
			ATTR_FALLTHROUGH
		case 2:
			argv[1] = ATOMIC_READ(usp[1]);
			ATTR_FALLTHROUGH
		case 1:
			argv[0] = ATOMIC_READ(usp[0]);
			ATTR_FALLTHROUGH
		case 0:
			break;
		default: __builtin_unreachable();
		}
	}
	if (double_wide) {
		u64 result64;
		result64 = (*(syscall_proto64_t)proto)(argv[0], argv[1],
		                                       argv[2], argv[3],
		                                       argv[4], argv[5]);
		data->saved_edx = (u32)(result64 >> 32);
		result = (u32)result64;
	} else {
		result = (*proto)(argv[0], argv[1],
		                  argv[2], argv[3],
		                  argv[4], argv[5]);
	}
	return result;
err_nosys:
	if (!(data->iret.ir_eflags & EFLAGS_CF))
		return (syscall_ulong_t)-ENOSYS;
	if likely(ADDR_IS_USER(usp)) {
		TRY {
			argv[5] = ATOMIC_READ(usp[5]);
			argv[4] = ATOMIC_READ(usp[4]);
			argv[3] = ATOMIC_READ(usp[3]);
			argv[2] = ATOMIC_READ(usp[2]);
			argv[1] = ATOMIC_READ(usp[1]);
			argv[0] = ATOMIC_READ(usp[0]);
		} EXCEPT {
		}
	}
	THROW(E_UNKNOWN_SYSTEMCALL,
	      sysno,
	      argv[0], argv[1], argv[2],
	      argv[3], argv[4], argv[5]);
}
#endif /* !__x86_64__ */






INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_sysenter)(void) {
	if (CPUID_FEATURES.ci_1d & CPUID_1D_SEP) {
		/* Configure support for the `sysenter' instruction. */
		__wrmsr(IA32_SYSENTER_CS, SEGMENT_KERNEL_CODE);
#ifdef __x86_64__
		__wrmsr(IA32_SYSENTER_ESP, (uintptr_t)&FORCPU(&_bootcpu, x86_cputss).t_rsp0);
#else /* __x86_64__ */
		__wrmsr(IA32_SYSENTER_ESP, (uintptr_t)&FORCPU(&_bootcpu, x86_cputss).t_esp0);
#endif /* !__x86_64__ */
		__wrmsr(IA32_SYSENTER_EIP, (uintptr_t)x86_sysenter_main);
	}
}



/* System call register count information. */
#define __BEGIN_SYSCALLS(min,max,cnt)          struct syscalls_argc_info {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) struct extended_syscalls_argc_info {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define __SYSCALL(name)                                              unsigned int argc_##name : 4;
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        unsigned int argc_unused_##sysno : 4;
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          unsigned int argc_unused_##sysno : 4;
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) unsigned int argc_unused_##sysno : 4;
#include <asm/ls_syscalls.h>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS

#define ARG_PLACEHOLDER_1  ,
#define TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define TAKE_SECOND_ARG(x) TAKE_SECOND_ARG_IMPL x
#define IS_DEFINED3(x) TAKE_SECOND_ARG((x 1,0))
#define IS_DEFINED2(x) IS_DEFINED3(ARG_PLACEHOLDER_##x)
#define IS_DEFINED(x) IS_DEFINED2(x)


DATDEF struct syscalls_argc_info const x86_syscall_register_count_s ASMNAME("x86_syscall_register_count");
DATDEF struct extended_syscalls_argc_info const x86_exsyscall_register_count_s ASMNAME("x86_exsyscall_register_count");

#define __BEGIN_SYSCALLS(min,max,cnt)             PUBLIC_CONST struct syscalls_argc_info const x86_syscall_register_count_s = {
#define __END_SYSCALLS(min,max,cnt)               };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt)    PUBLIC_CONST struct extended_syscalls_argc_info const x86_exsyscall_register_count_s = {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)      };
#ifdef __x86_64__
#define __SYSCALL(name)                                              /* .argc_##name  = */__NRAC_##name,
#else /* __x86_64__ */
#define IS_DOUBLE_WIDE(name)   IS_DEFINED(__NRDW386_##name)
#define __SYSCALL(name)                                              /* .argc_##name  = */__NRAC386_##name | (IS_DOUBLE_WIDE(name) ? 8 : 0),
#endif /* !__x86_64__ */
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        /* .argc_##sysno = */0,
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          /* .argc_##sysno = */0,
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) /* .argc_##sysno = */0,
#include <asm/ls_syscalls.h>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS


/* System call restart mode / cancellation point information. */
#define __BEGIN_SYSCALLS(min,max,cnt)          struct syscalls_restart_info {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) struct extended_syscalls_restart_info {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define __SYSCALL(name)                                              unsigned int rm_##name : 2;
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        unsigned int rm_unused_##sysno : 2;
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          unsigned int rm_unused_##sysno : 2;
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) unsigned int rm_unused_##sysno : 2;
#include <asm/ls_syscalls.h>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS

DATDEF struct syscalls_restart_info const x86_syscall_restart_mode_s ASMNAME("x86_syscall_restart_mode");
DATDEF struct extended_syscalls_restart_info const x86_exsyscall_restart_mode_s ASMNAME("x86_exsyscall_restart_mode");
#define __BEGIN_SYSCALLS(min,max,cnt)             PUBLIC_CONST struct syscalls_restart_info const x86_syscall_restart_mode_s = {
#define __END_SYSCALLS(min,max,cnt)               };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt)    PUBLIC_CONST struct extended_syscalls_restart_info const x86_exsyscall_restart_mode_s = {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)      };
#define __SYSCALL(name)                                              /* .rm_##name  = */__NRRM_##name,
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        /* .rm_unused_##sysno = */SYSCALL_RESTART_MODE_AUTO,
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          /* .rm_unused_##sysno = */SYSCALL_RESTART_MODE_AUTO,
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) /* .rm_unused_##sysno = */SYSCALL_RESTART_MODE_AUTO,
#include <asm/ls_syscalls.h>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS


#define __BEGIN_SYSCALLS(min,max,cnt)          struct syscalls_is_cancellation_point_info {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) struct extended_syscalls_is_cancellation_point_info {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define __SYSCALL(name)                                              unsigned int icp_##name : 1;
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        unsigned int icp_unused_##sysno : 1;
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          unsigned int icp_unused_##sysno : 1;
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) unsigned int icp_unused_##sysno : 1;
#include <asm/ls_syscalls.h>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS

DATDEF struct syscalls_is_cancellation_point_info const x86_syscall_is_cancellation_point_s ASMNAME("x86_syscall_is_cancellation_point");
DATDEF struct extended_syscalls_is_cancellation_point_info const x86_exsyscall_is_cancellation_point_s ASMNAME("x86_exsyscall_is_cancellation_point");
#define __BEGIN_SYSCALLS(min,max,cnt)             PUBLIC_CONST struct syscalls_is_cancellation_point_info const x86_syscall_is_cancellation_point_s = {
#define __END_SYSCALLS(min,max,cnt)               };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt)    PUBLIC_CONST struct extended_syscalls_is_cancellation_point_info const x86_exsyscall_is_cancellation_point_s = {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)      };
#define __SYSCALL(name)                                              /* .icp_##name  = */__NRCP_##name,
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        /* .icp_unused_##sysno = */1,
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          /* .icp_unused_##sysno = */1,
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) /* .icp_unused_##sysno = */1,
#include <asm/ls_syscalls.h>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS






#ifdef __x86_64__
#include <asm/syscalls32.inl>

#define __BEGIN_SYSCALLS(min,max,cnt)          struct syscalls32_argc_info {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) struct extended_syscalls32_argc_info {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define __SYSCALL(name)                                              unsigned int argc_##name : 4;
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        unsigned int argc_unused_##sysno : 4;
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          unsigned int argc_unused_##sysno : 4;
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) unsigned int argc_unused_##sysno : 4;
#include <asm/ls_syscalls32.inl>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS

DATDEF struct syscalls32_argc_info const x86_syscall32_register_count_s ASMNAME("x86_syscall32_register_count");
DATDEF struct extended_syscalls32_argc_info const x86_exsyscall32_register_count_s ASMNAME("x86_exsyscall32_register_count");

#define __BEGIN_SYSCALLS(min,max,cnt)          PUBLIC_CONST struct syscalls32_argc_info const x86_syscall32_register_count_s = {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) PUBLIC_CONST struct extended_syscalls32_argc_info const x86_exsyscall32_register_count_s = {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define IS_DOUBLE_WIDE_386(name)   IS_DEFINED(__NR32AC386_##name)
#define __SYSCALL(name)                                              /* .argc_##name  = */__NR32AC386_##name | (IS_DOUBLE_WIDE_386(name) ? 8 : 0),
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        /* .argc_##sysno = */0,
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          /* .argc_##sysno = */0,
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) /* .argc_##sysno = */0,
#include <asm/ls_syscalls32.inl>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS



/* System call restart mode / cancellation point information. */
#define __BEGIN_SYSCALLS(min,max,cnt)          struct syscalls32_restart_info {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) struct extended_syscalls32_restart_info {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define __SYSCALL(name)                                              unsigned int rm_##name : 2;
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        unsigned int rm_unused_##sysno : 2;
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          unsigned int rm_unused_##sysno : 2;
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) unsigned int rm_unused_##sysno : 2;
#include <asm/ls_syscalls32.inl>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS

DATDEF struct syscalls32_restart_info const x86_syscall32_restart_mode_s ASMNAME("x86_syscall32_restart_mode");
DATDEF struct extended_syscalls32_restart_info const x86_exsyscall32_restart_mode_s ASMNAME("x86_exsyscall32_restart_mode");
#define __BEGIN_SYSCALLS(min,max,cnt)             PUBLIC_CONST struct syscalls32_restart_info const x86_syscall32_restart_mode_s = {
#define __END_SYSCALLS(min,max,cnt)               };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt)    PUBLIC_CONST struct extended_syscalls32_restart_info const x86_exsyscall32_restart_mode_s = {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)      };
#define __SYSCALL(name)                                              /* .rm_##name  = */__NR32RM_##name,
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        /* .rm_unused_##sysno = */SYSCALL_RESTART_MODE_AUTO,
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          /* .rm_unused_##sysno = */SYSCALL_RESTART_MODE_AUTO,
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) /* .rm_unused_##sysno = */SYSCALL_RESTART_MODE_AUTO,
#include <asm/ls_syscalls32.inl>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS


#define __BEGIN_SYSCALLS(min,max,cnt)          struct syscalls32_is_cancellation_point_info {
#define __END_SYSCALLS(min,max,cnt)            };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt) struct extended_syscalls32_is_cancellation_point_info {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)   };
#define __SYSCALL(name)                                              unsigned int icp_##name : 1;
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        unsigned int icp_unused_##sysno : 1;
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          unsigned int icp_unused_##sysno : 1;
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) unsigned int icp_unused_##sysno : 1;
#include <asm/ls_syscalls32.inl>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS

DATDEF struct syscalls32_is_cancellation_point_info const x86_syscall32_is_cancellation_point_s ASMNAME("x86_syscall32_is_cancellation_point");
DATDEF struct extended_syscalls32_is_cancellation_point_info const x86_exsyscall32_is_cancellation_point_s ASMNAME("x86_exsyscall32_is_cancellation_point");
#define __BEGIN_SYSCALLS(min,max,cnt)             PUBLIC_CONST struct syscalls32_is_cancellation_point_info const x86_syscall32_is_cancellation_point_s = {
#define __END_SYSCALLS(min,max,cnt)               };
#define __BEGIN_SYSCALLS_EXTENDED(min,max,cnt)    PUBLIC_CONST struct extended_syscalls32_is_cancellation_point_info const x86_exsyscall32_is_cancellation_point_s = {
#define __END_SYSCALLS_EXTENDED(min,max,cnt)      };
#define __SYSCALL(name)                                              /* .icp_##name  = */__NR32CP_##name,
#define __SYSCALL_UNUSED_LEADING(sysno,index)                        /* .icp_unused_##sysno = */1,
#define __SYSCALL_UNUSED(sysno,index,index_without_leading)          /* .icp_unused_##sysno = */1,
#define __SYSCALL_EXTENDED_UNUSED_LEADING(sysno,index)               /* nothing */
#define __SYSCALL_EXTENDED_UNUSED(sysno,index,index_without_leading) /* .icp_unused_##sysno = */1,
#include <asm/ls_syscalls32.inl>
#undef __SYSCALL_EXTENDED_UNUSED
#undef __SYSCALL_EXTENDED_UNUSED_LEADING
#undef __SYSCALL_UNUSED
#undef __SYSCALL_UNUSED_LEADING
#undef __SYSCALL
#undef __END_SYSCALLS_EXTENDED
#undef __BEGIN_SYSCALLS_EXTENDED
#undef __END_SYSCALLS
#undef __BEGIN_SYSCALLS


#endif /* __x86_64__ */



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_C */
