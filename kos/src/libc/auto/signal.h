/* HASH CRC-32:0x5001be18 */
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
#ifndef GUARD_LIBC_AUTO_SIGNAL_H
#define GUARD_LIBC_AUTO_SIGNAL_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <signal.h>

DECL_BEGIN

DECL_END
#include <bits/sigaction.h>
DECL_BEGIN

#ifndef __sighandler_t_defined
#define __sighandler_t_defined 1
typedef __sighandler_t sighandler_t;
#endif /* !__sighandler_t_defined */

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_raise)(int signo);
/* @param signo: One of `SIG*' */
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_sysv_signal)(int signo, sighandler_t handler);
/* @param signo: One of `SIG*' */
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_signal)(int signo, sighandler_t handler);
/* @param signo: One of `SIG*' */
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_ssignal)(int signo, sighandler_t handler);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_gsignal)(int signo);
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigblock)(int mask);
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigsetmask)(int mask);
INTDEF int NOTHROW_NCX(LIBDCALL libd_siggetmask)(void);
INTDEF ATTR_NORETURN void NOTHROW_NCX(LIBDCALL libd_sigreturn)(struct sigcontext const *scp);
/* @param signo: One of `SIG*' */
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_bsd_signal)(int signo, sighandler_t handler);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBDCALL libd___xpg_sigpause)(int signo);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_kill)(pid_t pid, int signo);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_sigemptyset)(sigset_t *set);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigemptyset)(sigset_t *set);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_sigfillset)(sigset_t *set);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigfillset)(sigset_t *set);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param signo: One of `SIG*' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_sigaddset)(sigset_t *set, int signo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param signo: One of `SIG*' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigaddset)(sigset_t *set, int signo);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param signo: One of `SIG*' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_sigdelset)(sigset_t *set, int signo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param signo: One of `SIG*' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigdelset)(sigset_t *set, int signo);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param signo: One of `SIG*' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_sigismember)(sigset_t const *set, int signo);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* @param signo: One of `SIG*' */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigismember)(sigset_t const *set, int signo);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigprocmask)(int how, sigset_t const *set, sigset_t *oset);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_sigsuspend)(sigset_t const *set);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigaction)(int signo, struct sigaction const *act, struct sigaction *oact);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_sigpending)(sigset_t *__restrict set);
/* @param signo: One of `SIG*' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBDCALL libd_sigwait)(sigset_t const *__restrict set, int *__restrict signo);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBDCALL libd_sigisemptyset)(sigset_t const *__restrict set);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_PURE WUNUSED NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigisemptyset)(sigset_t const *__restrict set);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBDCALL libd_sigandset)(sigset_t *set, sigset_t const *left, sigset_t const *right);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc_sigandset)(sigset_t *set, sigset_t const *left, sigset_t const *right);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBDCALL libd_sigorset)(sigset_t *set, sigset_t const *left, sigset_t const *right);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF NONNULL((1, 2, 3)) int NOTHROW_NCX(LIBCCALL libc_sigorset)(sigset_t *set, sigset_t const *left, sigset_t const *right);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_sigwaitinfo)(sigset_t const *__restrict set, siginfo_t *__restrict info);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_sigtimedwait)(sigset_t const *__restrict set, siginfo_t *__restrict info, struct timespec const *timeout);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigqueue)(pid_t pid, int signo, union sigval const val);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_sigtimedwait64)(sigset_t const *__restrict set, siginfo_t *__restrict info, struct timespec64 const *timeout);
/* @param signo: One of `SIG*' */
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBDCALL libd_sigqueueinfo)(pid_t tgid, int signo, siginfo_t const *uinfo);
/* @param signo: One of `SIG*' */
INTDEF NONNULL((4)) int NOTHROW_NCX(LIBDCALL libd_tgsigqueueinfo)(pid_t tgid, pid_t tid, int signo, siginfo_t const *uinfo);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_killpg)(pid_t pgrp, int signo);
/* @param signo: One of `SIG*' */
INTDEF void NOTHROW_NCX(LIBDCALL libd_psignal)(int signo, char const *s);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_psiginfo)(siginfo_t const *pinfo, char const *s);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_siginterrupt)(int signo, int interrupt);
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigstack)(struct sigstack *ss, struct sigstack *oss);
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigaltstack)(struct sigaltstack const *ss, struct sigaltstack *oss);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sighold)(int signo);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigrelse)(int signo);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_sigignore)(int signo);
/* @param signo: One of `SIG*' */
INTDEF sighandler_t NOTHROW_NCX(LIBDCALL libd_sigset)(int signo, sighandler_t disp);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmin)(void);
INTDEF ATTR_CONST WUNUSED int NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmax)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SIGNAL_H */
