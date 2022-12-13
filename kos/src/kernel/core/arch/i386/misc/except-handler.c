/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_EXCEPT_HANDLER_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_EXCEPT_HANDLER_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/rt/except-syscall.h>
#include <kernel/syscall-properties.h>
#include <kernel/user.h>
#include <sched/atomic64.h>
#include <sched/x86/eflags-mask.h>

#include <hybrid/host.h>

#include <asm/cpu-flags.h>
#include <kos/bits/except-handler32.h>
#include <kos/bits/exception_data32.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/rpc.h>

#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#ifdef __x86_64__
#include <kos/bits/except-handler64.h>
#include <kos/bits/exception_data64.h>
#endif /* __x86_64__ */

DECL_BEGIN

LOCAL NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL log_userexcept_errno_propagate)(struct icpustate const *__restrict state,
                                              struct rpc_syscall_info const *__restrict sc_info,
                                              struct exception_data const *__restrict error,
                                              errno_t negative_errno_value) {
	unsigned int pointer_count = EXCEPTION_DATA_POINTERS;
	char const *name;
	(void)state;
	(void)sc_info;
	while (pointer_count != 0 &&
	       error->e_args.e_pointers[pointer_count - 1] == 0)
		--pointer_count;
	printk(KERN_TRACE "[except] Translate exception "
	                  "%#" PRIxN(__SIZEOF_EXCEPT_CLASS_T__) ":"
	                  "%#" PRIxN(__SIZEOF_EXCEPT_SUBCLASS_T__),
	       error->e_class, error->e_subclass);
	if ((name = except_name(error->e_code)) != NULL)
		printk(KERN_TRACE ",%s", name);
	if (pointer_count != 0) {
		unsigned int i;
		for (i = 0; i < pointer_count; ++i) {
			printk(KERN_TRACE "%c%#" PRIxPTR,
			       i == 0 ? '[' : ',',
			       error->e_args.e_pointers[i]);
		}
		printk(KERN_TRACE "]");
	}
	name = strerrorname_np(-negative_errno_value);
	if (name) {
		printk(KERN_TRACE " into errno=-%s\n", name);
	} else {
		printk(KERN_TRACE " into errno=%d\n", negative_errno_value);
	}
}

LOCAL NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL log_userexcept_error_propagate)(struct icpustate const *__restrict state,
                                              struct rpc_syscall_info const *__restrict sc_info,
                                              struct exception_data const *__restrict error,
                                              uintptr_t mode, USER void *handler, USER void *stack) {
	unsigned int pointer_count = EXCEPTION_DATA_POINTERS;
	char const *name;
	(void)state;
	(void)sc_info;
	while (pointer_count != 0 &&
	       error->e_args.e_pointers[pointer_count - 1] == 0)
		--pointer_count;
	printk(KERN_TRACE "[except] Propagate exception "
	                  "%#" PRIxN(__SIZEOF_EXCEPT_CLASS_T__) ":"
	                  "%#" PRIxN(__SIZEOF_EXCEPT_SUBCLASS_T__),
	       error->e_class, error->e_subclass);
	if ((name = except_name(error->e_code)) != NULL)
		printk(KERN_TRACE ",%s", name);
	if (pointer_count != 0) {
		unsigned int i;
		for (i = 0; i < pointer_count; ++i) {
			printk(KERN_TRACE "%c%#" PRIxPTR "",
			       i == 0 ? '[' : ',',
			       error->e_args.e_pointers[i]);
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
	       error->e_faultaddr, mode);
}



/* Arch-specific function:
 * Try to invoke the user-space exception handler for `error'
 * WARNING: Because this function writes to the user-space stack,
 *          it  is  capable of  throwing an  `E_SEGFAULT' itself.
 * @param: state:   The user-space CPU state (note that `icpustate_isuser(state)' is assumed!)
 * @param: sc_info: When  non-NULL, information about  the system call  that caused the exception.
 *                  Otherwise, if this argument is `NULL', the exception was caused by user-space,
 *                  such as a user-space program causing an `E_SEGFAULT', as opposed to the kernel
 *                  throwing an `E_FSERROR_FILE_NOT_FOUND'
 *            HINT: Additional information about how the system call was invoked can be
 *                  extracted from `sc_info->rsi_flags' (s.a. `<kos/asm/rpc-method.h>')
 * @return: NULL:   User-space does not define an exception handler.
 * @return: * :     The updated interrupt CPU state, modified to invoke the
 *                  user-space exception handler once user-space  execution
 *                  resumes. */
#ifdef __x86_64__
PRIVATE WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
x86_userexcept_callhandler32(struct icpustate *__restrict state,
                             struct rpc_syscall_info const *sc_info,
                             struct exception_data const *__restrict error)
		THROWS(E_SEGFAULT)
#else /* __x86_64__ */
PUBLIC WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
userexcept_callhandler(struct icpustate *__restrict state,
                       struct rpc_syscall_info const *sc_info,
                       struct exception_data const *__restrict error)
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
	mode = PERTASK_GET(this_user_except_handler.ueh_mode);
	if unlikely(!(mode & EXCEPT_HANDLER_FLAG_SETHANDLER))
		return NULL; /* No handler defined */
	handler = (__except_handler32_t)(uintptr_t)(void *)PERTASK_GET(this_user_except_handler.ueh_handler);
	stack   = (byte_t *)PERTASK_GET(this_user_except_handler.ueh_stack);
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
	user_error->e_class    = (__except_class32_t)error->e_class;
	user_error->e_subclass = (__except_subclass32_t)error->e_subclass;
#else /* __x86_64__ */
	user_error->e_code = (__except_code32_t)error->e_code;
#endif /* !__x86_64__ */
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
		user_error->e_args.e_pointers[i] = (u32)error->e_args.e_pointers[i];

	/* In case of  a system call,  set the  fault
	 * address as the system call return address. */
	user_error->e_faultaddr = sc_info != NULL
	                          ? (__HYBRID_PTR32(void))(u32)(uintptr_t)icpustate_getusersp(state)
	                          : (__HYBRID_PTR32(void))(u32)(uintptr_t)error->e_faultaddr;
	log_userexcept_error_propagate(state, sc_info, error, mode, (void *)handler, user_error);

	/* Redirect the given CPU state to return to the user-space handler. */
	gpregs_setpcx(&state->ics_gpregs, (uintptr_t)user_state); /* struct kcpustate32 *__restrict state */
	gpregs_setpdx(&state->ics_gpregs, (uintptr_t)user_error); /* struct __exception_data32 *__restrict error */
	icpustate_setusersp(state, user_error);
	icpustate_setpc(state, (void *)handler);
	{
		/* Mask `%Pflags', as specified by `x86_user_eflags_mask' */
		union x86_user_eflags_mask_union word;
		word.uem_word = atomic64_read(&x86_user_eflags_mask);
		word.uem_mask &= ~EFLAGS_RF; /* Always clear `EFLAGS_RF' so hw-breakpoints work on exception handler entry */
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

#ifdef __x86_64__
PRIVATE WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
x86_userexcept_callhandler64(struct icpustate *__restrict state,
                             struct rpc_syscall_info const *sc_info,
                             struct exception_data const *__restrict error)
		THROWS(E_SEGFAULT) {
	/* Call a 64-bit exception handler. */
	uintptr_t mode;
	USER CHECKED void *stack;
	USER CHECKED __except_handler64_t handler;
	USER CHECKED struct kcpustate64 *user_state;
	USER CHECKED struct __exception_data64 *user_error;
	unsigned int i;
	/* Call the user-space exception handler */
	mode = PERTASK_GET(this_user_except_handler.ueh_mode);
	if unlikely(!(mode & EXCEPT_HANDLER_FLAG_SETHANDLER))
		return NULL; /* No handler defined */
	handler = (__except_handler64_t)(uintptr_t)(void *)PERTASK_GET(this_user_except_handler.ueh_handler);
	stack   = PERTASK_GET(this_user_except_handler.ueh_stack);
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
	user_error->e_code = (__except_code64_t)error->e_code;
	for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i)
		user_error->e_args.e_pointers[i] = (u64)error->e_args.e_pointers[i];

	/* In case of  a system call,  set the  fault
	 * address as the system call return address. */
	user_error->e_faultaddr = sc_info != NULL
	                          ? (__HYBRID_PTR64(void))(u64)(uintptr_t)icpustate_getusersp(state)
	                          : (__HYBRID_PTR64(void))(u64)(uintptr_t)error->e_faultaddr;
	log_userexcept_error_propagate(state, sc_info, error, mode, (void *)handler, user_error);

	/* Redirect the given CPU state to return to the user-space handler. */
	gpregs_setpdi(&state->ics_gpregs, (uintptr_t)user_state); /* struct kcpustate64 *__restrict state */
	gpregs_setpsi(&state->ics_gpregs, (uintptr_t)user_error); /* struct __exception_data64 *__restrict error */
	icpustate_setusersp(state, user_error);
	icpustate_setpc(state, (void *)handler);
	{
		/* Mask `%Pflags', as specified by `x86_user_eflags_mask' */
		union x86_user_eflags_mask_union word;
		word.uem_word = atomic64_read(&x86_user_eflags_mask);
		word.uem_mask &= ~EFLAGS_RF; /* Always clear `EFLAGS_RF' so hw-breakpoints work on exception handler entry */
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
userexcept_callhandler(struct icpustate *__restrict state,
                       struct rpc_syscall_info const *sc_info,
                       struct exception_data const *__restrict error)
		THROWS(E_SEGFAULT) {
	struct icpustate *result;
	if (icpustate_is64bit(state)) {
		result = x86_userexcept_callhandler64(state, sc_info, error);
	} else {
		result = x86_userexcept_callhandler32(state, sc_info, error);
	}
	return result;
}
#endif /* __x86_64__ */



/* Arch-specific function:
 * Translate the current exception into an errno and set that errno
 * as the return value of  the system call described by  `sc_info'. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct icpustate *FCALL
userexcept_seterrno(struct icpustate *__restrict state,
                    struct rpc_syscall_info const *__restrict sc_info,
                    struct exception_data const *__restrict data)
		/* NOTE: On x86, this implementation is actually NOTHROW... */
		THROWS(E_SEGFAULT) {
	errno_t errval = -except_as_errno(data);
	log_userexcept_errno_propagate(state, sc_info, data, errval);

	/* All system call  methods return error  values through  EAX.
	 * If  this were ever to change (such that certain methods use
	 * different registers/locations), that special behavior would
	 * have to be implemented right here. */
	gpregs_setpax(&state->ics_gpregs, errval);

	/* Check if the system call is double-wide so we
	 * can  sign-extend the error code if necessary. */
	if (kernel_syscall_doublewide(sc_info))
		gpregs_setpdx(&state->ics_gpregs, (uintptr_t)-1); /* sign-extend */
	return state;
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_EXCEPT_HANDLER_C */
