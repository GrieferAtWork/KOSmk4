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
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/except-handler.h>
#include <sched/rpc.h>

#include <hybrid/atomic.h>

#include <asm/syscalls32.inl>
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

/* Gather RPC system call information for a specific system call invocation method */
LOCAL void FCALL
scinfo_get32_int80h(struct rpc_syscall_info *__restrict self,
                    struct icpustate const *__restrict state) {
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_INT80H_32 |
	                  RPC_SYSCALL_INFO_FARGVALID(0) |
	                  RPC_SYSCALL_INFO_FARGVALID(1) |
	                  RPC_SYSCALL_INFO_FARGVALID(2) |
	                  RPC_SYSCALL_INFO_FARGVALID(3) |
	                  RPC_SYSCALL_INFO_FARGVALID(4) |
	                  RPC_SYSCALL_INFO_FARGVALID(5);
	if (icpustate_getpflags(state) & EFLAGS_CF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ics_gpregs);
	self->rsi_args[0] = gpregs_getpbx(&state->ics_gpregs);
	self->rsi_args[1] = gpregs_getpcx(&state->ics_gpregs);
	self->rsi_args[2] = gpregs_getpdx(&state->ics_gpregs);
	self->rsi_args[3] = gpregs_getpsi(&state->ics_gpregs);
	self->rsi_args[4] = gpregs_getpdi(&state->ics_gpregs);
	self->rsi_args[5] = gpregs_getpbp(&state->ics_gpregs);
}

LOCAL void FCALL
scinfo_get32_sysenter(struct rpc_syscall_info *__restrict self,
                      struct icpustate const *__restrict state) {
	unsigned int regcount;
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_SYSENTER_32 |
	                  RPC_SYSCALL_INFO_FARGVALID(0) |
	                  RPC_SYSCALL_INFO_FARGVALID(1) |
	                  RPC_SYSCALL_INFO_FARGVALID(2) |
	                  RPC_SYSCALL_INFO_FARGVALID(3);
	if (icpustate_getpflags(state) & EFLAGS_CF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ics_gpregs);
	self->rsi_args[0] = gpregs_getpbx(&state->ics_gpregs);
	self->rsi_args[1] = gpregs_getpcx(&state->ics_gpregs);
	self->rsi_args[2] = gpregs_getpdx(&state->ics_gpregs);
	self->rsi_args[3] = gpregs_getpsi(&state->ics_gpregs);
	regcount = SYSCALL32_REGISTER_COUNT(self->rsi_sysno);
	if (regcount >= 5) {
		u32 *ebp = (u32 *)(uintptr_t)(u32)gpregs_getpbp(&state->ics_gpregs);
		validate_readable(ebp, 4);
		self->rsi_args[4] = __hybrid_atomic_load(ebp[0], __ATOMIC_ACQUIRE);
		self->rsi_flags |= RPC_SYSCALL_INFO_FARGVALID(4);
		if (regcount >= 6) {
			self->rsi_flags |= RPC_SYSCALL_INFO_FARGVALID(5);
			self->rsi_args[5] = __hybrid_atomic_load(ebp[1], __ATOMIC_ACQUIRE);
		}
	}
}

LOCAL void FCALL
scinfo_get32_cdecl(struct rpc_syscall_info *__restrict self,
                   struct icpustate const *__restrict state,
                   uintptr_t sysno, bool enable_except) {
	unsigned int regcount, i;
	u32 *esp;
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_CDECL_32;
	if (enable_except)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno = sysno;
	regcount = SYSCALL32_REGISTER_COUNT(sysno);
	if unlikely(!regcount)
		return;
	esp = (u32 *)(uintptr_t)(u32)icpustate_getuserpsp(state);
	validate_readable(esp, regcount * 4);
	for (i = 0; i < regcount; ++i) {
		self->rsi_args[i] = __hybrid_atomic_load(esp[i], __ATOMIC_ACQUIRE);
		self->rsi_flags |= RPC_SYSCALL_INFO_FARGVALID(i);
	}
}


#ifdef __x86_64__
LOCAL void FCALL
scinfo_get64_int80h(struct rpc_syscall_info *__restrict self,
                    struct icpustate const *__restrict state) {
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_INT80H_64 |
	                  RPC_SYSCALL_INFO_FARGVALID(0) |
	                  RPC_SYSCALL_INFO_FARGVALID(1) |
	                  RPC_SYSCALL_INFO_FARGVALID(2) |
	                  RPC_SYSCALL_INFO_FARGVALID(3) |
	                  RPC_SYSCALL_INFO_FARGVALID(4) |
	                  RPC_SYSCALL_INFO_FARGVALID(5);
	if (icpustate_getpflags(state) & EFLAGS_CF)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = gpregs_getpax(&state->ics_gpregs);
	self->rsi_args[0] = gpregs_getpdi(&state->ics_gpregs);
	self->rsi_args[1] = gpregs_getpsi(&state->ics_gpregs);
	self->rsi_args[2] = gpregs_getpdx(&state->ics_gpregs);
	self->rsi_args[3] = gpregs_getp10(&state->ics_gpregs);
	self->rsi_args[4] = gpregs_getp8(&state->ics_gpregs);
	self->rsi_args[5] = gpregs_getp9(&state->ics_gpregs);
}

LOCAL void FCALL
scinfo_get64_sysvabi(struct rpc_syscall_info *__restrict self,
                     struct icpustate const *__restrict state,
                     uintptr_t sysno, bool enable_except) {
	self->rsi_flags = RPC_SYSCALL_INFO_METHOD_SYSVABI_64 |
	                  RPC_SYSCALL_INFO_FARGVALID(0) |
	                  RPC_SYSCALL_INFO_FARGVALID(1) |
	                  RPC_SYSCALL_INFO_FARGVALID(2) |
	                  RPC_SYSCALL_INFO_FARGVALID(3) |
	                  RPC_SYSCALL_INFO_FARGVALID(4) |
	                  RPC_SYSCALL_INFO_FARGVALID(5);
	if (enable_except)
		self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	self->rsi_sysno   = sysno;
	self->rsi_args[0] = gpregs_getpdi(&state->ics_gpregs);
	self->rsi_args[1] = gpregs_getpsi(&state->ics_gpregs);
	self->rsi_args[2] = gpregs_getpdx(&state->ics_gpregs);
	self->rsi_args[3] = gpregs_getpcx(&state->ics_gpregs);
	self->rsi_args[4] = gpregs_getp8(&state->ics_gpregs);
	self->rsi_args[5] = gpregs_getp9(&state->ics_gpregs);
}
#endif /* __x86_64__ */


PUBLIC ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate32_int80h") struct icpustate *FCALL
x86_syscall_emulate32_int80h(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	scinfo_get32_int80h(&sc, state);
	return syscall_emulate(state, &sc);
}

PUBLIC ATTR_NORETURN ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate32_int80h_r") void FCALL
x86_syscall_emulate32_int80h_r(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	scinfo_get32_int80h(&sc, state);
	syscall_emulate_r(state, &sc);
}

PUBLIC ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate32_sysenter") struct icpustate *FCALL
x86_syscall_emulate32_sysenter(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	scinfo_get32_sysenter(&sc, state);
	return syscall_emulate(state, &sc);
}

PUBLIC ATTR_NORETURN ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate32_sysenter_r") void FCALL
x86_syscall_emulate32_sysenter_r(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	scinfo_get32_sysenter(&sc, state);
	syscall_emulate_r(state, &sc);
}

PUBLIC ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate32_cdecl") struct icpustate *FCALL
x86_syscall_emulate32_cdecl(struct icpustate *__restrict state,
                            syscall_ulong_t sysno, bool enable_except) {
	struct rpc_syscall_info sc;
	scinfo_get32_cdecl(&sc, state, sysno, enable_except);
	return syscall_emulate(state, &sc);
}

PUBLIC ATTR_NORETURN ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate32_cdecl_r") void FCALL
x86_syscall_emulate32_cdecl_r(struct icpustate *__restrict state,
                              syscall_ulong_t sysno, bool enable_except) {
	struct rpc_syscall_info sc;
	scinfo_get32_cdecl(&sc, state, sysno, enable_except);
	syscall_emulate_r(state, &sc);
}

#ifdef __x86_64__
PUBLIC ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate64_int80h") struct icpustate *FCALL
x86_syscall_emulate64_int80h(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	scinfo_get64_int80h(&sc, state);
	return syscall_emulate(state, &sc);
}

PUBLIC ATTR_NORETURN ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate64_int80h_r") void FCALL
x86_syscall_emulate64_int80h_r(struct icpustate *__restrict state) {
	struct rpc_syscall_info sc;
	scinfo_get64_int80h(&sc, state);
	syscall_emulate_r(state, &sc);
}

PUBLIC ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate64_sysvabi") struct icpustate *FCALL
x86_syscall_emulate64_sysvabi(struct icpustate *__restrict state,
                              syscall_ulong_t sysno, bool enable_except) {
	struct rpc_syscall_info sc;
	scinfo_get64_sysvabi(&sc, state, sysno, enable_except);
	return syscall_emulate(state, &sc);
}

PUBLIC ATTR_NORETURN ATTR_WEAK ATTR_SECTION(".text.x86.x86_syscall_emulate64_sysvabi_r") void FCALL
x86_syscall_emulate64_sysvabi_r(struct icpustate *__restrict state,
                                syscall_ulong_t sysno, bool enable_except) {
	struct rpc_syscall_info sc;
	scinfo_get64_sysvabi(&sc, state, sysno, enable_except);
	syscall_emulate_r(state, &sc);
}
#endif /* __x86_64__ */




typedef syscall_ulong_t (__ARCH_SYSCALLCC *syscall_proto_t)(syscall_ulong_t arg0, syscall_ulong_t arg1, syscall_ulong_t arg2, syscall_ulong_t arg3, syscall_ulong_t arg4, syscall_ulong_t arg5);
typedef u64 (__ARCH_SYSCALLCC *syscall_proto64_t)(syscall_ulong_t arg0, syscall_ulong_t arg1, syscall_ulong_t arg2, syscall_ulong_t arg3, syscall_ulong_t arg4, syscall_ulong_t arg5);
INTDEF syscall_proto_t const __c32_syscallrouter[];
INTDEF syscall_proto_t const __c32_exsyscallrouter[];
#ifdef __x86_64__
INTDEF syscall_proto_t const __c64_syscallrouter[];
INTDEF syscall_proto_t const __c64_exsyscallrouter[];
#endif /* __x86_64__ */


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
	syscall_proto_t proto;
	syscall_ulong_t sysno;
	assert(icpustate_isuser(state));
again:
	sysno = sc_info->rsi_sysno;
	TRY {
		if (sysno < __NR32_syscall_max) {
			u64 result;
			/* Normal system call */
			proto = __c64_syscallrouter[sysno];
do_syscall:
			result = (*(syscall_proto64_t)proto)(sc_info->rsi_args[0],
			                                     sc_info->rsi_args[1],
			                                     sc_info->rsi_args[2],
			                                     sc_info->rsi_args[3],
			                                     sc_info->rsi_args[4],
			                                     sc_info->rsi_args[5]);
			gpregs_setpax(&state->ics_gpregs, result);
		} else if (sysno >= __NR_exsyscall_min && sysno <= __NR_exsyscall_max) {
			/* Extended system call */
			proto = __c64_exsyscallrouter[sysno - __NR_exsyscall_min];
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
				      sc_info->rsi_sysno,
				      args[0], args[1], args[2],
				      args[3], args[4], args[5]);
			}
			gpregs_setpax(&state->ics_gpregs, (uintptr_t)(u64)(s64)-ENOSYS);
		}
	} EXCEPT {
		/* Service user-redirection RPCs to try and resolve the problem. */
		bool must_restart_syscall;
		struct exception_data *data;
		must_restart_syscall = false;
		state = rpc_serve_user_redirection_all(state,
		                                      TASK_RPC_REASON_SYSCALL,
		                                      sc_info,
		                                      &must_restart_syscall);
		data = error_data();
		if (data->e_code == ERROR_CODEOF(E_OK)) {
			if unlikely(must_restart_syscall)
				goto again; /* Do the restart */
			/* RPCs were able to handle the error!  -> return normally */
			goto done;
		}
		assert(!must_restart_syscall);
		if ((sc_info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) || /* propagate exceptions */
		    ERRORCODE_ISRTLPRIORITY(data->e_code))             /* Always propagate */
			RETHROW();
		/* Store the errno variant of the current exception
		 * in the user-space register context. */
		if (SYSCALL64_DOUBLE_WIDE(sysno))
			gpregs_setpdx(&state->ics_gpregs, (uintptr_t)-1); /* sign-extend */
		gpregs_setpax(&state->ics_gpregs, (uintptr_t)-error_as_errno(data));
		data->e_code = (error_code_t)ERROR_CODEOF(E_OK);
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
	syscall_proto_t proto;
	syscall_ulong_t sysno;
	assert(icpustate_isuser(state));
	/* TODO: This function doesn't (yet) do any form of system call tracing! */
again:
	sysno = sc_info->rsi_sysno;
	TRY {
		if (sysno < __NR32_syscall_max) {
			/* Normal system call */
			proto = __c32_syscallrouter[sysno];
			if (x86_syscall_double_wide_get(x86_syscall32_register_count, sysno)) {
				u64 result;
do_syscall64:
				result = (*(syscall_proto64_t)(void *)proto)(sc_info->rsi_args[0],
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
				result = (*proto)(sc_info->rsi_args[0],
				                  sc_info->rsi_args[1],
				                  sc_info->rsi_args[2],
				                  sc_info->rsi_args[3],
				                  sc_info->rsi_args[4],
				                  sc_info->rsi_args[5]);
				gpregs_setpax(&state->ics_gpregs, result);
			}
		} else if (sysno >= __NR_exsyscall_min && sysno <= __NR_exsyscall_max) {
			/* Extended system call */
			proto = __c32_exsyscallrouter[sysno - __NR_exsyscall_min];
			if (x86_syscall_double_wide_get(x86_exsyscall32_register_count, sysno - __NR_exsyscall_min))
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
			gpregs_setpax(&state->ics_gpregs, (uintptr_t)(u32)(s32)-ENOSYS);
		}
	} EXCEPT {
		/* Service user-redirection RPCs to try and resolve the problem. */
		bool must_restart_syscall;
		struct exception_data *data;
		must_restart_syscall = false;
		state = rpc_serve_user_redirection_all(state,
		                                      TASK_RPC_REASON_SYSCALL,
		                                      sc_info,
		                                      &must_restart_syscall);
		data = error_data();
		if (data->e_code == ERROR_CODEOF(E_OK)) {
			if unlikely(must_restart_syscall)
				goto again; /* Do the restart */
			/* RPCs were able to handle the error!  -> return normally */
			goto done;
		}
		assert(!must_restart_syscall);
		if ((sc_info->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT) || /* propagate exceptions */
		    ERRORCODE_ISRTLPRIORITY(data->e_code))             /* Always propagate */
			RETHROW();
		/* Store the errno variant of the current exception
		 * in the user-space register context. */
		if (SYSCALL32_DOUBLE_WIDE(sysno))
			gpregs_setpdx(&state->ics_gpregs, (uintptr_t)-1); /* sign-extend */
		gpregs_setpax(&state->ics_gpregs, (uintptr_t)-error_as_errno(data));
		data->e_code = (error_code_t)ERROR_CODEOF(E_OK);
	}
done:
	return state;
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SYSCALL_EMULATE_C */
