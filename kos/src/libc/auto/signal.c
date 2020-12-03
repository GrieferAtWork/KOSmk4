/* HASH CRC-32:0x9108f82e */
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
#ifndef GUARD_LIBC_AUTO_SIGNAL_C
#define GUARD_LIBC_AUTO_SIGNAL_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/signal.h"
#include "../user/stdio.h"
#include "../user/string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/signal.h>
#include <bits/os/sigset.h>
/* >> sigblock(3)
 * Deprecated method of SIG_BLOCK-ing a given set of signals.
 * Modern code should use `sigprocmask()' instead.
 * @return: 0: Success */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_DEPRECATED("Using `sigprocmask(SIG_BLOCK)\' instead") int
NOTHROW_NCX(LIBCCALL libc_sigblock)(int mask) {
	sigset_t sigset;
	libc_sigemptyset(&sigset);
	sigset.__val[0] = (uintptr_t)(unsigned int)mask;
	return libc_sigprocmask(__SIG_BLOCK, &sigset, NULL);
}
#include <asm/os/signal.h>
#include <bits/os/sigset.h>
/* >> sigsetmask(3)
 * Deprecated method of SIG_SETMASK-ing a given set of signals.
 * Modern code should use `sigprocmask(SIG_SETMASK)' instead.
 * @return: 0: Success */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_DEPRECATED("Using `sigprocmask()\' instead") int
NOTHROW_NCX(LIBCCALL libc_sigsetmask)(int mask) {
	sigset_t sigset;
	libc_sigemptyset(&sigset);
	sigset.__val[0] = (uintptr_t)(unsigned int)mask;
	return libc_sigprocmask(__SIG_SETMASK, &sigset, NULL);
}
#include <asm/os/signal.h>
#include <bits/os/sigset.h>
#include <hybrid/typecore.h>
/* >> sigsetmask(3)
 * Deprecated method of retrieving the masking-state of
 * the lowest-numberred `sizeof(int) * NBBY - 1' signals.
 * @return: <= INT_MAX: An incomplete signal mask bitset for a couple
 *                      of the lowest-numbered couple of signal.
 * @return: -1:         Error */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_DEPRECATED("Using `sigprocmask()\' instead") int
NOTHROW_NCX(LIBCCALL libc_siggetmask)(void) {
	sigset_t sigset;
#ifdef __SIG_SETMASK
	if (libc_sigprocmask(__SIG_SETMASK, NULL, &sigset))
		return -1;
#else /* __SIG_SETMASK */
	if (libc_sigprocmask(0, NULL, &sigset))
		return -1;
#endif /* !__SIG_SETMASK */
	return sigset.__val[0] & __INT_MAX__;
}
/* >> sigpause(3)
 * Atomically save and set the caller's signal mask to consist solely
 * of the signal signal `signo', then wait for that signal to arrive
 * before restoring the old signal mask.
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc___xpg_sigpause)(signo_t signo) {
	sigset_t mask;
	libc_sigemptyset(&mask);
	libc_sigaddset(&mask, signo);
	return libc_sigsuspend(&mask);
}
#endif /* !__KERNEL__ */
#include <bits/os/sigset.h>
/* >> sigemptyset(3)
 * Clear the given signal set of all contained signals
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigemptyset)(sigset_t *set) {
	libc_bzeroc(set->__val, COMPILER_LENOF(set->__val), __SIZEOF_POINTER__);
	return 0;
}
/* >> sigfillset(3)
 * Add all possible signals (possibly even including undefined signals,
 * though these would be ignored by the kernel) to the given signal set
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigfillset)(sigset_t *set) {
#if __SIZEOF_POINTER__ == 8
	libc_memsetq(set->__val, __UINT64_C(0xffffffffffffffff), COMPILER_LENOF(set->__val));
#elif __SIZEOF_POINTER__ == 4
	libc_memsetl(set->__val, __UINT32_C(0xffffffff), COMPILER_LENOF(set->__val));
#elif __SIZEOF_POINTER__ == 2
	libc_memsetw(set->__val, __UINT16_C(0xffff), COMPILER_LENOF(set->__val));
#else /* ... */
	libc_memset(set->__val, __UINT8_C(0xff), __SIZEOF_SIGSET_T__);
#endif /* !... */
	return 0;
}
#include <libc/errno.h>
#include <asm/os/signal.h>
#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#ifdef __KERNEL__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ */
#if defined(__KERNEL__) && defined(__KOS__)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) /* nothing */
#elif defined(__NSIG) && defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(__EINVAL);          \
	}
#elif defined(__NSIG)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(1);                 \
	}
#elif defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(__EINVAL);      \
	}
#else /* ... */
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(1);             \
	}
#endif /* !... */
#endif /* !__PRIVATE_SIGSET_VALIDATE_SIGNO */
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigaddset)(sigset_t *set,
                                     signo_t signo) {
	ulongptr_t mask, word;
	__PRIVATE_SIGSET_VALIDATE_SIGNO(signo)
	mask = __sigset_mask(signo);
	word = __sigset_word(signo);
	set->__val[word] |= mask;
	return 0;
}
/* >> sigdelset(3)
 * Remove only the given `signo' from the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigdelset)(sigset_t *set,
                                     signo_t signo) {
	ulongptr_t mask, word;
	__PRIVATE_SIGSET_VALIDATE_SIGNO(signo)
	mask = __sigset_mask(signo);
	word = __sigset_word(signo);
	set->__val[word] &= ~mask;
	return 0;
}
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
 * @return:  1: The given `signo' is apart of `set'
 * @return:  0: The given `signo' isn't apart of `set'
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigismember)(sigset_t const *set,
                                       signo_t signo) {
	ulongptr_t mask, word;
	__PRIVATE_SIGSET_VALIDATE_SIGNO(signo)
	mask = __sigset_mask(signo);
	word = __sigset_word(signo);
	return (set->__val[word] & mask) __PRIVATE_SIGSET_ISMEMBER_EXT;
}
/* >> sigisemptyset(3)
 * Check if the given signal set is empty
 * @return: != 0: The given `set' is non-empty
 * @return: == 0: The given `set' is empty */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigisemptyset)(sigset_t const *__restrict set) {
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(ulongptr_t); ++i) {
		if (set->__val[i])
			return 0;
	}
	return 1;
}
/* >> sigandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & right[S]'
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_sigandset)(sigset_t *set,
                                     sigset_t const *left,
                                     sigset_t const *right) {
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(ulongptr_t); ++i)
		set->__val[i] = left->__val[i] & right->__val[i];
	return 0;
}
/* >> sigorset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] | right[S]'
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_sigorset)(sigset_t *set,
                                    sigset_t const *left,
                                    sigset_t const *right) {
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(ulongptr_t); ++i)
		set->__val[i] = left->__val[i] | right->__val[i];
	return 0;
}
/* >> signandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & ~right[S]'
 * @return: 0: Always returns `0' */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBCCALL libc_signandset)(sigset_t *set,
                                      sigset_t const *left,
                                      sigset_t const *right) {
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(ulongptr_t); ++i)
		set->__val[i] = left->__val[i] & ~right->__val[i];
	return 0;
}
#ifndef __KERNEL__
/* >> killpg(3)
 * Alias for `kill(-pgrp, signo)'
 * @param: signo: The signal number to deliver. When set to `0', no signal is delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pgrp'
 * @return: -1:   [errno=ESRCH]  No process group is identified by `pgrp' */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_killpg)(pid_t pgrp,
                                  signo_t signo) {
	return libc_kill(-pgrp, signo);
}
/* >> psignal(3)
 * Same as `fprintf(stderr, "%s: %s\n", s, strsignal_s(signo) ?: strdupf("Unknown signal %d", signo))'
 * When `s' is `NULL' or an empty string, omit the leading "%s: " from the format. */
INTERN ATTR_SECTION(".text.crt.sched.signal") void
NOTHROW_NCX(LIBCCALL libc_psignal)(signo_t signo,
                                   char const *s) {
	char const *signam = libc_strsignal_s(signo);
	if (s && *s)
		libc_fprintf(stderr, "%s: ", s);
	if (signam) {
		libc_fprintf(stderr, "%s\n", signam);
	} else {
		libc_fprintf(stderr, "Unknown signal %d\n", signo);
	}
}
#include <bits/os/sigstack.h>
/* >> sigstack(2)
 * Deprecated, and slightly different version of `sigaltstack(2)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigstack)(struct sigstack *ss,
                                    struct sigstack *oss) {
	struct sigaltstack ass, aoss;
	int result;
	if (ss) {
		ass.ss_flags = ss->ss_onstack
		                 ? __SS_ONSTACK
		                 : __SS_DISABLE;
		ass.ss_sp   = ss->ss_sp;
		ass.ss_size = (size_t)-1;
	}
	result = libc_sigaltstack(ss ? &ass : NULL,
	                     oss ? &aoss : NULL);
	if (likely(!result) && oss) {
		oss->ss_onstack = !!(aoss.ss_flags & __SS_ONSTACK);
		oss->ss_sp      = aoss.ss_sp;
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_set_single_signal_action)(int sig,
                                                    int how) {
	sigset_t set;
	libc_sigemptyset(&set);
	libc_sigaddset(&set, sig);
	return libc_sigprocmask(how, &set, NULL);
}
/* >> sighold(3)
 * Mask a single signal `signo', which is the same
 * as `sigprocmask(SIG_BLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sighold)(signo_t signo) {
	return libc_set_single_signal_action(signo, __SIG_BLOCK);
}
/* >> sighold(3)
 * Unmask a single signal `signo', which is the same
 * as `sigprocmask(SIG_UNBLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigrelse)(signo_t signo) {
	return libc_set_single_signal_action(signo, __SIG_UNBLOCK);
}
/* >> sigignore(3)
 * Change the disposition of `signo' to `SIG_IGN' using `bsd_signal(3)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigignore)(signo_t signo) {
	return libc_bsd_signal(signo, (sighandler_t)__SIG_IGN) == (sighandler_t)__SIG_ERR ? -1 : 0;
}
#include <bits/os/sigaction.h>
/* >> sigset(3)
 * Set the handler of `signo' to `disp', or add `signo' to
 * the calling threads's signal mask when `disp == SIG_HOLD'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") sighandler_t
NOTHROW_NCX(LIBCCALL libc_sigset)(signo_t signo,
                                  sighandler_t disp) {
	struct sigaction act, oact;
	sigset_t set, oset;
	if unlikely(disp == (sighandler_t)__SIG_ERR)
		goto err_inval;
	libc_sigemptyset(&set);
	libc_sigaddset(&set, signo);
	if (disp == (sighandler_t)__SIG_HOLD) {
		if unlikely(libc_sigprocmask(__SIG_BLOCK, &set, &oset) != 0)
			goto err;
		if unlikely(libc_sigismember(&oset, signo))
			goto err;
		if unlikely(libc_sigaction(signo, NULL, &oact) != 0)
			goto err;
		return oact.sa_handler;
	}
	act.sa_handler = disp;
	libc_sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if unlikely(libc_sigaction(signo, &act, &oact) != 0)
		goto err;
	if unlikely(libc_sigprocmask(SIG_UNBLOCK, &set, &oset) != 0)
		goto err;
	return libc_sigismember(&oset, signo)
	       ? (sighandler_t)__SIG_HOLD
	       : oact.sa_handler;
err_inval:
#ifdef EINVAL
	__libc_seterrno(EINVAL);
#else /* EINVAL */
	__libc_seterrno(1);
#endif /* !EINVAL */
err:
	return (sighandler_t)__SIG_ERR;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST WUNUSED signo_t
NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmin)(void) {
	return __SIGRTMIN;
}
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST WUNUSED signo_t
NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmax)(void) {
	return __SIGRTMAX;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(sigblock, libc_sigblock);
DEFINE_PUBLIC_ALIAS(sigsetmask, libc_sigsetmask);
DEFINE_PUBLIC_ALIAS(siggetmask, libc_siggetmask);
DEFINE_PUBLIC_ALIAS(__xpg_sigpause, libc___xpg_sigpause);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigemptyset, libc_sigemptyset);
DEFINE_PUBLIC_ALIAS(sigfillset, libc_sigfillset);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__sigaddset, libc_sigaddset);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigaddset, libc_sigaddset);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__sigdelset, libc_sigdelset);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigdelset, libc_sigdelset);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__sigismember, libc_sigismember);
#endif /* !__KERNEL__ */
DEFINE_PUBLIC_ALIAS(sigismember, libc_sigismember);
DEFINE_PUBLIC_ALIAS(sigisemptyset, libc_sigisemptyset);
DEFINE_PUBLIC_ALIAS(sigandset, libc_sigandset);
DEFINE_PUBLIC_ALIAS(sigorset, libc_sigorset);
DEFINE_PUBLIC_ALIAS(signandset, libc_signandset);
#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(killpg, libc_killpg);
DEFINE_PUBLIC_ALIAS(psignal, libc_psignal);
DEFINE_PUBLIC_ALIAS(sigstack, libc_sigstack);
DEFINE_PUBLIC_ALIAS(sighold, libc_sighold);
DEFINE_PUBLIC_ALIAS(sigrelse, libc_sigrelse);
DEFINE_PUBLIC_ALIAS(sigignore, libc_sigignore);
DEFINE_PUBLIC_ALIAS(sigset, libc_sigset);
DEFINE_PUBLIC_ALIAS(__libc_current_sigrtmin, libc___libc_current_sigrtmin);
DEFINE_PUBLIC_ALIAS(__libc_current_sigrtmax, libc___libc_current_sigrtmax);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SIGNAL_C */
