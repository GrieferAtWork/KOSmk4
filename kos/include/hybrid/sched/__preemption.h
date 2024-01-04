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
#ifndef __GUARD_HYBRID_SCHED___PREEMPTION_H
#define __GUARD_HYBRID_SCHED___PREEMPTION_H 1

#include <__stdinc.h>

/* ===========================================================================
 * ==== Preemption control ===================================================
 * ===========================================================================
 *
 * ---------------------------------------------------------------------------
 * Guaranty non-reentrancy by disabling interrupts/signals
 * ---------------------------------------------------------------------------
 *
 * - typedef ... __hybrid_preemption_flag_t;
 *   - Data type for the preemption state flag
 *
 * - void __hybrid_preemption_pushoff(__hybrid_preemption_flag_t *p_flag);
 *   - Store the current preemption state in `*p_flag' and disable preemption
 *
 * - void __hybrid_preemption_pop(__hybrid_preemption_flag_t *p_flag);
 *   - Restore the current preemption state from `*p_flag'
 *   - Be careful  to nest  these two  functions correctly;  don't  skip
 *     elements during restore, and don't restore in an incorrect order.
 *
 * - bool __hybrid_preemption_ison(void);
 *   - Check if preemption is currently enabled
 *
 * - bool __hybrid_preemption_wason(__hybrid_preemption_flag_t const *p_flag);
 *   - Check if preemption was currently enabled before `p_flag' was
 *     initialized by  a  call  to  `__hybrid_preemption_pushoff()'.
 *
 * - void __hybrid_preemption_tryyield();
 *   - Special  function for safe `sched_yield()', both with preemption
 *     enabled and disabled. Use as loop-hint when acquiring SMP locks.
 *   SEMANTICS:
 *   >> __hybrid_preemption_tryyield() {
 *   >>     if (__hybrid_preemption_ison()) {
 *   >>         __hybrid_yield();
 *   >>     } else {
 *   >>         __hybrid_preemption_tryyield_nopr();
 *   >>     }
 *   >> }
 *
 * - void __hybrid_preemption_tryyield_f(__hybrid_preemption_flag_t *p_flag);
 *   - If  doing so grants  improved performance (iow: `__hybrid_preemption_tryyield()'
 *     and `__hybrid_preemption_tryyield_nopr()' are different functions), then briefly
 *     restore the  preemption behavior  of `p_flag',  follow this  up with  a call  to
 *     `__hybrid_preemption_tryyield()', before finally disabling preemption once again
 *     with a call to `__hybrid_preemption_pushoff()'.
 *     When `__hybrid_preemption_tryyield()' and `__hybrid_preemption_tryyield_nopr()'
 *     are the same function, `p_flag' is ignored and `__hybrid_preemption_tryyield()'
 *     is called as-is.
 *
 * - void __hybrid_preemption_tryyield_nopr(void);
 *   - A specialized variant of `__hybrid_preemption_tryyield()' that expects preemption
 *     to be disabled at  the moment. This function  will not re-enable preemption,  but
 *     will  instead try to yield execution to another CPU (if doing so is possible), or
 *     to  another thread (in case every thread behaves like it is hosted by a dedicated
 *     CPU, as is the case in user-space).
 *
 * - #define __HYBRID_PREEMPTION_NO_SMP
 *   - Defined if `__hybrid_preemption_pushoff()' results in the calling thread
 *     to become the only thread that's  still running in the caller's  address
 *     space. (Iow: anything  that's done  at this  point will  appear to  have
 *     happened atomically to other threads)
 *   - This is the case in 2 situations:
 *     - When building kernel-code for an operating system
 *       configured  to  now  support  more  than  one CPU
 *     - When building user-code when  threads aren't used, or  the
 *       threading library is based on signal + alarm + swapcontext
 *
 * - #define __HYBRID_PREEMPTION_NO_CONTROL
 *   - Defined if preemption cannot be controlled (in this case, all of the
 *     other  macros are simply no-ops, except for the yield functions, all
 *     of which simply map to `__hybrid_yield(3H)').
 *
 *
 * Function mappings for the KOS kernel:
 * - __hybrid_preemption_flag_t           <--->  pflag_t
 * - __hybrid_preemption_pushoff()        <--->  PREEMPTION_PUSHOFF()
 * - __hybrid_preemption_pop()            <--->  PREEMPTION_POP()
 * - __hybrid_preemption_ison()           <--->  PREEMPTION_ENABLED()
 * - __hybrid_preemption_wason()          <--->  PREEMPTION_WASENABLED()
 * - __hybrid_preemption_tryyield()       <--->  task_tryyield_or_pause()
 * - __hybrid_preemption_tryyield_f()     <--->  PREEMPTION_POP() + task_tryyield_or_pause() + PREEMPTION_PUSHOFF()
 * - __hybrid_preemption_tryyield_nopr()  <--->  task_pause()
 *
 */
#ifndef __CC__
/* ... */
#elif defined(__KOS__) && defined(__CHECKER__)
#undef __NOPREEMPT
#define __NOPREEMPT __ATTR_NOPREEMPT
__DECL_BEGIN
typedef int __hybrid_preemption_flag_t;
#define __hybrid_preemption_flag_t __hybrid_preemption_flag_t
__DECL_END

#define __hybrid_preemption_ison()             (!__builtin_tag_get("NOPREEMPT"))
#define __hybrid_preemption_wason(p_flag)      (*(p_flag))
#define __hybrid_preemption_pushoff(p_flag)    (*(p_flag) = __hybrid_preemption_ison(), __builtin_tag_set("NOPREEMPT", 1))
#define __hybrid_preemption_pop(p_flag)        __builtin_tag_set("NOPREEMPT", !*(p_flag))
#define __hybrid_preemption_tryyield()         (void)0
#define __hybrid_preemption_tryyield_f(p_flag) (void)0
#define __hybrid_preemption_tryyield_nopr()    (void)0
#ifdef __KERNEL__
#define __HYBRID_PREEMPTION_OFF_VALUE 0
#define __HYBRID_PREEMPTION_ON_VALUE  1
#include <kernel/compiler.h> /* CONFIG_NO_SMP */
#undef __HYBRID_PREEMPTION_NO_SMP
#ifdef CONFIG_NO_SMP
#define __HYBRID_PREEMPTION_NO_SMP
#endif /* CONFIG_NO_SMP */
#endif /* __KERNEL__ */
#elif defined(__INTELLISENSE__)
#ifndef __NOPREEMPT
#define __NOPREEMPT /* Annotation for functions that may only be called with preemption disabled. */
#endif /* !__NOPREEMPT */
__DECL_BEGIN

/* >> preemption_flag_t(3H)
 * Opaque data type to represent a saved preemption state. */
typedef struct { int __hpf_flag; } __hybrid_preemption_flag_t;
#define __hybrid_preemption_flag_t __hybrid_preemption_flag_t
#if defined(__KOS__) && defined(__KERNEL__)
__hybrid_preemption_flag_t const __HYBRID_PREEMPTION_OFF_VALUE = { 0 };
__hybrid_preemption_flag_t const __HYBRID_PREEMPTION_ON_VALUE  = { 1 };
#define __HYBRID_PREEMPTION_OFF_VALUE __HYBRID_PREEMPTION_OFF_VALUE
#define __HYBRID_PREEMPTION_ON_VALUE  __HYBRID_PREEMPTION_ON_VALUE
#endif /* __KOS__ && __KERNEL__ */

/* >> preemption_ison(3H)
 * Check if preemption is currently enabled:
 * - kernelspace: EFLAGS.IF  (x86)
 * - userspace:   at least 1 signal from `sigprocmask(3)' is unmasked */
__ATTR_WUNUSED __BOOL __hybrid_preemption_ison(void);
#define __hybrid_preemption_ison __hybrid_preemption_ison

/* Check if preemption was enabled when `preemption_pushoff(3H)'
 * was called (s.a. `preemption_ison(3H)'). */
__ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__hybrid_preemption_wason(__hybrid_preemption_flag_t const *__restrict __p_flag);
#define __hybrid_preemption_wason __hybrid_preemption_wason

/* >> preemption_pushoff(3H)
 * Save the current preemption context in `*p_flag' and disable preemption.
 * NOTE: The saved state can later be restored with `preemption_pop(3H)'
 * - kernelspace: `pushfP; cli;'  (x86)
 * - userspace:   setsigmaskfullptr(3) */
__ATTR_NONNULL((1)) void
__hybrid_preemption_pushoff(__hybrid_preemption_flag_t *__restrict __p_flag);
#define __hybrid_preemption_pushoff __hybrid_preemption_pushoff

/* >> preemption_pop(3H)
 * Restore the saved preemption context from `*p_flag'. After a call to this
 * function, the contents of `*p_flag'  become undefined and must either  be
 * discarded, or re-initialized by `preemption_pushoff(3H)'.
 * - kernelspace: `popfP;'  (x86)
 * - userspace:   setsigmaskptr(3) */
__ATTR_NONNULL((1)) void
__hybrid_preemption_pop(__hybrid_preemption_flag_t *__restrict __p_flag);
#define __hybrid_preemption_pop __hybrid_preemption_pop

/* >> preemption_tryyield(3H)
 * Safely try to yield execution to another thread if doing is allowed by the
 * current  preemption-state  (s.a.  `preemption_ison(3H)'). If  doing  so is
 * allowed,  yield to the next thread like  normal. Else, try to instruct the
 * CPU  to let another  core consume additional processing  power for a while
 * (if possible, as is the case with multi-threading), or simply do  nothing.
 *
 * - kernelspace: task_tryyield_or_pause()
 *                >> if (EFLAGS.IF) {     (x86)
 *                >>     task_yield();
 *                >> } else {
 *                >>     task_pause(); // "pause"
 *                >> }
 * - userspace:   sched_yield(3) */
void __hybrid_preemption_tryyield(void);
#define __hybrid_preemption_tryyield __hybrid_preemption_tryyield

/* >> preemption_tryyield_f(3H)
 * If `preemption_tryyield(3H)' requires preemption to be enabled in order to do
 * more than instruct the CPU with a loop-hint (x86: "pause"), then restore  the
 * preemption  state saved in  `*p_flag', and call `task_tryyield_or_pause(3H)'.
 * Once that function returns, disable preemption once again (possibly modifying
 * the state of `*p_flag' to differ from prior to the call).
 * When `preemption_tryyield(3H)' doesn't care about the preemption state, simply
 * do the same as `__hybrid_preemption_tryyield(3H)'.
 *
 * - kernelspace: PREEMPTION_POP([p_flag])
 *                task_tryyield_or_pause()
 *                PREEMPTION_DISABLE()
 * - userspace:   sched_yield(3) */
__ATTR_NONNULL((1)) void
__hybrid_preemption_tryyield_f(__hybrid_preemption_flag_t *__restrict __p_flag);
#define __hybrid_preemption_tryyield_f __hybrid_preemption_tryyield_f

/* >> preemption_tryyield_nopr(3H)
 * If task yielding is possible without preemption needing to be enabled,  then
 * do a normal task yield. Otherwise, only instruct the current CPU with a loop
 * hint (x86: "pause"), or do nothing of this isn't supported.
 *
 * For the sake of consistency, try not to call this function when preemption
 * isn't guarantied to be disabled.
 *
 * - kernelspace: task_pause()
 * - userspace:   sched_yield(3) */
__NOPREEMPT void __hybrid_preemption_tryyield_nopr(void);
#define __hybrid_preemption_tryyield_nopr __hybrid_preemption_tryyield_nopr

#if defined(__KOS__) && defined(__KERNEL__)
#include <kernel/compiler.h> /* CONFIG_NO_SMP */
#undef __HYBRID_PREEMPTION_NO_SMP
#ifdef CONFIG_NO_SMP
#define __HYBRID_PREEMPTION_NO_SMP
#endif /* CONFIG_NO_SMP */
#endif /* __KOS__ && __KERNEL__ */

__DECL_END
#elif defined(__KOS__) && defined(__KERNEL__)
/* KOS Kernel version */
#include <sched/task.h>
#define __hybrid_preemption_flag_t          pflag_t
#define __HYBRID_PREEMPTION_ON_VALUE        PREEMPTION_ENABLED_VALUE
#define __HYBRID_PREEMPTION_OFF_VALUE       PREEMPTION_DISABLED_VALUE
#define __hybrid_preemption_tryyield()      (void)task_tryyield_or_pause()
#define __hybrid_preemption_ison()          PREEMPTION_ENABLED()
#define __hybrid_preemption_wason(p_flag)   PREEMPTION_WASENABLED(*(p_flag))
#define __hybrid_preemption_pushoff(p_flag) (void)(*(p_flag) = PREEMPTION_PUSHOFF())
#define __hybrid_preemption_pop(p_flag)     (void)(PREEMPTION_POP(*(p_flag)))
#define __hybrid_preemption_tryyield_nopr() (void)task_pause()
#define __hybrid_preemption_tryyield_f(p_flag) \
	(__hybrid_preemption_pop(p_flag),          \
	 __hybrid_preemption_tryyield(),           \
	 PREEMPTION_DISABLE())

/* If configured for single-core use, disabling preemption means that nothing
 * will be able to interrupt the calling thread, also meaning that  disabling
 * preemption results in execution continuing in a single-threaded mode. */
#undef __HYBRID_PREEMPTION_NO_SMP
#ifdef CONFIG_NO_SMP
#define __HYBRID_PREEMPTION_NO_SMP
#endif /* CONFIG_NO_SMP */
#else /* ... */

/* KOS system headers expose all functions we need in an escaped namespace,
 * meaning  we  don't have  to include  <signal.h>  and clobber  the global
 * namespace. */
#ifdef __KOS_SYSTEM_HEADERS__
#include <libc/signal.h>
#if defined(__libc_setsigmaskfullptr) && defined(__libc_setsigmaskptr)
#define __hybrid_preemption_flag_t          struct __sigset_struct *
#define __hybrid_preemption_pushoff(p_flag) (void)(*(p_flag) = __libc_setsigmaskfullptr())
#define __hybrid_preemption_pop(p_flag)     (void)(__libc_setsigmaskptr(*(p_flag)))
#define __hybrid_preemption_ison()          (!__libc_sigisemptyset(__libc_getsigmaskptr()))
#define __hybrid_preemption_wason(p_flag)   (!__libc_sigisemptyset(*(p_flag)))
#else /* __libc_setsigmaskfullptr && __libc_setsigmaskptr */
#include <libc/sys.signal.h>
#if defined(__libc_sigblockall) && defined(__libc_sigunblockall)
#define __hybrid_preemption_flag_t          int
#define __hybrid_preemption_pushoff(p_flag) (void)(*(p_flag) = __libc_sigblockall())
#define __hybrid_preemption_pop(p_flag)     ((void)(p_flag), (void)__libc_sigunblockall())
#define __hybrid_preemption_ison()          (__libc_sigblockall(), (__libc_sigunblockall() & 0x7fffffff) == 0)
#define __hybrid_preemption_wason(p_flag)   (*(p_flag) == 1)
#elif defined(__libc_sigprocmask)
#include <asm/os/signal.h>
#define __hybrid_preemption_flag_t struct __sigset_struct
#define __hybrid_preemption_pop(p_flag) \
	(void)__libc_sigprocmask(__SIG_SETMASK, p_flag, __NULLPTR)
#define __hybrid_preemption_wason(p_flag) (!__libc_sigisemptyset(p_flag))
#ifdef __NO_XBLOCK
#define __hybrid_preemption_pushoff (__NAMESPACE_INT_SYM __hybrid_private_preemption_pushoff)
#define __hybrid_preemption_ison    (__NAMESPACE_INT_SYM __hybrid_private_preemption_ison)
__DECL_BEGIN
__NAMESPACE_INT_BEGIN
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW(__hybrid_private_preemption_pushoff)(sigset_t *__restrict __p_flag) {
	struct __sigset_struct __hpp_nss;
	__libc_sigfillset(&__hpp_nss);
	__libc_sigprocmask(__SIG_SETMASK, p_flag, &__hpp_nss);
}
__LOCAL __ATTR_PURE __ATTR_WUNUSED __BOOL
__NOTHROW(__hybrid_private_preemption_ison)(void) {
	sigset_t __hpio_nss;
	__libc_sigprocmask(SIG_SETMASK, __NULLPTR, &__hpio_nss);
	return !__hybrid_sigisemptyset(&__hpio_nss)
}
__NAMESPACE_INT_END
__DECL_END
#else /* __NO_XBLOCK */
#define __hybrid_preemption_pushoff(p_flag)                    \
	__XBLOCK({                                                 \
		struct __sigset_struct __hpp_nss;                      \
		__libc_sigfillset(&__hpp_nss);                         \
		__libc_sigprocmask(__SIG_SETMASK, p_flag, &__hpp_nss); \
	})
#define __hybrid_preemption_ison()                                 \
	__XBLOCK({                                                     \
		struct __sigset_struct __hpio_nss;                         \
		__libc_sigprocmask(__SIG_SETMASK, __NULLPTR, &__hpio_nss); \
		__XRETURN !__libc_sigisemptyset(&__hpio_nss);              \
	})
#endif /* !__NO_XBLOCK */
#endif /* ... */
#endif /* !__libc_setsigmaskfullptr || !__libc_setsigmaskptr */
#endif /* __KOS_SYSTEM_HEADERS__ */


#ifndef __hybrid_preemption_flag_t
/* Optimized implementation for DragonFly's `sigblockall(3)' */
#if (defined(__DragonFly__) || defined(__KOS__) ||                \
     (defined(HAVE_SIGBLOCKALL) && defined(HAVE_SIGUNBLOCKALL) && \
      (defined(HAVE_SYS_SIGNAL_H) || __has_include(<sys/signal.h>))))
#ifndef _BSD_SOURCE
#define _BSD_SOURCE 1
#endif /* !_BSD_SOURCE */
#include <sys/signal.h>
#define __hybrid_preemption_flag_t          int
#define __hybrid_preemption_pushoff(p_flag) (void)(*(p_flag) = sigblockall())
#define __hybrid_preemption_pop(p_flag)     ((void)(p_flag), (void)sigunblockall())
#define __hybrid_preemption_ison()          (sigblockall(), (sigunblockall() & 0x7fffffff) == 0)
#define __hybrid_preemption_wason(p_flag)   (*(p_flag) == 1)
#endif /* __DragonFly__ || ... */

#ifndef __hybrid_preemption_flag_t
/* Fallback implementation for a generic UNIX target */
#include <hybrid/host.h>
#if defined(__unix__) || defined(HAVE_SIGNAL_H) || __has_include(<signal.h>)
#include <signal.h>
#endif /* <signal.h>... */

#ifdef SIG_SETMASK
#if defined(HAVE_SIGFILLSET) || (defined(__USE_POSIX) && !defined(NO_SIGFILLSET))
#define __hybrid_sigfillset sigfillset
#else /* HAVE_SIGFILLSET || (__USE_POSIX && !NO_SIGFILLSET) */
#include <string.h>
#define __hybrid_sigfillset(set) memset(set, 0xff, sizeof(sigset_t))
#endif /* !HAVE_SIGFILLSET && (!__USE_POSIX || NO_SIGFILLSET) */

#if defined(HAVE_SIGISEMPTYSET) || (defined(__USE_GNU) && !defined(NO_SIGISEMPTYSET))
#define __hybrid_sigisemptyset(set) sigisemptyset(set)
#else /* HAVE_SIGISEMPTYSET || (__USE_GNU && !NO_SIGISEMPTYSET) */
#include <hybrid/typecore.h>
#define __hybrid_sigisemptyset (__NAMESPACE_INT_SYM __hybrid_private_sigisemptyset)
__DECL_BEGIN
__NAMESPACE_INT_BEGIN
__LOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __BOOL
__NOTHROW(__hybrid_private_sigisemptyset)(sigset_t const *__restrict __set) {
	__STATIC_IF ((sizeof(sigset_t) % __SIZEOF_POINTER__) == 0) {
		__SIZE_TYPE__ __i;
		for (__i = 0; __i < sizeof(sigset_t) / __SIZEOF_POINTER__; ++__i) {
			if (((__UINTPTR_TYPE__ *)__set)[__i] != 0)
				return 0;
		}
	} __STATIC_ELSE ((sizeof(sigset_t) % __SIZEOF_POINTER__) == 0) {
		__SIZE_TYPE__ __i;
		for (__i = 0; __i < sizeof(sigset_t); ++__i) {
			if (((__BYTE_TYPE__ *)__set)[__i] != 0)
				return 0;
		}
	}
	return 1;
}
__NAMESPACE_INT_END
__DECL_END
#endif /* !HAVE_SIGISEMPTYSET && (!__USE_GNU || NO_SIGISEMPTYSET) */

#define __hybrid_preemption_flag_t sigset_t
#ifdef __NO_XBLOCK
#define __hybrid_preemption_pushoff (__NAMESPACE_INT_SYM __hybrid_private_preemption_pushoff)
#define __hybrid_preemption_ison    (__NAMESPACE_INT_SYM __hybrid_private_preemption_ison)
__DECL_BEGIN
__NAMESPACE_INT_BEGIN
__LOCAL __ATTR_NONNULL((1)) void
__NOTHROW(__hybrid_private_preemption_pushoff)(sigset_t *__restrict __p_flag) {
	sigset_t __hpp_nss;
	__hybrid_sigfillset(&__hpp_nss);
	sigprocmask(SIG_SETMASK, &__hpp_nss, __p_flag);
}
__LOCAL __ATTR_PURE __ATTR_WUNUSED __BOOL
__NOTHROW(__hybrid_private_preemption_ison)(void) {
	sigset_t __hpio_nss;
	sigprocmask(SIG_SETMASK, __NULLPTR, &__hpio_nss);
	return !__hybrid_sigisemptyset(&__hpio_nss)
}
__NAMESPACE_INT_END
__DECL_END
#else /* __NO_XBLOCK */
#define __hybrid_preemption_pushoff(p_flag)           \
	__XBLOCK({                                        \
		sigset_t __hpp_nss;                           \
		__hybrid_sigfillset(&__hpp_nss);              \
		sigprocmask(SIG_SETMASK, &__hpp_nss, p_flag); \
	})
#define __hybrid_preemption_ison()                        \
	__XBLOCK({                                            \
		struct __sigset_struct __hpio_nss;                \
		sigprocmask(SIG_SETMASK, __NULLPTR, &__hpio_nss); \
		__XRETURN !__hybrid_sigisemptyset(&__hpio_nss);   \
	})
#endif /* !__NO_XBLOCK */

#define __hybrid_preemption_pop(p_flag)   (void)sigprocmask(SIG_SETMASK, p_flag, __NULLPTR)
#define __hybrid_preemption_wason(p_flag) (!__hybrid_sigisemptyset(p_flag))
#endif /* SIG_SETMASK */
#endif /* !__hybrid_preemption_flag_t */
#endif /* !__hybrid_preemption_flag_t */

#if 0 /* Technically correct, but only if `-pthread' is used correctly and passes `-D_REENTRANT' */
#ifndef _REENTRANT
#define __HYBRID_PREEMPTION_NO_SMP
#endif /* !_REENTRANT */
#endif

#endif /* !... */

/* Fallback definition */
#ifndef __hybrid_preemption_flag_t
#define __HYBRID_PREEMPTION_NO_CONTROL
#define __hybrid_preemption_flag_t          int
#define __hybrid_preemption_pushoff(p_flag) (void)0
#define __hybrid_preemption_pop(p_flag)     (void)0
#define __hybrid_preemption_ison()          1
#define __hybrid_preemption_wason(p_flag)   1
#endif /* !__hybrid_preemption_flag_t */

#ifndef __hybrid_preemption_tryyield
#include "__yield.h"
#define __hybrid_preemption_tryyield() (void)__hybrid_yield_nx()
#define __HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD
#endif /* !__hybrid_preemption_tryyield */

/* Same as `__hybrid_preemption_tryyield()', but optimized
 * for  the  case  where  preemption  has  been  disabled. */
#ifndef __hybrid_preemption_tryyield_nopr
#define __hybrid_preemption_tryyield_nopr() __hybrid_preemption_tryyield()
#endif /* !__hybrid_preemption_tryyield_nopr */

/* Same as `__hybrid_preemption_tryyield()', but allowed to temporarily
 * restore `p_flag'  if doing  so can  make the  yield perform  better. */
#ifndef __hybrid_preemption_tryyield_f
#ifdef __HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD
#define __hybrid_preemption_tryyield_f(p_flag) __hybrid_preemption_tryyield()
#else /* __HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD */
#define __hybrid_preemption_tryyield_f(p_flag) \
	(__hybrid_preemption_pop(p_flag),          \
	 __hybrid_preemption_tryyield(),           \
	 __hybrid_preemption_pushoff(p_flag))
#endif /* !__HYBRID_PREEMPTION_TRYYIELD_IS_HYBRID_YIELD */
#endif /* !__hybrid_preemption_tryyield_f */



/* Helper macro to declare preemption flag variables. */
#ifdef __HYBRID_PREEMPTION_NO_CONTROL
#define __hybrid_preemption_flagvar(name) /* nothing */
#else /* __HYBRID_PREEMPTION_NO_CONTROL */
#define __hybrid_preemption_flagvar(name) __hybrid_preemption_flag_t name
#endif /* !__HYBRID_PREEMPTION_NO_CONTROL */


/* Helper macros to acquire/release locks whilst simultaneously disabling preemption */
#ifdef __HYBRID_PREEMPTION_NO_CONTROL
#include "__yield.h"
/* No preemption control -> must implement regular acquire/release semantics */
#ifdef __NO_XBLOCK
#define __hybrid_preemption_acquire_smp_r(_tryacquire, p_flag) \
	do {                                                       \
		while (!(_tryacquire)) {                               \
			__hybrid_yield();                                  \
		}                                                      \
	}	__WHILE0
#else /* __NO_XBLOCK */
#define __hybrid_preemption_acquire_smp_r(_tryacquire, p_flag) \
	__XBLOCK({                                                 \
		while (!(_tryacquire)) {                               \
			__hybrid_yield();                                  \
		}                                                      \
	})
#endif /* !__NO_XBLOCK */
#define __hybrid_preemption_release_smp_r(_release, p_flag) \
	(_release)
#elif defined(__HYBRID_PREEMPTION_NO_SMP)
/* Preemption control causes us to enter single-threaded mode -> no need to touch external locks. */
#define __hybrid_preemption_acquire_smp_r(_tryacquire, p_flag) \
	__hybrid_preemption_pushoff(p_flag)
#define __hybrid_preemption_release_smp_r(_release, p_flag) \
	__hybrid_preemption_pop(p_flag)
#else /* ... */
/* Preemption  control must interlock with lock acquisition, but still try to
 * keep preemption enabled whenever trying to yield to other waiting threads. */
#ifdef __NO_XBLOCK
#define __hybrid_preemption_acquire_smp_r(_tryacquire, p_flag) \
	do {                                                       \
		__hybrid_preemption_pushoff(p_flag);                   \
		if (_tryacquire)                                       \
			break;                                             \
		__hybrid_preemption_pop(p_flag);                       \
		__hybrid_preemption_tryyield();                        \
	}	__WHILE1
#else /* __NO_XBLOCK */
#define __hybrid_preemption_acquire_smp_r(_tryacquire, p_flag) \
	__XBLOCK({                                                 \
		do {                                                   \
			__hybrid_preemption_pushoff(p_flag);               \
			if (_tryacquire)                                   \
				break;                                         \
			__hybrid_preemption_pop(p_flag);                   \
			__hybrid_preemption_tryyield();                    \
		}	__WHILE1;                                          \
	})
#endif /* !__NO_XBLOCK */
#define __hybrid_preemption_release_smp_r(_release, p_flag) \
	(_release, __hybrid_preemption_pop(p_flag))
#endif /* !... */


/* Some more helper macros to automate the creation of local variables. */
#define __hybrid_preemption_acquire_smp(_tryacquire) \
	do {                                             \
		__hybrid_preemption_flagvar(__hpsmp_pflag);  \
		__hybrid_preemption_acquire_smp_r(_tryacquire, &__hpsmp_pflag)
#define __hybrid_preemption_acquire_smp_b(_tryacquire) __hybrid_preemption_acquire_smp_r(_tryacquire, &__hpsmp_pflag)
#define __hybrid_preemption_release_smp_b(_release)    __hybrid_preemption_release_smp_r(_release, &__hpsmp_pflag)
#define __hybrid_preemption_release_smp(_release)                    \
		__hybrid_preemption_release_smp_r(_release, &__hpsmp_pflag); \
	}	__WHILE0



#endif /* !__GUARD_HYBRID_SCHED___PREEMPTION_H */
