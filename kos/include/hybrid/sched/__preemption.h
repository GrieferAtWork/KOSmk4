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
#ifndef __GUARD_HYBRID_SCHED___PREEMPTION_H
#define __GUARD_HYBRID_SCHED___PREEMPTION_H 1

#include <__stdinc.h>

/* Preemption control:
 * - Guaranty non-reentrancy by disabling interrupts/signals
 *
 * - typedef ... __hybrid_preemption_flag_t;
 *   - Data type for the preemption state flag
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
 * - void __hybrid_preemption_pushoff(__hybrid_preemption_flag_t *p_flag);
 *   - Store the current preemption state in `*p_flag' and disable preemption
 *
 * - void __hybrid_preemption_pop(__hybrid_preemption_flag_t const *p_flag);
 *   - Restore the current preemption state from `*p_flag'
 *   - Be careful  to nest  these two  functions correctly;  don't  skip
 *     elements during restore, and don't restore in an incorrect order.
 *
 * - #define __HYBRID_NO_PREEMPTION_SMP
 *   - Defined  if `__hybrid_preemption_pushoff()' results in the calling thread
 *     to become the only thread that's still running in the caller's address
 *     space.  (Iow: anything that's  done at this point  will appear to have
 *     happened atomically to other threads)
 *
 * - #define __HYBRID_NO_PREEMPTION_CONTROL
 *   - Defined if preemption cannot be controlled (in this case, all of the other macros are simply no-ops).
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
#ifdef __INTELLISENSE__
typedef struct { int __hpf_flag; } __hybrid_preemption_flag_t;
#define __hybrid_preemption_flag_t          __hybrid_preemption_flag_t
#define __hybrid_preemption_tryyield()      (void)0
#define __hybrid_preemption_ison()          1
#define __hybrid_preemption_wason(p_flag)   1
#define __hybrid_preemption_pushoff(p_flag) (void)((p_flag)->__hpf_flag = 0)
#define __hybrid_preemption_pop(p_flag)     (void)((p_flag)->__hpf_flag)
#elif defined(__KOS__) && defined(__KERNEL__)
/* KOS Kernel version */
#include <sched/task.h>
#define __hybrid_preemption_flag_t          pflag_t
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
#undef __HYBRID_NO_PREEMPTION_SMP
#ifdef CONFIG_NO_SMP
#define __HYBRID_NO_PREEMPTION_SMP
#endif /* CONFIG_NO_SMP */
#else  /* ... */

#ifdef __KOS_SYSTEM_HEADERS__
#include <libc/signal.h>
#if defined(__libc_setsigmaskfullptr) && defined(__libc_setsigmaskptr)
#define __hybrid_preemption_flag_t          struct __sigset_struct *
#define __hybrid_preemption_pushoff(p_flag) (void)(*(p_flag) = __libc_setsigmaskfullptr())
#define __hybrid_preemption_pop(p_flag)     (void)(__libc_setsigmaskptr(*(p_flag)))
#define __hybrid_preemption_ison()          (!__libc_sigisemptyset(__libc_getsigmaskptr()))
#define __hybrid_preemption_wason(p_flag)   (!__libc_sigisemptyset(*(p_flag)))
#elif defined(__libc_sigprocmask)
#include <asm/os/signal.h>
#define __hybrid_preemption_flag_t struct __sigset_struct
#define __hybrid_preemption_pushoff(p_flag)                    \
	__XBLOCK({                                                 \
		struct __sigset_struct __hpp_nss;                      \
		__libc_sigfillset(&__hpp_nss);                         \
		__libc_sigprocmask(__SIG_SETMASK, p_flag, &__hpp_nss); \
	})
#define __hybrid_preemption_pop(p_flag) \
	(void)__libc_sigprocmask(__SIG_SETMASK, p_flag, __NULLPTR)
#define __hybrid_preemption_ison()                                \
	__XBLOCK({                                                    \
		struct __sigset_struct __hpp_nss;                         \
		__libc_sigprocmask(__SIG_SETMASK, __NULLPTR, &__hpp_nss); \
		__XRETURN !__libc_sigisemptyset(&__hpp_nss);              \
	})
#define __hybrid_preemption_wason(p_flag) (!__libc_sigisemptyset(p_flag))
#endif /* ... */
#endif /* __KOS_SYSTEM_HEADERS__ */

#ifndef __hybrid_preemption_flag_t
#include <hybrid/host.h>
#if defined(__unix__) || defined(HAVE_SIGNAL_H) || __has_include(<signal.h>)
#include <signal.h>
#endif /* <signal.h>... */
#ifdef SIG_SETMASK
#define __hybrid_preemption_flag_t sigset_t
#define __hybrid_preemption_pushoff(p_flag)           \
	__XBLOCK({                                        \
		sigset_t __hpp_nss;                           \
		sigfillset(&__hpp_nss);                       \
		sigprocmask(SIG_SETMASK, p_flag, &__hpp_nss); \
	})
#define __hybrid_preemption_pop(p_flag) \
	(void)sigprocmask(SIG_SETMASK, p_flag, __NULLPTR)
#define __hybrid_preemption_ison()                       \
	__XBLOCK({                                           \
		struct __sigset_struct __hpp_nss;                \
		sigprocmask(SIG_SETMASK, __NULLPTR, &__hpp_nss); \
		__XRETURN !sigisemptyset(&__hpp_nss);            \
	})
#define __hybrid_preemption_wason(p_flag) (!sigisemptyset(p_flag))
#endif /* SIG_SETMASK */
#endif /* !__hybrid_preemption_flag_t */

#if 0 /* Technically correct, but only if `-pthread' is used correctly and passes `-D_REENTRANT' */
#ifndef _REENTRANT
#define __HYBRID_NO_PREEMPTION_SMP
#endif /* !_REENTRANT */
#endif

#endif /* !... */

/* Fallback definition */
#ifndef __hybrid_preemption_flag_t
#define __HYBRID_NO_PREEMPTION_CONTROL
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
 * for  the  case where  preemption has  been disabled. */
#ifndef __hybrid_preemption_tryyield_nopr
#define __hybrid_preemption_tryyield_nopr() __hybrid_preemption_tryyield()
#endif /* !__hybrid_preemption_tryyield_nopr */

/* Same as `__hybrid_preemption_tryyield()', but allowed to temporarily
 * restore `p_flag' if doing so  can make the yield perform  better. */
#ifndef __hybrid_preemption_tryyield_f
#define __hybrid_preemption_tryyield_f(p_flag) __hybrid_preemption_tryyield()
#endif /* !__hybrid_preemption_tryyield_f */



/* Helper macro to declare preemption flag variables. */
#ifdef __HYBRID_NO_PREEMPTION_CONTROL
#define __hybrid_preemption_flagvar(name) /* nothing */
#else /* __HYBRID_NO_PREEMPTION_CONTROL */
#define __hybrid_preemption_flagvar(name) __hybrid_preemption_flag_t name
#endif /* !__HYBRID_NO_PREEMPTION_CONTROL */


/* Helper macros to acquire/release locks whilst simultaneously disabling preemption */
#ifdef __HYBRID_NO_PREEMPTION_CONTROL
#include "__yield.h"
/* No preemption control -> must implement regular acquire/release semantics */
#define __hybrid_preemption_acquire_smp_r(_tryacquire, p_flag) \
	__XBLOCK({                                                 \
		while (!(_tryacquire)) {                               \
			__hybrid_yield();                                  \
		}                                                      \
	})
#define __hybrid_preemption_release_smp_r(_release, p_flag) \
	(_release)
#elif defined(__HYBRID_NO_PREEMPTION_SMP)
/* Preemption control causes us to enter single-threaded mode -> no need to touch external locks. */
#define __hybrid_preemption_acquire_smp_r(_tryacquire, p_flag) \
	__hybrid_preemption_pushoff(p_flag)
#define __hybrid_preemption_release_smp_r(_release, p_flag) \
	__hybrid_preemption_pop(p_flag)
#else /* ... */
/* Preemption  control must interlock with lock acquisition, but still try to
 * keep preemption enabled whenever trying to yield to other waiting threads. */
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
