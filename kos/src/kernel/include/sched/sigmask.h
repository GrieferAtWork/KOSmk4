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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIGMASK_H
#define GUARD_KERNEL_INCLUDE_SCHED_SIGMASK_H 1

#include <kernel/compiler.h>

#include <kernel/rt/except-syscall.h> /* CONFIG_HAVE_KERNEL_USERPROCMASK */
#include <kernel/types.h>

#include <asm/os/signal.h>
#include <bits/os/sigset.h>
#include <kos/aref.h>

#ifndef CONFIG_HAVE_KERNEL_USERPROCMASK
#include <libc/string.h>
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */

#ifndef SIGSET_NWORDS
#define SIGSET_NWORDS __SIGSET_NWORDS
#endif /* !SIGSET_NWORDS */

#ifdef __CC__
DECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

/* Add/remove all unmaskable signals to/from a given `sigset_t' */
#if __sigset_word_c(__SIGKILL) == __sigset_word_c(__SIGSTOP)
#define sigaddset_nmi(self) \
	(void)((self)->__val[__sigset_word_c(__SIGKILL)] |= (__sigset_mask(__SIGKILL) | __sigset_mask(__SIGSTOP)))
#define sigdelset_nmi(self) \
	(void)((self)->__val[__sigset_word_c(__SIGKILL)] &= ~(__sigset_mask(__SIGKILL) | __sigset_mask(__SIGSTOP)))
#else /* __sigset_word_c(__SIGKILL) == __sigset_word_c(__SIGSTOP) */
#define sigaddset_nmi(self)                                                       \
	(void)((self)->__val[__sigset_word_c(__SIGKILL)] |= __sigset_mask(__SIGKILL), \
	       (self)->__val[__sigset_word_c(__SIGSTOP)] |= __sigset_mask(__SIGSTOP))
#define sigdelset_nmi(self)                                                        \
	(void)((self)->__val[__sigset_word_c(__SIGKILL)] &= ~__sigset_mask(__SIGKILL), \
	       (self)->__val[__sigset_word_c(__SIGSTOP)] &= ~__sigset_mask(__SIGSTOP))
#endif /* __sigset_word_c(__SIGKILL) != __sigset_word_c(__SIGSTOP) */

/************************************************************************/
/* SIGNAL MASK                                                          */
/************************************************************************/

/* A full signal mask (i.e. one that blocks all signals; except for SIGKILL and SIGSTOP) */
DATDEF sigset_t const sigmask_full;

/* [lock(READ(ATOMIC), WRITE(THIS_TASK))]
 * Reference to the signal mask (set of signals being blocked) in the  current
 * thread. The pointed-to object is meaningless (but must still be valid) when
 * the associated thread make use of userprocmask.
 *
 * WARNING: This signal set must  _NEVER_ contain `SIGKILL' or  `SIGSTOP'.
 *          Not when `TASK_USERPROCMASK' is set, and neither for only just
 *          a couple of moments. -- NO EXCEPTIONS!
 * Furthermore, this set may not contain garbage when `TASK_USERPROCMASK'
 * is set. Instead, in this case  it must contain the last-active  signal
 * mask prior to the calling thread activating `TASK_USERPROCMASK'.  This
 * is needed so that after  checking that `TASK_USERPROCMASK' isn't  set,
 * any  thread can safely read from this  set with the knowledge that any
 * unmasked signal was masked at  the time of the of  `TASK_USERPROCMASK'
 * not having been set, or has since become masked by the thread  itself. */
DATDEF ATTR_PERTASK sigset_t this_kernel_sigmask;
#define THIS_KERNEL_SIGMASK PERTASK(this_kernel_sigmask)


/* Check if a given `signo' is currently masked. This function
 * handles all of the special cases, including TASK_VFORK  and
 * TASK_USERPROCMASK, as well as making sure that SIGSTOP  and
 * SIGKILL are never considered to be masked. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
FUNDEF ATTR_PURE WUNUSED __BOOL FCALL sigmask_ismasked(signo_t signo) THROWS(E_SEGFAULT);
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL NOTHROW(FCALL sigmask_ismasked)(signo_t signo);
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */


#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
#define SIGMASK_ISMASKED_NOPF_NO  0 /* The signal isn't masked */
#define SIGMASK_ISMASKED_NOPF_YES 1 /* The signal is masked */
/* The signal may be masked, or it may not be, however due  to
 * the target thread running on a different CPU, or using VIO,
 * a faulty pointer, or memory  currently not loaded into  the
 * core for the backing memory of its usersigmask, the calling
 * thread cannot conclusively determine this. */
#define SIGMASK_ISMASKED_NOPF_FAULT (-2)

/* Non-faulting version of `sigmask_ismasked()'.
 * @return: * : One of `SIGMASK_ISMASKED_NOPF_*' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED int
NOTHROW(FCALL sigmask_ismasked_nopf)(signo_t signo);
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
#define SIGMASK_ISMASKED_NOPF_NO     false /* The signal isn't masked */
#define SIGMASK_ISMASKED_NOPF_YES    true  /* The signal is masked */
#define sigmask_ismasked_nopf(signo) sigmask_ismasked(signo)
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */
/************************************************************************/

/* Helper  function that can  be used to determine  the masking status for
 * an arbitrary signal within an  arbitrary thread. Not that  userprocmask
 * signals  can _ONLY_  be determined (at  all) when `self'  is running on
 * the same CPU as the calling thread. If this is not the case, and `self'
 * uses the  userprocmask mechanism,  then SIGMASK_ISMASKED_NOPF_FAULT  is
 * _always_ returned.
 * @param: allow_blocking_and_exception_when_self_is_THIS_TASK:
 *              Like the argument name says: When self == THIS_TASK,
 *              and this argument is true, then this call is allowed
 *              to block, as well as throw exceptions.
 * @return: * : One of `SIGMASK_ISMASKED_*' (see above) */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
FUNDEF NOBLOCK_IF(!allow_blocking_and_exception_when_self_is_THIS_TASK || self != THIS_TASK)
ATTR_PURE WUNUSED NONNULL((1)) int FCALL
sigmask_ismasked_in(struct task *__restrict self, signo_t signo,
                    __BOOL allow_blocking_and_exception_when_self_is_THIS_TASK __DFL(0))
		THROWS(E_SEGFAULT); /* Is NOTHROW when `allow_blocking_and_exception_when_self_is_THIS_TASK == false && self == THIS_TASK' */
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW(FCALL sigmask_ismasked_in)(struct task *__restrict self, signo_t signo);
#define sigmask_ismasked_in(self, signo, ...) sigmask_ismasked_in(self, signo)
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */


/* Set  the given signal mask as active for the calling thread.
 * Primarily used for  `sigreturn(2)', this  function has  some
 * special handling to ensure that `SIGKILL' and `SIGSTOP'  are
 * not masked, whilst still ensuring not to modify a  potential
 * userprocmask unless absolutely necessary (including the case
 * where the userprocmask indicates that SIGKILL or SIGSTOP are
 * currently masked (which isn't actually the case))
 *
 * @return: true:  Changes were made to the caller's signal mask. In
 *                 this case, the caller should make another call to
 *                 `userexcept_sysret_inject_self()'  in  order   to
 *                 check for pending signals upon the next return to
 *                 user-space (unless it  is known  that the  signal
 *                 mask didn't get less restrictive)
 * @return: false: The caller's signal mask remains unchanged. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
FUNDEF NONNULL((1)) __BOOL FCALL
sigmask_setmask(sigset_t const *__restrict mask)
		THROWS(E_SEGFAULT);
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL sigmask_setmask)(sigset_t const *__restrict mask);
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */

/* Helper wrapper for `sigmask_setmask()' that takes a signal-set from user-space. */
FUNDEF __BOOL FCALL
sigmask_setmask_from_user(USER CHECKED sigset_t const *mask, size_t size)
		THROWS(E_SEGFAULT);

/* Get the calling thread's current signal mask. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
FUNDEF NONNULL((1)) void FCALL
sigmask_getmask(sigset_t *__restrict mask)
		THROWS(E_SEGFAULT);
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
#define sigmask_getmask(mask) \
	(void)__libc_memcpy(mask, &THIS_KERNEL_SIGMASK, sizeof(sigset_t))
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */

/* Return the first word from the calling thread's signal mask. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
FUNDEF ATTR_PURE WUNUSED ulongptr_t FCALL sigmask_getmask_word0(void) THROWS(E_SEGFAULT);
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
#define sigmask_getmask_word0() PERTASK_GET(this_kernel_sigmask.__val[0])
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */

/* Return the `index' word from the calling thread's signal mask.
 * @param: index: Index into the caller's sigmask mask sigset (`< SIGSET_NWORDS') */
#if SIGSET_NWORDS <= 1
#define sigmask_getmask_word(index)   sigmask_getmask_word0()
#elif defined(CONFIG_HAVE_KERNEL_USERPROCMASK)
FUNDEF ATTR_PURE WUNUSED ulongptr_t FCALL
sigmask_getmask_word(size_t index)
		THROWS(E_SEGFAULT);
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
#define sigmask_getmask_word(index) \
	PERTASK_GET(this_kernel_sigmask.__val[index])
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */

/* Same as `sigmask_getmask_word()', but returns `(ulongptr_t)-1' when `index' is invalid. */
#define sigmask_getmask_word_s(index) \
	(likely((index) < SIGSET_NWORDS) ? sigmask_getmask_word(index) : (ulongptr_t)-1)


/* Or the given set of signals `these' with the calling thread's
 * signal mask, thus effectively blocking all of those  signals. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
FUNDEF NONNULL((1)) void FCALL
sigmask_blockmask(sigset_t const *__restrict these)
		THROWS(E_SEGFAULT);
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sigmask_blockmask)(sigset_t const *__restrict these);
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */


/* Unblock the given set of signals `these' within the calling thread's signal mask.
 * @return: true:  Changes were made to the caller's signal mask. In
 *                 this case, the caller should make another call to
 *                 `userexcept_sysret_inject_self()'  in  order   to
 *                 check for pending signals upon the next return to
 *                 user-space (unless it  is known  that the  signal
 *                 mask didn't get less restrictive)
 * @return: false: The caller's signal mask remains unchanged. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
FUNDEF NONNULL((1)) __BOOL FCALL
sigmask_unblockmask(sigset_t const *__restrict these)
		THROWS(E_SEGFAULT);
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL sigmask_unblockmask)(sigset_t const *__restrict these);
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */



/* Combination of `sigmask_getmask()' and `sigmask_setmask()'
 *
 * @return: true:  Changes were made to the caller's signal mask. In
 *                 this case, the caller should make another call to
 *                 `userexcept_sysret_inject_self()'  in  order   to
 *                 check for pending signals upon the next return to
 *                 user-space (unless it  is known  that the  signal
 *                 mask didn't get less restrictive)
 * @return: false: The caller's signal mask remains unchanged. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
FUNDEF NONNULL((1, 2)) __BOOL FCALL
sigmask_getmask_and_setmask(sigset_t *__restrict oldmask,
                            sigset_t const *__restrict newmask)
		THROWS(E_SEGFAULT);
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL
NOTHROW(FCALL sigmask_getmask_and_setmask)(sigset_t *__restrict oldmask,
                                           sigset_t const *__restrict newmask);
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */



/* Combination of `sigmask_getmask()' and `sigmask_blockmask()'
 * @return: true:  Changes were made to the caller's signal mask.
 * @return: false: The caller's signal mask remains unchanged. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
FUNDEF NONNULL((1, 2)) __BOOL FCALL
sigmask_getmask_and_blockmask(sigset_t *__restrict oldmask,
                              sigset_t const *__restrict these)
		THROWS(E_SEGFAULT);
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL
NOTHROW(FCALL sigmask_getmask_and_blockmask)(sigset_t *__restrict oldmask,
                                             sigset_t const *__restrict these);
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */



/* Combination of `sigmask_getmask()' and `sigmask_unblockmask()'
 * @return: true:  Changes were made to the caller's signal mask. In
 *                 this case, the caller should make another call to
 *                 `userexcept_sysret_inject_self()'  in  order   to
 *                 check for pending signals upon the next return to
 *                 user-space (unless it  is known  that the  signal
 *                 mask didn't get less restrictive)
 * @return: false: The caller's signal mask remains unchanged. */
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
FUNDEF NONNULL((1, 2)) __BOOL FCALL
sigmask_getmask_and_unblockmask(sigset_t *__restrict oldmask,
                                sigset_t const *__restrict these)
		THROWS(E_SEGFAULT);
#else /* CONFIG_HAVE_KERNEL_USERPROCMASK */
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL
NOTHROW(FCALL sigmask_getmask_and_unblockmask)(sigset_t *__restrict oldmask,
                                               sigset_t const *__restrict these);
#endif /* !CONFIG_HAVE_KERNEL_USERPROCMASK */




/* Prepare the calling thread for a sigsuspend operation.
 *
 * This  function must be  called during the  setup phase of a
 * system call that intends to use `task_serve_with_sigmask()' */
FUNDEF NOBLOCK void
NOTHROW(FCALL sigmask_prepare_sigsuspend)(void);


DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIGMASK_H */
