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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TASK_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TASK_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>

#include <hybrid/__atomic.h>
#include <hybrid/host.h>

#include <kos/kernel/cpu-state.h>

#ifdef __x86_64__
#include <kos/kernel/gdt.h>
#include <kernel/paging.h>
#endif /* __x86_64__ */

DECL_BEGIN



#ifdef __CC__
#define task_pause()    x86_pause()
FORCELOCAL NOBLOCK void
NOTHROW(KCALL x86_pause)(void) {
	__asm__ __volatile__("pause");
}

/* Preemption control. */
FORCELOCAL NOBLOCK void
NOTHROW(KCALL x86_interrupt_enable)(void) {
	COMPILER_BARRIER();
	__asm__ __volatile__("sti"
	                     :
	                     :
	                     : "memory");
	COMPILER_BARRIER();
}

FORCELOCAL NOBLOCK void
NOTHROW(KCALL x86_interrupt_enable_wait)(void) {
	COMPILER_BARRIER();
	__asm__ __volatile__("sti\n\t"
	                     "hlt"
	                     :
	                     :
	                     : "memory");
	COMPILER_BARRIER();
}

FORCELOCAL NOBLOCK void
NOTHROW(KCALL x86_interrupt_enable_wait_disable)(void) {
	COMPILER_BARRIER();
	__asm__ __volatile__("sti\n\t"
	                     "hlt\n\t"
	                     "cli"
	                     :
	                     :
	                     : "memory");
	COMPILER_BARRIER();
}

FORCELOCAL void
NOTHROW(KCALL x86_interrupt_wait)(void) {
	COMPILER_BARRIER();
	__asm__ __volatile__("hlt"
	                     :
	                     :
	                     : "memory");
	COMPILER_BARRIER();
}

FORCELOCAL ATTR_NORETURN void
NOTHROW(KCALL x86_interrupt_halt)(void) {
	COMPILER_BARRIER();
	__asm__ __volatile__("cli\n\t"
	                     "hlt"
	                     :
	                     :
	                     : "memory");
	COMPILER_BARRIER();
	__builtin_unreachable();
	COMPILER_BARRIER();
}

FORCELOCAL NOBLOCK void
NOTHROW(KCALL x86_interrupt_enable_p)(void) {
	COMPILER_BARRIER();
	__asm__ __volatile__("sti\n\t"
	                     "nop"
	                     :
	                     :
	                     : "memory");
	COMPILER_BARRIER();
}

FORCELOCAL NOBLOCK void
NOTHROW(KCALL x86_interrupt_disable)(void) {
	COMPILER_BARRIER();
	__asm__ __volatile__("cli"
	                     :
	                     :
	                     : "memory");
	COMPILER_BARRIER();
}

typedef uintptr_t pflag_t;

#ifdef __x86_64__
FORCELOCAL NOBLOCK pflag_t
NOTHROW(KCALL x86_interrupt_enabled)(void) {
	pflag_t result;
	__asm__ __volatile__("pushfq\n\t"
	                     "popq %0"
	                     : "=g" (result)
	                     :
	                     : "memory");
	return result & 0x00000200; /* EFLAGS_IF */
}

FORCELOCAL NOBLOCK pflag_t
NOTHROW(KCALL x86_interrupt_push)(void) {
	pflag_t result;
	COMPILER_BARRIER();
	__asm__ __volatile__("pushfq\n\t"
	                     "popq %0"
	                     : "=g" (result)
	                     :
	                     : "memory");
	COMPILER_BARRIER();
	return result & 0x00000200; /* EFLAGS_IF */
}

FORCELOCAL NOBLOCK pflag_t
NOTHROW(KCALL x86_interrupt_pushon)(void) {
	pflag_t result;
	COMPILER_BARRIER();
	__asm__ __volatile__("pushfq\n\t"
	                     "popq %0\n\t"
	                     "sti"
	                     : "=g" (result)
	                     :
	                     : "memory");
	COMPILER_BARRIER();
	return result & 0x00000200; /* EFLAGS_IF */
}

FORCELOCAL NOBLOCK pflag_t
NOTHROW(KCALL x86_interrupt_pushoff)(void) {
	pflag_t result;
	COMPILER_BARRIER();
	__asm__ __volatile__("pushfq\n\t"
	                     "popq %0\n\t"
	                     "cli"
	                     : "=g" (result)
	                     :
	                     : "memory");
	COMPILER_BARRIER();
	return result & 0x00000200; /* EFLAGS_IF */
}

FORCELOCAL NOBLOCK void
NOTHROW(KCALL x86_interrupt_pop)(pflag_t flag) {
	COMPILER_BARRIER();
	__asm__ __volatile__("pushq %0\n\t"
	                     "popfq"
	                     :
	                     : "g" (flag)
	                     : "memory", "cc");
	COMPILER_BARRIER();
}

#else /* __x86_64__ */

FORCELOCAL NOBLOCK pflag_t
NOTHROW(KCALL x86_interrupt_enabled)(void) {
	pflag_t result;
	__asm__ __volatile__("pushfl\n\t"
	                     "popl %0"
	                     : "=g" (result)
	                     :
	                     : "memory");
	return result & 0x00000200; /* EFLAGS_IF */
}

FORCELOCAL NOBLOCK pflag_t
NOTHROW(KCALL x86_interrupt_push)(void) {
	pflag_t result;
	COMPILER_BARRIER();
	__asm__ __volatile__("pushfl\n\t"
	                     "popl %0"
	                     : "=g" (result)
	                     :
	                     : "memory");
	COMPILER_BARRIER();
	return result & 0x00000200; /* EFLAGS_IF */
}

FORCELOCAL NOBLOCK pflag_t
NOTHROW(KCALL x86_interrupt_pushon)(void) {
	pflag_t result;
	COMPILER_BARRIER();
	__asm__ __volatile__("pushfl\n\t"
	                     "popl %0\n\t"
	                     "sti"
	                     : "=g" (result)
	                     :
	                     : "memory");
	COMPILER_BARRIER();
	return result & 0x00000200; /* EFLAGS_IF */
}

FORCELOCAL NOBLOCK pflag_t
NOTHROW(KCALL x86_interrupt_pushoff)(void) {
	pflag_t result;
	COMPILER_BARRIER();
	__asm__ __volatile__("pushfl\n\t"
	                     "popl %0\n\t"
	                     "cli"
	                     : "=g" (result)
	                     :
	                     : "memory");
	COMPILER_BARRIER();
	return result & 0x00000200; /* EFLAGS_IF */
}

FORCELOCAL NOBLOCK void
NOTHROW(KCALL x86_interrupt_pop)(pflag_t flag) {
	COMPILER_BARRIER();
	__asm__ __volatile__("pushl %0\n\t"
	                     "popfl"
	                     :
	                     : "g" (flag)
	                     : "memory", "cc");
	COMPILER_BARRIER();
}
#endif /* !__x86_64__ */

#define PREEMPTION_ENABLE()              x86_interrupt_enable()
#define PREEMPTION_ENABLE_WAIT()         x86_interrupt_enable_wait()
#define PREEMPTION_ENABLE_WAIT_DISABLE() x86_interrupt_enable_wait_disable()
#define PREEMPTION_ENABLE_P()            x86_interrupt_enable_p()
#define PREEMPTION_DISABLE()             x86_interrupt_disable()
#define PREEMPTION_ENABLED()             x86_interrupt_enabled()
#define PREEMPTION_PUSH()                x86_interrupt_push()
#define PREEMPTION_PUSHON()              x86_interrupt_pushon()
#define PREEMPTION_PUSHOFF()             x86_interrupt_pushoff()
#define PREEMPTION_WASENABLED(flag)    ((flag) & 0x00000200 /* EFLAGS_IF */)
#define PREEMPTION_WAIT()                x86_interrupt_wait()
#define PREEMPTION_HALT()                x86_interrupt_halt()
#define PREEMPTION_POP(flag)             x86_interrupt_pop(flag)


/* Entry point for IRET tails that have been re-directed for RPC.
 * Used to redirect how the kernel will return to user-space:
 * >> redirect_iret_to_execute_rpcs() {
 * >>     struct irregs_kernel *irr;
 * >>     PREEMPTION_DISABLE(); // Redirection is only
 * >>     if (IS_VM86_TASK) {
 * >>         irr = GET_KERNEL_STACK_BASE() - sizeof(struct irregs_vm86);
 * >>     } else {
 * >>         irr = GET_KERNEL_STACK_BASE() - sizeof(struct irregs_user);
 * >>     }
 * >>     memcpy(&PERTASK(this_x86_rpc_redirection_iret),irr,
 * >>            sizeof(struct irregs_kernel));
 * >>     irr->ir_eip    = &x86_rpc_user_redirectionS;
 * >>     irr->ir_cs     = SEGMENT_KERNEL_CS;
 * >>     irr->ir_eflags = 0; // Most importantly: disable interrupts
 * >> }
 * The `redirect_iret_to_execute_rpcs()' is then simply called
 * from another, asynchronous kernel RPC:
 * >> task_schedule_asynchronous_rpc(target,&redirect_iret_to_execute_rpcs);
 * Once entered, `x86_rpc_user_redirection()' will then restore the saved IRET
 * tail, before proceeding to serve _all_ pending RPC callbacks (s.a.:
 * the `Anytime the thread returns to user-space' row in `task_rpc()')
 * WARNING:
 *    Because of the redirection, in order to get/set any of the kernel IRET
 *    registers when inside of an interrupt/syscall with preemption enabled,
 *    you must always use the functions below, so-as to ensure that you don't
 *    re-override the RPC redirection, but modify the saved state when it
 *    comes to the IRET tail. */
FUNDEF void ASMCALL x86_rpc_user_redirection(void);


#ifdef __x86_64__

DATDEF ATTR_PERTASK struct irregs this_x86_rpc_redirection_iret;

#ifndef ___this_x86_kernel_psp0_defined
#define ___this_x86_kernel_psp0_defined 1
/* [== vm_node_getend(THIS_KERNEL_STACK)]
 * The per-task value written to `t_esp0' / `t_rsp0' during scheduler preemption. */
DATDEF ATTR_PERTASK uintptr_t const this_x86_kernel_psp0;
#endif /* !___this_x86_kernel_psp0_defined */

/* Return a pointer to the original user-space IRET tail of the calling thread.
 * This is the pointer to the IRET structure located at the base of the caller's kernel stack.
 * NOTE: The caller must ensure that preemption is disabled,
 *       and that `thread' is hosted by the calling CPU. */
#define x86_get_irregs(thread) \
	((struct irregs *)FORTASK(thread, *(uintptr_t *)&this_x86_kernel_psp0) - 1)

/* Safely modify the values of saved registers that may be modified by RPC redirection. */
FORCELOCAL NOBLOCK WUNUSED uintptr_t
NOTHROW(FCALL irregs_rdip)(struct irregs const *__restrict self) {
	uintptr_t result = __hybrid_atomic_load(self->ir_rip, __ATOMIC_ACQUIRE);
	if (result == (uintptr_t)&x86_rpc_user_redirection)
		result = PERTASK_GET(this_x86_rpc_redirection_iret.ir_rip);
	return result;
}

FORCELOCAL NOBLOCK WUNUSED u16
NOTHROW(FCALL irregs_rdcs)(struct irregs const *__restrict self) {
	/* NOTE: The read-order here is very important! */
	u16 result = __hybrid_atomic_load(self->ir_cs16, __ATOMIC_ACQUIRE);
	if (SEGMENT_IS_VALID_KERNCODE(result)) {
		uintptr_t eip = __hybrid_atomic_load(self->ir_rip, __ATOMIC_ACQUIRE);
		if (eip == (uintptr_t)&x86_rpc_user_redirection)
			result = PERTASK_GET(this_x86_rpc_redirection_iret.ir_cs16);
	}
	return result;
}

FORCELOCAL NOBLOCK WUNUSED uintptr_t
NOTHROW(FCALL irregs_rdflags)(struct irregs const *__restrict self) {
	/* NOTE: The read-order here is very important! */
	uintptr_t result = __hybrid_atomic_load(self->ir_rflags, __ATOMIC_ACQUIRE);
	uintptr_t eip    = __hybrid_atomic_load(self->ir_rip, __ATOMIC_ACQUIRE);
	if (eip == (uintptr_t)&x86_rpc_user_redirection)
		result = PERTASK_GET(this_x86_rpc_redirection_iret.ir_rflags);
	return result;
}

FORCELOCAL NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL irregs_isuser)(struct irregs const *__restrict self) {
	/* NOTE: The read-order here is very important! */
	u16 cs = __hybrid_atomic_load(self->ir_cs16, __ATOMIC_ACQUIRE);
	if (cs & 3)
		return 1;
	if (SEGMENT_IS_VALID_KERNCODE(cs)) {
		uintptr_t eip;
		eip = __hybrid_atomic_load(self->ir_rip, __ATOMIC_ACQUIRE);
		if (eip == (uintptr_t)&x86_rpc_user_redirection)
			return 1;
	}
	return 0;
}

FORCELOCAL NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL irregs_iscompat)(struct irregs const *__restrict self) {
	u16 cs = __hybrid_atomic_load(self->ir_cs16, __ATOMIC_ACQUIRE);
	if (cs == SEGMENT_USER_CODE32_RPL)
		return 1;
	if (SEGMENT_IS_VALID_KERNCODE(cs)) {
		uintptr_t eip;
		eip = __hybrid_atomic_load(self->ir_rip, __ATOMIC_ACQUIRE);
		if (eip == (uintptr_t)&x86_rpc_user_redirection) {
			cs = PERTASK_GET(this_x86_rpc_redirection_iret.ir_cs16);
			if (cs == SEGMENT_USER_CODE32_RPL)
				return 1;
		}
	}
	return 0;
}

FORCELOCAL NOBLOCK WUNUSED uintptr_t
NOTHROW(FCALL irregs_rdsp)(struct irregs const *__restrict self) {
	/* NOTE: The read-order here is very important! */
	uintptr_t result = __hybrid_atomic_load(self->ir_rsp, __ATOMIC_ACQUIRE);
	if (ADDR_ISKERN(result)) {
		uintptr_t eip = __hybrid_atomic_load(self->ir_rip, __ATOMIC_ACQUIRE);
		if (eip == (uintptr_t)&x86_rpc_user_redirection)
			result = PERTASK_GET(this_x86_rpc_redirection_iret.ir_rsp);
	}
	return result;
}

FORCELOCAL NOBLOCK WUNUSED u16
NOTHROW(FCALL irregs_rdss)(struct irregs const *__restrict self) {
	/* NOTE: The read-order here is very important! */
	u16 result = __hybrid_atomic_load(self->ir_ss16, __ATOMIC_ACQUIRE);
	if (SEGMENT_IS_VALID_KERNDATA(result)) {
		uintptr_t eip = __hybrid_atomic_load(self->ir_rip, __ATOMIC_ACQUIRE);
		if (eip == (uintptr_t)&x86_rpc_user_redirection)
			result = PERTASK_GET(this_x86_rpc_redirection_iret.ir_ss16);
	}
	return result;
}

FORCELOCAL NOBLOCK void
NOTHROW(FCALL irregs_wrip)(struct irregs *__restrict self, uintptr_t value) {
	uintptr_t oldval;
	do {
		oldval = __hybrid_atomic_load(self->ir_rip, __ATOMIC_ACQUIRE);
		if (oldval == (uintptr_t)&x86_rpc_user_redirection) {
			PERTASK_SET(this_x86_rpc_redirection_iret.ir_rip, value);
			break;
		}
	} while (!__hybrid_atomic_cmpxch_weak(self->ir_rip, oldval, value,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
}

/* Sadly, these last 2 can only be implemented by disabling preemption... */
FORCELOCAL NOBLOCK void
NOTHROW(FCALL irregs_wrcs)(struct irregs *__restrict self, u16 value) {
	pflag_t was = PREEMPTION_PUSHOFF();
	if (self->ir_rip == (uintptr_t)&x86_rpc_user_redirection) {
		PERTASK_SET(this_x86_rpc_redirection_iret.ir_cs, (uintptr_t)value);
	} else {
		self->ir_cs = (uintptr_t)value;
	}
	PREEMPTION_POP(was);
}

FORCELOCAL NOBLOCK void
NOTHROW(FCALL irregs_wrflags)(struct irregs *__restrict self, uintptr_t value) {
	pflag_t was = PREEMPTION_PUSHOFF();
	if (self->ir_rip == (uintptr_t)&x86_rpc_user_redirection) {
		PERTASK_SET(this_x86_rpc_redirection_iret.ir_rflags, value);
	} else {
		self->ir_rflags = value;
	}
	PREEMPTION_POP(was);
}

FORCELOCAL NOBLOCK void
NOTHROW(FCALL irregs_mskflags)(struct irregs *__restrict self, uintptr_t mask, uintptr_t flags) {
	pflag_t was = PREEMPTION_PUSHOFF();
	if (self->ir_rip == (uintptr_t)&x86_rpc_user_redirection) {
		uintptr_t newval;
		newval = PERTASK_GET(this_x86_rpc_redirection_iret.ir_rflags);
		PERTASK_SET(this_x86_rpc_redirection_iret.ir_rflags, (newval & mask) | flags);
	} else {
		self->ir_rflags &= mask;
		self->ir_rflags |= flags;
	}
	PREEMPTION_POP(was);
}

FORCELOCAL NOBLOCK void
NOTHROW(FCALL irregs_wrsp)(struct irregs *__restrict self, uintptr_t value) {
	pflag_t was = PREEMPTION_PUSHOFF();
	if (self->ir_rip == (uintptr_t)&x86_rpc_user_redirection) {
		PERTASK_SET(this_x86_rpc_redirection_iret.ir_rsp, value);
	} else {
		self->ir_rsp = value;
	}
	PREEMPTION_POP(was);
}

FORCELOCAL NOBLOCK void
NOTHROW(FCALL irregs_wrss)(struct irregs *__restrict self, u16 value) {
	pflag_t was = PREEMPTION_PUSHOFF();
	if (self->ir_rip == (uintptr_t)&x86_rpc_user_redirection) {
		PERTASK_SET(this_x86_rpc_redirection_iret.ir_ss, (uintptr_t)value);
	} else {
		self->ir_ss = (uintptr_t)value;
	}
	PREEMPTION_POP(was);
}

#else /* __x86_64__ */

DATDEF ATTR_PERTASK struct irregs_kernel this_x86_rpc_redirection_iret;

struct irregs_user;

/* Return a pointer to the original user-space IRET tail of the calling thread.
 * This is the pointer to the IRET structure located at the base of the caller's kernel stack.
 * NOTE: The caller must ensure that preemption is disabled,
 *       and that `thread' is hosted by the calling CPU. */
FUNDEF ATTR_CONST ATTR_RETNONNULL NOBLOCK NONNULL((1)) struct irregs_user *
NOTHROW(FCALL x86_get_irregs)(struct task const *__restrict thread);

/* Safely modify the values of saved registers that may be modified by RPC redirection. */
FORCELOCAL NOBLOCK WUNUSED uintptr_t
NOTHROW(FCALL irregs_rdip)(struct irregs_kernel const *__restrict self) {
	uintptr_t result = __hybrid_atomic_load(self->ir_eip, __ATOMIC_ACQUIRE);
	if (result == (uintptr_t)&x86_rpc_user_redirection)
		result = PERTASK_GET(this_x86_rpc_redirection_iret.ir_eip);
	return result;
}

FORCELOCAL NOBLOCK WUNUSED u16
NOTHROW(FCALL irregs_rdcs)(struct irregs_kernel const *__restrict self) {
	/* NOTE: The read-order here is very important! */
	u16 result    = __hybrid_atomic_load(self->ir_cs16, __ATOMIC_ACQUIRE);
	uintptr_t eip = __hybrid_atomic_load(self->ir_eip, __ATOMIC_ACQUIRE);
	if (eip == (uintptr_t)&x86_rpc_user_redirection)
		result = PERTASK_GET(this_x86_rpc_redirection_iret.ir_cs16);
	return result;
}

FORCELOCAL NOBLOCK WUNUSED uintptr_t
NOTHROW(FCALL irregs_rdflags)(struct irregs_kernel const *__restrict self) {
	/* NOTE: The read-order here is very important! */
	uintptr_t result = __hybrid_atomic_load(self->ir_eflags, __ATOMIC_ACQUIRE);
	uintptr_t eip    = __hybrid_atomic_load(self->ir_eip, __ATOMIC_ACQUIRE);
	if (eip == (uintptr_t)&x86_rpc_user_redirection)
		result = PERTASK_GET(this_x86_rpc_redirection_iret.ir_eflags);
	return result;
}

FORCELOCAL NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL irregs_isuser)(struct irregs_kernel const *__restrict self) {
	/* NOTE: The read-order here is very important! */
	u16 cs;
	uintptr_t eflags, eip;
	cs = __hybrid_atomic_load(self->ir_cs16, __ATOMIC_ACQUIRE);
	if (cs & 3)
		return 1;
	eflags = __hybrid_atomic_load(self->ir_eflags, __ATOMIC_ACQUIRE);
	if (eflags & 0x20000)
		return 1;
	eip = __hybrid_atomic_load(self->ir_eip, __ATOMIC_ACQUIRE);
	if (eip == (uintptr_t)&x86_rpc_user_redirection)
		return 1;
	return 0;
}

/* Not guarantied to return `1' for vm86 interrupt registers. */
FORCELOCAL NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL irregs_isuser_novm86)(struct irregs_kernel const *__restrict self) {
	/* NOTE: The read-order here is very important! */
	u16 cs;
	uintptr_t eip;
	cs = __hybrid_atomic_load(self->ir_cs16, __ATOMIC_ACQUIRE);
	if (cs & 3)
		return 1;
	eip = __hybrid_atomic_load(self->ir_eip, __ATOMIC_ACQUIRE);
	if (eip == (uintptr_t)&x86_rpc_user_redirection)
		return 1;
	return 0;
}

FORCELOCAL NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL irregs_isvm86)(struct irregs_kernel const *__restrict self) {
	/* NOTE: The read-order here is very important! */
	uintptr_t eip, eflags;
	eflags = __hybrid_atomic_load(self->ir_eflags, __ATOMIC_ACQUIRE);
	if (eflags & 0x20000)
		return 1;
	eip = __hybrid_atomic_load(self->ir_eip, __ATOMIC_ACQUIRE);
	if (eip == (uintptr_t)&x86_rpc_user_redirection) {
		eflags = PERTASK_GET(this_x86_rpc_redirection_iret.ir_eflags);
		if (eflags & 0x20000)
			return 1;
	}
	return 0;
}

FORCELOCAL NOBLOCK WUNUSED uintptr_t
NOTHROW(FCALL irregs_rdsp)(struct irregs_kernel const *__restrict self) {
	/* NOTE: The read-order here is very important! */
	uintptr_t result = (uintptr_t)(self + 1);
	u16 cs           = __hybrid_atomic_load(self->ir_cs16, __ATOMIC_ACQUIRE);
	uintptr_t eflags = __hybrid_atomic_load(self->ir_eflags, __ATOMIC_ACQUIRE);
	uintptr_t eip    = __hybrid_atomic_load(self->ir_eip, __ATOMIC_ACQUIRE);
	if (eip == (uintptr_t)&x86_rpc_user_redirection || (cs & 3) || (eflags & 0x20000))
		result = *(u32 *)(self + 1);
	return result;
}

FORCELOCAL NOBLOCK void
NOTHROW(FCALL irregs_wrip)(struct irregs_kernel *__restrict self, uintptr_t value) {
	uintptr_t oldval;
	do {
		oldval = __hybrid_atomic_load(self->ir_eip, __ATOMIC_ACQUIRE);
		if (oldval == (uintptr_t)&x86_rpc_user_redirection) {
			PERTASK_SET(this_x86_rpc_redirection_iret.ir_eip, value);
			break;
		}
	} while (!__hybrid_atomic_cmpxch_weak(self->ir_eip, oldval, value, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
}

/* Sadly, these last 2 can only be implemented by disabling preemption... */
FORCELOCAL NOBLOCK void
NOTHROW(FCALL irregs_wrcs)(struct irregs_kernel *__restrict self, u16 value) {
	pflag_t was = PREEMPTION_PUSHOFF();
	if (self->ir_eip == (uintptr_t)&x86_rpc_user_redirection) {
		PERTASK_SET(this_x86_rpc_redirection_iret.ir_cs, (uintptr_t)value);
	} else {
		self->ir_cs = (uintptr_t)value;
	}
	PREEMPTION_POP(was);
}

FORCELOCAL NOBLOCK void
NOTHROW(FCALL irregs_wrflags)(struct irregs_kernel *__restrict self, uintptr_t value) {
	pflag_t was = PREEMPTION_PUSHOFF();
	if (self->ir_eip == (uintptr_t)&x86_rpc_user_redirection) {
		PERTASK_SET(this_x86_rpc_redirection_iret.ir_eflags, value);
	} else {
		self->ir_eflags = value;
	}
	PREEMPTION_POP(was);
}

FORCELOCAL NOBLOCK void
NOTHROW(FCALL irregs_mskflags)(struct irregs_kernel *__restrict self, uintptr_t mask, uintptr_t flags) {
	pflag_t was = PREEMPTION_PUSHOFF();
	if (self->ir_eip == (uintptr_t)&x86_rpc_user_redirection) {
		uintptr_t newval;
		newval = PERTASK_GET(this_x86_rpc_redirection_iret.ir_eflags);
		PERTASK_SET(this_x86_rpc_redirection_iret.ir_eflags, (newval & mask) | flags);
	} else {
		self->ir_eflags &= mask;
		self->ir_eflags |= flags;
	}
	PREEMPTION_POP(was);
}

#endif /* !__x86_64__ */


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TASK_H */
