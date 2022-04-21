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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_TASK_REGISTERS_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_TASK_REGISTERS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>
#include <sched/arch/task.h>

#include <hybrid/atomic.h>
#include <hybrid/host.h>
#include <hybrid/sched/preemption.h>

#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>

#include <stdbool.h>

DECL_BEGIN

/* Safely get/set the values of saved registers that may be modified by RPC redirection. */

/* Check if `self' returns to user-space. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL irregs_isuser)(struct irregs_kernel const *__restrict self) {
	uintptr_t pip;
	u16 cs = ATOMIC_READ(self->ir_cs16);
	if (cs & 3)
		return true;
#ifndef __x86_64__
#ifndef __I386_NO_VM86
	{
		u32 eflags;
		eflags = ATOMIC_READ(self->ir_eflags);
		if unlikely(eflags & EFLAGS_VM)
			return true;
	}
#endif /* !__I386_NO_VM86 */
#endif /* !__x86_64__ */
	if (cs != SEGMENT_KERNEL_CODE)
		return false;
	pip = ATOMIC_READ(self->ir_Pip);
	if unlikely(pip == (uintptr_t)&x86_userexcept_sysret)
		return true;
	return false;
}

/* get: `self->ir_Pip' */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(FCALL irregs_rdip)(struct irregs_kernel const *__restrict self) {
	uintptr_t result = ATOMIC_READ(self->ir_Pip);
	if unlikely(result == (uintptr_t)&x86_userexcept_sysret)
		result = PERTASK_GET(this_x86_sysret_iret.ir_Pip);
	return result;
}

/* get: `self->ir_cs16' */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) u16
NOTHROW(FCALL irregs_rdcs)(struct irregs_kernel const *__restrict self) {
	u16 result = ATOMIC_READ(self->ir_cs16);
	if (result == SEGMENT_KERNEL_CODE) {
		uintptr_t pip = ATOMIC_READ(self->ir_Pip);
		if unlikely(pip == (uintptr_t)&x86_userexcept_sysret)
			result = PERTASK_GET(this_x86_sysret_iret.ir_cs16);
	}
	return result;
}

/* get: `self->ir_Pflags' */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(FCALL irregs_rdflags)(struct irregs_kernel const *__restrict self) {
	uintptr_t result = ATOMIC_READ(self->ir_Pflags);
	if unlikely(result == 0) {
		uintptr_t pip = ATOMIC_READ(self->ir_Pip);
		if unlikely(pip == (uintptr_t)&x86_userexcept_sysret)
			result = PERTASK_GET(this_x86_sysret_iret.ir_Pflags);
	}
	return result;
}

/* get: `self->ir_rsp' */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(FCALL irregs_rdsp)(struct irregs_kernel const *__restrict self) {
#ifdef __x86_64__
	u64 result = ATOMIC_READ(self->ir_rsp);
	if (ADDR_ISKERN(result)) {
		u64 rip = ATOMIC_READ(self->ir_rip);
		if unlikely(rip == (u64)&x86_userexcept_sysret)
			result = PERTASK_GET(this_x86_sysret_iret.ir_rsp);
	}
	return result;
#else /* __x86_64__ */
	u32 result = (u32)((byte_t *)self + SIZEOF_IRREGS32_KERNEL);
	u16 cs = ATOMIC_READ(self->ir_cs16);
	if (cs & 3)
		goto is_user_iret;
#ifndef __I386_NO_VM86
	if (ATOMIC_READ(self->ir_eflags) & EFLAGS_VM)
		goto is_user_iret;
#endif /* !__I386_NO_VM86 */
	if (cs == SEGMENT_KERNEL_CODE) {
		u32 eip;
		eip = ATOMIC_READ(self->ir_eip);
		if unlikely(eip == (u32)&x86_userexcept_sysret) {
is_user_iret:
			result = *(u32 const *)result;
		}
	}
	return result;
#endif /* !__x86_64__ */
}

/* set: `self->ir_Pip' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrip)(struct irregs_kernel *__restrict self, uintptr_t value) {
	uintptr_t oldval;
	do {
		oldval = ATOMIC_READ(self->ir_Pip);
		if unlikely(oldval == (uintptr_t)&x86_userexcept_sysret) {
			PERTASK_SET(this_x86_sysret_iret.ir_Pip, value);
			break;
		}
	} while unlikely(!ATOMIC_CMPXCH_WEAK(self->ir_Pip, oldval, value));
}

/* set: `self->ir_cs' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrcs)(struct irregs_kernel *__restrict self, u16 value) {
	preemption_flag_t was;
	preemption_pushoff(&was);
	COMPILER_READ_BARRIER();
	if unlikely(self->ir_Pip == (uintptr_t)&x86_userexcept_sysret) {
		PERTASK_SET(this_x86_sysret_iret.ir_cs, value);
	} else {
		self->ir_cs = value;
	}
	COMPILER_WRITE_BARRIER();
	preemption_pop(&was);
}

/* set: `self->ir_Pflags' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrflags)(struct irregs_kernel *__restrict self, uintptr_t value) {
	preemption_flag_t was;
	preemption_pushoff(&was);
	COMPILER_READ_BARRIER();
	if unlikely(self->ir_Pip == (uintptr_t)&x86_userexcept_sysret) {
		PERTASK_SET(this_x86_sysret_iret.ir_Pflags, value);
	} else {
		self->ir_Pflags = value;
	}
	COMPILER_WRITE_BARRIER();
	preemption_pop(&was);
}

/* set: `self->ir_Pflags = (self->ir_Pflags & mask) | flags' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_mskflags)(struct irregs_kernel *__restrict self,
                               uintptr_t mask, uintptr_t flags) {
	preemption_flag_t was;
	preemption_pushoff(&was);
	COMPILER_READ_BARRIER();
	if unlikely(self->ir_Pip == (uintptr_t)&x86_userexcept_sysret) {
		uintptr_t newval;
		newval = PERTASK_GET(this_x86_sysret_iret.ir_Pflags);
		PERTASK_SET(this_x86_sysret_iret.ir_Pflags, (newval & mask) | flags);
	} else {
		self->ir_Pflags &= mask;
		self->ir_Pflags |= flags;
	}
	COMPILER_WRITE_BARRIER();
	preemption_pop(&was);
}



#ifdef __x86_64__

/* Check if `self' returns to compatibility-mode. */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL irregs_iscompat)(struct irregs const *__restrict self) {
	u16 cs = ATOMIC_READ(self->ir_cs16);
	if (SEGMENT_IS_VALID_USERCODE32(cs))
		return true;
	if (cs == SEGMENT_KERNEL_CODE) {
		u64 rip = ATOMIC_READ(self->ir_rip);
		if unlikely(rip == (u64)&x86_userexcept_sysret) {
			cs = PERTASK_GET(this_x86_sysret_iret.ir_cs16);
			if (SEGMENT_IS_VALID_USERCODE32(cs))
				return true;
		}
	}
	return false;
}

/* get: `self->ir_ss16' */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) u16
NOTHROW(FCALL irregs_rdss)(struct irregs const *__restrict self) {
	u16 result = ATOMIC_READ(self->ir_ss16);
	if (result == SEGMENT_KERNEL_DATA0) {
		u64 rip = ATOMIC_READ(self->ir_rip);
		if unlikely(rip == (u64)&x86_userexcept_sysret)
			result = PERTASK_GET(this_x86_sysret_iret.ir_ss16);
	}
	return result;
}

/* set: `self->ir_rsp' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrsp)(struct irregs *__restrict self, uintptr_t value) {
	preemption_flag_t was;
	preemption_pushoff(&was);
	COMPILER_READ_BARRIER();
	if unlikely(self->ir_rip == (u64)&x86_userexcept_sysret) {
		PERTASK_SET(this_x86_sysret_iret.ir_rsp, value);
	} else {
		self->ir_rsp = value;
	}
	COMPILER_WRITE_BARRIER();
	preemption_pop(&was);
}

/* set: `self->ir_ss' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrss)(struct irregs *__restrict self, u16 value) {
	preemption_flag_t was;
	preemption_pushoff(&was);
	COMPILER_READ_BARRIER();
	if unlikely(self->ir_rip == (u64)&x86_userexcept_sysret) {
		PERTASK_SET(this_x86_sysret_iret.ir_ss, (u64)value);
	} else {
		self->ir_ss = (u64)value;
	}
	COMPILER_WRITE_BARRIER();
	preemption_pop(&was);
}

#else /* __x86_64__ */

#ifndef __I386_NO_VM86
/* Check if `self' returns to user-space (return value is undefined if vm86). */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL irregs_isuser_novm86)(struct irregs_kernel const *__restrict self) {
	u16 cs;
	u32 eip;
	cs = ATOMIC_READ(self->ir_cs16);
	if (cs & 3)
		return true;
	eip = ATOMIC_READ(self->ir_eip);
	if unlikely(eip == (u32)&x86_userexcept_sysret)
		return true;
	return false;
}

PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL irregs_isvm86)(struct irregs_kernel const *__restrict self) {
	u32 eip, eflags;
	eflags = ATOMIC_READ(self->ir_eflags);
	if (eflags & EFLAGS_VM)
		return true;
	eip = ATOMIC_READ(self->ir_eip);
	if unlikely(eip == (u32)&x86_userexcept_sysret) {
		eflags = PERTASK_GET(this_x86_sysret_iret.ir_eflags);
		if (eflags & EFLAGS_VM)
			return true;
	}
	return false;
}
#endif /* !__I386_NO_VM86 */

#endif /* !__x86_64__ */



DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_TASK_REGISTERS_C */
