/* HASH CRC-32:0xfa32b28a */
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
#ifndef __local_siggetmask_defined
#define __local_siggetmask_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: sigprocmask from signal */
#ifndef __local___localdep_sigprocmask_defined
#define __local___localdep_sigprocmask_defined 1
#ifdef __CRT_HAVE_sigprocmask
__NAMESPACE_LOCAL_END
#include <features.h>
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
/* Change the signal mask for the calling thread. Note that portable
 * programs that also make use of multithreading must instead use the
 * pthread-specific `pthread_sigmask()' function instead, as POSIX
 * states that this function behaves undefined in such scenarios.
 * However, on KOS, `pthread_sigmask()' is simply an alias for this
 * function, and `sigprocmask()' always operates thread-local.
 * Note also that on KOS 2 additional functions `getsigmaskptr()'
 * and `setsigmaskptr()' exist, which can be used to get/set the
 * address of the signal mask used by the kernel.
 * @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] Invalid `how' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_pthread_sigmask)
__NAMESPACE_LOCAL_END
#include <features.h>
struct __sigset_struct;
__NAMESPACE_LOCAL_BEGIN
/* Change the signal mask for the calling thread. Note that portable
 * programs that also make use of multithreading must instead use the
 * pthread-specific `pthread_sigmask()' function instead, as POSIX
 * states that this function behaves undefined in such scenarios.
 * However, on KOS, `pthread_sigmask()' is simply an alias for this
 * function, and `sigprocmask()' always operates thread-local.
 * Note also that on KOS 2 additional functions `getsigmaskptr()'
 * and `setsigmaskptr()' exist, which can be used to get/set the
 * address of the signal mask used by the kernel.
 * @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] Invalid `how' */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),pthread_sigmask,(__how,__set,__oset))
#else /* ... */
#undef __local___localdep_sigprocmask_defined
#endif /* !... */
#endif /* !__local___localdep_sigprocmask_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/signal.h>
#include <bits/os/sigset.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigsetmask(3)
 * Deprecated method of retrieving the masking-state of
 * the lowest-numberred `sizeof(int) * NBBY - 1' signals.
 * @return: <= INT_MAX: An incomplete signal mask bitset for a couple
 *                      of the lowest-numbered couple of signal.
 * @return: -1:         Error */
__LOCAL_LIBC(siggetmask) __ATTR_DEPRECATED("Using `sigprocmask()\' instead") int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(siggetmask))(void) {
	struct __sigset_struct __sigset;
#ifdef __SIG_SETMASK
	if (__localdep_sigprocmask(__SIG_SETMASK, __NULLPTR, &__sigset))
		return -1;
#else /* __SIG_SETMASK */
	if (__localdep_sigprocmask(0, __NULLPTR, &__sigset))
		return -1;
#endif /* !__SIG_SETMASK */
	return __sigset.__val[0] & __INT_MAX__;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_siggetmask_defined
#define __local___localdep_siggetmask_defined 1
#define __localdep_siggetmask __LIBC_LOCAL_NAME(siggetmask)
#endif /* !__local___localdep_siggetmask_defined */
#else /* __CRT_HAVE_sigprocmask || __CRT_HAVE_pthread_sigmask */
#undef __local_siggetmask_defined
#endif /* !__CRT_HAVE_sigprocmask && !__CRT_HAVE_pthread_sigmask */
#endif /* !__local_siggetmask_defined */
