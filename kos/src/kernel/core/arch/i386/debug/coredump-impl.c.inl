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
#ifdef __INTELLISENSE__
#include "coredump.c"
#define DEFINE_sys32_coredump
//#define DEFINE_sys64_coredump
#endif /* __INTELLISENSE__ */

#include <kernel/coredump.h>
#include <kernel/except.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/rpc.h>
#include <sched/sig.h>

#include <hybrid/host.h>
#include <hybrid/pointer.h>

#include <asm/cpu-flags.h>
#include <asm/registers.h>
#include <bits/os/kos/siginfo-convert.h>
#include <kos/bits/coredump.h>
#include <kos/bits/exception_data-convert.h>
#include <kos/bits/exception_data.h>
#include <kos/coredump.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state-verify.h>
#include <kos/kernel/cpu-state.h>
#include <sys/wait.h>

#include <alloca.h>
#include <assert.h>
#include <malloca.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#include <libunwind/errno.h>

#if (defined(DEFINE_sys32_coredump) + \
     defined(DEFINE_sys64_coredump)) != 1
#error "Must #define exactly one of these"
#endif /* ... */

#ifdef DEFINE_sys32_coredump
#include <kos/bits/coredump32.h>
#include <kos/bits/exception_data32.h>
#include <kos/kernel/bits/cpu-state32.h>
#else /* DEFINE_sys32_coredump */
#include <kos/bits/coredump64.h>
#include <kos/bits/exception_data64.h>
#include <kos/kernel/bits/cpu-state64.h>
#endif /* !DEFINE_sys32_coredump */


#ifdef DEFINE_sys64_coredump
#define LOCAL_struct_ucpustate      struct ucpustate64
#define LOCAL_uintptr_t             u32
#define LOCAL_ucpustate_decode      ucpustate_decode64
#define LOCAL_sys_coredump_impl     sys_coredump64_impl
#define LOCAL_sys_coredump_rpc      sys_coredump64_rpc
#define LOCAL_union_coredump_info   union coredump_info64
#define LOCAL_pointer               PTR64
#define LOCAL_siginfox_decode       siginfox64_to_siginfo
#define LOCAL_exception_data_decode exception_data64_to_exception_data
#else /* DEFINE_sys64_coredump */
#define LOCAL_struct_ucpustate      struct ucpustate32
#define LOCAL_uintptr_t             u64
#define LOCAL_ucpustate_decode      ucpustate_decode32
#define LOCAL_sys_coredump_impl     sys_coredump32_impl
#define LOCAL_sys_coredump_rpc      sys_coredump32_rpc
#define LOCAL_union_coredump_info   union coredump_info32
#define LOCAL_pointer               PTR32
#define LOCAL_siginfox_decode       siginfox32_to_siginfo
#define LOCAL_exception_data_decode exception_data32_to_exception_data
#endif /* !DEFINE_sys64_coredump */

DECL_BEGIN

PRIVATE NONNULL((1, 3)) void KCALL
LOCAL_ucpustate_decode(struct icpustate const *__restrict return_state,
                       USER CHECKED LOCAL_struct_ucpustate const *ust,
                       struct ucpustate *__restrict result)
		THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
#ifdef DEFINE_sys32_coredump
	ucpustate32_to_ucpustate(ust, result);
	cpustate_verify_usereflags((u32)icpustate_getpflags(return_state),
	                           (u32)ucpustate_getpflags(result),
	                           /* Accept `EFLAGS_RF' (needed for coredump on exception) */
	                           EFLAGS_RF | (u32)cred_allow_eflags_modify_mask());
#else /* DEFINE_sys32_coredump */
	ucpustate64_to_ucpustate(ust, result);
	cpustate_verify_userrflags(icpustate_getpflags(return_state),
	                           ucpustate_getpflags(result),
	                           /* Accept `EFLAGS_RF' (needed for coredump on exception) */
	                           EFLAGS_RF | cred_allow_eflags_modify_mask());
#endif /* !DEFINE_sys32_coredump */
#ifdef DEFINE_sys32_coredump
#ifndef __I386_NO_VM86
	if (!icpustate_isvm86(return_state))
#endif /* !__I386_NO_VM86 */
	{
		cpustate_verify_usercs(result->ucs_cs16);
		cpustate_verify_userss(result->ucs_ss16);
		cpustate_verify_usergs(result->ucs_sgregs.sg_gs16);
		cpustate_verify_userfs(result->ucs_sgregs.sg_fs16);
		cpustate_verify_useres(result->ucs_sgregs.sg_es16);
		cpustate_verify_userds(result->ucs_sgregs.sg_ds16);
	}
#endif /* DEFINE_sys32_coredump */
}

INTERN ATTR_NORETURN NONNULL((1)) void FCALL
LOCAL_sys_coredump_impl(struct icpustate *__restrict return_state,
                        USER UNCHECKED LOCAL_struct_ucpustate const *curr_state,
                        USER UNCHECKED LOCAL_struct_ucpustate const *orig_state,
                        USER UNCHECKED LOCAL_uintptr_t const *const *traceback_vector, size_t traceback_length,
                        USER UNCHECKED LOCAL_union_coredump_info const *reason,
                        unwind_errno_t unwind_error) {
	struct ucpustate curr_ustate, orig_ustate;
	void **utb_vector;
	signo_t signo = SIGABRT;
	if (!curr_state && !orig_state) {
		icpustate_user_to_ucpustate(return_state, &curr_ustate);
		memcpy(&orig_ustate, &curr_ustate, sizeof(struct ucpustate));
		traceback_vector = NULL;
		traceback_length = 0;
	} else if (!curr_state) {
		validate_readable(orig_state, sizeof(*orig_state));
		LOCAL_ucpustate_decode(return_state, orig_state, &orig_ustate);
		memcpy(&curr_ustate, &orig_ustate, sizeof(struct ucpustate));
		traceback_vector = NULL;
		traceback_length = 0;
	} else if (!orig_state) {
		validate_readable(curr_state, sizeof(*curr_state));
		LOCAL_ucpustate_decode(return_state, curr_state, &curr_ustate);
		memcpy(&orig_ustate, &curr_ustate, sizeof(struct ucpustate));
		traceback_vector = NULL;
		traceback_length = 0;
	} else {
		validate_readable(curr_state, sizeof(*curr_state));
		validate_readable(orig_state, sizeof(*orig_state));
		LOCAL_ucpustate_decode(return_state, curr_state, &curr_ustate);
		LOCAL_ucpustate_decode(return_state, orig_state, &orig_ustate);
		if (bcmp(&curr_ustate, &orig_ustate, sizeof(ucpustate)) == 0) {
			traceback_vector = NULL;
			traceback_length = 0;
		}
	}
	utb_vector = NULL;
	if (traceback_length > COREDUMP_TRACEBACK_LIMIT)
		traceback_length = COREDUMP_TRACEBACK_LIMIT;
	if (traceback_length != 0) {
		size_t i;
		utb_vector = (void **)alloca(traceback_length * sizeof(void *));
		for (i = 0; i < traceback_length; ++i)
			utb_vector[i] = (void *)(uintptr_t)traceback_vector[i];
	}
	if (!reason) {
		/* Coredump not caused by an exception or signal. */
		coredump_create(&curr_ustate, utb_vector, traceback_length,
		                &orig_ustate, NULL, 0, NULL, NULL,
		                unwind_error);
	} else if (COREDUMP_INFO_ISSIGNAL(unwind_error)) {
		/* Coredump caused by a signal. */
		siginfo_t si;
		validate_readable(&reason->ci_signal, sizeof(reason->ci_signal));
		LOCAL_siginfox_decode(&reason->ci_signal, &si);
		COMPILER_READ_BARRIER();
		signo = si.si_signo;
		coredump_create(&curr_ustate, utb_vector, traceback_length,
		                &orig_ustate, NULL, 0, NULL,
		                container_of(&si, union coredump_info, ci_signal),
		                unwind_error);
	} else if (COREDUMP_INFO_ISDLERROR(unwind_error)) {
		char *dlbuf;
		size_t errlen;
		validate_readable(reason->ci_dlerror, 1);
		errlen = strnlen(reason->ci_dlerror, COREDUMP_DLERROR_MAXLEN - 1);
		dlbuf  = (char *)alloca((errlen + 1) * sizeof(char));
		*(char *)mempcpy(dlbuf, reason->ci_dlerror, errlen, sizeof(char)) = '\0';
		coredump_create(&curr_ustate, utb_vector, traceback_length,
		                &orig_ustate, NULL, 0, NULL,
		                (union coredump_info *)dlbuf,
		                unwind_error);
	} else if (COREDUMP_INFO_ISASSERT(unwind_error)) {
		struct coredump_assert as;
		validate_readable(&reason->ci_assert, sizeof(reason->ci_assert));
		as.ca_expr = reason->ci_assert.ca_expr;
		as.ca_file = reason->ci_assert.ca_file;
		as.ca_line = reason->ci_assert.ca_line;
		as.ca_func = reason->ci_assert.ca_func;
		as.ca_mesg = reason->ci_assert.ca_mesg;
		/* Copy assertion strings into kernelspace. */
#define COPY_USERSPACE_STRING(field, maxlen)                        \
		if (field) {                                                \
			size_t len;                                             \
			char *buf;                                              \
			validate_readable(field, 1);                            \
			len = strnlen(field, (maxlen)-1);                       \
			buf = (char *)alloca((len + 1) * sizeof(char));         \
			*(char *)mempcpy(buf, field, len, sizeof(char)) = '\0'; \
			field = buf;                                            \
		}
		COPY_USERSPACE_STRING(as.ca_expr, COREDUMP_ASSERT_EXPR_MAXLEN);
		COPY_USERSPACE_STRING(as.ca_file, COREDUMP_ASSERT_FILE_MAXLEN);
		COPY_USERSPACE_STRING(as.ca_func, COREDUMP_ASSERT_FUNC_MAXLEN);
		COPY_USERSPACE_STRING(as.ca_mesg, COREDUMP_ASSERT_MESG_MAXLEN);
#undef COPY_USERSPACE_STRING
		coredump_create(&curr_ustate, utb_vector, traceback_length,
		                &orig_ustate, NULL, 0, NULL,
		                container_of(&as, union coredump_info, ci_assert),
		                unwind_error);
	} else {
		/* Coredump caused by an exception. */
		struct exception_data exc;
		validate_readable(&reason->ci_except, sizeof(reason->ci_except));
		LOCAL_exception_data_decode(&reason->ci_except, &exc);
		COMPILER_READ_BARRIER();
		coredump_create(&curr_ustate, utb_vector, traceback_length,
		                &orig_ustate, NULL, 0, NULL,
		                container_of(&exc, union coredump_info, ci_except),
		                unwind_error);
		/* If we get here, try to exit the application with a signo that
		 * is based on the exception that resulted in the coredump being
		 * created. */
		{
			siginfo_t si;
			if (except_as_signal(&exc, &si))
				signo = si.si_signo;
		}
	}
	assert(!task_wasconnected());
	THROW(E_EXIT_PROCESS,
	      W_EXITCODE(1, signo & 0x7f) | WCOREFLAG);
}

PRIVATE NONNULL((1, 2)) void PRPC_EXEC_CALLBACK_CC
LOCAL_sys_coredump_rpc(struct rpc_context *__restrict ctx,
                       void *UNUSED(cookie)) {
	if unlikely(ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	LOCAL_sys_coredump_impl(ctx->rc_state,
	                        (USER UNCHECKED LOCAL_struct_ucpustate const *)ctx->rc_scinfo.rsi_regs[0],
	                        (USER UNCHECKED LOCAL_struct_ucpustate const *)ctx->rc_scinfo.rsi_regs[1],
	                        (USER UNCHECKED LOCAL_uintptr_t const *const *)ctx->rc_scinfo.rsi_regs[2],
	                        (size_t)ctx->rc_scinfo.rsi_regs[3],
	                        (USER UNCHECKED LOCAL_union_coredump_info const *)ctx->rc_scinfo.rsi_regs[4],
	                        (unwind_errno_t)ctx->rc_scinfo.rsi_regs[5]);
}

/************************************************************************/
/* coredump()                                                           */
/************************************************************************/
#ifdef DEFINE_sys64_coredump
DEFINE_SYSCALL64_6(errno_t, coredump,
                   USER UNCHECKED LOCAL_struct_ucpustate const *, curr_state,
                   USER UNCHECKED LOCAL_struct_ucpustate const *, orig_state,
                   USER UNCHECKED LOCAL_pointer(void const) const *, traceback_vector,
                   size_t, traceback_length,
                   USER UNCHECKED LOCAL_union_coredump_info const *, reason,
                   unwind_errno_t, unwind_error)
#else /* DEFINE_sys64_coredump */
DEFINE_SYSCALL32_6(errno_t, coredump,
                   USER UNCHECKED LOCAL_struct_ucpustate const *, curr_state,
                   USER UNCHECKED LOCAL_struct_ucpustate const *, orig_state,
                   USER UNCHECKED LOCAL_pointer(void const) const *, traceback_vector,
                   size_t, traceback_length,
                   USER UNCHECKED LOCAL_union_coredump_info const *, reason,
                   unwind_errno_t, unwind_error)
#endif /* !DEFINE_sys64_coredump */
{
	(void)curr_state;
	(void)orig_state;
	(void)traceback_vector;
	(void)traceback_length;
	(void)reason;
	(void)unwind_error;
	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&LOCAL_sys_coredump_rpc, NULL);
	__builtin_unreachable();
}

#undef LOCAL_struct_ucpustate
#undef LOCAL_uintptr_t
#undef LOCAL_ucpustate_decode
#undef LOCAL_sys_coredump_impl
#undef LOCAL_sys_coredump_rpc
#undef LOCAL_union_coredump_info
#undef LOCAL_pointer
#undef LOCAL_siginfox_decode
#undef LOCAL_exception_data_decode

DECL_END

#undef DEFINE_sys32_coredump
#undef DEFINE_sys64_coredump
