/* HASH CRC-32:0x66bc0ad7 */
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
#ifndef GUARD_LIBC_USER_SIGNAL_H
#define GUARD_LIBC_USER_SIGNAL_H 1

#include "../api.h"
#include "../auto/signal.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <signal.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> raise(3)
 * Raise a signal within the current thread.
 * In  a *-threaded process this is same as:
 *   *=multi:  `pthread_kill(pthread_self(), signo)'
 *   *=single: `kill(getpid(), signo)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
INTDEF int NOTHROW_NCX(LIBDCALL libd_raise)(signo_t signo);
/* >> raise(3)
 * Raise a signal within the current thread.
 * In  a *-threaded process this is same as:
 *   *=multi:  `pthread_kill(pthread_self(), signo)'
 *   *=single: `kill(getpid(), signo)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
INTDEF int NOTHROW_NCX(LIBCCALL libc_raise)(signo_t signo);
/* >> sysv_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> act.sa_flags   = (SA_RESETHAND | SA_NODEFER) & ~SA_RESTART;
 *     >> sigemptyset(&act.sa_mask);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_sysv_signal)(signo_t signo, sighandler_t handler);
/* >> sysv_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> act.sa_flags   = (SA_RESETHAND | SA_NODEFER) & ~SA_RESTART;
 *     >> sigemptyset(&act.sa_mask);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_sysv_signal)(signo_t signo, sighandler_t handler);
INTDEF int NOTHROW_NCX(LIBCCALL libc_tgkill)(pid_t pid, pid_t tid, signo_t signo);
/* >> signal(2/3)
 * Non-portable  signal  handler  establishment  function  that  behaves
 * either like `sysv_signal()', `bsd_signal()', or has its own behavior.
 * On KOS, this function behaves identical to `bsd_signal()'
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_signal)(signo_t signo, sighandler_t handler);
/* >> signal(2/3)
 * Non-portable  signal  handler  establishment  function  that  behaves
 * either like `sysv_signal()', `bsd_signal()', or has its own behavior.
 * On KOS, this function behaves identical to `bsd_signal()'
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_signal)(signo_t signo, sighandler_t handler);
/* >> ssignal(3)
 * Establish a software-signal-handler. This handler may or may not
 * be distinct from normal signal handlers, and should be triggered
 * by `gsignal(3)', rather than `raise(3)'.
 * On KOS, this function behaves identical to `bsd_signal()'
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_ssignal)(signo_t signo, sighandler_t handler);
/* >> ssignal(3)
 * Establish a software-signal-handler. This handler may or may not
 * be distinct from normal signal handlers, and should be triggered
 * by `gsignal(3)', rather than `raise(3)'.
 * On KOS, this function behaves identical to `bsd_signal()'
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_ssignal)(signo_t signo, sighandler_t handler);
/* >> gsignal(3)
 * Raise a software-signal  by invoking  a previously  established
 * software-signal-handler,  as   set  by   `ssignal(signo, ...)'.
 * This method by which a software signal is raised may or may not
 * be distinct from normal signal handlers.
 * On KOS, this function behaves identical to `raise()'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
INTDEF int NOTHROW_NCX(LIBDCALL libd_gsignal)(signo_t signo);
/* >> gsignal(3)
 * Raise a software-signal  by invoking  a previously  established
 * software-signal-handler,  as   set  by   `ssignal(signo, ...)'.
 * This method by which a software signal is raised may or may not
 * be distinct from normal signal handlers.
 * On KOS, this function behaves identical to `raise()'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
INTDEF int NOTHROW_NCX(LIBCCALL libc_gsignal)(signo_t signo);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char const *const *NOTHROW(LIBCCALL libc___p_sys_siglist)(void);
/* Don't  call directly. Used internally to resume
 * execution when returning from a signal handler. */
INTDEF ATTR_NORETURN void NOTHROW_NCX(LIBCCALL libc_sigreturn)(struct sigcontext const *scp);
/* >> bsd_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> sigemptyset(&act.sa_mask);
 *     >> sigaddset(&act.sa_mask, signo);
 *     >> act.sa_flags = sigismember(&[SIGNALS_WITH_SIGINTERRUPT], signo) ? 0 : SA_RESTART;
 *     >> SET_SIGRESTORE(act);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 *     Where `SIGNALS_WITH_SIGINTERRUPT' is the set of signals for  which
 *     `siginterrupt(3)' had last been called with a non-zero `interrupt'
 *     argument
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_bsd_signal)(signo_t signo, sighandler_t handler);
/* >> bsd_signal(3)
 * Wrapper for `sigaction(2)' to establish a signal handler as:
 *     >> struct sigaction act, oact
 *     >> act.sa_handler = handler;
 *     >> sigemptyset(&act.sa_mask);
 *     >> sigaddset(&act.sa_mask, signo);
 *     >> act.sa_flags = sigismember(&[SIGNALS_WITH_SIGINTERRUPT], signo) ? 0 : SA_RESTART;
 *     >> SET_SIGRESTORE(act);
 *     >> if (sigaction(signo, &act, &oact) != 0)
 *     >>     oact.sa_handler = SIG_ERR;
 *     >> return oact.sa_handler;
 *     Where `SIGNALS_WITH_SIGINTERRUPT' is the set of signals for  which
 *     `siginterrupt(3)' had last been called with a non-zero `interrupt'
 *     argument
 * @return: * :      The previous signal handler function.
 * @return: SIG_ERR: Error (s.a. `errno') */
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_bsd_signal)(signo_t signo, sighandler_t handler);
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
INTDEF int NOTHROW_NCX(LIBCCALL libc_kill)(pid_t pid, signo_t signo);
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
INTDEF ATTR_IN_OPT(2) ATTR_OUT_OPT(3) int NOTHROW_NCX(LIBCCALL libc_sigprocmask)(__STDC_INT_AS_UINT_T how, sigset_t const *set, sigset_t *oset);
/* >> getsigmaskptr(3)
 * Return   the   current  signal   mask  pointer.
 * See the documentation of `setsigmaskptr(3)' for
 * what this function is all about.
 * @return: * : A pointer to the calling thread's current signal mask */
INTDEF ATTR_RETNONNULL WUNUSED sigset_t *NOTHROW_NCX(LIBCCALL libc_getsigmaskptr)(void);
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
INTDEF ATTR_RETNONNULL NONNULL((1)) sigset_t *NOTHROW_NCX(LIBCCALL libc_setsigmaskptr)(sigset_t *sigmaskptr);
/* >> setsigmaskfullptr(3)
 * Same as  `setsigmaskptr()',  but  set a  statically  allocated,  fully
 * filled signal  mask  as  the calling  thread's  current  signal  mask.
 * This essentially means that this  function can be used to  temporarily
 * disable the reception of all  signals within the calling thread,  thus
 * allowing the thread to run  without being interrupted (by another  but
 * SIGKILL and SIGSTOP, which can't be masked), until the returned signal
 * mask is restored.
 * >> sigset_t *os;
 * >> os = setsigmaskfullptr();
 * >> ...
 * >> setsigmaskptr(os); */
INTDEF ATTR_RETNONNULL sigset_t *NOTHROW_NCX(LIBCCALL libc_setsigmaskfullptr)(void);
#endif /* !__KERNEL__ */
#if !defined(__KERNEL__) && defined(__LIBC_CONFIG_HAVE_USERPROCMASK)
/* >> getuserprocmask(3)
 * Return a pointer to the calling thread's userprocmask
 * This function is only  declared if supported by  libc */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED struct userprocmask *NOTHROW(LIBCCALL libc_getuserprocmask)(void);
/* >> chkuserprocmask(3)
 * Following the calling thread's userprocmask becoming less
 * restrictive, check for pending signals and handle them if
 * necessary
 * This function is only declared if supported by libc */
INTDEF void NOTHROW(LIBCCALL libc_chkuserprocmask)(void);
#endif /* !__KERNEL__ && __LIBC_CONFIG_HAVE_USERPROCMASK */
#ifndef __KERNEL__
/* >> sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the unmasked (iow: `!sigismember')-signals to arrive before restoring
 * the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBCCALL libc_sigsuspend)(sigset_t const *set);
/* >> sigaction(2)
 * Get/Set the  action that  shall  be performed  when  a
 * signal `signo' must be handled by the calling process.
 * This function will modify the caller's kernel-space signal handler  descriptor,
 * who's shared/unshared behavior between threads is controlled by `CLONE_SIGHAND'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
INTDEF ATTR_IN_OPT(2) ATTR_OUT_OPT(3) int NOTHROW_NCX(LIBCCALL libc_sigaction)(signo_t signo, struct sigaction const *act, struct sigaction *oact);
/* >> sigpending(2)
 * Retrieve the set of signals that are pending
 * in  either  the calling  thread  and process
 * @return: 0: Success */
INTDEF ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_sigpending)(sigset_t *__restrict set);
/* >> sigwait(3)
 * Same as `sigsuspend(2)', but write-back the actual signal that was raised to `*signo'
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
INTDEF ATTR_IN(1) ATTR_OUT(2) int NOTHROW_RPC(LIBCCALL libc_sigwait)(sigset_t const *__restrict set, signo_t *__restrict signo);
/* >> sigwaitinfo(2)
 * Same as `sigsuspend(2)',  but write-back extended  information in the  signal,
 * as it would/has also been passed to a signal handler's second (info) argument.
 * @param: set:  The set of signals on which to wait
 * @param: info: Information about the signal on which to wait.
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
INTDEF ATTR_IN(1) ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBCCALL libc_sigwaitinfo)(sigset_t const *__restrict set, siginfo_t *__restrict info);
/* >> sigtimedwait(2), sigtimedwait64(2)
 * Same as `sigwaitinfo(2)', but stop waiting after a total of `rel_timeout' has passed
 * @param: set:         The set of signals on which to wait
 * @param: info:        Information about the signal on which to wait.
 * @param: rel_timeout: The timeout specifying for how long to wait (or `NULL' to wait indefinitely)
 * @return: -1: [errno=EINTR]  The signal handler for `signo' was executed.
 * @return: -1: [errno=EAGAIN] A total of `rel_timeout' has passed. */
INTDEF ATTR_IN(1) ATTR_IN_OPT(3) ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBCCALL libc_sigtimedwait)(sigset_t const *__restrict set, siginfo_t *__restrict info, struct timespec const *rel_timeout);
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
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigqueue)(pid_t pid, signo_t signo, union sigval const val);
/* >> sigtimedwait(2), sigtimedwait64(2)
 * Same as `sigwaitinfo(2)', but stop waiting after a total of `rel_timeout' has passed
 * @param: set:         The set of signals on which to wait
 * @param: info:        Information about the signal on which to wait.
 * @param: rel_timeout: The timeout specifying for how long to wait (or `NULL' to wait indefinitely)
 * @return: -1: [errno=EINTR]  The signal handler for `signo' was executed.
 * @return: -1: [errno=EAGAIN] A total of `rel_timeout' has passed. */
INTDEF ATTR_IN(1) ATTR_IN_OPT(3) ATTR_OUT_OPT(2) int NOTHROW_RPC(LIBCCALL libc_sigtimedwait64)(sigset_t const *__restrict set, siginfo_t *__restrict info, struct timespec64 const *rel_timeout);
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
INTDEF ATTR_IN(3) int NOTHROW_NCX(LIBCCALL libc_sigqueueinfo)(pid_t pid, signo_t signo, siginfo_t const *uinfo);
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
INTDEF ATTR_IN(4) int NOTHROW_NCX(LIBCCALL libc_tgsigqueueinfo)(pid_t pid, pid_t tid, signo_t signo, siginfo_t const *uinfo);
/* >> siginterrupt(3)
 * Set the `SA_RESTART' of the already-established signal handler for `signo',
 * as well as cause any future handler established by `bsd_signal()' or one of
 * its aliases to immediately be established with `SA_RESTART' set/cleared
 * @param: interrupt: When == 0: clear `SA_RESTART' for the signal handler of `signo'
 *                    When != 0: set `SA_RESTART'  for the signal handler of  `signo'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
INTDEF int NOTHROW_NCX(LIBCCALL libc_siginterrupt)(signo_t signo, __STDC_INT_AS_UINT_T interrupt);
/* >> sigaltstack(2)
 * Get/Set the alternate signal stack for the calling thread. When set,
 * the alternate signal stack can be used to host signal handlers  that
 * have been established with the `SA_ONSTACK' flag in `sa_flags'.
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN_OPT(1) ATTR_OUT_OPT(2) int NOTHROW_NCX(LIBCCALL libc_sigaltstack)(struct sigaltstack const *ss, struct sigaltstack *oss);
INTDEF WUNUSED signo_t NOTHROW_NCX(LIBCCALL libc___libc_allocate_rtsig)(int high);
INTDEF ATTR_CONST WUNUSED signo_t NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmin)(void);
INTDEF ATTR_CONST WUNUSED signo_t NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmax)(void);
/* >> pthread_kill(3)
 * Portable function for sending a signal to a specific `pthread' within one's own process.
 * @return: EOK:    Success
 * @return: EINVAL: The given `signo' is invalid */
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_kill)(pthread_t pthread, signo_t signo);
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
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_pthread_sigqueue)(pthread_t pthread, signo_t signo, union sigval const val);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SIGNAL_H */
