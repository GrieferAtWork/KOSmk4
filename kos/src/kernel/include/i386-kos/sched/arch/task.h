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

/* Inline optimizations for scheduler functions implemented via assembly.
 * Using  this, we can help GCC generate  better code by telling it which
 * registers  get clobbered by  which function, allowing  it to keep more
 * variables in registers across calls to these functions (which is quite
 * useful, considering that these functions often appear in the middle of
 * long functions needing to use the  same objects both before and  after
 * the call) */
#ifndef __INTELLISENSE__
#ifdef __NO_XBLOCK
#define task_pause() __x86_task_pause()
FORCELOCAL ATTR_ARTIFICIAL void NOTHROW(__x86_task_pause)(void) {
	__asm__("pause");
}
#define task_yield_nx() __x86_task_yield_nx()
FORCELOCAL ATTR_ARTIFICIAL __BOOL NOTHROW(__x86_task_yield_nx)(void) {
	__register __BOOL __res;
#ifdef __x86_64__
	__asm__("call task_yield_nx" : "=a" (__res) : : "%rcx", "memory");
#else /* __x86_64__ */
	__asm__("call task_yield_nx" : "=a" (__res) : : "memory");
#endif /* !__x86_64__ */
	return __res;
}
#define task_tryyield() __x86_task_tryyield()
FORCELOCAL ATTR_ARTIFICIAL unsigned int NOTHROW(__x86_task_tryyield)(void) {
	__register unsigned int __res;
#ifdef __x86_64__
	__asm__("call task_tryyield" : "=a" (__res) : : "%rcx", "memory");
#else /* __x86_64__ */
	__asm__("call task_tryyield" : "=a" (__res) : : "memory");
#endif /* !__x86_64__ */
	return __res;
}
#define task_tryyield_or_pause() __x86_task_tryyield_or_pause()
FORCELOCAL ATTR_ARTIFICIAL unsigned int NOTHROW(__x86_task_tryyield_or_pause)(void) {
	__register unsigned int __res;
#ifdef __x86_64__
	__asm__("call task_tryyield_or_pause" : "=a" (__res) : : "%rcx", "memory");
#else /* __x86_64__ */
	__asm__("call task_tryyield_or_pause" : "=a" (__res) : : "memory");
#endif /* !__x86_64__ */
	return __res;
}
#else /* __NO_XBLOCK */
#define task_pause() __XBLOCK({ __asm__("pause"); (void)0; })
#ifdef __x86_64__
#define task_yield_nx()          __XBLOCK({ __register __BOOL __ty_res; __asm__("call task_yield_nx" : "=a" (__ty_res) : : "%rcx", "memory"); __XRETURN __ty_res; })
#define task_tryyield()          __XBLOCK({ __register unsigned int __ty_res; __asm__("call task_tryyield" : "=a" (__ty_res) : : "%rcx", "memory"); __XRETURN __ty_res; })
#define task_tryyield_or_pause() __XBLOCK({ __register unsigned int __ty_res; __asm__("call task_tryyield_or_pause" : "=a" (__ty_res) : : "%rcx", "memory"); __XRETURN __ty_res; })
#else /* __x86_64__ */
#define task_yield_nx()          __XBLOCK({ __register __BOOL __ty_res; __asm__("call task_yield_nx" : "=a" (__ty_res) : : "memory"); __XRETURN __ty_res; })
#define task_tryyield()          __XBLOCK({ __register unsigned int __ty_res; __asm__("call task_tryyield" : "=a" (__ty_res) : : "memory"); __XRETURN __ty_res; })
#define task_tryyield_or_pause() __XBLOCK({ __register unsigned int __ty_res; __asm__("call task_tryyield_or_pause" : "=a" (__ty_res) : : "memory"); __XRETURN __ty_res; })
#endif /* !__x86_64__ */
#endif /* !__NO_XBLOCK */

#define task_yield() __x86_task_yield()
/* This wrapper cannot be implemented using __XBLOCK due to a GCC bug
 * that causes `__asm__ __volatile__' by  itself to be considered  as
 * NOTHROW, forcing one to wrap by an inline function:
 *     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=94357
 */
FORCELOCAL ATTR_ARTIFICIAL void (__x86_task_yield)(void) {
#ifdef __x86_64__
	__asm__ __volatile__("call task_yield" : : : "%rax", "%rcx", "memory");
#else /* __x86_64__ */
	__asm__ __volatile__("call task_yield" : : : "%eax", "memory");
#endif /* !__x86_64__ */
}
#endif /* !__INTELLISENSE__ */



/* Preemption control. */
typedef uintptr_t pflag_t;
#define PREEMPTION_WASENABLED(flag) ((flag) & 0x200 /* EFLAGS_IF */)
#define PREEMPTION_ENABLED_VALUE  0x200
#define PREEMPTION_DISABLED_VALUE 0

#ifdef __NO_XBLOCK
#define PREEMPTION_ENABLE()              __x86_preemption_enable()
#define PREEMPTION_ENABLE_WAIT()         __x86_preemption_enable_wait()
#define PREEMPTION_ENABLE_WAIT_DISABLE() __x86_preemption_enable_wait_disable()
#define PREEMPTION_ENABLE_P()            __x86_preemption_enable_p()
#define PREEMPTION_DISABLE()             __x86_preemption_disable()
#define PREEMPTION_WAIT()                __x86_preemption_wait()
#define PREEMPTION_HALT()                __x86_preemption_halt()

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(__x86_preemption_enable)(void) {
	__COMPILER_BARRIER();
	__asm__ __volatile__("sti" : : : "memory");
	__COMPILER_BARRIER();
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(__x86_preemption_enable_wait)(void) {
	__COMPILER_BARRIER();
	__asm__ __volatile__("sti\n\t"
	                     "hlt"
	                     : : : "memory");
	__COMPILER_BARRIER();
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(__x86_preemption_enable_wait_disable)(void) {
	__COMPILER_BARRIER();
	__asm__ __volatile__("sti\n\t"
	                     "hlt\n\t"
	                     "cli"
	                     : : : "memory");
	__COMPILER_BARRIER();
}

FORCELOCAL ATTR_ARTIFICIAL void
NOTHROW(__x86_preemption_wait)(void) {
	__COMPILER_BARRIER();
	__asm__ __volatile__("hlt"
	                     : : : "memory");
	__COMPILER_BARRIER();
}

FORCELOCAL ATTR_ARTIFICIAL ATTR_NORETURN void
NOTHROW(__x86_preemption_halt)(void) {
	__COMPILER_BARRIER();
	__asm__ __volatile__("cli\n\t"
	                     "hlt"
	                     : : : "memory");
	__COMPILER_BARRIER();
	__builtin_unreachable();
	__COMPILER_BARRIER();
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(__x86_preemption_enable_p)(void) {
	__COMPILER_BARRIER();
	__asm__ __volatile__("sti\n\t"
	                     "nop"
	                     : : : "memory");
	__COMPILER_BARRIER();
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(__x86_preemption_disable)(void) {
	__COMPILER_BARRIER();
	__asm__ __volatile__("cli" : : : "memory");
	__COMPILER_BARRIER();
}

#define PREEMPTION_ENABLED() (__x86_preemption_enabled() & 0x00000200 /* EFLAGS_IF */)
#define PREEMPTION_PUSH()    __x86_preemption_push()
#define PREEMPTION_PUSHON()  __x86_preemption_pushon()
#define PREEMPTION_PUSHOFF() __x86_preemption_pushoff()
#define PREEMPTION_POP(flag) __x86_preemption_pop(flag)
FORCELOCAL NOBLOCK WUNUSED pflag_t
NOTHROW(__x86_preemption_enabled)(void) {
	pflag_t result;
	__asm__ __volatile__(""
#ifdef __x86_64__
	                     "pushfq\n\t"
	                     "popq %q0"
#else /* __x86_64__ */
	                     "pushfl\n\t"
	                     "popl %k0"
#endif /* !__x86_64__ */
	                     : "=g" (result)
	                     :
	                     : "memory");
	return result;
}

FORCELOCAL NOBLOCK WUNUSED pflag_t
NOTHROW(__x86_preemption_push)(void) {
	pflag_t result;
	__COMPILER_BARRIER();
	__asm__ __volatile__(""
#ifdef __x86_64__
	                     "pushfq\n\t"
	                     "popq %q0"
#else /* __x86_64__ */
	                     "pushfl\n\t"
	                     "popl %k0"
#endif /* !__x86_64__ */
	                     : "=g" (result)
	                     :
	                     : "memory");
	__COMPILER_BARRIER();
	return result;
}

FORCELOCAL NOBLOCK WUNUSED pflag_t
NOTHROW(__x86_preemption_pushon)(void) {
	pflag_t result;
	__COMPILER_BARRIER();
	__asm__ __volatile__(""
#ifdef __x86_64__
	                     "pushfq\n\t"
	                     "popq %q0\n\t"
#else /* __x86_64__ */
	                     "pushfl\n\t"
	                     "popl %k0\n\t"
#endif /* !__x86_64__ */
	                     "sti"
	                     : "=g" (result)
	                     :
	                     : "memory");
	__COMPILER_BARRIER();
	return result;
}

FORCELOCAL NOBLOCK WUNUSED pflag_t
NOTHROW(__x86_preemption_pushoff)(void) {
	pflag_t result;
	__COMPILER_BARRIER();
	__asm__ __volatile__(""
#ifdef __x86_64__
	                     "pushfq\n\t"
	                     "popq %q0\n\t"
#else /* __x86_64__ */
	                     "pushfl\n\t"
	                     "popl %k0\n\t"
#endif /* !__x86_64__ */
	                     "cli"
	                     : "=g" (result)
	                     :
	                     : "memory");
	__COMPILER_BARRIER();
	return result;
}

FORCELOCAL NOBLOCK void
NOTHROW(__x86_preemption_pop)(pflag_t flag) {
	__COMPILER_BARRIER();
	__asm__ __volatile__(""
#ifdef __x86_64__
	                     "pushq %q0\n\t"
	                     "popfq"
#else /* __x86_64__ */
	                     "pushl %k0\n\t"
	                     "popfl"
#endif /* !__x86_64__ */
	                     :
	                     : "g" (flag)
	                     : "memory"
	                     , "cc");
	__COMPILER_BARRIER();
}
#else /* __NO_XBLOCK */
#define PREEMPTION_ENABLE()              __XBLOCK({ __COMPILER_BARRIER(); __asm__ __volatile__("sti" : : : "memory"); __COMPILER_BARRIER(); (void)0; })
#define PREEMPTION_ENABLE_WAIT()         __XBLOCK({ __COMPILER_BARRIER(); __asm__ __volatile__("sti\n\thlt" : : : "memory"); __COMPILER_BARRIER(); (void)0; })
#define PREEMPTION_ENABLE_WAIT_DISABLE() __XBLOCK({ __COMPILER_BARRIER(); __asm__ __volatile__("sti\n\thlt\n\tcli" : : : "memory"); __COMPILER_BARRIER(); (void)0; })
#define PREEMPTION_WAIT()                __XBLOCK({ __COMPILER_BARRIER(); __asm__ __volatile__("hlt" : : : "memory"); __COMPILER_BARRIER(); (void)0; })
#define PREEMPTION_HALT()                __XBLOCK({ __COMPILER_BARRIER(); __asm__ __volatile__("cli\n\thlt" : : : "memory"); __COMPILER_BARRIER(); __builtin_unreachable(); __COMPILER_BARRIER(); (void)0; })
#define PREEMPTION_ENABLE_P()            __XBLOCK({ __COMPILER_BARRIER(); __asm__ __volatile__("sti\n\t" "nop" : : : "memory"); __COMPILER_BARRIER(); (void)0; })
#define PREEMPTION_DISABLE()             __XBLOCK({ __COMPILER_BARRIER(); __asm__ __volatile__("cli" : : : "memory"); __COMPILER_BARRIER(); (void)0; })
#ifdef __x86_64__
#define PREEMPTION_ENABLED()             __XBLOCK({ pflag_t __Pflags; __asm__ __volatile__("pushfq\n\tpopq %q0" : "=g" (__Pflags) : : "memory"); __XRETURN __Pflags & 0x00000200 /* EFLAGS_IF */; })
#define PREEMPTION_PUSH()                __XBLOCK({ pflag_t __Pflags; __COMPILER_BARRIER(); __asm__ __volatile__("pushfq\n\tpopq %q0" : "=g" (__Pflags) : : "memory"); __COMPILER_BARRIER(); __XRETURN __Pflags; })
#define PREEMPTION_PUSHON()              __XBLOCK({ pflag_t __Pflags; __COMPILER_BARRIER(); __asm__ __volatile__("pushfq\n\tpopq %q0\n\tsti" : "=g" (__Pflags) : : "memory"); __COMPILER_BARRIER(); __XRETURN __Pflags; })
#define PREEMPTION_PUSHOFF()             __XBLOCK({ pflag_t __Pflags; __COMPILER_BARRIER(); __asm__ __volatile__("pushfq\n\tpopq %q0\n\tcli" : "=g" (__Pflags) : : "memory"); __COMPILER_BARRIER(); __XRETURN __Pflags; })
#define PREEMPTION_POP(flag)             __XBLOCK({ __COMPILER_BARRIER(); __asm__ __volatile__("pushq %q0\n\tpopfq" : : "g" (flag) : "memory", "cc"); __COMPILER_BARRIER(); (void)0; })
#else /* __x86_64__ */
#define PREEMPTION_ENABLED()             __XBLOCK({ pflag_t __Pflags; __asm__ __volatile__("pushfl\n\tpopl %k0" : "=g" (__Pflags) : : "memory"); __XRETURN __Pflags & 0x00000200 /* EFLAGS_IF */; })
#define PREEMPTION_PUSH()                __XBLOCK({ pflag_t __Pflags; __COMPILER_BARRIER(); __asm__ __volatile__("pushfl\n\tpopl %k0" : "=g" (__Pflags) : : "memory"); __COMPILER_BARRIER(); __XRETURN __Pflags; })
#define PREEMPTION_PUSHON()              __XBLOCK({ pflag_t __Pflags; __COMPILER_BARRIER(); __asm__ __volatile__("pushfl\n\tpopl %k0\n\tsti" : "=g" (__Pflags) : : "memory"); __COMPILER_BARRIER(); __XRETURN __Pflags; })
#define PREEMPTION_PUSHOFF()             __XBLOCK({ pflag_t __Pflags; __COMPILER_BARRIER(); __asm__ __volatile__("pushfl\n\tpopl %k0\n\tcli" : "=g" (__Pflags) : : "memory"); __COMPILER_BARRIER(); __XRETURN __Pflags; })
#define PREEMPTION_POP(flag)             __XBLOCK({ __COMPILER_BARRIER(); __asm__ __volatile__("pushl %k0\n\tpopfl" : : "g" (flag) : "memory", "cc"); __COMPILER_BARRIER(); (void)0; })
#endif /* !__x86_64__ */
#endif /* !__NO_XBLOCK */


/* Entry point for IRET tails that have been re-directed for RPC.
 * Used  to redirect  how the  kernel will  return to user-space:
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
 * >> task_schedule_asynchronous_rpc(target, &redirect_iret_to_execute_rpcs);
 * Once entered, `x86_rpc_user_redirection()' will then restore the saved IRET
 * tail,  before  proceeding  to  serve  _all_  pending  RPC  callbacks (s.a.:
 * the `Anytime the thread returns to user-space' row in `task_rpc()')
 * WARNING:
 *    Because of the redirection, in order to get/set any of the kernel  IRET
 *    registers when inside of an interrupt/syscall with preemption  enabled,
 *    you must always use the functions below, so-as to ensure that you don't
 *    re-override the RPC  redirection, but  modify the saved  state when  it
 *    comes to the IRET tail. */
FUNDEF void ASMCALL x86_rpc_user_redirection(void);


#ifdef __x86_64__

DATDEF ATTR_PERTASK struct irregs this_x86_rpc_redirection_iret;

#ifndef ___this_x86_kernel_psp0_defined
#define ___this_x86_kernel_psp0_defined 1
/* [== mnode_getendaddr(THIS_KERNEL_STACK)]
 * The per-task value written to `t_psp0' during scheduler preemption. */
DATDEF ATTR_PERTASK uintptr_t const this_x86_kernel_psp0;
#endif /* !___this_x86_kernel_psp0_defined */

/* Return  a  pointer  to   the  original  user-space  IRET   tail  of  the  calling   thread.
 * This is the pointer to the IRET structure located at the base of the caller's kernel stack.
 * NOTE: The caller must ensure that preemption is disabled,
 *       and that  `thread' is  hosted by  the calling  CPU. */
#define x86_get_irregs(thread) \
	((struct irregs *)FORTASK(thread, *(uintptr_t *)&this_x86_kernel_psp0) - 1)

#else /* __x86_64__ */

DATDEF ATTR_PERTASK struct irregs_kernel this_x86_rpc_redirection_iret;

struct irregs_user;

/* Return  a  pointer  to   the  original  user-space  IRET   tail  of  the  calling   thread.
 * This is the pointer to the IRET structure located at the base of the caller's kernel stack.
 * NOTE: The caller must ensure that preemption is disabled,
 *       and that  `thread' is  hosted by  the calling  CPU. */
FUNDEF ATTR_CONST ATTR_RETNONNULL NOBLOCK NONNULL((1)) struct irregs_user *
NOTHROW(FCALL x86_get_irregs)(struct task const *__restrict thread);
#endif /* !__x86_64__ */


/* Safely get/set the values of saved registers that may be modified by RPC redirection. */

/* Check if `self' returns to user-space. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL irregs_isuser)(struct irregs_kernel const *__restrict self);

/* get:`self->ir_pip' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(FCALL irregs_rdip)(struct irregs_kernel const *__restrict self);

/* get:`self->ir_cs16' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) u16
NOTHROW(FCALL irregs_rdcs)(struct irregs_kernel const *__restrict self);

/* get:`self->ir_pflags' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(FCALL irregs_rdflags)(struct irregs_kernel const *__restrict self);

/* set:`self->ir_pip' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrip)(struct irregs_kernel *__restrict self, uintptr_t value);

/* set:`self->ir_cs' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrcs)(struct irregs_kernel *__restrict self, u16 value);

/* set:`self->ir_pflags' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrflags)(struct irregs_kernel *__restrict self, uintptr_t value);

/* set:`self->ir_pflags = (self->ir_pflags & mask) | flags' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_mskflags)(struct irregs_kernel *__restrict self,
                               uintptr_t mask, uintptr_t flags);

/* get:`self->ir_psp' (with accounting for kernel-space return-sp on i386) */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(FCALL irregs_rdsp)(struct irregs_kernel const *__restrict self);


#ifdef __x86_64__
/* Check if `self' returns to compatibility-mode. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL irregs_iscompat)(struct irregs const *__restrict self);

/* get:`self->ir_ss16' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) u16
NOTHROW(FCALL irregs_rdss)(struct irregs const *__restrict self);

/* set:`self->ir_rsp' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrsp)(struct irregs *__restrict self, uintptr_t value);

/* set:`self->ir_ss' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrss)(struct irregs *__restrict self, u16 value);
#else /* __x86_64__ */

/* Check if `self' returns to user-space (but returns `false' if it returns to vm86). */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL irregs_isuser_novm86)(struct irregs_kernel const *__restrict self);

/* Check if `self' returns to vm86. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL irregs_isvm86)(struct irregs_kernel const *__restrict self);
#endif /* !__x86_64__ */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TASK_H */
