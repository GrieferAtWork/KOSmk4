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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE_C
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/syscall-info.h>
#include <kernel/syscall-properties.h>
#include <kernel/syscall-tables.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/except-handler.h>
#include <sched/rpc.h>

#include <hybrid/atomic.h>

#include <asm/syscalls32_d.h>
#include <asm/unistd.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state-helpers32.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/cpu-state32.h>

#include <assert.h>
#include <errno.h>
#include <string.h>

#include <librpc/rpc.h>

DECL_BEGIN

PUBLIC ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate32_int80h") struct icpustate *FCALL
x86_syscall_emulate32_int80h(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get32_int80h(&sc, state);
	return syscall_emulate(state, &sc);
}

PUBLIC ATTR_NORETURN ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate32_int80h_r") void FCALL
x86_syscall_emulate32_int80h_r(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get32_int80h(&sc, state);
	syscall_emulate_r(state, &sc);
}

PUBLIC ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate32_sysenter") struct icpustate *FCALL
x86_syscall_emulate32_sysenter(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get32_sysenter(&sc, state);
	return syscall_emulate(state, &sc);
}

PUBLIC ATTR_NORETURN ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate32_sysenter_r") void FCALL
x86_syscall_emulate32_sysenter_r(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get32_sysenter(&sc, state);
	syscall_emulate_r(state, &sc);
}

PUBLIC ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate32_cdecl") struct icpustate *FCALL
x86_syscall_emulate32_cdecl(struct icpustate *__restrict state,
                            syscall_ulong_t sysno, bool enable_except) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get32_cdecl(&sc, state, sysno, enable_except);
	return syscall_emulate(state, &sc);
}

PUBLIC ATTR_NORETURN ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate32_cdecl_r") void FCALL
x86_syscall_emulate32_cdecl_r(struct icpustate *__restrict state,
                              syscall_ulong_t sysno, bool enable_except) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get32_cdecl(&sc, state, sysno, enable_except);
	syscall_emulate_r(state, &sc);
}

#ifdef __x86_64__
PUBLIC ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate64_int80h") struct icpustate *FCALL
x86_syscall_emulate64_int80h(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get64_int80h(&sc, state);
	return syscall_emulate(state, &sc);
}

PUBLIC ATTR_NORETURN ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate64_int80h_r") void FCALL
x86_syscall_emulate64_int80h_r(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get64_int80h(&sc, state);
	syscall_emulate_r(state, &sc);
}

PUBLIC ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate64_sysvabi") struct icpustate *FCALL
x86_syscall_emulate64_sysvabi(struct icpustate *__restrict state,
                              syscall_ulong_t sysno, bool enable_except) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get64_sysvabi(&sc, state, sysno, enable_except);
	return syscall_emulate(state, &sc);
}

PUBLIC ATTR_NORETURN ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate64_sysvabi_r") void FCALL
x86_syscall_emulate64_sysvabi_r(struct icpustate *__restrict state,
                                syscall_ulong_t sysno, bool enable_except) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get64_sysvabi(&sc, state, sysno, enable_except);
	syscall_emulate_r(state, &sc);
}
#endif /* __x86_64__ */




typedef syscall_ulong_t (__ARCH_SYSCALLCC *syscall_proto_t)(syscall_ulong_t arg0, syscall_ulong_t arg1, syscall_ulong_t arg2, syscall_ulong_t arg3, syscall_ulong_t arg4, syscall_ulong_t arg5);
typedef u64 (__ARCH_SYSCALLCC *syscall_proto64_t)(syscall_ulong_t arg0, syscall_ulong_t arg1, syscall_ulong_t arg2, syscall_ulong_t arg3, syscall_ulong_t arg4, syscall_ulong_t arg5);

INTDEF struct icpustate *
NOTHROW(FCALL rpc_serve_user_redirection_all)(struct icpustate *__restrict state,
                                              unsigned int reason,
                                              struct rpc_syscall_info const *sc_info,
                                              bool *prestart_system_call);

/* Emulate the execution of a system call.
 * NOTE: `syscall_emulate_r()' is the same as `syscall_emulate()', however
 *       will reset the kernel-space stack and will not unwind, or return to the
 *       stack of the caller */
#ifdef __x86_64__
PUBLIC ATTR_RETNONNULL WUNUSED struct icpustate *FCALL
syscall_emulate(struct icpustate *__restrict state,
                struct rpc_syscall_info *__restrict sc_info) {
	struct icpustate *result;
	if (icpustate_is64bit(state)) {
		result = syscall_emulate64(state, sc_info);
	} else {
		result = syscall_emulate32(state, sc_info);
	}
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED struct icpustate *FCALL
syscall_emulate64(struct icpustate *__restrict state,
                  struct rpc_syscall_info *__restrict sc_info) {
	void *proto;
	syscall_ulong_t sysno;
	assert(icpustate_isuser(state));
again:
	sysno = sc_info->rsi_sysno;
	TRY {
		if (sysno < __NR32_syscall0_max) {
			u64 result;
			/* Normal system call */
			proto = x86_sysroute0_c[sysno];
do_syscall:
			result = (*(syscall_proto64_t)proto)(sc_info->rsi_args[0],
			                                     sc_info->rsi_args[1],
			                                     sc_info->rsi_args[2],
			                                     sc_info->rsi_args[3],
			                                     sc_info->rsi_args[4],
			                                     sc_info->rsi_args[5]);
			gpregs_setpax(&state->ics_gpregs, result);
		} else if (sysno >= __NR_syscall1_min && sysno <= __NR_syscall1_max) {
			/* Extended system call */
			proto = x86_sysroute1_c[sysno - __NR_syscall1_min];
			goto do_syscall;
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
				      sc_info->rsi_flags,
				      sc_info->rsi_sysno,
				      args[0], args[1], args[2],
				      args[3], args[4], args[5]);
			}
			gpregs_setpax(&state->ics_gpregs, (uintptr_t)(u64)(s64)-ENOSYS);
		}
	} EXCEPT {
		/* Service user-redirection RPCs to try and resolve the problem. */
		bool must_restart_syscall;
		error_code_t code = PERTASK_GET(this_exception_code);
		must_restart_syscall = false;
		state = rpc_serve_user_redirection_all(state,
		                                       TASK_RPC_REASON_SYSCALL,
		                                       sc_info,
		                                       &must_restart_syscall);
		if (code == ERROR_CODEOF(E_OK)) {
			if unlikely(must_restart_syscall)
				goto again; /* Do the restart */
			/* RPCs were able to handle the error!  -> return normally */
			goto done;
		}
		assert(!must_restart_syscall);
		if ((sc_info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) || /* propagate exceptions */
		    ERRORCODE_ISRTLPRIORITY(code))                     /* Always propagate RTL exceptions */
			RETHROW();
		/* Store the errno variant of the current exception
		 * in the user-space register context. */
		state = x86_userexcept_seterrno64(state, sc_info);
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_OK));
	}
done:
	return state;
}

PUBLIC ATTR_RETNONNULL WUNUSED struct icpustate *FCALL
syscall_emulate32(struct icpustate *__restrict state,
                  struct rpc_syscall_info *__restrict sc_info)
#else /* __x86_64__ */
PUBLIC WUNUSED struct icpustate *FCALL
syscall_emulate(struct icpustate *__restrict state,
                struct rpc_syscall_info *__restrict sc_info)
#endif /* !__x86_64__ */
{
	void *proto;
	syscall_ulong_t sysno;
	assert(icpustate_isuser(state));
	/* TODO: This function doesn't (yet) do any form of system call tracing! */
again:
	sysno = sc_info->rsi_sysno;
	TRY {
		if (sysno < __NR32_syscall0_max) {
			/* Normal system call */
			proto = x86_sysroute0_c32[sysno];
			if (__kernel_syscall_regcnt(kernel_syscall0_regcnt, sysno)) {
				u64 result;
do_syscall64:
				result = (*(syscall_proto64_t)proto)(sc_info->rsi_args[0],
				                                     sc_info->rsi_args[1],
				                                     sc_info->rsi_args[2],
				                                     sc_info->rsi_args[3],
				                                     sc_info->rsi_args[4],
				                                     sc_info->rsi_args[5]);
				gpregs_setpax(&state->ics_gpregs, (u32)(result));
				gpregs_setpdx(&state->ics_gpregs, (u32)(result >> 32));
			} else {
				u32 result;
do_syscall32:
				result = (*(syscall_proto_t)proto)(sc_info->rsi_args[0],
				                                   sc_info->rsi_args[1],
				                                   sc_info->rsi_args[2],
				                                   sc_info->rsi_args[3],
				                                   sc_info->rsi_args[4],
				                                   sc_info->rsi_args[5]);
				gpregs_setpax(&state->ics_gpregs, result);
			}
		} else if (sysno >= __NR_syscall1_min && sysno <= __NR_syscall1_max) {
			/* Extended system call */
			proto = x86_sysroute1_c32[sysno - __NR_syscall1_min];
			if (__kernel_syscall_doublewide(kernel_syscall1_regcnt, sysno - __NR_syscall1_min))
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
				      sc_info->rsi_flags,
				      sc_info->rsi_sysno,
				      args[0], args[1], args[2],
				      args[3], args[4], args[5]);
			}
			gpregs_setpax(&state->ics_gpregs, (uintptr_t)(u32)(s32)-ENOSYS);
		}
	} EXCEPT {
		/* Service user-redirection RPCs to try and resolve the problem. */
		bool must_restart_syscall;
		error_code_t code = PERTASK_GET(this_exception_code);
		must_restart_syscall = false;
		state = rpc_serve_user_redirection_all(state,
		                                       TASK_RPC_REASON_SYSCALL,
		                                       sc_info,
		                                       &must_restart_syscall);
		if (code == ERROR_CODEOF(E_OK)) {
			if unlikely(must_restart_syscall)
				goto again; /* Do the restart */
			/* RPCs were able to handle the error!  -> return normally */
			goto done;
		}
		assert(!must_restart_syscall);
		if ((sc_info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) || /* propagate exceptions */
		    ERRORCODE_ISRTLPRIORITY(code))                     /* Always propagate RTL exceptions */
			RETHROW();
		/* Store the errno variant of the current exception
		 * in the user-space register context. */
		state = x86_userexcept_seterrno32(state, sc_info);
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_OK));
	}
done:
	return state;
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE_C */
