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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EXCEPT_HANDLER_C
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EXCEPT_HANDLER_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/coredump.h>
#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/syscall-properties.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/except-handler.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/host.h>

#include <kos/bits/except-handler.h>
#include <kos/bits/except-handler32.h>
#include <kos/bits/exception_data.h>
#include <kos/bits/exception_data32.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state-helpers32.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/cpu-state32.h>
#include <sys/wait.h>

#include <assert.h>
#include <inttypes.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#include <libcpustate/apply.h>
#include <librpc/rpc.h>

DECL_BEGIN

LOCAL NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL log_userexcept_errno_propagate)(struct icpustate const *__restrict state,
                                              struct rpc_syscall_info const *__restrict sc_info,
                                              struct exception_data const *__restrict except_data,
                                              errno_t negative_errno_value) {
	unsigned int pointer_count = EXCEPTION_DATA_POINTERS;
	char const *name;
	(void)state;
	(void)sc_info;
	while (pointer_count != 0 &&
	       except_data->e_args.e_pointers[pointer_count - 1] == 0)
		--pointer_count;
	printk(KERN_TRACE "[except] Translate exception "
	                  "%#" PRIxN(__SIZEOF_ERROR_CLASS_T__) ":"
	                  "%#" PRIxN(__SIZEOF_ERROR_SUBCLASS_T__),
	       except_data->e_class, except_data->e_subclass);
	if ((name = error_name(except_data->e_code)) != NULL)
		printk(KERN_TRACE ",%s", name);
	if (pointer_count != 0) {
		unsigned int i;
		for (i = 0; i < pointer_count; ++i) {
			printk(KERN_TRACE "%c%#" PRIxPTR,
			       i == 0 ? '[' : ',',
			       except_data->e_args.e_pointers[i]);
		}
		printk(KERN_TRACE "]");
	}
	printk(KERN_TRACE " into errno=%d\n",
	       negative_errno_value);
}

LOCAL NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL log_userexcept_error_propagate)(struct icpustate const *__restrict state,
                                              struct rpc_syscall_info const *__restrict sc_info,
                                              struct exception_data const *__restrict except_data,
                                              uintptr_t mode,
                                              USER void *handler,
                                              USER void *stack) {
	unsigned int pointer_count = EXCEPTION_DATA_POINTERS;
	char const *name;
	(void)state;
	(void)sc_info;
	while (pointer_count != 0 &&
	       except_data->e_args.e_pointers[pointer_count - 1] == 0)
		--pointer_count;
	printk(KERN_TRACE "[except] Propagate exception "
	                  "%#" PRIxN(__SIZEOF_ERROR_CLASS_T__) ":"
	                  "%#" PRIxN(__SIZEOF_ERROR_SUBCLASS_T__),
	       except_data->e_class, except_data->e_subclass);
	if ((name = error_name(except_data->e_code)) != NULL)
		printk(KERN_TRACE ",%s", name);
	if (pointer_count != 0) {
		unsigned int i;
		for (i = 0; i < pointer_count; ++i) {
			printk(KERN_TRACE "%c%#" PRIxPTR "",
			       i == 0 ? '[' : ',',
			       except_data->e_args.e_pointers[i]);
		}
		printk(KERN_TRACE "]");
	}
	printk(KERN_TRACE " hand:[pc=%" PRIXPTR ",sp=%" PRIXPTR "]"
	                  " orig:[pc=%" PRIXPTR ",sp=%" PRIXPTR "]"
	                  " fault:[pc=%" PRIXPTR "]"
	                  " [mode=%#" PRIxPTR "]\n",
	       handler, stack,
	       icpustate_getpc(state),
	       icpustate_getusersp(state),
	       except_data->e_faultaddr, mode);
}



/* Try to invoke the user-space exception handler for  the
 * currently set exception, as described by `error_info()'
 * @param: state:   The user-space CPU state (note that `icpustate_isuser(state)' is assumed!)
 * @param: sc_info: When  non-NULL, information about  the system call  that caused the exception.
 *                  Otherwise, if this argument is `NULL', the exception was caused by user-space,
 *                  such as a user-space program causing an `E_SEGFAULT', as opposed to the kernel
 *                  throwing an `E_FSERROR_FILE_NOT_FOUND'
 *            HINT: Additional information about how the system call was invoked can be extracted
 *                  from      `sc_info->rsi_flags'!      (s.a.      `<librpc/bits/rpc-common.h>')
 * @return: NULL:   User-space does not define an exception handler.
 * @return: * :     The updated interrupt CPU state, modified to invoke the
 *                  user-space exception handler once user-space  execution
 *                  resumes. */
#ifdef __x86_64__
PUBLIC WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
x86_userexcept_callhandler(struct icpustate *__restrict state,
                           struct rpc_syscall_info const *sc_info,
                           struct exception_data const *__restrict except_data)
		THROWS(E_SEGFAULT) {
	struct icpustate *result;
	if (icpustate_is64bit(state)) {
		result = x86_userexcept_callhandler64(state, sc_info, except_data);
	} else {
		result = x86_userexcept_callhandler32(state, sc_info, except_data);
	}
	return result;
}

PUBLIC WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
x86_userexcept_callhandler64(struct icpustate *__restrict state,
                             struct rpc_syscall_info const *sc_info,
                             struct exception_data const *__restrict except_data)
		THROWS(E_SEGFAULT) {
	/* Call a 64-bit exception handler. */
	uintptr_t mode;
	USER CHECKED void *stack;
	USER CHECKED __except_handler64_t handler;
	USER CHECKED struct kcpustate64 *user_state;
	USER CHECKED struct __exception_data64 *user_error;
	unsigned int i;
	/* Call the user-space exception handler */
	mode    = PERTASK_GET(this_user_except_handler.ueh_mode);
	handler = (__except_handler64_t)(uintptr_t)(void *)PERTASK_GET(this_user_except_handler.ueh_handler);
	stack   = PERTASK_GET(this_user_except_handler.ueh_stack);
	if unlikely(!(mode & EXCEPT_HANDLER_FLAG_SETHANDLER))
		return NULL; /* No handler defined */
	if (stack == EXCEPT_HANDLER_SP_CURRENT) {
		stack = icpustate_getusersp(state);
		stack = (byte_t *)stack - 128; /* Red zone (TODO: Make this configurable!) */
	}
	/* Align the stack. */
	stack = (void *)((uintptr_t)stack & ~7);
	/* Allocate structures */
	user_state = (struct kcpustate64 *)((byte_t *)stack - sizeof(struct kcpustate64));
	user_error = (struct __exception_data64 *)((byte_t *)user_state - sizeof(struct __exception_data64));
	/* Ensure that we can write to the given stack. */
	validate_writable(user_error, sizeof(struct __exception_data64) + sizeof(struct kcpustate64));
	COMPILER_WRITE_BARRIER();
	/* Fill in user-space context information */
	icpustate_user_to_kcpustate64(state, user_state);
	/* Copy exception data onto the user-space stack. */
	user_error->e_code = (__error_code64_t)except_data->e_code;
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
		user_error->e_args.e_pointers[i] = (u64)except_data->e_args.e_pointers[i];
	/* In case of  a system call,  set the  fault
	 * address as the system call return address. */
	user_error->e_faultaddr = sc_info != NULL
	                          ? (__HYBRID_PTR64(void))(u64)(uintptr_t)icpustate_getusersp(state)
	                          : (__HYBRID_PTR64(void))(u64)(uintptr_t)except_data->e_faultaddr;
	log_userexcept_error_propagate(state, sc_info, except_data, mode, (void *)handler, user_error);
	/* Redirect the given CPU state to return to the user-space handler. */
	gpregs_setpdi(&state->ics_gpregs, (uintptr_t)user_state); /* struct kcpustate64 *__restrict state */
	gpregs_setpsi(&state->ics_gpregs, (uintptr_t)user_error); /* struct __exception_data64 *__restrict error */
	icpustate_setusersp(state, user_error);
	icpustate_setpc(state, (void *)handler);
	{
		union x86_user_eflags_mask word;
		word.uem_word = atomic64_read(&x86_user_eflags_mask);
		/* Mask %eflags, as specified by `x86_user_eflags_mask' */
		icpustate_mskpflags(state, word.uem_mask, word.uem_flag);
	}
	COMPILER_WRITE_BARRIER();
	/* Disable exception handling in one-shot mode. */
	if (mode & EXCEPT_HANDLER_FLAG_ONESHOT) {
		PERTASK_SET(this_user_except_handler.ueh_mode,
		            (mode & ~EXCEPT_HANDLER_MODE_MASK) |
		            EXCEPT_HANDLER_MODE_DISABLED);
	}
	return state;
}

PUBLIC WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
x86_userexcept_callhandler32(struct icpustate *__restrict state,
                             struct rpc_syscall_info const *sc_info,
                             struct exception_data const *__restrict except_data)
		THROWS(E_SEGFAULT)
#else /* __x86_64__ */
PUBLIC WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
x86_userexcept_callhandler(struct icpustate *__restrict state,
                           struct rpc_syscall_info const *sc_info,
                           struct exception_data const *__restrict except_data)
		THROWS(E_SEGFAULT)
#endif /* !__x86_64__ */
{
	/* Call a 32-bit exception handler. */
	uintptr_t mode;
	USER CHECKED byte_t *stack;
	USER CHECKED __except_handler32_t handler;
	USER CHECKED struct kcpustate32 *user_state;
	USER CHECKED struct __exception_data32 *user_error;
	unsigned int i;
	/* Call the user-space exception handler */
	mode    = PERTASK_GET(this_user_except_handler.ueh_mode);
	handler = (__except_handler32_t)(uintptr_t)(void *)PERTASK_GET(this_user_except_handler.ueh_handler);
	stack   = (byte_t *)PERTASK_GET(this_user_except_handler.ueh_stack);
	if unlikely(!(mode & EXCEPT_HANDLER_FLAG_SETHANDLER))
		return NULL; /* No handler defined */
	if (stack == EXCEPT_HANDLER_SP_CURRENT)
		stack = icpustate_getusersp(state);
	/* Align the stack. */
	stack = (byte_t *)((uintptr_t)stack & ~3);
	/* Allocate structures */
	user_state = (struct kcpustate32 *)(stack - sizeof(struct kcpustate32));
	user_error = (struct __exception_data32 *)((byte_t *)user_state - sizeof(struct __exception_data32));
	/* Ensure that we can write to the given stack. */
	validate_writable(user_error, sizeof(struct __exception_data32) + sizeof(struct kcpustate32));
	COMPILER_WRITE_BARRIER();
	/* Fill in user-space context information */
	icpustate_user_to_kcpustate32(state, user_state);
	/* Copy exception data onto the user-space stack. */
#ifdef __x86_64__
	/* Propagate class & sub-class individually, since the way in
	 * which they form e_code is  different in x32 and x64  mode. */
	user_error->e_class    = (__error_class32_t)except_data->e_class;
	user_error->e_subclass = (__error_subclass32_t)except_data->e_subclass;
#else /* __x86_64__ */
	user_error->e_code = (__error_code32_t)except_data->e_code;
#endif /* !__x86_64__ */
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
		user_error->e_args.e_pointers[i] = (u32)except_data->e_args.e_pointers[i];
	/* In case of  a system call,  set the  fault
	 * address as the system call return address. */
	user_error->e_faultaddr = sc_info != NULL
	                          ? (__HYBRID_PTR32(void))(u32)(uintptr_t)icpustate_getusersp(state)
	                          : (__HYBRID_PTR32(void))(u32)(uintptr_t)except_data->e_faultaddr;
	log_userexcept_error_propagate(state, sc_info, except_data, mode, (void *)handler, user_error);
	/* Redirect the given CPU state to return to the user-space handler. */
	gpregs_setpcx(&state->ics_gpregs, (uintptr_t)user_state); /* struct kcpustate32 *__restrict state */
	gpregs_setpdx(&state->ics_gpregs, (uintptr_t)user_error); /* struct __exception_data32 *__restrict error */
	icpustate_setusersp(state, user_error);
	icpustate_setpc(state, (void *)handler);
	{
		union x86_user_eflags_mask word;
		word.uem_word = atomic64_read(&x86_user_eflags_mask);
		/* Mask %eflags, as specified by `x86_user_eflags_mask' */
		icpustate_mskpflags(state, word.uem_mask, word.uem_flag);
	}
	COMPILER_WRITE_BARRIER();
	/* Disable exception handling in one-shot mode. */
	if (mode & EXCEPT_HANDLER_FLAG_ONESHOT) {
		PERTASK_SET(this_user_except_handler.ueh_mode,
		            (mode & ~EXCEPT_HANDLER_MODE_MASK) |
		            EXCEPT_HANDLER_MODE_DISABLED);
	}
	return state;
}


LOCAL ATTR_NORETURN void
NOTHROW(FCALL process_exit)(int reason) {
	if (!task_isprocessleader()) {
		/* We need to terminate the _process_; not just this thread!
		 * This can be done by re-using our exit RPC, and sending it
		 * to the process leader. */
		struct rpc_entry *rpc;
		rpc = ATOMIC_XCH(PERTASK(this_taskgroup.tg_thread_exit), NULL);
		/* When `rpc' was already `NULL', then our leader must already be
		 * in the process of exiting, and already took our exit RPC away,
		 * trying to terminate us.
		 * Handle this case by letting it do its thing, even though this
		 * will cause us to use a different exit reason than the leader. */
		if likely(rpc) {
			int rpc_status;
			rpc->re_arg = (void *)(uintptr_t)(unsigned int)reason;
			rpc_status = task_deliver_rpc(task_getprocess(), rpc, TASK_RPC_FNORMAL);
			if (TASK_DELIVER_RPC_WASOK(rpc_status))
				goto done;
			/* Failed to deliver the RPC. The only reason this should be able to happen
			 * is when the process leader has/is already terminated/terminating, and is
			 * no longer able to service any RPCs. */
			assertf(rpc_status == TASK_DELIVER_RPC_TERMINATED,
			        "Unexpected failure reason for terminating process leader\n"
			        "rpc_status = %d", rpc_status);
			/* Cleanup the RPC, since it isn't inherited by `task_deliver_rpc()' upon failure. */
			task_free_rpc(rpc);
		}
	}
done:
	task_exit(reason);
}

LOCAL ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL process_exit_for_exception_after_coredump)(struct exception_data const *__restrict except_data) {
	siginfo_t si;
	/* Try to translate the current exception  into a signal, so that  we
	 * can use that signal code as reason for why the process has exited. */
	if (!error_as_signal(except_data, &si))
		si.si_signo = SIGILL;
	process_exit(W_EXITCODE(1, si.si_signo) | WCOREFLAG);
}



/* Raise a posix signal in user-space for `siginfo'
 * @param: state:   The user-space CPU state (note that `icpustate_isuser(state)' is assumed!)
 * @param: sc_info: When  non-NULL,  information about  the system  call  that caused  the signal.
 *                  Otherwise,  if this argument  is `NULL', the signal  was caused by user-space,
 *                  such as a user-space program causing an `E_SEGFAULT', as opposed to the kernel
 *                  throwing an `E_FSERROR_FILE_NOT_FOUND'
 *            HINT: Additional information about how the system call was invoked can be extracted
 *                  from      `sc_info->rsi_flags'!      (s.a.      `<librpc/bits/rpc-common.h>')
 * @param: siginfo: The signal that is being raised
 * @param: except_info: When non-NULL, `siginfo' was generated through `error_as_signal(&except_info->ei_data)',
 *                  and  if a coredump ends up being generated  as a result of the signal being
 *                  raised, that coredump will include information about `error_info()', rather
 *                  than the given `siginfo'
 * @return: NULL:   User-space does not define an signal handler.
 * @return: * :     The updated interrupt CPU state, modified to invoke the
 *                  user-space signal  handler  once  user-space  execution
 *                  resumes. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
x86_userexcept_raisesignal(struct icpustate *__restrict state,
                           struct rpc_syscall_info const *sc_info,
                           siginfo_t const *__restrict siginfo,
                           struct exception_info const *except_info) {
	struct icpustate *result;
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
#if 0 /* `SA_RESETHAND' only affects user-space signal handler functions */
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
		    unlikely(!sighand_reset_handler(siginfo->si_signo, &action)))
			goto again_gethand;
#endif
		if (sc_info && except_info)
			state = x86_userexcept_seterrno(state, sc_info, &except_info->ei_data);
		return state;

	case KERNEL_SIG_CORE:
		xdecref_unlikely(action.sa_mask);
		if (except_info) {
			/* If we've gotten here because of a system call, then we can assume that
			 * the exception does have a kernel-space side, and thus we must  include
			 * information about that exception's origin. */
			coredump_create_for_exception(state, except_info, sc_info != NULL);
		} else {
			coredump_create_for_signal(state, siginfo);
		}
		process_exit(W_EXITCODE(1, siginfo->si_signo) | WCOREFLAG);

	case KERNEL_SIG_TERM:
		xdecref_unlikely(action.sa_mask);
		process_exit(W_EXITCODE(1, siginfo->si_signo));

	case KERNEL_SIG_EXIT:
		xdecref_unlikely(action.sa_mask);
		task_exit(W_EXITCODE(1, siginfo->si_signo));

	case KERNEL_SIG_CONT:
		xdecref_unlikely(action.sa_mask);
#if 0 /* `SA_RESETHAND' only affects user-space signal handler functions */
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
		    unlikely(!sighand_reset_handler(siginfo->si_signo, &action)))
			goto again_gethand;
#endif
		/* Continue execution. */
		task_sigcont(THIS_TASK);
		return state;

	case KERNEL_SIG_STOP:
		/* TODO: Mask additional signals by looking at `SIGACTION_SA_NODEFER' and `action.sa_mask' */
		xdecref_unlikely(action.sa_mask);
#if 0 /* `SA_RESETHAND' only affects user-space signal handler functions */
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
			unlikely(!sighand_reset_handler(siginfo->si_signo, &action)))
			goto again_gethand;
#endif
		/* Suspend execution. */
		task_sigstop(W_STOPCODE(siginfo->si_signo));
		return state;

#undef __CCAST
#define __CCAST(T) (T)
	default: break;
	}

	/* Invoke a regular, old signal handler. */
	{
		FINALLY_XDECREF_UNLIKELY(action.sa_mask);
		result = sighand_raise_signal(state,
		                              &action,
		                              siginfo,
		                              sc_info);
	}
	if unlikely(!result)
		goto again_gethand;
	return result;
}


/* Helper function for  `x86_userexcept_raisesignal()' that  may be  used
 * to raise the appropriate POSIX signal for the currently set exception.
 * @return: NULL: The current exception cannot be translated into a posix signal.
 * @return: * :     The updated interrupt CPU state, modified to invoke the
 *                  user-space signal  handler  once  user-space  execution
 *                  resumes. */
PUBLIC WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
x86_userexcept_raisesignal_from_exception(struct icpustate *__restrict state,
                                          struct rpc_syscall_info const *sc_info,
                                          struct exception_info const *__restrict except_info) {
	siginfo_t siginfo;
	/* Try to translate the current exception into a signal. */
	if (!error_as_signal(&except_info->ei_data, &siginfo))
		return NULL;
	/* Include missing information within the signal info. */
	switch (siginfo.si_signo) {

	case SIGSYS:
		siginfo.si_call_addr = (void *)icpustate_getpc(state);
		break;

	default: break;
	}
	return x86_userexcept_raisesignal(state,
	                                  sc_info,
	                                  &siginfo,
	                                  except_info);
}


/* Set the appropriate error flag for the system call method described by `sc_info' (if any)
 * We (no longer) have a dedicated system error-flag. */
LOCAL NOBLOCK NONNULL((1, 2, 3)) struct icpustate *
NOTHROW(FCALL x86_userexcept_set_error_flag)(struct icpustate *__restrict state,
                                             struct rpc_syscall_info const *__restrict sc_info,
                                             struct exception_data const *__restrict data) {
	(void)sc_info;
	(void)data;
	/* We (no longer) have a dedicated system error-flag. */
	return state;
}


/* Translate the current exception into an errno and set that errno
 * as the return value of  the system call described by  `sc_info'. */
#ifdef __x86_64__
PUBLIC WUNUSED NONNULL((1, 2, 3)) struct icpustate *
NOTHROW(FCALL x86_userexcept_seterrno)(struct icpustate *__restrict state,
                                       struct rpc_syscall_info const *__restrict sc_info,
                                       struct exception_data const *__restrict data) {
	struct icpustate *result;
	if (icpustate_is64bit(state)) {
		result = x86_userexcept_seterrno64(state, sc_info, data);
	} else {
		result = x86_userexcept_seterrno32(state, sc_info, data);
	}
	return result;
}

PUBLIC WUNUSED NONNULL((1, 2, 3)) struct icpustate *
NOTHROW(FCALL x86_userexcept_seterrno64)(struct icpustate *__restrict state,
                                         struct rpc_syscall_info const *__restrict sc_info,
                                         struct exception_data const *__restrict data) {
	errno_t errval;
	(void)sc_info;
	errval = -error_as_errno(data);
	log_userexcept_errno_propagate(state, sc_info, data, errval);
	gpregs_setpax(&state->ics_gpregs, (uintptr_t)(intptr_t)errval);
	/* Check if the system call is double-wide so we
	 * can  sign-extend the error code if necessary. */
	if (kernel_syscall64_doublewide(sc_info->rsi_sysno))
		gpregs_setpdx(&state->ics_gpregs, (uintptr_t)-1); /* sign-extend */
	/* Set an error flag (if any) */
	state = x86_userexcept_set_error_flag(state, sc_info, data);
	return state;
}

PUBLIC WUNUSED NONNULL((1, 2, 3)) struct icpustate *
NOTHROW(FCALL x86_userexcept_seterrno32)(struct icpustate *__restrict state,
                                         struct rpc_syscall_info const *__restrict sc_info,
                                         struct exception_data const *__restrict data)
#else /* __x86_64__ */
PUBLIC WUNUSED NONNULL((1, 2, 3)) struct icpustate *
NOTHROW(FCALL x86_userexcept_seterrno)(struct icpustate *__restrict state,
                                       struct rpc_syscall_info const *__restrict sc_info,
                                       struct exception_data const *__restrict data)
#endif /* !__x86_64__ */
{
	errno_t errval;
	errval = -error_as_errno(data);
	log_userexcept_errno_propagate(state, sc_info, data, errval);

	/* All system call  methods return error  values through  EAX.
	 * If  this were ever to change (such that certain methods use
	 * different registers/locations), that special behavior would
	 * have to be implemented right here. */
	gpregs_setpax(&state->ics_gpregs, errval);

	/* Check if the system call is double-wide so we
	 * can  sign-extend the error code if necessary. */
	if (kernel_syscall32_doublewide(sc_info->rsi_sysno))
		gpregs_setpdx(&state->ics_gpregs, (uintptr_t)-1); /* sign-extend */

	/* Set an error flag (if any) */
	state = x86_userexcept_set_error_flag(state, sc_info, data);
	return state;
}


/* Propagate the currently  thrown exception  into user-space, using  either the  user-space
 * exception handler, by raising  a POSIX signal,  or by translating  the exception into  an
 * E* error code in  the event of a  system call with exceptions  disabled (on x86,  except-
 * enabled is usually controlled by the DF bit, however this function takes that information
 * from the `RPC_SYSCALL_INFO_FEXCEPT' bit in `sc_info->rsi_flags'). */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL x86_userexcept_propagate)(struct icpustate *__restrict state,
                                        struct rpc_syscall_info const *sc_info) {
	struct icpustate *result;
	struct exception_info info;
	struct exception_info *tls_info;

	/* Assert that there are no active connections. */
#ifndef NDEBUG
	{
		struct task_connections *self;
		struct task_connection *con;
		self = THIS_CONNECTIONS;
		con  = self->tcs_con;
		assertf(con == NULL, "con = %p", con);
	}
#endif /* !NDEBUG */
	tls_info = error_info();
	memcpy(&info, tls_info, sizeof(info));
	tls_info->ei_code  = ERROR_CODEOF(E_OK);
	tls_info->ei_flags = EXCEPT_FNORMAL;
again:
	assertf(tls_info->ei_code == ERROR_CODEOF(E_OK),
	        "Exception wasn't properly deleted");
	assertf(tls_info->ei_flags == EXCEPT_FNORMAL,
	        "Unexpected exception flags");
	assertf(tls_info->ei_nesting == 0,
	        "There are still saved, nested exception somewhere on our stack");
	assertf(PREEMPTION_ENABLED(),
	        "Preemption must be enabled to propagate exceptions to user-space.");

	/* Handle special exception codes */
	switch (info.ei_code) {

	case ERROR_CODEOF(E_EXIT_PROCESS):
		process_exit((int)info.ei_data.e_args.e_exit_process.ep_exit_code);

	case ERROR_CODEOF(E_EXIT_THREAD):
		task_exit((int)info.ei_data.e_args.e_exit_thread.et_exit_code);

	case ERROR_CODEOF(E_UNKNOWN_SYSTEMCALL): {
		enum { MMASK = RPC_SYSCALL_INFO_FMETHOD & ~RPC_SYSCALL_INFO_METHOD_F3264 };
		uintptr_t flags;
		if (!sc_info)
			break;
		/* Amend missing information about how a system call was invoked. */
		flags = info.ei_data.e_args.e_unknown_systemcall.us_flags;
		if ((flags & MMASK) == (RPC_SYSCALL_INFO_METHOD_OTHER & ~RPC_SYSCALL_INFO_METHOD_F3264)) {
			flags = (flags & ~MMASK) | (sc_info->rsi_flags & MMASK);
			info.ei_data.e_args.e_unknown_systemcall.us_flags = flags;
		}
	}	break;

	default: break;
	}

	/* Handle exception unwinding into user-space. */
	TRY {
		if (sc_info != NULL) {
			if (sc_info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) {
				/* System call exceptions are enabled. */
				/* Propagate the exception to user-space if handlers are enabled. */
				if ((PERTASK_GET(this_user_except_handler.ueh_mode) &
				     EXCEPT_HANDLER_MODE_MASK) != EXCEPT_HANDLER_MODE_DISABLED) {
					result = x86_userexcept_callhandler(state, sc_info, &info.ei_data);
					if likely(result)
						goto done;
				}
				/* If exceptions don't work, try to propagate a POSIX signal */
				result = x86_userexcept_raisesignal_from_exception(state, sc_info, &info);
				if likely(result)
					goto done;
				/* If the exception still cannot be handled, terminate the program. */
				goto terminate_app;
			}
			/* Translate the current exception into an errno. */
			result = x86_userexcept_seterrno(state, sc_info, &info.ei_data);
			goto done;
		}

		/* Check if signal exceptions should be propagated in non-syscall scenarios. */
		if ((PERTASK_GET(this_user_except_handler.ueh_mode) &
		     EXCEPT_HANDLER_MODE_MASK) == EXCEPT_HANDLER_MODE_SIGHAND) {
			result = x86_userexcept_callhandler(state, sc_info, &info.ei_data);
			if likely(result)
				goto done;
		}
		/* Deliver a signal to the calling user-space thread. */
		result = x86_userexcept_raisesignal_from_exception(state, sc_info, &info);
		if likely(result)
			goto done;
	} EXCEPT {
		error_printf("raising exception/signal");
		if (error_priority(tls_info->ei_code) > error_priority(info.ei_code)) {
			memcpy(&info, tls_info, sizeof(info));
			assert(PREEMPTION_ENABLED());
			goto again;
		}
	}

terminate_app:
	/* If we've gotten here because of a system call, then we can assume that
	 * the exception does have a kernel-space side, and thus we must  include
	 * information about that exception's origin. */
	coredump_create_for_exception(state, &info, sc_info != NULL);
	process_exit_for_exception_after_coredump(&info.ei_data);
	__builtin_unreachable();
done:
	assert(tls_info->ei_code == ERROR_CODEOF(E_OK));
	assert(tls_info->ei_flags == EXCEPT_FNORMAL);
	assert(tls_info->ei_nesting == 0);
	assert(PREEMPTION_ENABLED());
	return result;
}




/* Serve all user-space redirection RPCs
 * @return: * : The new CPU state to restore
 * @param: prestart_system_call: If `reason == TASK_RPC_REASON_SYSCALL', whilst an `E_INTERRUPT_USER_RPC'
 *                               exception was handled, when `RPC_KIND_USER_SYNC' RPCs exist that  cannot
 *                               be handled in the current context, then set to true. */
INTDEF WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL rpc_serve_user_redirection_all)(struct icpustate *__restrict state,
                                              unsigned int reason,
                                              struct rpc_syscall_info const *sc_info,
                                              bool *prestart_system_call);


/* Given a user-space UCPUSTATE, load that state into the active IRET tail, whilst
 * accounting for additional user-space RPC redirection, before serving user-level
 * RPC functions, and finally propagating the then set exception (if one still is)
 * into user-space with the help of `x86_userexcept_propagate()'.
 * Afterwards, load the updated icpustate at the base of the calling thread's stack,
 * and  finally  fully unwind  into  user-space by  use  of `cpu_apply_icpustate()'. */
PUBLIC ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL x86_userexcept_unwind)(struct ucpustate *__restrict ustate,
                                     struct rpc_syscall_info const *sc_info) {
	struct icpustate *return_state;
	assert(!(PERTASK_GET(this_task.t_flags) & TASK_FKERNTHREAD));
	/* Disable interrupts to prevent Async-RPCs from doing even more re-directions! */
	__cli();
#define kernel_stack_top() ((byte_t *)PERTASK_GET(this_x86_kernel_psp0))
	/* Figure out where the return icpustate needs to go. */
	return_state = (struct icpustate *)(kernel_stack_top() -
	                                    (
#ifdef __x86_64__
	                                    SIZEOF_ICPUSTATE64
#else /* __x86_64__ */
	                                    ucpustate_isvm86(ustate)
	                                    ? OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_VM86
	                                    : OFFSET_ICPUSTATE32_IRREGS + SIZEOF_IRREGS32_USER
#endif /* !__x86_64__ */
	                                    ));
	/* Check if user-space got redirected (if so, we need to follow some custom unwinding rules). */
	if (return_state->ics_irregs.ir_pip == (uintptr_t)&x86_rpc_user_redirection) {
		/* A re-direction may have happened whilst we were unwinding. - Adjust for that now!
		 * HINT: The actual user-space return location is stored in `this_x86_rpc_redirection_iret' */
		assert(PERTASK_GET(this_x86_rpc_redirection_iret.ir_pip) != (uintptr_t)&x86_rpc_user_redirection);
		assert(return_state->ics_irregs.ir_pflags == 0);
		assert(SEGMENT_IS_VALID_KERNCODE(return_state->ics_irregs.ir_cs));
		/* Manually unwind additional FLAGS registers.
		 * Because .cfi_iret_signal_frame perform a kernel-space unwind
		 * due to  the  redirection,  we  must  manually  complete  the
		 * unwind to also include ESP and SS
		 *  - Right now, ESP points at &irregs_user::ir_esp / &irregs_vm86::ir_esp */
#ifdef __x86_64__
		assertf(ustate->ucs_gpregs.gp_rsp == return_state->ics_irregs.ir_rsp,
		        "ustate->ucs_gpregs.gp_rsp       = %p\n"
		        "return_state->ics_irregs.ir_rsp = %p\n",
		        ustate->ucs_gpregs.gp_rsp,
		        return_state->ics_irregs.ir_rsp);
#else /* __x86_64__ */
		assertf(ustate->ucs_gpregs.gp_esp == (u32)&return_state->ics_irregs_u.ir_esp,
		        "ustate->ucs_gpregs.gp_esp          = %p\n"
		        "&return_state->ics_irregs_u.ir_esp = %p\n",
		        ustate->ucs_gpregs.gp_esp,
		        &return_state->ics_irregs_u.ir_esp);
#endif /* !__x86_64__ */

#ifdef __x86_64__
		return_state->ics_irregs.ir_rip    = PERTASK_GET(this_x86_rpc_redirection_iret.ir_rip);
		return_state->ics_irregs.ir_cs     = PERTASK_GET(this_x86_rpc_redirection_iret.ir_cs16);
		return_state->ics_irregs.ir_rflags = PERTASK_GET(this_x86_rpc_redirection_iret.ir_rflags);
		return_state->ics_irregs.ir_rsp    = PERTASK_GET(this_x86_rpc_redirection_iret.ir_rsp);
		return_state->ics_irregs.ir_ss     = PERTASK_GET(this_x86_rpc_redirection_iret.ir_ss16);
#else /* __x86_64__ */
		return_state->ics_irregs_u.ir_eip    = PERTASK_GET(this_x86_rpc_redirection_iret.ir_eip);
		return_state->ics_irregs_u.ir_cs     = PERTASK_GET(this_x86_rpc_redirection_iret.ir_cs16);
		return_state->ics_irregs_u.ir_eflags = PERTASK_GET(this_x86_rpc_redirection_iret.ir_eflags);
#if 0 /* Still initialized correctly... */
		return_state->ics_irregs_u.ir_ss     = return_state->ics_irregs_u.ir_ss16;
		return_state->ics_irregs_u.ir_esp    = return_state->ics_irregs_u.ir_esp;
#endif
#endif /* !__x86_64__ */
	} else {
		/* Fill in the user-space return location to match `ustate' */
#ifdef __x86_64__
		return_state->ics_irregs.ir_rip    = ustate->ucs_rip;
		return_state->ics_irregs.ir_cs     = ustate->ucs_cs16;
		return_state->ics_irregs.ir_rflags = ustate->ucs_rflags;
		return_state->ics_irregs.ir_rsp    = ustate->ucs_gpregs.gp_rsp;
		return_state->ics_irregs.ir_ss     = ustate->ucs_ss16;
#else /* __x86_64__ */
		return_state->ics_irregs_u.ir_eip    = ustate->ucs_eip;
		return_state->ics_irregs_u.ir_cs     = ustate->ucs_cs16;
		return_state->ics_irregs_u.ir_eflags = ustate->ucs_eflags;
		return_state->ics_irregs_u.ir_esp    = ustate->ucs_gpregs.gp_esp;
		return_state->ics_irregs_u.ir_ss     = ustate->ucs_ss16;
#endif /* !__x86_64__ */
	}
#ifdef __x86_64__
	gpregs_to_gpregsnsp(&ustate->ucs_gpregs, &return_state->ics_gpregs);
	__wrds(ustate->ucs_sgregs.sg_ds16);
	__wres(ustate->ucs_sgregs.sg_es16);
	__wrfs(ustate->ucs_sgregs.sg_fs16);
	{
		struct task *me = THIS_TASK;
		__wrgs(ustate->ucs_sgregs.sg_gs16);
		__wrgsbase(me);
	}
	/* FIXME: Restoring  segment  base  registers here  is  correct, however
	 *        unnecessary  in all  current use  cases. -  The solution would
	 *        be to have  another kind  of cpustate structure  that is  like
	 *        ucpustate, but don't contain segment base registers on x86_64! */
	x86_set_user_gsbase(ustate->ucs_sgbase.sg_gsbase);
	x86_set_user_fsbase(ustate->ucs_sgbase.sg_fsbase);
#else /* __x86_64__ */
	return_state->ics_gpregs = ustate->ucs_gpregs;
	if (ustate->ucs_eflags & EFLAGS_VM) {
		/* Special case: vm86 return state */
		return_state->ics_ds             = SEGMENT_USER_DATA_RPL;
		return_state->ics_es             = SEGMENT_USER_DATA_RPL;
		return_state->ics_fs             = SEGMENT_USER_FSBASE_RPL;
		return_state->ics_irregs_v.ir_es = ustate->ucs_sgregs.sg_es16;
		return_state->ics_irregs_v.ir_ds = ustate->ucs_sgregs.sg_ds16;
		return_state->ics_irregs_v.ir_fs = ustate->ucs_sgregs.sg_fs16;
		return_state->ics_irregs_v.ir_gs = ustate->ucs_sgregs.sg_gs16;
	} else {
		icpustate_setds_novm86(return_state, ustate->ucs_sgregs.sg_ds16);
		icpustate_setes_novm86(return_state, ustate->ucs_sgregs.sg_es16);
		icpustate_setfs_novm86(return_state, ustate->ucs_sgregs.sg_fs16);
		icpustate_setgs_novm86(return_state, ustate->ucs_sgregs.sg_gs16);
	}
#endif /* !__x86_64__ */

	/* Now that we've constructed an entirely valid ICPUSTATE at the base of our
	 * own stack, we can re-enable interrupts, as it will be this state which is
	 * (presumably) going to be restored when jumping back into user-space. */
	__sti();

	x86_userexcept_unwind_i(return_state, sc_info);
}

/* Same  as  `x86_userexcept_unwind()',  however  the  caller  has  already  done  the work
 * of constructing a `struct icpustate *' at the base of the current thread's kernel stack. */
PUBLIC ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL x86_userexcept_unwind_i)(struct icpustate *__restrict state,
                                       struct rpc_syscall_info const *sc_info) {
	/* Service RPCs before returning to user-space. */
	assert(!task_wasconnected());
	assertf(PREEMPTION_ENABLED(),
	        "Preemption must be enabled to propagate exceptions to user-space.");

	if (sc_info) {
		bool must_restart_syscall;
		must_restart_syscall = false;
		state = rpc_serve_user_redirection_all(state,
		                                       TASK_RPC_REASON_SYSCALL,
		                                       sc_info,
		                                       &must_restart_syscall);
		assert(PREEMPTION_ENABLED());
		/* If there is still an active exception (i.e. RPC handling didn't  resolve
		 * the exception, as would be the case for `E_INTERRUPT_USER_RPC'), then we
		 * must somehow propagate the exception into user-space. */
		if (error_code() != E_OK) {
			assert(!must_restart_syscall);
			state = x86_userexcept_propagate(state, sc_info);
		} else if unlikely(must_restart_syscall) {
			/* Reset the system call by resetting the kernel stack. */
			syscall_emulate_r(state, sc_info);
		}
	} else {
		state = rpc_serve_user_redirection_all(state,
		                                       TASK_RPC_REASON_ASYNCUSER,
		                                       NULL,
		                                       NULL);
		/* If there is still an active exception (i.e. RPC handling didn't  resolve
		 * the exception, as would be the case for `E_INTERRUPT_USER_RPC'), then we
		 * must somehow propagate the exception into user-space. */
		if (error_code() != E_OK)
			state = x86_userexcept_propagate(state, NULL);
	}

	/* Unwind into to the target state, thus returning back to userspace,
	 * though with the associated  target potentially changed. Note  that
	 * at this point no kernel exception remains set! */
	cpu_apply_icpustate(state);
}




DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EXCEPT_HANDLER_C */
