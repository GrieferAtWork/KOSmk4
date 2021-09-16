/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_SIGNAL_C
#define GUARD_LIBC_USER_SIGNAL_C 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>
#include <hybrid/bit.h>

#include <kos/exec/idata.h>
#include <kos/syscalls.h>
#include <sys/param.h>

#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>

#include "../libc/compat.h"
#include "../libc/tls.h"
#include "signal.h"
#include "string.h"

DECL_BEGIN

LOCAL signo_t LIBCCALL
libc_signo_dos2kos(signo_t dos_signo) {
	if (dos_signo == DOS_SIGABRT)
		return SIGABRT;
	return dos_signo;
}

LOCAL int LIBCCALL
libc_sigms_dos2kos(int dos_sigms) {
	if ((unsigned int)dos_sigms & (1 << (DOS_SIGABRT - 1))) {
		dos_sigms &= ~(1 << (DOS_SIGABRT - 1));
		dos_sigms |= ~(1 << (SIGABRT - 1));
	}
	return dos_sigms;
}


#ifdef LIBC_ARCH_HAVE_SIG_RESTORE
INTDEF void /*ASMCALL*/ libc_sig_restore(void);
#define SET_SIGRESTORE(x) ((x).sa_restorer = &libc_sig_restore, (x).sa_flags |= SA_RESTORER)
#endif /* LIBC_ARCH_HAVE_SIG_RESTORE */

#ifndef SET_SIGRESTORE
#define SET_SIGRESTORE(x) (void)0
#endif /* !SET_SIGRESTORE */




/*[[[head:libd_raise,hash:CRC-32=0x2247937f]]]*/
/* >> raise(3)
 * Raise a signal within the current thread.
 * In  a *-theaded process  this is same as:
 *   *=multi:  `pthread_kill(pthread_self(), signo)'
 *   *=single: `kill(getpid(), signo)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") int
NOTHROW_NCX(LIBDCALL libd_raise)(signo_t signo)
/*[[[body:libd_raise]]]*/
{
	return libc_raise(libc_signo_dos2kos(signo));
}
/*[[[end:libd_raise]]]*/

/*[[[head:libc_raise,hash:CRC-32=0xbb96ae5]]]*/
/* >> raise(3)
 * Raise a signal within the current thread.
 * In  a *-theaded process  this is same as:
 *   *=multi:  `pthread_kill(pthread_self(), signo)'
 *   *=single: `kill(getpid(), signo)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_raise)(signo_t signo)
/*[[[body:libc_raise]]]*/
{
	return kill(getpid(),
	            (syscall_ulong_t)(syscall_slong_t)signo);
}
/*[[[end:libc_raise]]]*/

/*[[[head:libd_sysv_signal,hash:CRC-32=0xa472bfcf]]]*/
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
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") sighandler_t
NOTHROW_NCX(LIBDCALL libd_sysv_signal)(signo_t signo,
                                       sighandler_t handler)
/*[[[body:libd_sysv_signal]]]*/
{
	return libc_sysv_signal(libc_signo_dos2kos(signo), handler);
}
/*[[[end:libd_sysv_signal]]]*/

/*[[[head:libc_sysv_signal,hash:CRC-32=0xa82fcb1f]]]*/
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
INTERN ATTR_SECTION(".text.crt.sched.signal") sighandler_t
NOTHROW_NCX(LIBCCALL libc_sysv_signal)(signo_t signo,
                                       sighandler_t handler)
/*[[[body:libc_sysv_signal]]]*/
{
	errno_t result;
	struct sigaction act, oact;
	if unlikely(handler == SIG_ERR) {
		libc_seterrno(EINVAL);
		return SIG_ERR;
	}
	act.sa_handler = handler;
	libc_sigemptyset(&act.sa_mask);
	act.sa_flags = (SA_RESETHAND | SA_NODEFER) & ~SA_RESTART;
	SET_SIGRESTORE(act);
#ifdef __NR_sigaction
	result = sys_sigaction(signo, &act, &oact);
#else /* __NR_sigaction */
	result = sys_rt_sigaction(signo, &act, &oact, sizeof(sigset_t));
#endif /* !__NR_sigaction */
	if unlikely(E_ISERR(result)) {
		libc_seterrno_neg(result);
		oact.sa_handler = SIG_ERR;
	}
	return oact.sa_handler;
}
/*[[[end:libc_sysv_signal]]]*/


#undef sys_siglist
#undef _sys_siglist
PRIVATE ATTR_SECTION(".bss.crt.errno.sys_siglist") char const *
libc_sys_siglist[NSIG] = { NULL };

DEFINE_PUBLIC_IDATA_G(sys_siglist, libc___p_sys_siglist, NSIG * __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA_G(_sys_siglist, libc___p_sys_siglist, NSIG * __SIZEOF_POINTER__);

/*[[[head:libc___p_sys_siglist,hash:CRC-32=0xa33e9b16]]]*/
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_CONST ATTR_RETNONNULL WUNUSED char const *const *
NOTHROW(LIBCCALL libc___p_sys_siglist)(void)
/*[[[body:libc___p_sys_siglist]]]*/
{
	char const **result = libc_sys_siglist;
	if (!result[0]) {
		unsigned int i = NSIG;
		/* Lazily initialize */
		for (;;) {
			result[i] = libc_sigdescr_np(i);
			COMPILER_WRITE_BARRIER();
			if (!i)
				break;
			--i;
		}
	}
	return result;
}
/*[[[end:libc___p_sys_siglist]]]*/

/*[[[head:libc_sigreturn,hash:CRC-32=0x5194db98]]]*/
/* Don't  call directly. Used internally to resume
 * execution when returning from a signal handler. */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_NORETURN void
NOTHROW_NCX(LIBCCALL libc_sigreturn)(struct sigcontext const *scp)
/*[[[body:libc_sigreturn]]]*/
/*AUTO*/{
	(void)scp;
	CRT_UNIMPLEMENTEDF("sigreturn(%p)", scp); /* TODO */
	assert_failed("Not implemented");
}
/*[[[end:libc_sigreturn]]]*/




PRIVATE ATTR_SECTION(".bss.crt.sched.signal") sigset_t __sigintr;

/*[[[head:libc_bsd_signal,hash:CRC-32=0x8c366111]]]*/
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
INTERN ATTR_SECTION(".text.crt.sched.signal") sighandler_t
NOTHROW_NCX(LIBCCALL libc_bsd_signal)(signo_t signo,
                                      sighandler_t handler)
/*[[[body:libc_bsd_signal]]]*/
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
/*[[[end:libc_bsd_signal]]]*/

/*[[[head:libd_bsd_signal,hash:CRC-32=0x1a7cc9f2]]]*/
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
INTERN ATTR_SECTION(".text.crt.dos.sched.signal") sighandler_t
NOTHROW_NCX(LIBDCALL libd_bsd_signal)(signo_t signo,
                                      sighandler_t handler)
/*[[[body:libd_bsd_signal]]]*/
{
	return libc_bsd_signal(libc_signo_dos2kos(signo), handler);
}
/*[[[end:libd_bsd_signal]]]*/



/*[[[head:libc_kill,hash:CRC-32=0x1a67950e]]]*/
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
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_kill)(pid_t pid,
                                signo_t signo)
/*[[[body:libc_kill]]]*/
{
	errno_t result;
	result = sys_kill(pid, (syscall_ulong_t)(unsigned int)signo);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_kill]]]*/


#ifndef __NR_sigprocmask
#define sys_sigprocmask(how, set, oset) \
	sys_rt_sigprocmask(how, set, oset, sizeof(sigset_t))
#endif /* !__NR_sigprocmask */


/*[[[head:libc_sigprocmask,hash:CRC-32=0x45302536]]]*/
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
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigprocmask)(__STDC_INT_AS_UINT_T how,
                                       sigset_t const *set,
                                       sigset_t *oset)
/*[[[body:libc_sigprocmask]]]*/
{
#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
	struct pthread *me = &current;
	sigset_t *old_set, *new_set;
	old_set = me->pt_pmask.lpm_pmask.pm_sigmask;
	if unlikely(!old_set) {
		/* Special case: The userprocmask sub-system isn't initialized, yet.
		 * So initialize it now. */
		old_set = &me->pt_pmask.lpm_masks[0];
		me->pt_pmask.lpm_pmask.pm_sigmask = old_set;
		if unlikely(sys_set_userprocmask_address(&me->pt_pmask.lpm_pmask) != EOK) {
			/* Fallback: Use the legacy sigprocmask(2) system call. */
			goto do_legacy_sigprocmask;
		}
	}
	if (oset)
		memcpy(oset, old_set, sizeof(sigset_t));

	/* Check for special case: do we even need to set a new procmask? */
	if (!set)
		return 0;

	/* Select the new storage location. */
	new_set = old_set + 1;
	if (new_set != &me->pt_pmask.lpm_masks[0] &&
	    new_set != &me->pt_pmask.lpm_masks[1])
		new_set = &me->pt_pmask.lpm_masks[0];

	/* Initialize `new_set' based on `how', `old_set' and `set' */
	switch (how) {

	case SIG_SETMASK:
		memcpy(new_set, set, sizeof(sigset_t));
		break;

	case SIG_BLOCK:
		sigorset(new_set, old_set, set);
		break;

	case SIG_UNBLOCK:
		signandset(new_set, old_set, set);
		break;

	default:
		return libc_seterrno(EINVAL);
	}

	/* Atomically enable use of the new, updated mask
	 * From this point forth, signals sent to our thread will be masked by `new_set' */
	ATOMIC_WRITE(me->pt_pmask.lpm_pmask.pm_sigmask, new_set);

	/* Optimization: If we know that no signal became unmasked, we don't
	 *               have  to search for  any pending, unmasked signals! */
	if (how == SIG_BLOCK)
		return 0;

	/* Check if previously pending signals became available.
	 *
	 * Q: It the below ~really~ reentrant-safe (in terms of a  signal
	 *    handler being invoked while we're down below, which in turn
	 *    ends up doing yet another call to sigprocmask(2))?
	 * A: I think it's reentrant-safe (as far as signal-masking logic
	 *    goes), because the  below's only supposed  to do  something
	 *    when a signal became unmasked.  - If a signal handler  ends
	 *    up re-masking a signal before then, then it wouldn't be our
	 *    fault,  and the  async nature  of posix  signals in general
	 *    would allow us to argue  that the signal may have  actually
	 *    been  delivered  _after_ the  signal handler  re-masked the
	 *    associates signal! */
	{
		unsigned int i;
		for (i = 0; i < __SIGSET_NWORDS; ++i) {
			ulongptr_t pending_word;
			ulongptr_t newmask_word;
			pending_word = ATOMIC_READ(me->pt_pmask.lpm_pmask.pm_pending.__val[i]);
			if (!pending_word)
				continue; /* Nothing pending in here. */
			newmask_word = new_set->__val[i];

			/* Check if any of the pending signals are currently unmasked. */
			if ((pending_word & ~newmask_word) != 0) {

				/* Clear the set of pending signals (because the kernel won't do this)
				 * Also  note that  there is no  guaranty that the  signal that became
				 * available in the mean time is still available now. - The signal may
				 * have  been directed at  our process as a  whole, and another thread
				 * may have already handled it. */
				sigemptyset(&me->pt_pmask.lpm_pmask.pm_pending);

				/* Calls the kernel's `sigmask_check()' function */
				sys_sigmask_check();
				break;
			}
		}
	}
	return 0;
	{
		errno_t error;
do_legacy_sigprocmask:
		me->pt_pmask.lpm_pmask.pm_sigmask = NULL;
		error = sys_sigprocmask((syscall_ulong_t)(unsigned int)how,
		                         set, oset);
		return libc_seterrno_syserr(error);
	}
#else /* __LIBC_CONFIG_HAVE_USERPROCMASK */
	errno_t error;
	error = sys_sigprocmask((syscall_ulong_t)(unsigned int)how,
	                         set, oset);
	return libc_seterrno_syserr(error);
#endif /* !__LIBC_CONFIG_HAVE_USERPROCMASK */
}
/*[[[end:libc_sigprocmask]]]*/


#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
STATIC_ASSERT(sizeof(sigset_t) >= sizeof(void *));
#define FALLBACK_SIGMASKPTR(me) (*(struct __sigset_struct **)((byte_t *)(me) + __OFFSET_PTHREAD_PMASK + __OFFSET_USERPROCMASK_PENDING))
#define INITIAL_SIGMASKBUF(me)  ((me)->pt_pmask.lpm_masks[0])
#else /* __LIBC_CONFIG_HAVE_USERPROCMASK */
#define FALLBACK_SIGMASKPTR(me) (me)->pt_emumaskptr
#define INITIAL_SIGMASKBUF(me)  (me)->pt_emumask
#endif /* !__LIBC_CONFIG_HAVE_USERPROCMASK */

/*[[[head:libc_getsigmaskptr,hash:CRC-32=0x46aed0ec]]]*/
/* >> getsigmaskptr(3)
 * Return   the   current  signal   mask  pointer.
 * See the documentation of `setsigmaskptr(3)' for
 * what this function is all about.
 * @return: * : A pointer to the calling thread's current signal mask */
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_RETNONNULL WUNUSED sigset_t *
NOTHROW_NCX(LIBCCALL libc_getsigmaskptr)(void)
/*[[[body:libc_getsigmaskptr]]]*/
{
	sigset_t *result;
	struct pthread *me = &current;
#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
	result = me->pt_pmask.lpm_pmask.pm_sigmask;
	if unlikely(!result) {
		/* Lazily initialize the userprocmask sub-system. */
		result = &me->pt_pmask.lpm_masks[0];
		me->pt_pmask.lpm_pmask.pm_sigmask = result;
		if unlikely(sys_set_userprocmask_address(&me->pt_pmask.lpm_pmask) != -EOK)
			goto do_legacy_sigprocmask;
	}
	return result;
do_legacy_sigprocmask:
#endif /* __LIBC_CONFIG_HAVE_USERPROCMASK */
	result = FALLBACK_SIGMASKPTR(me);
	if (!result) {
		result = &INITIAL_SIGMASKBUF(me);
		FALLBACK_SIGMASKPTR(me) = result;
	}
	/* Read the current signal mask from the kernel. */
	if unlikely(sys_sigprocmask(0, NULL, result) != -EOK)
		sigemptyset(result);
	return result;
}
/*[[[end:libc_getsigmaskptr]]]*/

/*[[[head:libc_setsigmaskptr,hash:CRC-32=0xa9c00d13]]]*/
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
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_RETNONNULL NONNULL((1)) sigset_t *
NOTHROW_NCX(LIBCCALL libc_setsigmaskptr)(sigset_t *sigmaskptr)
/*[[[body:libc_setsigmaskptr]]]*/
{
	struct pthread *me = &current;
#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
	sigset_t *result;
	result = me->pt_pmask.lpm_pmask.pm_sigmask;
	if unlikely(!result) {
		/* Lazily initialize the userprocmask sub-system. */
		result = &me->pt_pmask.lpm_masks[0];
		me->pt_pmask.lpm_pmask.pm_sigmask = result;
		if unlikely(sys_set_userprocmask_address(&me->pt_pmask.lpm_pmask) != -EOK)
			goto do_legacy_sigprocmask;
	}
	/* Atomically switch over to the new signal mask. */
	ATOMIC_WRITE(me->pt_pmask.lpm_pmask.pm_sigmask, sigmaskptr);
	/* Check previously pending signals became available */
	{
		unsigned int i;
		for (i = 0; i < __SIGSET_NWORDS; ++i) {
			ulongptr_t pending_word;
			ulongptr_t newmask_word;
			pending_word = ATOMIC_READ(me->pt_pmask.lpm_pmask.pm_pending.__val[i]);
			if (!pending_word)
				continue; /* Nothing pending in here. */
			newmask_word = sigmaskptr->__val[i];
			/* Check if any of the pending signals are currently unmasked. */
			if ((pending_word & ~newmask_word) != 0) {
				/* Clear the set of pending signals (because the kernel won't do this)
				 * Also  note that  there is no  guaranty that the  signal that became
				 * available in the mean time is still available now. - The signal may
				 * have  been directed at  our process as a  whole, and another thread
				 * may have already handled it. */
				sigemptyset(&me->pt_pmask.lpm_pmask.pm_pending);
				/* Calls the kernel's `sigmask_check()' function */
				sys_sigmask_check();
				break;
			}
		}
	}
	return result;
do_legacy_sigprocmask:
#endif /* __LIBC_CONFIG_HAVE_USERPROCMASK */
	result = FALLBACK_SIGMASKPTR(me);
	if (!result)
		result = &INITIAL_SIGMASKBUF(me);
	FALLBACK_SIGMASKPTR(me) = sigmaskptr;
	/* Load the new signal mask into the kernel. */
	if unlikely(sys_sigprocmask(SIG_SETMASK, sigmaskptr, result) != -EOK)
		sigemptyset(result);
	return result;
}
/*[[[end:libc_setsigmaskptr]]]*/

/*[[[head:libc_setsigmaskfullptr,hash:CRC-32=0x305821b0]]]*/
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
INTERN ATTR_SECTION(".text.crt.sched.signal") ATTR_RETNONNULL sigset_t *
NOTHROW_NCX(LIBCCALL libc_setsigmaskfullptr)(void)
/*[[[body:libc_setsigmaskfullptr]]]*/
{
	static sigset_t const ss_full = __SIGSET_INIT((__ULONGPTR_TYPE__)-1);
	struct pthread *me            = &current;
#ifdef __LIBC_CONFIG_HAVE_USERPROCMASK
	sigset_t *result;
	result = me->pt_pmask.lpm_pmask.pm_sigmask;
	if unlikely(!result) {
		/* Lazily initialize the userprocmask sub-system. */
		result = &me->pt_pmask.lpm_masks[0];
		me->pt_pmask.lpm_pmask.pm_sigmask = result;
		if unlikely(sys_set_userprocmask_address(&me->pt_pmask.lpm_pmask) != -EOK)
			goto do_legacy_sigprocmask;
	}
	/* Atomically switch over to the new signal mask. */
	ATOMIC_WRITE(me->pt_pmask.lpm_pmask.pm_sigmask, (sigset_t *)&ss_full);
	/* No need to check if  anything because unmasked, since we  know
	 * that the new signal mask doesn't contain any unmasked signals! */
	return result;
do_legacy_sigprocmask:
#endif /* __LIBC_CONFIG_HAVE_USERPROCMASK */
	result = FALLBACK_SIGMASKPTR(me);
	if (!result)
		result = &INITIAL_SIGMASKBUF(me);
	FALLBACK_SIGMASKPTR(me) = (sigset_t *)&ss_full;
	/* Load the new signal mask into the kernel. */
	if unlikely(sys_sigprocmask(SIG_SETMASK, &ss_full, result) != -EOK)
		sigemptyset(result);
	return result;
}
/*[[[end:libc_setsigmaskfullptr]]]*/


/*[[[head:libc_sigsuspend,hash:CRC-32=0x7d1515b8]]]*/
/* >> sigsuspend(2)
 * Atomically save and  set the caller's  signal mask to  `set', then wait  for
 * one of the contained signals to arrive before restoring the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_sigsuspend)(sigset_t const *set)
/*[[[body:libc_sigsuspend]]]*/
{
	errno_t result;
#ifdef __NR_sigsuspend
	result = sys_sigsuspend(set);
#else /* __NR_sigsuspend */
	result = sys_rt_sigsuspend(set, sizeof(sigset_t));
#endif /* !__NR_sigsuspend */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigsuspend]]]*/

/*[[[head:libc_sigaction,hash:CRC-32=0x42476a3b]]]*/
/* >> sigaction(2)
 * Get/Set the  action that  shall  be performed  when  a
 * signal `signo' must be handled by the calling process.
 * This function will modifiy the caller's kernel-space signal handler descriptor,
 * who's shared/unshared behavior between threads is controlled by `CLONE_SIGHAND'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigaction)(signo_t signo,
                                     struct sigaction const *act,
                                     struct sigaction *oact)
/*[[[body:libc_sigaction]]]*/
{
	errno_t result;
#ifdef LIBC_ARCH_HAVE_SIG_RESTORE
	struct sigaction real_act;
	if (act && !(act->sa_flags & SA_RESTORER)) {
		memcpy(&real_act, act, sizeof(struct sigaction));
		SET_SIGRESTORE(real_act);
		act = &real_act;
	}
#endif /* LIBC_ARCH_HAVE_SIG_RESTORE */
#ifdef __NR_sigaction
	result = sys_sigaction(signo, act, oact);
#else /* __NR_sigaction */
	result = sys_rt_sigaction(signo, act, oact, sizeof(sigset_t));
#endif /* !__NR_sigaction */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigaction]]]*/

/*[[[head:libc_sigpending,hash:CRC-32=0x1ea4539]]]*/
/* >> sigpending(2)
 * Retrieve the set of signals that are pending
 * in  either  the calling  thread  and process
 * @return: 0: Success */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_NCX(LIBCCALL libc_sigpending)(sigset_t *__restrict set)
/*[[[body:libc_sigpending]]]*/
{
	errno_t result;
#ifdef __NR_sigpending
	result = sys_sigpending(set);
#else /* __NR_sigpending */
	result = sys_rt_sigpending(set, sizeof(sigset_t));
#endif /* !__NR_sigpending */
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigpending]]]*/

/*[[[head:libc_sigwait,hash:CRC-32=0xf676c990]]]*/
/* >> sigwait(3)
 * Same as `sigsuspend(2)', but write-back the actual signal that was raised to `*signo'
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1, 2)) int
NOTHROW_RPC(LIBCCALL libc_sigwait)(sigset_t const *__restrict set,
                                   signo_t *__restrict signo)
/*[[[body:libc_sigwait]]]*/
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
/*[[[end:libc_sigwait]]]*/

/*[[[head:libc_sigwaitinfo,hash:CRC-32=0x5ddcefd2]]]*/
/* >> sigwaitinfo(2)
 * Same as `sigsuspend(2)',  but write-back extended  information in the  signal,
 * as it would/has also been passed to a signal handler's second (info) argument.
 * @param: set:  The set of signals on which to wait
 * @param: info: Information about the signal on which to wait.
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_sigwaitinfo)(sigset_t const *__restrict set,
                                       siginfo_t *__restrict info)
/*[[[body:libc_sigwaitinfo]]]*/
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
/*[[[end:libc_sigwaitinfo]]]*/

/*[[[head:libc_sigtimedwait,hash:CRC-32=0x30cd6d43]]]*/
/* >> sigtimedwait(2), sigtimedwait64(2)
 * Same as `sigwaitinfo(2)', but stop waiting after a total of `rel_timeout' has passed
 * @param: set:         The set of signals on which to wait
 * @param: info:        Information about the signal on which to wait.
 * @param: rel_timeout: The timeout specifying for how long to wait (or `NULL' to wait indefinitely)
 * @return: -1: [errno=EINTR]  The signal handler for `signo' was executed.
 * @return: -1: [errno=EAGAIN] A total of `rel_timeout' has passed. */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_sigtimedwait)(sigset_t const *__restrict set,
                                        siginfo_t *__restrict info,
                                        struct timespec const *rel_timeout)
/*[[[body:libc_sigtimedwait]]]*/
{
	errno_t result;
	result = sys_rt_sigtimedwait(set,
	                             info,
	                             rel_timeout,
	                             sizeof(sigset_t));
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigtimedwait]]]*/

/*[[[head:libc_sigtimedwait64,hash:CRC-32=0x26c965df]]]*/
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
DEFINE_INTERN_ALIAS(libc_sigtimedwait64, libc_sigtimedwait);
#else /* MAGIC:alias */
/* >> sigtimedwait(2), sigtimedwait64(2)
 * Same as `sigwaitinfo(2)', but stop waiting after a total of `rel_timeout' has passed
 * @param: set:         The set of signals on which to wait
 * @param: info:        Information about the signal on which to wait.
 * @param: rel_timeout: The timeout specifying for how long to wait (or `NULL' to wait indefinitely)
 * @return: -1: [errno=EINTR]  The signal handler for `signo' was executed.
 * @return: -1: [errno=EAGAIN] A total of `rel_timeout' has passed. */
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((1)) int
NOTHROW_RPC(LIBCCALL libc_sigtimedwait64)(sigset_t const *__restrict set,
                                          siginfo_t *__restrict info,
                                          struct timespec64 const *rel_timeout)
/*[[[body:libc_sigtimedwait64]]]*/
{
	errno_t result;
#ifdef SYS_rt_sigtimedwait64
	result = sys_rt_sigtimedwait64(set,
	                               info,
	                               rel_timeout,
	                               sizeof(sigset_t));
#elif defined(SYS_rt_sigtimedwait_time64)
	result = sys_rt_sigtimedwait_time64(set,
	                                    info,
	                                    rel_timeout,
	                                    sizeof(sigset_t));
#else /* ... */
#error "No way to implement `sigtimedwait64()'"
#endif /* !... */
	return libc_seterrno_syserr(result);
}
#endif /* MAGIC:alias */
/*[[[end:libc_sigtimedwait64]]]*/

/*[[[head:libc_sigqueue,hash:CRC-32=0x60844282]]]*/
/* >> sigqueue(2)
 * Similar to  `kill(2)',  but  `pid'  must  be positive  and  reference  a  process's  PID,
 * meaning that this function can only be uesd to send a signal to single, specific process.
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
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigqueue)(pid_t pid,
                                    signo_t signo,
                                    union sigval const val)
/*[[[body:libc_sigqueue]]]*/
{
	siginfo_t info;
	memset(&info, 0, sizeof(siginfo_t));
	info.si_value = val;
	info.si_code  = SI_QUEUE;
	return sigqueueinfo(pid, signo, &info);
}
/*[[[end:libc_sigqueue]]]*/

/*[[[head:libc_sigqueueinfo,hash:CRC-32=0xbbf4d0ea]]]*/
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
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((3)) int
NOTHROW_NCX(LIBCCALL libc_sigqueueinfo)(pid_t pid,
                                        signo_t signo,
                                        siginfo_t const *uinfo)
/*[[[body:libc_sigqueueinfo]]]*/
{
	errno_t result;
	result = sys_rt_sigqueueinfo(pid,
	                             (syscall_ulong_t)(unsigned int)signo,
	                             uinfo);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigqueueinfo]]]*/

/*[[[head:libc_tgsigqueueinfo,hash:CRC-32=0x3077d25e]]]*/
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
INTERN ATTR_SECTION(".text.crt.sched.signal") NONNULL((4)) int
NOTHROW_NCX(LIBCCALL libc_tgsigqueueinfo)(pid_t pid,
                                          pid_t tid,
                                          signo_t signo,
                                          siginfo_t const *uinfo)
/*[[[body:libc_tgsigqueueinfo]]]*/
{
	errno_t result;
	result = sys_rt_tgsigqueueinfo(pid,
	                               tid,
	                               (syscall_ulong_t)(unsigned int)signo,
	                               uinfo);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_tgsigqueueinfo]]]*/

/*[[[head:libc_siginterrupt,hash:CRC-32=0x18f58b8f]]]*/
/* >> siginterrupt(3)
 * Set the `SA_RESTART' of the already-established signal handler for `signo',
 * as well as cause any future handler established by `bsd_signal()' or one of
 * its aliases to immediately be established with `SA_RESTART' set/cleared
 * @param: interrupt: When == 0: clear `SA_RESTART' for the signal handler of `signo'
 *                    When != 0: set `SA_RESTART'  for the signal handler of  `signo'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_siginterrupt)(signo_t signo,
                                        __STDC_INT_AS_UINT_T interrupt)
/*[[[body:libc_siginterrupt]]]*/
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
/*[[[end:libc_siginterrupt]]]*/

/*[[[head:libc_sigaltstack,hash:CRC-32=0x732220e5]]]*/
/* >> sigaltstack(2)
 * Get/Set the alternate signal stack for the calling thread. When set,
 * the alternate signal stack can be used to host signal handlers  that
 * have been established with the `SA_ONSTACK' flag in `sa_flags'.
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTERN ATTR_SECTION(".text.crt.sched.signal") int
NOTHROW_NCX(LIBCCALL libc_sigaltstack)(struct sigaltstack const *ss,
                                       struct sigaltstack *oss)
/*[[[body:libc_sigaltstack]]]*/
{
	errno_t result;
	result = sys_sigaltstack(ss, oss);
	return libc_seterrno_syserr(result);
}
/*[[[end:libc_sigaltstack]]]*/

/*[[[head:libc_pthread_kill,hash:CRC-32=0xccc0e8e7]]]*/
/* >> pthread_kill(3)
 * Portable function for sending a signal to a specific `pthread' within one's own process.
 * @return: EOK:    Success
 * @return: EINVAL: The given `signo' is invalid */
INTERN ATTR_SECTION(".text.crt.sched.signal") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_kill)(pthread_t pthread,
                                        signo_t signo)
/*[[[body:libc_pthread_kill]]]*/
{
	pid_t tid;
	errno_t result;
	tid = ATOMIC_READ(_pthread_tid(pthread));
	if unlikely(tid == 0)
		return ESRCH;
	/* No way to handle the case where `pt_tid' got set
	 * to  zero,  and  `tid'  got  re-used.  - Sorry... */
	result = sys_tkill(tid, signo);
	return -result;
}
/*[[[end:libc_pthread_kill]]]*/

/*[[[head:libc_pthread_sigqueue,hash:CRC-32=0x9c00ca3b]]]*/
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
INTERN ATTR_SECTION(".text.crt.sched.signal") errno_t
NOTHROW_NCX(LIBCCALL libc_pthread_sigqueue)(pthread_t pthread,
                                            signo_t signo,
                                            union sigval const val)
/*[[[body:libc_pthread_sigqueue]]]*/
{
	siginfo_t info;
	errno_t result;
	pid_t tid;
	memset(&info, 0, sizeof(siginfo_t));
	info.si_value = val;
	info.si_code  = SI_QUEUE;
	tid = ATOMIC_READ(_pthread_tid(pthread));
	if unlikely(tid == 0)
		return ESRCH;
	/* No way to handle the case where `pt_tid' got set
	 * to  zero,  and  `tid'  got  re-used.  - Sorry... */
	/* XXX: Do this without having to call `getpid()' ??? */
	result = sys_rt_tgsigqueueinfo(getpid(), tid, signo, &info);
	return -result;
}
/*[[[end:libc_pthread_sigqueue]]]*/


/*[[[impl:libc_signal]]]*/
/*[[[impl:libc_ssignal]]]*/
/*[[[impl:libc_gsignal]]]*/
/*[[[impl:libd_signal]]]*/
/*[[[impl:libd_ssignal]]]*/
/*[[[impl:libd_gsignal]]]*/
DEFINE_INTERN_ALIAS(libc_signal, libc_bsd_signal);
DEFINE_INTERN_ALIAS(libc_ssignal, libc_bsd_signal);
DEFINE_INTERN_ALIAS(libc_gsignal, libc_raise);
DEFINE_INTERN_ALIAS(libd_signal, libd_bsd_signal);
DEFINE_INTERN_ALIAS(libd_ssignal, libd_bsd_signal);
DEFINE_INTERN_ALIAS(libd_gsignal, libd_raise);



/*[[[start:exports,hash:CRC-32=0x875fcea2]]]*/
DEFINE_PUBLIC_ALIAS(DOS$raise, libd_raise);
DEFINE_PUBLIC_ALIAS(raise, libc_raise);
DEFINE_PUBLIC_ALIAS(DOS$__sysv_signal, libd_sysv_signal);
DEFINE_PUBLIC_ALIAS(DOS$sysv_signal, libd_sysv_signal);
DEFINE_PUBLIC_ALIAS(__sysv_signal, libc_sysv_signal);
DEFINE_PUBLIC_ALIAS(sysv_signal, libc_sysv_signal);
DEFINE_PUBLIC_ALIAS(DOS$_signal, libd_signal);
DEFINE_PUBLIC_ALIAS(DOS$signal, libd_signal);
DEFINE_PUBLIC_ALIAS(signal, libc_signal);
DEFINE_PUBLIC_ALIAS(DOS$ssignal, libd_ssignal);
DEFINE_PUBLIC_ALIAS(ssignal, libc_ssignal);
DEFINE_PUBLIC_ALIAS(DOS$gsignal, libd_gsignal);
DEFINE_PUBLIC_ALIAS(gsignal, libc_gsignal);
DEFINE_PUBLIC_ALIAS(__p_sys_siglist, libc___p_sys_siglist);
DEFINE_PUBLIC_ALIAS(sigreturn, libc_sigreturn);
DEFINE_PUBLIC_ALIAS(DOS$bsd_signal, libd_bsd_signal);
DEFINE_PUBLIC_ALIAS(bsd_signal, libc_bsd_signal);
DEFINE_PUBLIC_ALIAS(kill, libc_kill);
DEFINE_PUBLIC_ALIAS(pthread_sigmask, libc_sigprocmask);
DEFINE_PUBLIC_ALIAS(sigprocmask, libc_sigprocmask);
DEFINE_PUBLIC_ALIAS(getsigmaskptr, libc_getsigmaskptr);
DEFINE_PUBLIC_ALIAS(setsigmaskptr, libc_setsigmaskptr);
DEFINE_PUBLIC_ALIAS(setsigmaskfullptr, libc_setsigmaskfullptr);
DEFINE_PUBLIC_ALIAS(__sigsuspend, libc_sigsuspend);
DEFINE_PUBLIC_ALIAS(sigsuspend, libc_sigsuspend);
DEFINE_PUBLIC_ALIAS(__sigaction, libc_sigaction);
DEFINE_PUBLIC_ALIAS(sigaction, libc_sigaction);
DEFINE_PUBLIC_ALIAS(sigpending, libc_sigpending);
DEFINE_PUBLIC_ALIAS(sigwait, libc_sigwait);
DEFINE_PUBLIC_ALIAS(sigwaitinfo, libc_sigwaitinfo);
DEFINE_PUBLIC_ALIAS(sigtimedwait, libc_sigtimedwait);
DEFINE_PUBLIC_ALIAS(sigqueue, libc_sigqueue);
DEFINE_PUBLIC_ALIAS(sigtimedwait64, libc_sigtimedwait64);
DEFINE_PUBLIC_ALIAS(sigqueueinfo, libc_sigqueueinfo);
DEFINE_PUBLIC_ALIAS(tgsigqueueinfo, libc_tgsigqueueinfo);
DEFINE_PUBLIC_ALIAS(siginterrupt, libc_siginterrupt);
DEFINE_PUBLIC_ALIAS(sigaltstack, libc_sigaltstack);
DEFINE_PUBLIC_ALIAS(pthread_kill, libc_pthread_kill);
DEFINE_PUBLIC_ALIAS(pthread_sigqueue, libc_pthread_sigqueue);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_SIGNAL_C */
