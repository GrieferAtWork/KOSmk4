/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE_C
#define GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/syscall-properties.h>
#include <kernel/syscall-trace.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <kernel/x86/syscall-info.h>
#include <kernel/x86/syscall-tables.h>
#include <sched/rpc.h>

#include <asm/syscalls32_d.h>
#include <asm/unistd.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/bits/cpu-state-helpers32.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/bits/cpu-state32.h>

#include <assert.h>
#include <errno.h>
#include <string.h>

DECL_BEGIN

/* NOTE: Generic system  call emulation  helpers are  implemented as  WEAK
 *       because  some of  them have  more efficient  assembly versions in
 *       some of the (32|64).S files within the same folder as this  file.
 *       As such, we simply define everything there is, and let the linker
 *       get rid of the (inefficient) C versions if assembly versions have
 *       been defined. */

/* Emulate x32:int80h */
PUBLIC ATTR_SECTION(".text.x86." PP_STR(x86_syscall_emulate32_int80h))
ATTR_WEAK WUNUSED NONNULL((1)) struct icpustate *FCALL
x86_syscall_emulate32_int80h(struct icpustate *__restrict state)
		THROWS(...) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get32_int80h(&sc, state);
	return syscall_emulate32(state, &sc);
}

/* Emulate x32:int80h */
PUBLIC ATTR_SECTION(".text.x86." PP_STR(x86_syscall_emulate32_int80h_r))
ABNORMAL_RETURN ATTR_NORETURN ATTR_WEAK NONNULL((1)) void
NOTHROW(FCALL x86_syscall_emulate32_int80h_r)(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get32_int80h(&sc, state);
	syscall_emulate32_r(state, &sc);
}

/* Emulate x32:sysenter */
PUBLIC ATTR_SECTION(".text.x86." PP_STR(x86_syscall_emulate32_sysenter))
ATTR_WEAK WUNUSED NONNULL((1)) struct icpustate *FCALL
x86_syscall_emulate32_sysenter(struct icpustate *__restrict state)
		THROWS(...) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get32_sysenter(&sc, state);
	return syscall_emulate32(state, &sc);
}

/* Emulate x32:sysenter */
PUBLIC ATTR_SECTION(".text.x86." PP_STR(x86_syscall_emulate32_sysenter_r))
ABNORMAL_RETURN ATTR_NORETURN ATTR_WEAK NONNULL((1)) void
NOTHROW(FCALL x86_syscall_emulate32_sysenter_r)(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get32_sysenter(&sc, state);
	syscall_emulate32_r(state, &sc);
}

/* Emulate x32:cdecl */
PUBLIC ATTR_SECTION(".text.x86." PP_STR(x86_syscall_emulate32_cdecl))
ATTR_WEAK WUNUSED NONNULL((1)) struct icpustate *FCALL
x86_syscall_emulate32_cdecl(struct icpustate *__restrict state,
                            syscall_ulong_t sysno, bool enable_except)
		THROWS(...) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get32_cdecl(&sc, state, sysno, enable_except);
	return syscall_emulate32(state, &sc);
}

/* Emulate x32:cdecl */
PUBLIC ATTR_SECTION(".text.x86." PP_STR(x86_syscall_emulate32_cdecl_r))
ABNORMAL_RETURN ATTR_NORETURN ATTR_WEAK NONNULL((1)) void
NOTHROW(FCALL x86_syscall_emulate32_cdecl_r)(struct icpustate *__restrict state,
                                             syscall_ulong_t sysno, bool enable_except) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get32_cdecl(&sc, state, sysno, enable_except);
	syscall_emulate32_r(state, &sc);
}

#ifdef __x86_64__
/* Emulate x32:int80h, x64:int80h or x64:syscall */
PUBLIC ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate_int80h")
WUNUSED NONNULL((1)) struct icpustate *FCALL
x86_syscall_emulate_int80h(struct icpustate *__restrict state)
		THROWS(...) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get64_int80h(&sc, state);
	return syscall_emulate(state, &sc);
}

/* Emulate x32:int80h, x64:int80h or x64:syscall */
PUBLIC ABNORMAL_RETURN ATTR_NORETURN ATTR_WEAK
ATTR_SECTION(".text.x86.x86_syscall_emulate_int80h_r") NONNULL((1)) void
NOTHROW(FCALL x86_syscall_emulate_int80h_r)(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get64_int80h(&sc, state);
	syscall_emulate_r(state, &sc);
}

/* Emulate x64:int80h or x64:syscall */
PUBLIC ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate64_int80h")
WUNUSED NONNULL((1)) struct icpustate *FCALL
x86_syscall_emulate64_int80h(struct icpustate *__restrict state)
		THROWS(...) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get64_int80h(&sc, state);
	return syscall_emulate64(state, &sc);
}

/* Emulate x64:int80h or x64:syscall */
PUBLIC ABNORMAL_RETURN ATTR_NORETURN ATTR_WEAK
ATTR_SECTION(".text.x86.x86_syscall_emulate64_int80h_r") NONNULL((1)) void
NOTHROW(FCALL x86_syscall_emulate64_int80h_r)(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get64_int80h(&sc, state);
	syscall_emulate64_r(state, &sc);
}

/* Emulate x64:sysvabi */
PUBLIC ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate_sysvabi")
WUNUSED NONNULL((1)) struct icpustate *FCALL
x86_syscall_emulate_sysvabi(struct icpustate *__restrict state,
                            syscall_ulong_t sysno, bool enable_except)
		THROWS(...) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get64_sysvabi(&sc, state, sysno, enable_except);
	return syscall_emulate64(state, &sc);
}

/* Emulate x64:sysvabi */
PUBLIC ABNORMAL_RETURN ATTR_NORETURN ATTR_WEAK
ATTR_SECTION(".text.x86.x86_syscall_emulate_sysvabi_r") NONNULL((1)) void
NOTHROW(FCALL x86_syscall_emulate_sysvabi_r)(struct icpustate *__restrict state,
                                             syscall_ulong_t sysno, bool enable_except) {
	struct rpc_syscall_info sc;
	rpc_syscall_info_get64_sysvabi(&sc, state, sysno, enable_except);
	syscall_emulate64_r(state, &sc);
}
#endif /* __x86_64__ */




typedef syscall_ulong_t
(__ARCH_SYSCALLCC *syscall_proto_t)(syscall_ulong_t arg0, syscall_ulong_t arg1,
                                    syscall_ulong_t arg2, syscall_ulong_t arg3,
                                    syscall_ulong_t arg4, syscall_ulong_t arg5)
		THROWS(...);
typedef u64
(__ARCH_SYSCALLCC *syscall_proto64_t)(syscall_ulong_t arg0, syscall_ulong_t arg1,
                                      syscall_ulong_t arg2, syscall_ulong_t arg3,
                                      syscall_ulong_t arg4, syscall_ulong_t arg5)
		THROWS(...);

INTDEF bool syscall_tracing_enabled;

/* Emulate the execution of a system call.
 * NOTE: `syscall_emulate_r()' is the same as `syscall_emulate()', however already
 *       includes all of the necessary exception handling ~ala userexcept_handler:
 * >> PUBLIC ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void
 * >> NOTHROW(FCALL syscall_emulate_r)(struct icpustate *__restrict state,
 * >>                                  struct rpc_syscall_info const *__restrict sc_info) {
 * >> again:
 * >>     TRY {
 * >>         state = syscall_emulate(state, sc_info);
 * >>         cpu_apply_icpustate(state);
 * >>     } EXCEPT {
 * >>         state = userexcept_handler(state, sc_info);
 * >>         // PERTASK_SET(this_exception_code, 1); // Prevent internal assertion check
 * >>         goto again;
 * >>     }
 * >> } */
#ifdef __x86_64__
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
syscall_emulate(struct icpustate *__restrict state,
                struct rpc_syscall_info const *__restrict sc_info)
		THROWS(...) {
	struct icpustate *result;
	if (icpustate_is64bit(state)) {
		result = syscall_emulate64(state, sc_info);
	} else {
		result = syscall_emulate32(state, sc_info);
	}
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
syscall_emulate64(struct icpustate *__restrict state,
                  struct rpc_syscall_info const *__restrict sc_info)
		THROWS(...) {
	void *proto;
	syscall_ulong_t sysno;
	assert(icpustate_isuser(state));
	sysno = sc_info->rsi_sysno;
	if (syscall_tracing_enabled)
		syscall_trace(sc_info);
	if (sysno <= __NR_syscall0_max) {
		u64 result;
		/* Normal system call */
		proto = x86_sysroute0_c[sysno];
do_syscall:
		result = (*(syscall_proto64_t)proto)(sc_info->rsi_regs[0],
		                                     sc_info->rsi_regs[1],
		                                     sc_info->rsi_regs[2],
		                                     sc_info->rsi_regs[3],
		                                     sc_info->rsi_regs[4],
		                                     sc_info->rsi_regs[5]);
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
			memcpy(args, sc_info->rsi_regs, sizeof(args));
			for (i = 0; i < 6; ++i) {
				if (!(sc_info->rsi_flags & RPC_SYSCALL_INFO_FREGVALID(i)))
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
	return state;
}

typedef NONNULL((1)) u32 (__ARCH_SYSCALLCC *syscall_run32_32_t)(u64 const *regv);
typedef NONNULL((1)) u64 (__ARCH_SYSCALLCC *syscall_run32_64_t)(u64 const *regv);

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
syscall_emulate32(struct icpustate *__restrict state,
                  struct rpc_syscall_info const *__restrict sc_info)
		THROWS(...) {
	void *proto;
	syscall_ulong_t sysno;
	assert(icpustate_isuser(state));
	if (syscall_tracing_enabled)
		syscall_trace(sc_info);
	sysno = sc_info->rsi_sysno;
	if (sysno <= __NR32_syscall0_max) {
		/* Normal system call */
		proto = x86_sysroute0_runc32[sysno];
		if (_kernel_private_syscall_doublewide(kernel_syscall0_regcnt, sysno)) {
			u64 result;
do_syscall64:
			result = (*(syscall_run32_64_t)proto)(sc_info->rsi_regs);
			gpregs_setpax(&state->ics_gpregs, (u32)(result));
			gpregs_setpdx(&state->ics_gpregs, (u32)(result >> 32));
		} else {
			u32 result;
do_syscall32:
			result = (*(syscall_run32_32_t)proto)(sc_info->rsi_regs);
			gpregs_setpax(&state->ics_gpregs, result);
		}
	} else if (sysno >= __NR32_syscall1_min && sysno <= __NR32_syscall1_max) {
		/* Extended system call */
		proto = x86_sysroute1_runc32[sysno - __NR32_syscall1_min];
		if (_kernel_private_syscall_doublewide(kernel_syscall1_regcnt, sysno - __NR32_syscall1_min))
			goto do_syscall64;
		goto do_syscall32;
	} else {
		/* Invalid system call */
		if (sc_info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) {
			syscall_ulong_t regs[6];
			unsigned int i;
			memcpy(regs, sc_info->rsi_regs, sizeof(regs));
			for (i = 0; i < 6; ++i) {
				if (!(sc_info->rsi_flags & RPC_SYSCALL_INFO_FREGVALID(i)))
					regs[i] = 0;
			}
			THROW(E_UNKNOWN_SYSTEMCALL,
			      sc_info->rsi_flags,
			      sc_info->rsi_sysno,
			      regs[0], regs[1], regs[2],
			      regs[3], regs[4], regs[5]);
		}
		gpregs_setpax(&state->ics_gpregs, (uintptr_t)-ENOSYS);
	}
	return state;
}

#else /* __x86_64__ */
PUBLIC WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
syscall_emulate(struct icpustate *__restrict state,
                struct rpc_syscall_info const *__restrict sc_info)
		THROWS(...) {
	void *proto;
	syscall_ulong_t sysno;
	assert(icpustate_isuser(state));
	if (syscall_tracing_enabled)
		syscall_trace(sc_info);
	sysno = sc_info->rsi_sysno;
	if (sysno <= __NR32_syscall0_max) {
		/* Normal system call */
		proto = x86_sysroute0_c32[sysno];
		if (_kernel_private_syscall_doublewide(kernel_syscall0_regcnt, sysno)) {
			u64 result;
do_syscall64:
			result = (*(syscall_proto64_t)proto)(sc_info->rsi_regs[0],
			                                     sc_info->rsi_regs[1],
			                                     sc_info->rsi_regs[2],
			                                     sc_info->rsi_regs[3],
			                                     sc_info->rsi_regs[4],
			                                     sc_info->rsi_regs[5]);
			gpregs_setpax(&state->ics_gpregs, (u32)(result));
			gpregs_setpdx(&state->ics_gpregs, (u32)(result >> 32));
		} else {
			u32 result;
do_syscall32:
			result = (*(syscall_proto_t)proto)(sc_info->rsi_regs[0],
			                                   sc_info->rsi_regs[1],
			                                   sc_info->rsi_regs[2],
			                                   sc_info->rsi_regs[3],
			                                   sc_info->rsi_regs[4],
			                                   sc_info->rsi_regs[5]);
			gpregs_setpax(&state->ics_gpregs, result);
		}
	} else if (sysno >= __NR32_syscall1_min && sysno <= __NR32_syscall1_max) {
		/* Extended system call */
		proto = x86_sysroute1_c32[sysno - __NR32_syscall1_min];
		if (_kernel_private_syscall_doublewide(kernel_syscall1_regcnt, sysno - __NR32_syscall1_min))
			goto do_syscall64;
		goto do_syscall32;
	} else {
		/* Invalid system call */
		if (sc_info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) {
			syscall_ulong_t args[6];
			unsigned int i;
			memcpy(args, sc_info->rsi_regs, sizeof(args));
			for (i = 0; i < 6; ++i) {
				if (!(sc_info->rsi_flags & RPC_SYSCALL_INFO_FREGVALID(i)))
					args[i] = 0;
			}
			THROW(E_UNKNOWN_SYSTEMCALL,
			      sc_info->rsi_flags,
			      sc_info->rsi_sysno,
			      args[0], args[1], args[2],
			      args[3], args[4], args[5]);
		}
		gpregs_setpax(&state->ics_gpregs, (uintptr_t)-ENOSYS);
	}
	return state;
}
#endif /* !__x86_64__ */



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE_C */
