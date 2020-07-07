/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_TASK_REGISTERS_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_TASK_REGISTERS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/host.h>

#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>

#include <stdbool.h>

DECL_BEGIN

/* Safely get/set the values of saved registers that may be modified by RPC redirection. */

/* Check if `self' returns to user-space. */
PUBLIC NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) bool
NOTHROW(FCALL irregs_isuser)(struct irregs_kernel const *__restrict self) {
	uintptr_t pip;
	u16 cs = ATOMIC_READ(self->ir_cs16);
	if (cs & 3)
		return true;
#ifndef __x86_64__
	{
		u32 eflags;
		eflags = ATOMIC_READ(self->ir_eflags);
		if unlikely(eflags & EFLAGS_VM)
			return true;
	}
#endif /* !__x86_64__ */
	if (cs != SEGMENT_KERNEL_CODE)
		return false;
	pip = ATOMIC_READ(self->ir_pip);
	if unlikely(pip == (uintptr_t)&x86_rpc_user_redirection)
		return true;
	return false;
}

/* get:`self->ir_pip' */
PUBLIC NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) uintptr_t
NOTHROW(FCALL irregs_rdip)(struct irregs_kernel const *__restrict self) {
	uintptr_t result = ATOMIC_READ(self->ir_pip);
	if unlikely(result == (uintptr_t)&x86_rpc_user_redirection)
		result = PERTASK_GET(this_x86_rpc_redirection_iret.ir_pip);
	return result;
}

/* get:`self->ir_cs16' */
PUBLIC NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) u16
NOTHROW(FCALL irregs_rdcs)(struct irregs_kernel const *__restrict self) {
	u16 result = ATOMIC_READ(self->ir_cs16);
	if (result == SEGMENT_KERNEL_CODE) {
		uintptr_t pip = ATOMIC_READ(self->ir_pip);
		if unlikely(pip == (uintptr_t)&x86_rpc_user_redirection)
			result = PERTASK_GET(this_x86_rpc_redirection_iret.ir_cs16);
	}
	return result;
}

/* get:`self->ir_pflags' */
PUBLIC NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) uintptr_t
NOTHROW(FCALL irregs_rdflags)(struct irregs_kernel const *__restrict self) {
	uintptr_t result = ATOMIC_READ(self->ir_pflags);
	if unlikely(result == 0) {
		uintptr_t pip = ATOMIC_READ(self->ir_pip);
		if unlikely(pip == (uintptr_t)&x86_rpc_user_redirection)
			result = PERTASK_GET(this_x86_rpc_redirection_iret.ir_pflags);
	}
	return result;
}

/* get:`self->ir_rsp' */
PUBLIC NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) uintptr_t
NOTHROW(FCALL irregs_rdsp)(struct irregs_kernel const *__restrict self) {
#ifdef __x86_64__
	u64 result = ATOMIC_READ(self->ir_rsp);
	if (ADDR_ISKERN(result)) {
		u64 rip = ATOMIC_READ(self->ir_rip);
		if unlikely(rip == (u64)&x86_rpc_user_redirection)
			result = PERTASK_GET(this_x86_rpc_redirection_iret.ir_rsp);
	}
	return result;
#else /* __x86_64__ */
	u32 result = (u32)((byte_t *)self + SIZEOF_IRREGS32_KERNEL);
	u16 cs = ATOMIC_READ(self->ir_cs16);
	if (cs & 3)
		goto is_user_iret;
	if (ATOMIC_READ(self->ir_eflags) & EFLAGS_VM)
		goto is_user_iret;
	if (cs == SEGMENT_KERNEL_CODE) {
		u32 eip;
		eip = ATOMIC_READ(self->ir_eip);
		if unlikely(eip == (u32)&x86_rpc_user_redirection) {
is_user_iret:
			result = *(u32 *)result;
		}
	}
	return result;
#endif /* !__x86_64__ */
}

/* set:`self->ir_pip' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrip)(struct irregs_kernel *__restrict self, uintptr_t value) {
	uintptr_t oldval;
	do {
		oldval = ATOMIC_READ(self->ir_pip);
		if unlikely(oldval == (uintptr_t)&x86_rpc_user_redirection) {
			PERTASK_SET(this_x86_rpc_redirection_iret.ir_pip, value);
			break;
		}
	} while unlikely(!ATOMIC_CMPXCH_WEAK(self->ir_pip, oldval, value));
}

/* set:`self->ir_cs' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrcs)(struct irregs_kernel *__restrict self, u16 value) {
	pflag_t was;
	was = PREEMPTION_PUSHOFF();
	COMPILER_READ_BARRIER();
	if unlikely(self->ir_pip == (uintptr_t)&x86_rpc_user_redirection) {
		PERTASK_SET(this_x86_rpc_redirection_iret.ir_cs, (uintptr_t)value);
	} else {
		self->ir_cs = (uintptr_t)value;
	}
	COMPILER_WRITE_BARRIER();
	PREEMPTION_POP(was);
}

/* set:`self->ir_pflags' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrflags)(struct irregs_kernel *__restrict self, uintptr_t value) {
	pflag_t was;
	was = PREEMPTION_PUSHOFF();
	COMPILER_READ_BARRIER();
	if unlikely(self->ir_pip == (uintptr_t)&x86_rpc_user_redirection) {
		PERTASK_SET(this_x86_rpc_redirection_iret.ir_pflags, value);
	} else {
		self->ir_pflags = value;
	}
	COMPILER_WRITE_BARRIER();
	PREEMPTION_POP(was);
}

/* set:`self->ir_pflags = (self->ir_pflags & mask) | flags' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_mskflags)(struct irregs_kernel *__restrict self,
                               uintptr_t mask, uintptr_t flags) {
	pflag_t was;
	was = PREEMPTION_PUSHOFF();
	COMPILER_READ_BARRIER();
	if unlikely(self->ir_pip == (uintptr_t)&x86_rpc_user_redirection) {
		uintptr_t newval;
		newval = PERTASK_GET(this_x86_rpc_redirection_iret.ir_pflags);
		PERTASK_SET(this_x86_rpc_redirection_iret.ir_pflags, (newval & mask) | flags);
	} else {
		self->ir_pflags &= mask;
		self->ir_pflags |= flags;
	}
	COMPILER_WRITE_BARRIER();
	PREEMPTION_POP(was);
}



#ifdef __x86_64__

/* Check if `self' returns to compatibility-mode. */
PUBLIC NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) bool
NOTHROW(FCALL irregs_iscompat)(struct irregs const *__restrict self) {
	u16 cs = ATOMIC_READ(self->ir_cs16);
	if (SEGMENT_IS_VALID_USERCODE32(cs))
		return true;
	if (cs == SEGMENT_KERNEL_CODE) {
		u64 rip = ATOMIC_READ(self->ir_rip);
		if unlikely(rip == (u64)&x86_rpc_user_redirection) {
			cs = PERTASK_GET(this_x86_rpc_redirection_iret.ir_cs16);
			if (SEGMENT_IS_VALID_USERCODE32(cs))
				return true;
		}
	}
	return false;
}

/* get:`self->ir_ss16' */
PUBLIC NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) u16
NOTHROW(FCALL irregs_rdss)(struct irregs const *__restrict self) {
	u16 result = ATOMIC_READ(self->ir_ss16);
	if (result == SEGMENT_KERNEL_DATA0) {
		u64 rip = ATOMIC_READ(self->ir_rip);
		if unlikely(rip == (u64)&x86_rpc_user_redirection)
			result = PERTASK_GET(this_x86_rpc_redirection_iret.ir_ss16);
	}
	return result;
}

/* set:`self->ir_rsp' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrsp)(struct irregs *__restrict self, uintptr_t value) {
	pflag_t was;
	was = PREEMPTION_PUSHOFF();
	COMPILER_READ_BARRIER();
	if unlikely(self->ir_rip == (u64)&x86_rpc_user_redirection) {
		PERTASK_SET(this_x86_rpc_redirection_iret.ir_rsp, value);
	} else {
		self->ir_rsp = value;
	}
	COMPILER_WRITE_BARRIER();
	PREEMPTION_POP(was);
}

/* set:`self->ir_ss' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrss)(struct irregs *__restrict self, u16 value) {
	pflag_t was;
	was = PREEMPTION_PUSHOFF();
	COMPILER_READ_BARRIER();
	if unlikely(self->ir_rip == (u64)&x86_rpc_user_redirection) {
		PERTASK_SET(this_x86_rpc_redirection_iret.ir_ss, (u64)value);
	} else {
		self->ir_ss = (u64)value;
	}
	COMPILER_WRITE_BARRIER();
	PREEMPTION_POP(was);
}

#else /* __x86_64__ */

/* Not guarantied to return `1' for vm86 interrupt registers. */
PUBLIC NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) bool
NOTHROW(FCALL irregs_isuser_novm86)(struct irregs_kernel const *__restrict self) {
	u16 cs;
	u32 eip;
	cs = ATOMIC_READ(self->ir_cs16);
	if (cs & 3)
		return true;
	eip = ATOMIC_READ(self->ir_eip);
	if unlikely(eip == (u32)&x86_rpc_user_redirection)
		return true;
	return false;
}

PUBLIC NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) bool
NOTHROW(FCALL irregs_isvm86)(struct irregs_kernel const *__restrict self) {
	u32 eip, eflags;
	eflags = ATOMIC_READ(self->ir_eflags);
	if (eflags & EFLAGS_VM)
		return true;
	eip = ATOMIC_READ(self->ir_eip);
	if unlikely(eip == (u32)&x86_rpc_user_redirection) {
		eflags = PERTASK_GET(this_x86_rpc_redirection_iret.ir_eflags);
		if (eflags & EFLAGS_VM)
			return true;
	}
	return false;
}
#endif /* !__x86_64__ */



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_TASK_REGISTERS_C */
