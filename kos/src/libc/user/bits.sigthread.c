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
#ifndef GUARD_LIBC_USER_BITS_SIGTHREAD_C
#define GUARD_LIBC_USER_BITS_SIGTHREAD_C 1

#include "../api.h"
/**/

#include <hybrid/atomic.h>

#include <kos/syscalls.h>

#include <signal.h>
#include <string.h>

#include "../libc/pthread.h"
#include "bits.sigthread.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:pthread_sigmask,hash:CRC-32=0x7a19d7df]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_sigmask") int
NOTHROW_NCX(LIBCCALL libc_pthread_sigmask)(int how,
                                           sigset_t const *__restrict newmask,
                                           sigset_t *__restrict oldmask)
/*[[[body:pthread_sigmask]]]*/
{
	errno_t result;
#ifdef __NR_sigprocmask
	result = sys_sigprocmask((syscall_ulong_t)(unsigned int)how,
	                         newmask, oldmask);
#else /* __NR_sigprocmask */
	result = sys_rt_sigprocmask((syscall_ulong_t)(unsigned int)how,
	                            newmask, oldmask, sizeof(sigset_t));
#endif /* !__NR_sigprocmask */
	return -result;
}
/*[[[end:pthread_sigmask]]]*/

/*[[[head:pthread_kill,hash:CRC-32=0x60b7371f]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_kill") int
NOTHROW_NCX(LIBCCALL libc_pthread_kill)(pthread_t threadid,
                                        int signo)
/*[[[body:pthread_kill]]]*/
{
	struct pthread *pt = (struct pthread *)threadid;
	pid_t tid;
	errno_t result;
	tid = ATOMIC_READ(pt->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	/* No way to handle the case where `pt_tid' got set
	 * to zero, and `tid' got re-used. - Sorry... */
	result = sys_kill(tid, signo);
	return -result;
}
/*[[[end:pthread_kill]]]*/

/*[[[head:pthread_sigqueue,hash:CRC-32=0x9e96b219]]]*/
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.sched.pthread.pthread_sigqueue") int
NOTHROW_NCX(LIBCCALL libc_pthread_sigqueue)(pthread_t threadid,
                                            int signo,
                                            union sigval const value)
/*[[[body:pthread_sigqueue]]]*/
{
	struct pthread *pt = (struct pthread *)threadid;
	siginfo_t info;
	errno_t result;
	pid_t tid;
	memset(&info, 0, sizeof(siginfo_t));
	info.si_value = value;
	info.si_code  = SI_QUEUE;
	tid = ATOMIC_READ(pt->pt_tid);
	if unlikely(tid == 0)
		return ESRCH;
	/* No way to handle the case where `pt_tid' got set
	 * to zero, and `tid' got re-used. - Sorry... */
	result = sys_rt_sigqueueinfo(tid, signo, &info);
	return -result;
}
/*[[[end:pthread_sigqueue]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xc13f78d]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(pthread_sigmask, libc_pthread_sigmask);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_kill, libc_pthread_kill);
DEFINE_PUBLIC_WEAK_ALIAS(pthread_sigqueue, libc_pthread_sigqueue);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_BITS_SIGTHREAD_C */
