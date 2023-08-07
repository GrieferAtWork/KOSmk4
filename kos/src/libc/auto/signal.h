/* HASH CRC-32:0xfc9170fa */
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
#ifndef GUARD_LIBC_AUTO_SIGNAL_H
#define GUARD_LIBC_AUTO_SIGNAL_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <signal.h>

DECL_BEGIN

#include <pthread.h>
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_NCX(LIBDCALL libd_tgkill)(pid_t pid, pid_t tid, signo_t signo);
/* >> sigblock(3)
 * Deprecated  method  of  SIG_BLOCK-ing  a  given  set  of
 * signals. Modern code should use `sigprocmask()' instead.
 * @return: * : First 32 bits of previous signal mask (or however many fit in `int') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigblock)(int mask);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sigblock(3)
 * Deprecated  method  of  SIG_BLOCK-ing  a  given  set  of
 * signals. Modern code should use `sigprocmask()' instead.
 * @return: * : First 32 bits of previous signal mask (or however many fit in `int') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigblock)(int mask);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sigsetmask(3)
 * Deprecated method of SIG_SETMASK-ing a given set of signals.
 * Modern code should  use `sigprocmask(SIG_SETMASK)'  instead.
 * @return: * : First 32 bits of previous signal mask (or however many fit in `int') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigsetmask)(int mask);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sigsetmask(3)
 * Deprecated method of SIG_SETMASK-ing a given set of signals.
 * Modern code should  use `sigprocmask(SIG_SETMASK)'  instead.
 * @return: * : First 32 bits of previous signal mask (or however many fit in `int') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigsetmask)(int mask);
/* >> sigsetmask(3)
 * Deprecated method of  retrieving the masking-state  of
 * the lowest-numberred `sizeof(int) * NBBY - 1' signals.
 * @return: * : First 32 bits of signal mask (or however many fit in `int') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_siggetmask)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> __old_sigpause(3)
 * For historical reasons, this is the ABI `sigpause(3)' function... */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigpause)(int sigmask0);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> __old_sigpause(3)
 * For historical reasons, this is the ABI `sigpause(3)' function... */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigpause)(int sigmask0);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Don't  call directly. Used internally to resume
 * execution when returning from a signal handler. */
INTDEF ATTR_NORETURN void NOTHROW_NCX(LIBDCALL libd_sigreturn)(struct sigcontext const *scp);
/* >> sigpause(3)
 * Atomically save and set the caller's signal mask to consist solely
 * of the signal signal `signo', then wait for that signal to  arrive
 * before restoring the old signal mask.
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
INTDEF int NOTHROW_NCX(LIBDCALL libd___xpg_sigpause)(signo_t signo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sigpause(3)
 * Atomically save and set the caller's signal mask to consist solely
 * of the signal signal `signo', then wait for that signal to  arrive
 * before restoring the old signal mask.
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
INTDEF int NOTHROW_NCX(LIBCCALL libc___xpg_sigpause)(signo_t signo);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> kill(2)
 * Raise a signal `signo' within the process(es) specified by `pid':
 *   - pid > 0:   Deliver `signo' to a process who's PID matches `pid'.
 *   - pid == 0:  Deliver `signo' to every process within the caller's process group.
 *   - pid == -1: Deliver  `signo'  to  every process  the  caller has  permission  to send
 *                signals to, with the exception of a process with pid=1 (i.e. `/bin/init')
 *   - pid < -1:  Deliver `signo' to every process within the process group `-pid'
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
 * @return: -1:   [errno=ESRCH]  No process is identified by `pid' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_kill)(pid_t pid, signo_t signo);
/* >> sigemptyset(3)
 * Clear the given signal set of all contained signals
 * @return: 0: Always returns `0' */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_sigemptyset)(sigset_t *set);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> sigemptyset(3)
 * Clear the given signal set of all contained signals
 * @return: 0: Always returns `0' */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_sigemptyset)(sigset_t *set);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sigfillset(3)
 * Add all possible signals (possibly even including undefined signals,
 * though these would be ignored by the kernel) to the given signal set
 * @return: 0: Always returns `0' */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_sigfillset)(sigset_t *set);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> sigfillset(3)
 * Add all possible signals (possibly even including undefined signals,
 * though these would be ignored by the kernel) to the given signal set
 * @return: 0: Always returns `0' */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_sigfillset)(sigset_t *set);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_sigaddset)(sigset_t *set, signo_t signo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_sigaddset)(sigset_t *set, signo_t signo);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sigdelset(3)
 * Remove only the given `signo' from the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_sigdelset)(sigset_t *set, signo_t signo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> sigdelset(3)
 * Remove only the given `signo' from the given signal set
 * @return: 0:  Success (Always returned by the kernel-version)
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_sigdelset)(sigset_t *set, signo_t signo);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
 * @return:  1: The given `signo' is apart of `set'
 * @return:  0: The given `signo' isn't apart of `set'
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_sigismember)(sigset_t const *set, signo_t signo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: >1: The given `signo' is apart of `set' (may be returned by the kernel-version of this function)
 * @return:  1: The given `signo' is apart of `set'
 * @return:  0: The given `signo' isn't apart of `set'
 * @return: -1: [errno=EINVAL] invalid `signo'.
 *              Not returned by the kernel-version of this function! */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc_sigismember)(sigset_t const *set, signo_t signo);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* Change  the signal mask for the calling thread. Note that portable
 * programs that also make use of multithreading must instead use the
 * pthread-specific  `pthread_sigmask()'  function instead,  as POSIX
 * states that  this function  behaves undefined  in such  scenarios.
 * However, on KOS, `pthread_sigmask()' is  simply an alias for  this
 * function,  and  `sigprocmask()'   always  operates   thread-local.
 * Note also  that on  KOS 2  additional functions  `getsigmaskptr()'
 * and `setsigmaskptr()'  exist, which  can be  used to  get/set  the
 * address of the signal mask used by the kernel.
 * @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] Invalid `how' */
INTDEF ATTR_IN_OPT(2) ATTR_OUT_OPT(3) int NOTHROW_NCX(LIBDCALL libd_sigprocmask)(__STDC_INT_AS_UINT_T how, sigset_t const *set, sigset_t *oset);
/* >> setsigmaskptr(3)
 * Set  the  current  signal  mask  pointer  to `sigmaskptr'
 * This  is  a kos-specific  function  that can  be  used to
 * speed up/replace  calls  to  `sigprocmask()'.  But  using
 * this function safely requires knowledge of its underlying
 * semantics. If you're unsure on those, you should  instead
 * just use the portable `sigprocmask()' and forget you ever
 * read this comment :)
 * Example usage:
 * >> static sigset_t const fullset = SIGSET_INIT_FULL;
 * >> sigset_t *oldset = setsigmaskptr((sigset_t *)&fullset);
 * >> // Code in here executes with all maskable signals masked
 * >> // Note however that code in here also mustn't call sigprocmask()
 * >> setsigmaskptr(oldset);
 * Equivalent code using sigprocmask (which has way more overhead):
 * >> static sigset_t const fullset = SIGSET_INIT_FULL;
 * >> sigset_t oldset;
 * >> sigprocmask(SIG_SETMASK, &fullset, &oldset);
 * >> // Code in here executes with all maskable signals masked
 * >> sigprocmask(SIG_SETMASK, &oldset, NULL);
 * @param: sigmaskptr: Address of the signal mask to use from now on.
 * @return: * : Address of the previously used signal mask. */
INTDEF ATTR_RETNONNULL NONNULL((1)) sigset_t *NOTHROW_NCX(LIBDCALL libd_setsigmaskptr)(sigset_t *sigmaskptr);
/* >> sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_sigsuspend)(sigset_t const *set);
/* >> sigaction(2)
 * Get/Set the  action that  shall  be performed  when  a
 * signal `signo' must be handled by the calling process.
 * This function will modify the caller's kernel-space signal handler  descriptor,
 * who's shared/unshared behavior between threads is controlled by `CLONE_SIGHAND'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
INTDEF ATTR_IN_OPT(2) ATTR_OUT_OPT(3) int NOTHROW_NCX(LIBDCALL libd_sigaction)(signo_t signo, struct sigaction const *act, struct sigaction *oact);
/* >> sigpending(2)
 * Retrieve the set of signals that are pending
 * in  either  the calling  thread  and process
 * @return: 0: Success */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_sigpending)(sigset_t *__restrict set);
/* >> sigwait(3)
 * Same as `sigsuspend(2)', but write-back the actual signal that was raised to `*signo'
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_RPC(LIBDCALL libd_sigwait)(sigset_t const *__restrict set, signo_t *__restrict signo);
/* >> sigisemptyset(3)
 * Check if the given signal set is empty
 * @return: != 0: Yes, it is empty
 * @return: == 0: No, at least 1 signal is contained */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_sigisemptyset)(sigset_t const *__restrict set);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> sigisemptyset(3)
 * Check if the given signal set is empty
 * @return: != 0: Yes, it is empty
 * @return: == 0: No, at least 1 signal is contained */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBCCALL libc_sigisemptyset)(sigset_t const *__restrict set);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sigandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & right[S]'
 * @return: 0: Always returns `0' */
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_sigandset)(sigset_t *set, sigset_t const *left, sigset_t const *right);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> sigandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & right[S]'
 * @return: 0: Always returns `0' */
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_sigandset)(sigset_t *set, sigset_t const *left, sigset_t const *right);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sigorset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] | right[S]'
 * @return: 0: Always returns `0' */
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_sigorset)(sigset_t *set, sigset_t const *left, sigset_t const *right);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> sigorset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] | right[S]'
 * @return: 0: Always returns `0' */
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_sigorset)(sigset_t *set, sigset_t const *left, sigset_t const *right);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> signandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & ~right[S]'
 * @return: 0: Always returns `0' */
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_signandset)(sigset_t *set, sigset_t const *left, sigset_t const *right);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> signandset(3)
 * Set-up every signal `S' from `set' as the result of `set[S] = left[S] & ~right[S]'
 * @return: 0: Always returns `0' */
INTDEF ATTR_IN(2) ATTR_IN(3) ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_signandset)(sigset_t *set, sigset_t const *left, sigset_t const *right);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sigwaitinfo(2)
 * Same as `sigsuspend(2)',  but write-back extended  information in the  signal,
 * as it would/has also been passed to a signal handler's second (info) argument.
 * @param: set:  The set of signals on which to wait
 * @param: info: Information about the signal on which to wait.
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
INTDEF ATTR_IN(1) ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBDCALL libd_sigwaitinfo)(sigset_t const *__restrict set, siginfo_t *__restrict info);
/* >> sigtimedwait(2), sigtimedwait64(2)
 * Same as `sigwaitinfo(2)', but stop waiting after a total of `rel_timeout' has passed
 * @param: set:         The set of signals on which to wait
 * @param: info:        Information about the signal on which to wait.
 * @param: rel_timeout: The timeout specifying for how long to wait (or `NULL' to wait indefinitely)
 * @return: -1: [errno=EINTR]  The signal handler for `signo' was executed.
 * @return: -1: [errno=EAGAIN] A total of `rel_timeout' has passed. */
INTDEF ATTR_IN(1) ATTR_IN_OPT(3) ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBDCALL libd_sigtimedwait)(sigset_t const *__restrict set, siginfo_t *__restrict info, struct timespec const *rel_timeout);
/* >> sigqueue(2)
 * Similar to  `kill(2)',  but  `pid'  must  be positive  and  reference  a  process's  PID,
 * meaning that this function can only be used to send a signal to single, specific process.
 * @param: pid:   The PID of the process that shall receive the signal.
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @param: val:   An additional value to pass alongside the signal itself. This value can
 *                read as `info->si_value' from within a 3-arg signal handler established
 *                by `pid', or  may also be  returned by a  call to `sigwaitinfo(2)'  and
 *                friends made by `pid'.
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
 * @return: -1:   [errno=ESRCH]  No process is identified by `pid' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigqueue)(pid_t pid, signo_t signo, union sigval const val);
/* >> sigtimedwait(2), sigtimedwait64(2)
 * Same as `sigwaitinfo(2)', but stop waiting after a total of `rel_timeout' has passed
 * @param: set:         The set of signals on which to wait
 * @param: info:        Information about the signal on which to wait.
 * @param: rel_timeout: The timeout specifying for how long to wait (or `NULL' to wait indefinitely)
 * @return: -1: [errno=EINTR]  The signal handler for `signo' was executed.
 * @return: -1: [errno=EAGAIN] A total of `rel_timeout' has passed. */
INTDEF ATTR_IN(1) ATTR_IN_OPT(3) ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBDCALL libd_sigtimedwait64)(sigset_t const *__restrict set, siginfo_t *__restrict info, struct timespec64 const *rel_timeout);
/* >> sigqueueinfo(2)
 * Similar to  `sigqueue(2)',  but  instead  of  only being  able  to  specify  a  custom
 * signal  value, everything  about signal meta-data  can be specified  by this function.
 * Note however  that  various privileges  are  required  to provide  custom  values  for
 * different values of `uinfo' that don't match what the equivalent call to `sigqueue(2)'
 * would have used.
 * @param: pid:   The PID of the process that shall receive the signal.
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @param: uinfo: Signal information to pass alongside the signal itself.
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EINVAL] The given `signo' doesn't match `uinfo->si_signo'
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
 * @return: -1:   [errno=EPERM]  `info->si_code' is invalid, and `pid' is a different process
 * @return: -1:   [errno=ESRCH]  No process is identified by `pid' */
INTDEF ATTR_IN(3) int NOTHROW_NCX(LIBDCALL libd_sigqueueinfo)(pid_t pid, signo_t signo, siginfo_t const *uinfo);
/* >> tgsigqueueinfo(2)
 * Similar  to `sigqueueinfo(2)', rather than sending a signal to a process
 * as a whole, only send the signal to a single thread within that process.
 * @param: pid:   The PID of the process that shall receive the signal.
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @param: uinfo: Signal information to pass alongside the signal itself.
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EINVAL] The given `signo' doesn't match `uinfo->si_signo'
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pid'
 * @return: -1:   [errno=EPERM]  `info->si_code' is invalid, and `pid' is a different process
 * @return: -1:   [errno=ESRCH]  No process is identified by `pid' */
INTDEF ATTR_IN(4) int NOTHROW_NCX(LIBDCALL libd_tgsigqueueinfo)(pid_t pid, pid_t tid, signo_t signo, siginfo_t const *uinfo);
/* >> killpg(3)
 * Alias for `kill(-pgrp, signo)'
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pgrp'
 * @return: -1:   [errno=ESRCH]  No process group is identified by `pgrp' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_killpg)(pid_t pgrp, signo_t signo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> killpg(3)
 * Alias for `kill(-pgrp, signo)'
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @return: 0:    Success
 * @return: -1:   [errno=EINVAL] The given `signo' is invalid
 * @return: -1:   [errno=EPERM]  The caller does not have permission to send signals to `pgrp'
 * @return: -1:   [errno=ESRCH]  No process group is identified by `pgrp' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_killpg)(pid_t pgrp, signo_t signo);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> psignal(3)
 * Same as `fprintf(stderr, "%s: %s\n", s, sigabbrev_np(signo) ? "SIG"+. : strdupf("Unknown signal %d", signo))'
 * When `s' is `NULL' or an empty string, omit the leading "%s: " from the format. */
INTDEF void NOTHROW_CB_NCX(LIBDCALL libd_psignal)(signo_t signo, char const *s);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> psignal(3)
 * Same as `fprintf(stderr, "%s: %s\n", s, sigabbrev_np(signo) ? "SIG"+. : strdupf("Unknown signal %d", signo))'
 * When `s' is `NULL' or an empty string, omit the leading "%s: " from the format. */
INTDEF void NOTHROW_CB_NCX(LIBCCALL libc_psignal)(signo_t signo, char const *s);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> psiginfo(3)
 * Similar to `psignal(3)', but instead print extended signal information from `*pinfo' */
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) void NOTHROW_CB_NCX(LIBDCALL libd_psiginfo)(siginfo_t const *pinfo, char const *s);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> psiginfo(3)
 * Similar to `psignal(3)', but instead print extended signal information from `*pinfo' */
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) void NOTHROW_CB_NCX(LIBCCALL libc_psiginfo)(siginfo_t const *pinfo, char const *s);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sigcodename_np(3)
 * Return a name of `code', as read from `siginfo_t::si_code',
 * and used  in  conjunction  with  a  given  signal  `signo'.
 * e.g.   `sigcodename_np(SIGILL, ILL_ILLOPC) -> "ILL_ILLOPC"' */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBDCALL libd_sigcodename_np)(signo_t signo, int code);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> sigcodename_np(3)
 * Return a name of `code', as read from `siginfo_t::si_code',
 * and used  in  conjunction  with  a  given  signal  `signo'.
 * e.g.   `sigcodename_np(SIGILL, ILL_ILLOPC) -> "ILL_ILLOPC"' */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_sigcodename_np)(signo_t signo, int code);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sigcodedesc_np(3)
 * Return a textual description of `code', as read from `siginfo_t::si_code',
 * and used in conjunction with a given signal `signo'. This function is used
 * for the implementation of `psiginfo(3)' */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBDCALL libd_sigcodedesc_np)(signo_t signo, int code);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> sigcodedesc_np(3)
 * Return a textual description of `code', as read from `siginfo_t::si_code',
 * and used in conjunction with a given signal `signo'. This function is used
 * for the implementation of `psiginfo(3)' */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBCCALL libc_sigcodedesc_np)(signo_t signo, int code);
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> siginterrupt(3)
 * Set the `SA_RESTART' of the already-established signal handler for `signo',
 * as well as cause any future handler established by `bsd_signal()' or one of
 * its aliases to immediately be established with `SA_RESTART' set/cleared
 * @param: interrupt: When == 0: clear `SA_RESTART' for the signal handler of `signo'
 *                    When != 0: set `SA_RESTART'  for the signal handler of  `signo'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
INTDEF int NOTHROW_NCX(LIBDCALL libd_siginterrupt)(signo_t signo, __STDC_INT_AS_UINT_T interrupt);
/* >> sigstack(2)
 * Deprecated, and slightly different version of `sigaltstack(2)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN_OPT(1) ATTR_OUT_OPT(2) int NOTHROW_NCX(LIBDCALL libd_sigstack)(struct sigstack const *ss, struct sigstack *oss);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sigstack(2)
 * Deprecated, and slightly different version of `sigaltstack(2)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN_OPT(1) ATTR_OUT_OPT(2) int NOTHROW_NCX(LIBCCALL libc_sigstack)(struct sigstack const *ss, struct sigstack *oss);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sigaltstack(2)
 * Get/Set the alternate signal stack for the calling thread. When set,
 * the alternate signal stack can be used to host signal handlers  that
 * have been established with the `SA_ONSTACK' flag in `sa_flags'.
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN_OPT(1) ATTR_OUT_OPT(2) int NOTHROW_NCX(LIBDCALL libd_sigaltstack)(struct sigaltstack const *ss, struct sigaltstack *oss);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc_set_single_signal_masked)(signo_t sig, int how);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sighold(3)
 * Mask a single signal  `signo', which is the  same
 * as `sigprocmask(SIG_BLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sighold)(signo_t signo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sighold(3)
 * Mask a single signal  `signo', which is the  same
 * as `sigprocmask(SIG_BLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sighold)(signo_t signo);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sighold(3)
 * Unmask a single signal  `signo', which is the  same
 * as `sigprocmask(SIG_UNBLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigrelse)(signo_t signo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sighold(3)
 * Unmask a single signal  `signo', which is the  same
 * as `sigprocmask(SIG_UNBLOCK, MASKFOR(signo), NULL)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigrelse)(signo_t signo);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sigignore(3)
 * Change the disposition of `signo' to `SIG_IGN' using `bsd_signal(3)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigignore)(signo_t signo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sigignore(3)
 * Change the disposition of `signo' to `SIG_IGN' using `bsd_signal(3)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigignore)(signo_t signo);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sigset(3)
 * Set the handler of `signo'  to `disp', or add `signo'  to
 * the calling threads's signal mask when `disp == SIG_HOLD'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_sigset)(signo_t signo, sighandler_t disp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sigset(3)
 * Set the handler of `signo'  to `disp', or add `signo'  to
 * the calling threads's signal mask when `disp == SIG_HOLD'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_sigset)(signo_t signo, sighandler_t disp);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF WUNUSED signo_t NOTHROW_NCX(LIBDCALL libd___libc_allocate_rtsig)(int high);
/* >> pthread_kill(3)
 * Portable function for sending a signal to a specific `pthread' within one's own process.
 * @return: EOK:    Success
 * @return: EINVAL: The given `signo' is invalid */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_kill)(pthread_t pthread, signo_t signo);
/* >> pthread_sigqueue(3)
 * This function is for `pthread_kill(3)', what `sigqueue(2)' is for  `kill(2)',
 * in that it sends a signal to `pthread', alongside a custom signal value `val'
 * @param: signo: The signal number to deliver. When set to `0', no signal is  delivered,
 *                and this function can be used to test if the caller would be allowed to
 *                send signals to the process(es) specified by `pid'
 * @param: val:   An additional value to pass alongside the signal itself. This value can
 *                read as `info->si_value' from within a 3-arg signal handler established
 *                by `pid', or  may also be  returned by a  call to `sigwaitinfo(2)'  and
 *                friends made by `pid'.
 * @return: EOK:    Success
 * @return: EINVAL: The given `signo' is invalid
 * @return: ESRCH:  The given `pthread' has already terminated, and could no longer handle the signal */
INTDEF errno_t NOTHROW_NCX(LIBDCALL libd_pthread_sigqueue)(pthread_t pthread, signo_t signo, union sigval const val);
/* >> signalnumber(3)
 * Similar to `strtosigno(3)', however ignore any leading `SIG*'
 * prefix of `name', and  do a case-insensitive compare  between
 * the given `name', and the  signal's actual name. When  `name'
 * isn't recognized, return `0' instead.
 * This function also handles stuff like "SIGRTMIN+1" or "9" */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) signo_t NOTHROW_NCX(LIBDCALL libd_signalnumber)(const char *name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> signalnumber(3)
 * Similar to `strtosigno(3)', however ignore any leading `SIG*'
 * prefix of `name', and  do a case-insensitive compare  between
 * the given `name', and the  signal's actual name. When  `name'
 * isn't recognized, return `0' instead.
 * This function also handles stuff like "SIGRTMIN+1" or "9" */
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) signo_t NOTHROW_NCX(LIBCCALL libc_signalnumber)(const char *name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> signalnext(3)
 * Return the next-greater signal number that comes after `signo'
 * When  no such signal number exists, return `0'. When the given
 * `signo' is `0', return the lowest valid signal number. */
INTDEF ATTR_CONST WUNUSED signo_t NOTHROW(LIBDCALL libd_signalnext)(signo_t signo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> signalnext(3)
 * Return the next-greater signal number that comes after `signo'
 * When  no such signal number exists, return `0'. When the given
 * `signo' is `0', return the lowest valid signal number. */
INTDEF ATTR_CONST WUNUSED signo_t NOTHROW(LIBCCALL libc_signalnext)(signo_t signo);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> sig2str(3)
 * Wrapper around  `sigabbrev_np(3)', that  also adds  additional
 * handling for `SIGRTMIN...`SIGRTMAX' signals, which are encoded
 * in a way that is compatible with `str2sig(3)'. */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_sig2str)(signo_t signo, char buf[32]);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> sig2str(3)
 * Wrapper around  `sigabbrev_np(3)', that  also adds  additional
 * handling for `SIGRTMIN...`SIGRTMAX' signals, which are encoded
 * in a way that is compatible with `str2sig(3)'. */
INTDEF ATTR_OUT(2) int NOTHROW_NCX(LIBCCALL libc_sig2str)(signo_t signo, char buf[32]);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> str2sig(3)
 * More restrictive version of `signalnumber(3)':
 *  - Requires all name-characters to be upper-case
 *  - Doesn't automatically remove any "SIG" prefix.
 * @return: 0 : Success; `*p_signo' was filled
 * @return: -1: Unrecognized `name' (`errno(3)' was _NOT_ modified) */
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBDCALL libd_str2sig)(const char *name, signo_t *p_signo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> str2sig(3)
 * More restrictive version of `signalnumber(3)':
 *  - Requires all name-characters to be upper-case
 *  - Doesn't automatically remove any "SIG" prefix.
 * @return: 0 : Success; `*p_signo' was filled
 * @return: -1: Unrecognized `name' (`errno(3)' was _NOT_ modified) */
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_NCX(LIBCCALL libc_str2sig)(const char *name, signo_t *p_signo);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SIGNAL_H */
