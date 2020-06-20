/* HASH CRC-32:0x6795c151 */
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

DECL_END
#include <bits/sigaction.h>
DECL_BEGIN

#ifndef __sighandler_t_defined
#define __sighandler_t_defined 1
typedef __sighandler_t sighandler_t;
#endif /* !__sighandler_t_defined */

#ifndef __KERNEL__
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_raise)(int signo);
/* @param signo: One of `SIG*' */
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_sysv_signal)(int signo, sighandler_t handler);
/* @param signo: One of `SIG*' */
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_signal)(int signo, sighandler_t handler);
/* @param signo: One of `SIG*' */
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_ssignal)(int signo, sighandler_t handler);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_gsignal)(int signo);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigblock)(int mask);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigsetmask)(int mask);
INTDEF int NOTHROW_NCX(LIBCCALL libc_siggetmask)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED char const *const *NOTHROW(LIBCCALL libc___p_sys_siglist)(void);
INTDEF ATTR_NORETURN void NOTHROW_NCX(LIBCCALL libc_sigreturn)(struct sigcontext const *scp);
/* @param signo: One of `SIG*' */
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_bsd_signal)(int signo, sighandler_t handler);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBCCALL libc___xpg_sigpause)(int signo);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_kill)(pid_t pid, int signo);
/* @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigprocmask)(int how, sigset_t const *set, sigset_t *oset);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_sigsuspend)(sigset_t const *set);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigaction)(int signo, struct sigaction const *act, struct sigaction *oact);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_sigpending)(sigset_t *__restrict set);
/* @param signo: One of `SIG*' */
INTDEF NONNULL((1, 2)) int NOTHROW_RPC(LIBCCALL libc_sigwait)(sigset_t const *__restrict set, int *__restrict signo);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_sigwaitinfo)(sigset_t const *__restrict set, siginfo_t *__restrict info);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_sigtimedwait)(sigset_t const *__restrict set, siginfo_t *__restrict info, struct timespec const *timeout);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigqueue)(pid_t pid, int signo, union sigval const val);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_sigtimedwait64)(sigset_t const *__restrict set, siginfo_t *__restrict info, struct timespec64 const *timeout);
/* @param signo: One of `SIG*' */
INTDEF NONNULL((3)) int NOTHROW_NCX(LIBCCALL libc_sigqueueinfo)(pid_t tgid, int signo, siginfo_t const *uinfo);
/* @param signo: One of `SIG*' */
INTDEF NONNULL((4)) int NOTHROW_NCX(LIBCCALL libc_tgsigqueueinfo)(pid_t tgid, pid_t tid, int signo, siginfo_t const *uinfo);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_killpg)(pid_t pgrp, int signo);
/* @param signo: One of `SIG*' */
INTDEF void NOTHROW_NCX(LIBCCALL libc_psignal)(int signo, char const *s);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_psiginfo)(siginfo_t const *pinfo, char const *s);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_siginterrupt)(int signo, int interrupt);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigstack)(struct sigstack *ss, struct sigstack *oss);
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigaltstack)(struct sigaltstack const *ss, struct sigaltstack *oss);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sighold)(int signo);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigrelse)(int signo);
/* @param signo: One of `SIG*' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigignore)(int signo);
/* @param signo: One of `SIG*' */
INTDEF sighandler_t NOTHROW_NCX(LIBCCALL libc_sigset)(int signo, sighandler_t disp);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SIGNAL_H */
