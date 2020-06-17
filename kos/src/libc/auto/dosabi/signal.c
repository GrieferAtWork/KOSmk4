/* HASH CRC-32:0xafc79e41 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SIGNAL_C
#define GUARD_LIBC_AUTO_DOSABI_SIGNAL_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/signal.h"

DECL_BEGIN

/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_raise)(int signo) {
	return libc_raise(signo);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") sighandler_t
NOTHROW_NCX(LIBDCALL libd_sysv_signal)(int signo,
                                       sighandler_t handler) {
	return libc_sysv_signal(signo, handler);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") sighandler_t
NOTHROW_NCX(LIBDCALL libd_signal)(int signo,
                                  sighandler_t handler) {
	return libc_signal(signo, handler);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") sighandler_t
NOTHROW_NCX(LIBDCALL libd_ssignal)(int signo,
                                   sighandler_t handler) {
	return libc_ssignal(signo, handler);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_gsignal)(int signo) {
	return libc_gsignal(signo);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_sigblock)(int mask) {
	return libc_sigblock(mask);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_sigsetmask)(int mask) {
	return libc_sigsetmask(mask);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_siggetmask)(void) {
	return libc_siggetmask();
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") ATTR_NORETURN void
NOTHROW_NCX(LIBDCALL libd_sigreturn)(struct sigcontext const *scp) {
	libc_sigreturn(scp);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") sighandler_t
NOTHROW_NCX(LIBDCALL libd_bsd_signal)(int signo,
                                      sighandler_t handler) {
	return libc_bsd_signal(signo, handler);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd___xpg_sigpause)(int signo) {
	return libc___xpg_sigpause(signo);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_kill)(pid_t pid,
                                int signo) {
	return libc_kill(pid, signo);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_sigemptyset)(sigset_t *set) {
	return libc_sigemptyset(set);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_sigfillset)(sigset_t *set) {
	return libc_sigfillset(set);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_sigaddset)(sigset_t *set,
                                     int signo) {
	return libc_sigaddset(set, signo);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_sigdelset)(sigset_t *set,
                                     int signo) {
	return libc_sigdelset(set, signo);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_sigismember)(sigset_t const *set,
                                       int signo) {
	return libc_sigismember(set, signo);
}
/* @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_sigprocmask)(int how,
                                       sigset_t const *set,
                                       sigset_t *oset) {
	return libc_sigprocmask(how, set, oset);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_sigsuspend)(sigset_t const *set) {
	return libc_sigsuspend(set);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_sigaction)(int signo,
                                     struct sigaction const *act,
                                     struct sigaction *oact) {
	return libc_sigaction(signo, act, oact);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_sigpending)(sigset_t *__restrict set) {
	return libc_sigpending(set);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((1, 2)) int
NOTHROW_RPC(LIBDCALL libd_sigwait)(sigset_t const *__restrict set,
                                   int *__restrict signo) {
	return libc_sigwait(set, signo);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_sigisemptyset)(sigset_t const *__restrict set) {
	return libc_sigisemptyset(set);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBDCALL libd_sigandset)(sigset_t *set,
                                     sigset_t const *left,
                                     sigset_t const *right) {
	return libc_sigandset(set, left, right);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((1, 2, 3)) int
NOTHROW_NCX(LIBDCALL libd_sigorset)(sigset_t *set,
                                    sigset_t const *left,
                                    sigset_t const *right) {
	return libc_sigorset(set, left, right);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_sigwaitinfo)(sigset_t const *__restrict set,
                                       siginfo_t *__restrict info) {
	return libc_sigwaitinfo(set, info);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_sigtimedwait)(sigset_t const *__restrict set,
                                        siginfo_t *__restrict info,
                                        struct timespec const *timeout) {
	return libc_sigtimedwait(set, info, timeout);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_sigqueue)(pid_t pid,
                                    int signo,
                                    union sigval const val) {
	return libc_sigqueue(pid, signo, val);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_sigtimedwait64)(sigset_t const *__restrict set,
                                          siginfo_t *__restrict info,
                                          struct timespec64 const *timeout) {
	return libc_sigtimedwait64(set, info, timeout);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((3)) int
NOTHROW_NCX(LIBDCALL libd_sigqueueinfo)(pid_t tgid,
                                        int signo,
                                        siginfo_t const *uinfo) {
	return libc_sigqueueinfo(tgid, signo, uinfo);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((4)) int
NOTHROW_NCX(LIBDCALL libd_tgsigqueueinfo)(pid_t tgid,
                                          pid_t tid,
                                          int signo,
                                          siginfo_t const *uinfo) {
	return libc_tgsigqueueinfo(tgid, tid, signo, uinfo);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_killpg)(pid_t pgrp,
                                  int signo) {
	return libc_killpg(pgrp, signo);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") void
NOTHROW_NCX(LIBDCALL libd_psignal)(int signo,
                                   char const *s) {
	libc_psignal(signo, s);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_psiginfo)(siginfo_t const *pinfo,
                                    char const *s) {
	libc_psiginfo(pinfo, s);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_siginterrupt)(int signo,
                                        int interrupt) {
	return libc_siginterrupt(signo, interrupt);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_sigstack)(struct sigstack *ss,
                                    struct sigstack *oss) {
	return libc_sigstack(ss, oss);
}
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_sigaltstack)(struct sigaltstack const *ss,
                                       struct sigaltstack *oss) {
	return libc_sigaltstack(ss, oss);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_sighold)(int signo) {
	return libc_sighold(signo);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_sigrelse)(int signo) {
	return libc_sigrelse(signo);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_sigignore)(int signo) {
	return libc_sigignore(signo);
}
/* @param signo: One of `SIG*' */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") sighandler_t
NOTHROW_NCX(LIBDCALL libd_sigset)(int signo,
                                  sighandler_t disp) {
	return libc_sigset(signo, disp);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$raise, libd_raise);
DEFINE_PUBLIC_ALIAS(DOS$__sysv_signal, libd_sysv_signal);
DEFINE_PUBLIC_ALIAS(DOS$sysv_signal, libd_sysv_signal);
DEFINE_PUBLIC_ALIAS(DOS$_signal, libd_signal);
DEFINE_PUBLIC_ALIAS(DOS$signal, libd_signal);
DEFINE_PUBLIC_ALIAS(DOS$ssignal, libd_ssignal);
DEFINE_PUBLIC_ALIAS(DOS$gsignal, libd_gsignal);
DEFINE_PUBLIC_ALIAS(DOS$sigblock, libd_sigblock);
DEFINE_PUBLIC_ALIAS(DOS$sigsetmask, libd_sigsetmask);
DEFINE_PUBLIC_ALIAS(DOS$siggetmask, libd_siggetmask);
DEFINE_PUBLIC_ALIAS(DOS$sigreturn, libd_sigreturn);
DEFINE_PUBLIC_ALIAS(DOS$bsd_signal, libd_bsd_signal);
DEFINE_PUBLIC_ALIAS(DOS$__xpg_sigpause, libd___xpg_sigpause);
DEFINE_PUBLIC_ALIAS(DOS$kill, libd_kill);
DEFINE_PUBLIC_ALIAS(DOS$sigemptyset, libd_sigemptyset);
DEFINE_PUBLIC_ALIAS(DOS$sigfillset, libd_sigfillset);
DEFINE_PUBLIC_ALIAS(DOS$__sigaddset, libd_sigaddset);
DEFINE_PUBLIC_ALIAS(DOS$sigaddset, libd_sigaddset);
DEFINE_PUBLIC_ALIAS(DOS$__sigdelset, libd_sigdelset);
DEFINE_PUBLIC_ALIAS(DOS$sigdelset, libd_sigdelset);
DEFINE_PUBLIC_ALIAS(DOS$__sigismember, libd_sigismember);
DEFINE_PUBLIC_ALIAS(DOS$sigismember, libd_sigismember);
DEFINE_PUBLIC_ALIAS(DOS$sigprocmask, libd_sigprocmask);
DEFINE_PUBLIC_ALIAS(DOS$__sigsuspend, libd_sigsuspend);
DEFINE_PUBLIC_ALIAS(DOS$sigsuspend, libd_sigsuspend);
DEFINE_PUBLIC_ALIAS(DOS$__sigaction, libd_sigaction);
DEFINE_PUBLIC_ALIAS(DOS$sigaction, libd_sigaction);
DEFINE_PUBLIC_ALIAS(DOS$sigpending, libd_sigpending);
DEFINE_PUBLIC_ALIAS(DOS$sigwait, libd_sigwait);
DEFINE_PUBLIC_ALIAS(DOS$sigisemptyset, libd_sigisemptyset);
DEFINE_PUBLIC_ALIAS(DOS$sigandset, libd_sigandset);
DEFINE_PUBLIC_ALIAS(DOS$sigorset, libd_sigorset);
DEFINE_PUBLIC_ALIAS(DOS$sigwaitinfo, libd_sigwaitinfo);
DEFINE_PUBLIC_ALIAS(DOS$sigtimedwait, libd_sigtimedwait);
DEFINE_PUBLIC_ALIAS(DOS$sigqueue, libd_sigqueue);
DEFINE_PUBLIC_ALIAS(DOS$sigtimedwait64, libd_sigtimedwait64);
DEFINE_PUBLIC_ALIAS(DOS$sigqueueinfo, libd_sigqueueinfo);
DEFINE_PUBLIC_ALIAS(DOS$tgsigqueueinfo, libd_tgsigqueueinfo);
DEFINE_PUBLIC_ALIAS(DOS$killpg, libd_killpg);
DEFINE_PUBLIC_ALIAS(DOS$psignal, libd_psignal);
DEFINE_PUBLIC_ALIAS(DOS$psiginfo, libd_psiginfo);
DEFINE_PUBLIC_ALIAS(DOS$siginterrupt, libd_siginterrupt);
DEFINE_PUBLIC_ALIAS(DOS$sigstack, libd_sigstack);
DEFINE_PUBLIC_ALIAS(DOS$sigaltstack, libd_sigaltstack);
DEFINE_PUBLIC_ALIAS(DOS$sighold, libd_sighold);
DEFINE_PUBLIC_ALIAS(DOS$sigrelse, libd_sigrelse);
DEFINE_PUBLIC_ALIAS(DOS$sigignore, libd_sigignore);
DEFINE_PUBLIC_ALIAS(DOS$sigset, libd_sigset);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SIGNAL_C */
