/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
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
#include <kos/kernel/x86/gdt.h>
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
#ifdef __CHECKER__
#define task_pause()             (void)0
#define task_yield_nx()          (__builtin_tag_get("NOPREEMPT") ? !1 : __builtin_rvoid(!0))
#define task_tryyield()          (__builtin_tag_get("NOPREEMPT") ? TASK_TRYYIELD_PREEMPTION_DISABLED : __builtin_rvoid(0u))
#define task_tryyield_or_pause() (__builtin_tag_get("NOPREEMPT") ? TASK_TRYYIELD_PREEMPTION_DISABLED : __builtin_rvoid(0u))
#elif defined(__NO_XBLOCK)
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
 * @throws: E_WOULDBLOCK_PREEMPTED: When preemption is disabled.
 */
FORCELOCAL ATTR_ARTIFICIAL void (__x86_task_yield)(void) THROWS(E_WOULDBLOCK_PREEMPTED) {
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

#ifdef __CHECKER__
#define PREEMPTION_ENABLE()              __builtin_tag_set("NOPREEMPT", 0)
#define PREEMPTION_ENABLE_WAIT()         __builtin_tag_set("NOPREEMPT", 0)
#define PREEMPTION_ENABLE_WAIT_DISABLE() __builtin_tag_set("NOPREEMPT", 1)
#define PREEMPTION_WAIT()                (void)0
#define PREEMPTION_HALT()                (__builtin_tag_set("NOPREEMPT", 1), __builtin_unreachable())
#define PREEMPTION_ENABLE_P()            __builtin_tag_set("NOPREEMPT", 0)
#define PREEMPTION_DISABLE()             __builtin_tag_set("NOPREEMPT", 1)
#define PREEMPTION_ENABLED()             (__builtin_tag_get("NOPREEMPT") ? 0 : PREEMPTION_ENABLED_VALUE)
#define PREEMPTION_PUSH()                (__builtin_tag_get("NOPREEMPT") ? 0 : PREEMPTION_ENABLED_VALUE)
#define PREEMPTION_PUSHON()              (__builtin_tag_get("NOPREEMPT") ? (__builtin_tag_set("NOPREEMPT", 0), 0) : PREEMPTION_ENABLED_VALUE)
#define PREEMPTION_PUSHOFF()             (__builtin_tag_get("NOPREEMPT") ? 0 : (__builtin_tag_set("NOPREEMPT", 0), PREEMPTION_ENABLED_VALUE))
#define PREEMPTION_POP(flag)             __builtin_tag_set("NOPREEMPT", !(flag))
#elif defined(__NO_XBLOCK)
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



/* Entry point for IRET tails that have been re-directed for sysret.
 * Used to  redirect  how  the kernel  will  return  to  user-space:
 * >> redirect_iret_for_sysret() {
 * >>     struct irregs_kernel *irr;
 * >>     PREEMPTION_DISABLE(); // Redirection is only
 * >> #ifndef __I386_NO_VM86
 * >>     if (IS_VM86_TASK) {
 * >>         irr = GET_KERNEL_STACK_BASE() - sizeof(struct irregs_vm86);
 * >>     } else
 * >> #endif // !__I386_NO_VM86
 * >>     {
 * >>         irr = GET_KERNEL_STACK_BASE() - sizeof(struct irregs_user);
 * >>     }
 * >>     memcpy(&PERTASK(this_x86_sysret_iret), irr,
 * >>            sizeof(struct irregs_kernel));
 * >>     irr->ir_eip    = &x86_userexcept_sysret;
 * >>     irr->ir_cs     = SEGMENT_KERNEL_CS;
 * >>     irr->ir_eflags = 0; // Most importantly: disable interrupts
 * >> }
 * WARNING:
 *    Because of the redirection, in order to get/set any of the kernel  IRET
 *    registers when inside of an interrupt/syscall with preemption  enabled,
 *    you must always use the functions below, so-as to ensure that you don't
 *    re-override  the sysret redirection, but modify the saved state when it
 *    comes to the IRET tail. */
FUNDEF void ASMCALL x86_userexcept_sysret(void);


#ifdef __x86_64__

DATDEF ATTR_PERTASK struct irregs this_x86_sysret_iret;

#ifndef ___this_x86_kernel_psp0_defined
#define ___this_x86_kernel_psp0_defined
/* [== mnode_getendaddr(THIS_KERNEL_STACK)]
 * The per-task value written to `t_psp0' during scheduler preemption. */
DATDEF ATTR_PERTASK uintptr_t const this_x86_kernel_psp0;
#endif /* !___this_x86_kernel_psp0_defined */

/* Return a pointer to the original user-space IRET tail of the given thread.
 * This is the pointer to the IRET structure located at the base of the given
 * thread's kernel stack.
 * NOTE: The caller must ensure that `thread == THIS_TASK', or that preemption
 *       is disabled, and that `thread' is hosted by the caller's current CPU. */
#define x86_get_irregs(thread) \
	((struct irregs *)FORTASK(thread, *(uintptr_t *)&this_x86_kernel_psp0) - 1)

#else /* __x86_64__ */

DATDEF ATTR_PERTASK struct irregs_kernel this_x86_sysret_iret;

struct irregs_user;

/* Return a pointer to the original user-space IRET tail of the given thread.
 * This is the pointer to the IRET structure located at the base of the given
 * thread's kernel stack.
 * NOTE: The caller must ensure that `thread == THIS_TASK', or that preemption
 *       is disabled, and that `thread' is hosted by the caller's current CPU. */
#ifdef __I386_NO_VM86
#define x86_get_irregs(thread) \
	((struct irregs_user *)FORTASK(thread, *(uintptr_t *)&this_x86_kernel_psp0) - 1)
#ifndef ___this_x86_kernel_psp0_defined
#define ___this_x86_kernel_psp0_defined
/* [== mnode_getendaddr(THIS_KERNEL_STACK)]
 * The per-task value written to `t_psp0' during scheduler preemption. */
DATDEF ATTR_PERTASK uintptr_t const this_x86_kernel_psp0;
#endif /* !___this_x86_kernel_psp0_defined */
#else /* __I386_NO_VM86 */
FUNDEF NOBLOCK ATTR_CONST ATTR_RETNONNULL NONNULL((1)) struct irregs_user *
NOTHROW(FCALL x86_get_irregs)(struct task const *__restrict thread);
#endif /* !__I386_NO_VM86 */
#endif /* !__x86_64__ */


/* Safely get/set the values of saved registers that may be modified by RPC redirection.
 *
 * These functions always get/set the registers that they'd appear WITHOUT RPC redirection:
 * - If `x86_userexcept_sysret' wasn't injected: access `self->[...]'
 * - If `x86_userexcept_sysret' was injected:    access `this_x86_sysret_iret.[...]'
 *
 * These functions must _ONLY_ be used when `self' points into the calling thread's
 * stack. DON'T use these to  try and set the  registers of some different  thread.
 */

/* Check if `self' returns to user-space. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL irregs_isuser)(struct irregs_kernel const *__restrict self);

/* get: `self->ir_Pip' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(FCALL irregs_rdip)(struct irregs_kernel const *__restrict self);

/* get: `self->ir_cs16' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) u16
NOTHROW(FCALL irregs_rdcs)(struct irregs_kernel const *__restrict self);

/* get: `self->ir_Pflags' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(FCALL irregs_rdflags)(struct irregs_kernel const *__restrict self);

/* set: `self->ir_Pip' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrip)(struct irregs_kernel *__restrict self, uintptr_t value);

/* set: `self->ir_cs' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrcs)(struct irregs_kernel *__restrict self, u16 value);

/* set: `self->ir_Pflags' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrflags)(struct irregs_kernel *__restrict self, uintptr_t value);

/* set: `self->ir_Pflags = (self->ir_Pflags & mask) | flags' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_mskflags)(struct irregs_kernel *__restrict self,
                               uintptr_t mask, uintptr_t flags);

/* get: `self->ir_Psp' (with accounting for kernel-space return-sp on i386) */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(FCALL irregs_rdsp)(struct irregs_kernel const *__restrict self);


#ifdef __x86_64__
/* Check if `self' returns to compatibility-mode. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL irregs_iscompat)(struct irregs const *__restrict self);

/* get: `self->ir_ss16' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) u16
NOTHROW(FCALL irregs_rdss)(struct irregs const *__restrict self);

/* set: `self->ir_rsp' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrsp)(struct irregs *__restrict self, uintptr_t value);

/* set: `self->ir_ss' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL irregs_wrss)(struct irregs *__restrict self, u16 value);
#else /* __x86_64__ */

#ifdef __I386_NO_VM86
#define irregs_isuser_novm86 irregs_isuser
#define irregs_isvm86(self)  0
#else /* __I386_NO_VM86 */
/* Check if `self' returns to user-space (return value is undefined if vm86). */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL irregs_isuser_novm86)(struct irregs_kernel const *__restrict self);

/* Check if `self' returns to vm86. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) __BOOL
NOTHROW(FCALL irregs_isvm86)(struct irregs_kernel const *__restrict self);
#endif /* !__I386_NO_VM86 */

#endif /* !__x86_64__ */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_TASK_H */
