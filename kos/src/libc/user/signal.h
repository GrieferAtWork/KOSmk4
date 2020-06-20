/* HASH CRC-32:0xd98f7ff9 */
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
/* @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_sigprocmask)(__STDC_INT_AS_UINT_T how, sigset_t const *set, sigset_t *oset);
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
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SIGNAL_H */
