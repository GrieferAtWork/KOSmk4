/* HASH CRC-32:0x2069052b */
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
#ifndef GUARD_LIBC_USER_SIGNAL_H
#define GUARD_LIBC_USER_SIGNAL_H 1

#include "../api.h"
#include "../auto/signal.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <signal.h>

DECL_BEGIN

#include <pthread.h>
#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBDCALL libd_raise)(signo_t signo);
INTDEF int NOTHROW_NCX(LIBCCALL libc_raise)(signo_t signo);
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_sysv_signal)(signo_t signo, sighandler_t handler);
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_sysv_signal)(signo_t signo, sighandler_t handler);
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_signal)(signo_t signo, sighandler_t handler);
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_signal)(signo_t signo, sighandler_t handler);
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_ssignal)(signo_t signo, sighandler_t handler);
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_ssignal)(signo_t signo, sighandler_t handler);
INTDEF int NOTHROW_NCX(LIBDCALL libd_gsignal)(signo_t signo);
INTDEF int NOTHROW_NCX(LIBCCALL libc_gsignal)(signo_t signo);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigblock)(int mask);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigsetmask)(int mask);
INTDEF int NOTHROW_NCX(LIBCCALL libc_siggetmask)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char const *const *NOTHROW(LIBCCALL libc___p_sys_siglist)(void);
INTDEF ATTR_NORETURN void NOTHROW_NCX(LIBCCALL libc_sigreturn)(struct sigcontext const *scp);
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_bsd_signal)(signo_t signo, sighandler_t handler);
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_bsd_signal)(signo_t signo, sighandler_t handler);
INTDEF int NOTHROW_NCX(LIBCCALL libc___xpg_sigpause)(signo_t signo);
INTDEF int NOTHROW_NCX(LIBCCALL libc_kill)(pid_t pid, signo_t signo);
/* Change the signal mask for the calling thread. Note that portable
 * programs that also make use of multithreading must instead use the
 * pthread-specific `pthread_sigmask()' function instead, as POSIX
 * states that this function behaves undefined in such szenarios.
 * However, on KOS, `pthread_sigmask()' is imply an alias for this
 * function, and `sigprocmask()' always operates thread-local.
 * Note also that on KOS 2 additional functions `getsigmaskptr()'
 * and `setsigmaskptr()' exist, which can be used to get/set the
 * address of the signal mask used by the kernel.
 * @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigprocmask)(__STDC_INT_AS_UINT_T how, sigset_t const *set, sigset_t *oset);
/* >> getsigmaskptr(3)
 * Return the current signal mask pointer.
 * See the documentation of `setsigmaskptr(3)' for
 * what this function is all about. */
INTDEF ATTR_RETNONNULL WUNUSED sigset_t *NOTHROW_NCX(LIBCCALL libc_getsigmaskptr)(void);
/* >> setsigmaskptr(3)
 * Set the current signal mask pointer to `sigmaskptr'
 * This is a kos-specific function that can be used to
 * speed up/replace calls to `sigprocmask()'. But using
 * this function safely requires knowledge of its underlying
 * semantics. If you're unsure on those, you should instead
 * just use the portable `sigprocmask()' and forget you ever
 * read this comment :)
 * Example usage:
 * >> static sigset_t const fullset = SIGSET_INIT_FULL;
 * >> sigset_t *oldset = setsigmaskptr((sigset_t *)&fullset);
 * >> // Code in here executes with all maskable signals masked
 * >> // Note however that code in here also musn't call sigprocmask()
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
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_sigsuspend)(sigset_t const *set);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigaction)(signo_t signo, struct sigaction const *act, struct sigaction *oact);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigpending)(sigset_t *__restrict set);
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_sigwait)(sigset_t const *__restrict set, signo_t *__restrict signo);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_sigwaitinfo)(sigset_t const *__restrict set, siginfo_t *__restrict info);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_sigtimedwait)(sigset_t const *__restrict set, siginfo_t *__restrict info, struct timespec const *timeout);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigqueue)(pid_t pid, signo_t signo, union sigval const val);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_sigtimedwait64)(sigset_t const *__restrict set, siginfo_t *__restrict info, struct timespec64 const *timeout);
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBCCALL libc_sigqueueinfo)(pid_t tgid, signo_t signo, siginfo_t const *uinfo);
INTDEF NONNULL((4)) int NOTHROW_NCX(LIBCCALL libc_tgsigqueueinfo)(pid_t tgid, pid_t tid, signo_t signo, siginfo_t const *uinfo);
INTDEF int NOTHROW_NCX(LIBCCALL libc_killpg)(pid_t pgrp, signo_t signo);
INTDEF void NOTHROW_NCX(LIBCCALL libc_psignal)(signo_t signo, char const *s);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_psiginfo)(siginfo_t const *pinfo, char const *s);
INTDEF int NOTHROW_NCX(LIBCCALL libc_siginterrupt)(signo_t signo, __STDC_INT_AS_UINT_T interrupt);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigstack)(struct sigstack *ss, struct sigstack *oss);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigaltstack)(struct sigaltstack const *ss, struct sigaltstack *oss);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sighold)(signo_t signo);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigrelse)(signo_t signo);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigignore)(signo_t signo);
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_sigset)(signo_t signo, sighandler_t disp);
INTDEF int NOTHROW_NCX(LIBCCALL libc_pthread_kill)(pthread_t threadid, signo_t signo);
INTDEF int NOTHROW_NCX(LIBCCALL libc_pthread_sigqueue)(pthread_t threadid, signo_t signo, union sigval const value);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SIGNAL_H */
