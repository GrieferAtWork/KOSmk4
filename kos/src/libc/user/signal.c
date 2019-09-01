/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SIGNAL_C
#define GUARD_LIBC_USER_SIGNAL_C 1

#include "../api.h"
#include "signal.h"

#include <kos/syscalls.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

DECL_BEGIN

LOCAL int LIBCCALL
libc_signo_dos2kos(int dos_signo) {
	if (dos_signo == 22)
		return SIGABRT;
	return dos_signo;
}
LOCAL int LIBCCALL
libc_sigms_dos2kos(int dos_sigms) {
	if ((unsigned int)dos_sigms & (1 << (22 - 1))) {
		dos_sigms &= ~(1 << (22 - 1));
		dos_sigms |= ~(1 << (SIGABRT - 1));
	}
	return dos_sigms;
}


#ifdef __x86_64__
#if 0 /* TODO */
#define HAVE_SET_SIGRESTORE 1
INTDEF void libc_sig_restore(void);
#define SET_SIGRESTORE(x) ((x).sa_restorer = &libc_sig_restore, (x).sa_flags |= SA_RESTORER)
#endif
#elif defined(__i386__)
#define HAVE_SET_SIGRESTORE 1
INTDEF void libc_sig_restore(void);
#define SET_SIGRESTORE(x) ((x).sa_restorer = &libc_sig_restore, (x).sa_flags |= SA_RESTORER)
#endif

#ifndef SET_SIGRESTORE
#define SET_SIGRESTORE(x) (void)0
#endif /* !SET_SIGRESTORE */




/*[[[start:implementation]]]*/

/*[[[head:DOS$raise,hash:0x8f2c09ef]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.sched.signal.raise") int
NOTHROW_NCX(LIBDCALL libd_raise)(int signo)
/*[[[body:DOS$raise]]]*/
{
	return libc_raise(libc_signo_dos2kos(signo));
}
/*[[[end:DOS$raise]]]*/

/*[[[head:DOS$signal,hash:0x9835922]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.dos.sched.signal.signal") sighandler_t
NOTHROW_NCX(LIBDCALL libd_signal)(int signo,
                                  sighandler_t handler)
/*[[[body:DOS$signal]]]*/
{
	if (handler == (sighandler_t)2) /* SIG_GET */
		handler = SIG_GET;
	else if (handler == (sighandler_t)3) /* SIG_SGE */
		handler = SIG_ERR;               /* ??? */
	else if (handler == (sighandler_t)4) /* SIG_ACK */
		handler = SIG_DFL;               /* ??? */
	return libc_signal(libc_signo_dos2kos(signo), handler);
}
/*[[[end:DOS$signal]]]*/


/*[[[head:raise,hash:0xb1af0209]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.raise") int
NOTHROW_NCX(LIBCCALL libc_raise)(int signo)
/*[[[body:raise]]]*/
{
	return kill(getpid(),
	            (syscall_ulong_t)(syscall_slong_t)signo);
}
/*[[[end:raise]]]*/

/*[[[head:sysv_signal,hash:0xb46c318]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sysv_signal") sighandler_t
NOTHROW_NCX(LIBCCALL libc_sysv_signal)(int signo,
                                       sighandler_t handler)
/*[[[body:sysv_signal]]]*/
{
	struct sigaction act, oact;
	if unlikely(handler == SIG_ERR) {
		libc_seterrno(EINVAL);
		return SIG_ERR;
	}
	act.sa_handler = handler;
	libc_sigemptyset(&act.sa_mask);
	act.sa_flags = SA_ONESHOT | SA_NOMASK | SA_INTERRUPT;
	/*act.sa_flags &= ~SA_RESTART;*/
	SET_SIGRESTORE(act);
	if unlikely(sigaction(signo, &act, &oact))
		oact.sa_handler = SIG_ERR;
	return oact.sa_handler;
}
/*[[[end:sysv_signal]]]*/

/*[[[head:sigblock,hash:0x3388e58d]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigblock") int
NOTHROW_NCX(LIBCCALL libc_sigblock)(int mask)
/*[[[body:sigblock]]]*/
{
	errno_t result;
	result = sys_rt_sigprocmask(SIG_BLOCK,
	                            (sigset_t *)&mask,
	                            NULL,
	                            sizeof(mask));
	return libc_seterrno_syserr(result);
}
/*[[[end:sigblock]]]*/

/*[[[head:sigsetmask,hash:0xadda4f28]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigsetmask") int
NOTHROW_NCX(LIBCCALL libc_sigsetmask)(int mask)
/*[[[body:sigsetmask]]]*/
{
	errno_t result;
	result = sys_rt_sigprocmask(SIG_SETMASK,
	                            (sigset_t *)&mask,
	                            NULL,
	                            sizeof(mask));
	return libc_seterrno_syserr(result);
}
/*[[[end:sigsetmask]]]*/

/*[[[head:siggetmask,hash:0xdea61e8a]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.siggetmask") int
NOTHROW_NCX(LIBCCALL libc_siggetmask)(void)
/*[[[body:siggetmask]]]*/
{
	int value, result;
	result = sys_rt_sigprocmask(SIG_SETMASK,
	                            NULL,
	                            (sigset_t *)&value,
	                            sizeof(value));
	if unlikely(E_ISERR(result)) {
		result = (int)libc_seterrno(-result);
	} else {
		result = value;
	}
	return result;
}
/*[[[end:siggetmask]]]*/

/*[[[head:sigreturn,hash:0x729c68e6]]]*/
INTERN ATTR_NORETURN
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigreturn") void
NOTHROW_NCX(LIBCCALL libc_sigreturn)(struct sigcontext const *scp)
/*[[[body:sigreturn]]]*/
{
	CRT_UNIMPLEMENTED("sigreturn"); /* TODO */
	libc_seterrno(ENOSYS);
	for (;;) {
	}
}
/*[[[end:sigreturn]]]*/



PRIVATE sigset_t __sigintr;

/*[[[head:bsd_signal,hash:0x1772935c]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.bsd_signal") sighandler_t
NOTHROW_NCX(LIBCCALL libc_bsd_signal)(int signo,
                                      sighandler_t handler)
/*[[[body:bsd_signal]]]*/
{
	struct sigaction act, oact;
	if unlikely(handler == SIG_ERR) {
		libc_seterrno(EINVAL);
		return SIG_ERR;
	}
	if unlikely(handler == SIG_GET) {
		if unlikely(libc_sigaction(signo, NULL, &oact) < 0)
			oact.sa_handler = SIG_ERR;
	} else {
		act.sa_handler = handler;
		libc_sigemptyset(&act.sa_mask);
		libc_sigaddset(&act.sa_mask, signo);
		act.sa_flags = libc_sigismember(&__sigintr, signo) ? 0 : SA_RESTART;
		SET_SIGRESTORE(act);
		if unlikely(libc_sigaction(signo, &act, &oact) < 0)
			oact.sa_handler = SIG_ERR;
	}
	return oact.sa_handler;
}
/*[[[end:bsd_signal]]]*/

/*[[[head:kill,hash:0xe59a348f]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.kill") int
NOTHROW_NCX(LIBCCALL libc_kill)(pid_t pid,
                                int signo)
/*[[[body:kill]]]*/
{
	errno_t result;
	result = sys_kill(pid, (syscall_ulong_t)(unsigned int)signo);
	return libc_seterrno_syserr(result);
}
/*[[[end:kill]]]*/

/*[[[head:sigprocmask,hash:0x20d8e9]]]*/
/* @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigprocmask") int
NOTHROW_NCX(LIBCCALL libc_sigprocmask)(int how,
                                       sigset_t const *__restrict set,
                                       sigset_t *__restrict oset)
/*[[[body:sigprocmask]]]*/
{
	errno_t result;
#ifdef __NR_sigprocmask
	result = sys_sigprocmask((syscall_ulong_t)(unsigned int)how,
	                         set, oset);
#else /* __NR_sigprocmask */
	result = sys_rt_sigprocmask((syscall_ulong_t)(unsigned int)how,
	                            set, oset, sizeof(sigset_t));
#endif /* !__NR_sigprocmask */
	return libc_seterrno_syserr(result);
}
/*[[[end:sigprocmask]]]*/

/*[[[head:sigsuspend,hash:0x89d952c0]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigsuspend") int
NOTHROW_RPC(LIBCCALL libc_sigsuspend)(sigset_t const *set)
/*[[[body:sigsuspend]]]*/
{
	errno_t result;
#ifdef __NR_sigsuspend
	result = sys_sigsuspend(set);
#else /* __NR_sigsuspend */
	result = sys_rt_sigsuspend(set, sizeof(sigset_t));
#endif /* !__NR_sigsuspend */
	return libc_seterrno_syserr(result);
}
/*[[[end:sigsuspend]]]*/

/*[[[head:sigaction,hash:0xa26d6bd0]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigaction") int
NOTHROW_NCX(LIBCCALL libc_sigaction)(int signo,
                                     struct sigaction const *__restrict act,
                                     struct sigaction *__restrict oact)
/*[[[body:sigaction]]]*/
{
	errno_t result;
#ifdef HAVE_SET_SIGRESTORE
	struct sigaction real_act;
	if (act && !(act->sa_flags & SA_RESTORER)) {
		memcpy(&real_act, act, sizeof(struct sigaction));
		SET_SIGRESTORE(real_act);
		act = &real_act;
	}
#endif /* HAVE_SET_SIGRESTORE */
#ifdef __NR_sigaction
	result = sys_sigaction(signo, act, oact);
#else /* __NR_sigaction */
	result = sys_rt_sigaction(signo, act, oact, sizeof(sigset_t));
#endif /* !__NR_sigaction */
	return libc_seterrno_syserr(result);
}
/*[[[end:sigaction]]]*/

/*[[[head:sigpending,hash:0xba047d03]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigpending") int
NOTHROW_NCX(LIBCCALL libc_sigpending)(sigset_t *set)
/*[[[body:sigpending]]]*/
{
	errno_t result;
#ifdef __NR_sigpending
	result = sys_sigpending(set);
#else /* __NR_sigpending */
	result = sys_rt_sigpending(set, sizeof(sigset_t));
#endif /* !__NR_sigpending */
	return libc_seterrno_syserr(result);
}
/*[[[end:sigpending]]]*/

/*[[[head:sigwait,hash:0xc75a958e]]]*/
/* @param signo: One of `SIG*' */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigwait") int
NOTHROW_RPC(LIBCCALL libc_sigwait)(sigset_t const *__restrict set,
                                   int *__restrict signo)
/*[[[body:sigwait]]]*/
{
	errno_t result;
	siginfo_t info;
#ifdef __NR_rt_sigtimedwait64
	result = sys_rt_sigtimedwait64(set,
	                               &info,
	                               NULL,
	                               sizeof(sigset_t));
#else /* __NR_rt_sigtimedwait64 */
	result = sys_rt_sigtimedwait(set,
	                             &info,
	                             NULL,
	                             sizeof(sigset_t));
#endif /* !__NR_rt_sigtimedwait64 */
	if likely(result >= 0) {
		*signo = result;
		return 0;
	}
	return -result;
}
/*[[[end:sigwait]]]*/

/*[[[head:sigwaitinfo,hash:0xe75bef0a]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigwaitinfo") int
NOTHROW_RPC(LIBCCALL libc_sigwaitinfo)(sigset_t const *__restrict set,
                                       siginfo_t *__restrict info)
/*[[[body:sigwaitinfo]]]*/
{
	errno_t result;
#ifdef __NR_rt_sigtimedwait64
	result = sys_rt_sigtimedwait64(set,
	                               info,
	                               NULL,
	                               sizeof(sigset_t));
#else /* __NR_rt_sigtimedwait64 */
	result = sys_rt_sigtimedwait(set,
	                             info,
	                             NULL,
	                             sizeof(sigset_t));
#endif /* !__NR_rt_sigtimedwait64 */
	return libc_seterrno_syserr(result);
}
/*[[[end:sigwaitinfo]]]*/

/*[[[head:sigtimedwait,hash:0xc66d8f33]]]*/
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigtimedwait") int
NOTHROW_RPC(LIBCCALL libc_sigtimedwait)(sigset_t const *__restrict set,
                                        siginfo_t *__restrict info,
                                        struct timespec const *timeout)
/*[[[body:sigtimedwait]]]*/
{
	errno_t result;
	result = sys_rt_sigtimedwait(set,
	                             info,
	                             timeout,
	                             sizeof(sigset_t));
	return libc_seterrno_syserr(result);
}
/*[[[end:sigtimedwait]]]*/

/*[[[head:sigtimedwait64,hash:0x79ee95ba]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_sigtimedwait64, libc_sigtimedwait);
#else
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigtimedwait64") int
NOTHROW_RPC(LIBCCALL libc_sigtimedwait64)(sigset_t const *__restrict set,
                                          siginfo_t *__restrict info,
                                          struct timespec64 const *timeout)
/*[[[body:sigtimedwait64]]]*/
{
	errno_t result;
	result = sys_rt_sigtimedwait64(set,
	                               info,
	                               timeout,
	                               sizeof(sigset_t));
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:sigtimedwait64]]]*/

/*[[[head:sigqueue,hash:0xa4ce162d]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigqueue") int
NOTHROW_NCX(LIBCCALL libc_sigqueue)(pid_t pid,
                                    int signo,
                                    union sigval const val)
/*[[[body:sigqueue]]]*/
{
	siginfo_t info;
	memset(&info, 0, sizeof(siginfo_t));
	info.si_value = val;
	info.si_code  = SI_QUEUE;
	return sigqueueinfo(pid, signo, &info);
}
/*[[[end:sigqueue]]]*/

/*[[[head:sigqueueinfo,hash:0x4533d027]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigqueueinfo") int
NOTHROW_NCX(LIBCCALL libc_sigqueueinfo)(pid_t tgid,
                                        int signo,
                                        siginfo_t const *uinfo)
/*[[[body:sigqueueinfo]]]*/
{
	errno_t result;
	result = sys_rt_sigqueueinfo(tgid,
	                             (syscall_ulong_t)(unsigned int)signo,
	                             uinfo);
	return libc_seterrno_syserr(result);
}
/*[[[end:sigqueueinfo]]]*/

/*[[[head:tgsigqueueinfo,hash:0xa2e16341]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.tgsigqueueinfo") int
NOTHROW_NCX(LIBCCALL libc_tgsigqueueinfo)(pid_t tgid,
                                          pid_t tid,
                                          int signo,
                                          siginfo_t const *uinfo)
/*[[[body:tgsigqueueinfo]]]*/
{
	errno_t result;
	result = sys_rt_tgsigqueueinfo(tgid,
	                               tid,
	                               (syscall_ulong_t)(unsigned int)signo,
	                               uinfo);
	return libc_seterrno_syserr(result);
}
/*[[[end:tgsigqueueinfo]]]*/

/*[[[head:killpg,hash:0x495075b1]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.killpg") int
NOTHROW_NCX(LIBCCALL libc_killpg)(pid_t pgrp,
                                  int signo)
/*[[[body:killpg]]]*/
{
	return kill(-pgrp, signo);
}
/*[[[end:killpg]]]*/

/*[[[head:psignal,hash:0xa8dcec33]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.psignal") void
NOTHROW_NCX(LIBCCALL libc_psignal)(int signo,
                                   char const *s)
/*[[[body:psignal]]]*/
{
	CRT_UNIMPLEMENTED("psignal"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:psignal]]]*/

/*[[[head:psiginfo,hash:0x3d78fa76]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.psiginfo") void
NOTHROW_NCX(LIBCCALL libc_psiginfo)(siginfo_t const *pinfo,
                                    char const *s)
/*[[[body:psiginfo]]]*/
{
	CRT_UNIMPLEMENTED("psiginfo"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:psiginfo]]]*/

/*[[[head:siginterrupt,hash:0xe2769a4a]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.siginterrupt") int
NOTHROW_NCX(LIBCCALL libc_siginterrupt)(int signo,
                                        int interrupt)
/*[[[body:siginterrupt]]]*/
{
	struct sigaction action;
	if (sigaction(signo, (struct sigaction *)NULL, &action) < 0)
		goto err;
	if (interrupt) {
		libc_sigaddset(&__sigintr, signo);
		action.sa_flags &= ~SA_RESTART;
	} else {
		libc_sigdelset(&__sigintr, signo);
		action.sa_flags |= SA_RESTART;
	}
	if (libc_sigaction(signo, &action, (struct sigaction *)NULL) < 0)
		goto err;
	return 0;
err:
	return -1;
}
/*[[[end:siginterrupt]]]*/

/*[[[head:sigstack,hash:0x8bdaebd4]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigstack") int
NOTHROW_NCX(LIBCCALL libc_sigstack)(struct sigstack *ss,
                                    struct sigstack *oss)
/*[[[body:sigstack]]]*/
{
	struct sigaltstack ass, aoss;
	int result;
	if (ss) {
		ass.ss_flags = ss->ss_onstack
		               ? SS_ONSTACK
		               : SS_DISABLE;
		ass.ss_sp   = ss->ss_sp;
		ass.ss_size = (size_t)-1;
	}
	result = sigaltstack(ss ? &ass : NULL,
	                     oss ? &aoss : NULL);
	if (likely(!result) && oss) {
		oss->ss_onstack = !!(aoss.ss_flags & SS_ONSTACK);
		oss->ss_sp      = aoss.ss_sp;
	}
	return result;
}
/*[[[end:sigstack]]]*/

/*[[[head:sigaltstack,hash:0x649e27c9]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigaltstack") int
NOTHROW_NCX(LIBCCALL libc_sigaltstack)(struct sigaltstack const *__restrict ss,
                                       struct sigaltstack *__restrict oss)
/*[[[body:sigaltstack]]]*/
{
	errno_t result;
	result = sys_sigaltstack(ss, oss);
	return libc_seterrno_syserr(result);
}
/*[[[end:sigaltstack]]]*/


PRIVATE int LIBCCALL
set_single_signal_action(int sig, int how) {
	sigset_t set;
	libc_sigemptyset(&set);
	libc_sigaddset(&set, sig);
	return libc_sigprocmask(SIG_BLOCK, &set, NULL);
}

/*[[[head:sighold,hash:0xf3be7a3f]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sighold") int
NOTHROW_NCX(LIBCCALL libc_sighold)(int signo)
/*[[[body:sighold]]]*/
{
	return set_single_signal_action(signo, SIG_BLOCK);
}
/*[[[end:sighold]]]*/

/*[[[head:sigrelse,hash:0x3a41f28]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigrelse") int
NOTHROW_NCX(LIBCCALL libc_sigrelse)(int signo)
/*[[[body:sigrelse]]]*/
{
	return set_single_signal_action(signo, SIG_UNBLOCK);
}
/*[[[end:sigrelse]]]*/

/*[[[head:sigignore,hash:0x994cd165]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigignore") int
NOTHROW_NCX(LIBCCALL libc_sigignore)(int signo)
/*[[[body:sigignore]]]*/
{
	return libc_bsd_signal(signo, SIG_IGN) == SIG_ERR ? -1 : 0;
}
/*[[[end:sigignore]]]*/

/*[[[head:sigset,hash:0x4e0c30ec]]]*/
/* @param signo: One of `SIG*' */
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.sigset") sighandler_t
NOTHROW_NCX(LIBCCALL libc_sigset)(int signo,
                                  sighandler_t disp)
/*[[[body:sigset]]]*/
{
	struct sigaction act, oact;
	sigset_t set, oset;
	if unlikely(disp == SIG_ERR)
		goto err_inval;
	libc_sigemptyset(&set);
	libc_sigaddset(&set, signo);
	if (disp == SIG_HOLD) {
		if unlikely(libc_sigprocmask(SIG_BLOCK, &set, &oset) < 0)
			goto err;
		if unlikely(libc_sigismember(&oset, signo))
			goto err;
		if unlikely(libc_sigaction(signo, NULL, &oact) < 0)
			goto err;
		return oact.sa_handler;
	}
	act.sa_handler = disp;
	libc_sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	SET_SIGRESTORE(act);
	if unlikely(sigaction(signo, &act, &oact) < 0)
		goto err;
	if unlikely(sigprocmask(SIG_UNBLOCK, &set, &oset) < 0)
		goto err;
	return libc_sigismember(&oset, signo)
	       ? SIG_HOLD
	       : oact.sa_handler;
err_inval:
	libc_seterrno(EINVAL);
err:
	return SIG_ERR;
}
/*[[[end:sigset]]]*/

/*[[[head:__libc_current_sigrtmin,hash:0x84a64035]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.__libc_current_sigrtmin") int
NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmin)(void)
/*[[[body:__libc_current_sigrtmin]]]*/
{
	return __SIGRTMIN;
}
/*[[[end:__libc_current_sigrtmin]]]*/

/*[[[head:__libc_current_sigrtmax,hash:0xfebe3d7f]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.signal.__libc_current_sigrtmax") int
NOTHROW_NCX(LIBCCALL libc___libc_current_sigrtmax)(void)
/*[[[body:__libc_current_sigrtmax]]]*/
{
	return __SIGRTMAX;
}
/*[[[end:__libc_current_sigrtmax]]]*/


/*[[[impl:signal]]]*/
/*[[[impl:ssignal]]]*/
/*[[[impl:gsignal]]]*/
DEFINE_INTERN_ALIAS(libc_signal, libc_bsd_signal);
DEFINE_INTERN_ALIAS(libc_ssignal, libc_bsd_signal);
DEFINE_INTERN_ALIAS(libc_gsignal, libc_raise);

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:0xf5c15dd9]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(raise, libc_raise);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$raise, libd_raise);
DEFINE_PUBLIC_WEAK_ALIAS(sysv_signal, libc_sysv_signal);
DEFINE_PUBLIC_WEAK_ALIAS(signal, libc_signal);
DEFINE_PUBLIC_WEAK_ALIAS(DOS$signal, libd_signal);
DEFINE_PUBLIC_WEAK_ALIAS(ssignal, libc_ssignal);
DEFINE_PUBLIC_WEAK_ALIAS(gsignal, libc_gsignal);
DEFINE_PUBLIC_WEAK_ALIAS(sigblock, libc_sigblock);
DEFINE_PUBLIC_WEAK_ALIAS(sigsetmask, libc_sigsetmask);
DEFINE_PUBLIC_WEAK_ALIAS(siggetmask, libc_siggetmask);
DEFINE_PUBLIC_WEAK_ALIAS(sigreturn, libc_sigreturn);
DEFINE_PUBLIC_WEAK_ALIAS(bsd_signal, libc_bsd_signal);
DEFINE_PUBLIC_WEAK_ALIAS(kill, libc_kill);
DEFINE_PUBLIC_WEAK_ALIAS(sigprocmask, libc_sigprocmask);
DEFINE_PUBLIC_WEAK_ALIAS(sigsuspend, libc_sigsuspend);
DEFINE_PUBLIC_WEAK_ALIAS(sigaction, libc_sigaction);
DEFINE_PUBLIC_WEAK_ALIAS(sigpending, libc_sigpending);
DEFINE_PUBLIC_WEAK_ALIAS(sigwait, libc_sigwait);
DEFINE_PUBLIC_WEAK_ALIAS(sigwaitinfo, libc_sigwaitinfo);
DEFINE_PUBLIC_WEAK_ALIAS(sigtimedwait, libc_sigtimedwait);
DEFINE_PUBLIC_WEAK_ALIAS(sigqueue, libc_sigqueue);
DEFINE_PUBLIC_WEAK_ALIAS(sigtimedwait64, libc_sigtimedwait64);
DEFINE_PUBLIC_WEAK_ALIAS(sigqueueinfo, libc_sigqueueinfo);
DEFINE_PUBLIC_WEAK_ALIAS(tgsigqueueinfo, libc_tgsigqueueinfo);
DEFINE_PUBLIC_WEAK_ALIAS(killpg, libc_killpg);
DEFINE_PUBLIC_WEAK_ALIAS(psignal, libc_psignal);
DEFINE_PUBLIC_WEAK_ALIAS(psiginfo, libc_psiginfo);
DEFINE_PUBLIC_WEAK_ALIAS(siginterrupt, libc_siginterrupt);
DEFINE_PUBLIC_WEAK_ALIAS(sigstack, libc_sigstack);
DEFINE_PUBLIC_WEAK_ALIAS(sigaltstack, libc_sigaltstack);
DEFINE_PUBLIC_WEAK_ALIAS(sighold, libc_sighold);
DEFINE_PUBLIC_WEAK_ALIAS(sigrelse, libc_sigrelse);
DEFINE_PUBLIC_WEAK_ALIAS(sigignore, libc_sigignore);
DEFINE_PUBLIC_WEAK_ALIAS(sigset, libc_sigset);
DEFINE_PUBLIC_WEAK_ALIAS(__libc_current_sigrtmin, libc___libc_current_sigrtmin);
DEFINE_PUBLIC_WEAK_ALIAS(__libc_current_sigrtmax, libc___libc_current_sigrtmax);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SIGNAL_C */
