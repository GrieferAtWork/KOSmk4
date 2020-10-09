/* HASH CRC-32:0x1b4ab21b */
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
#ifndef __local_sigset_defined
#define __local_sigset_defined 1
#include <__crt.h>
#include <asm/os/signal.h>
#if defined(__SIG_ERR) && defined(__SIG_HOLD) && defined(__SIG_BLOCK) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask)) && (defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: sigaction from signal */
#ifndef __local___localdep_sigaction_defined
#define __local___localdep_sigaction_defined 1
#ifdef __CRT_HAVE_sigaction
__NAMESPACE_LOCAL_END
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
/* >> sigaction(2)
 * Get/Set the action that shall be performed when a
 * signal `signo' must be handled by the calling process.
 * This function will modifiy the caller's kernel-space signal handler descriptor,
 * who's shared/unshared behavior between threads is controlled by `CLONE_SIGHAND'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),sigaction,(__signo,__act,__oact))
#elif defined(__CRT_HAVE___sigaction)
__NAMESPACE_LOCAL_END
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
/* >> sigaction(2)
 * Get/Set the action that shall be performed when a
 * signal `signo' must be handled by the calling process.
 * This function will modifiy the caller's kernel-space signal handler descriptor,
 * who's shared/unshared behavior between threads is controlled by `CLONE_SIGHAND'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),__sigaction,(__signo,__act,__oact))
#else /* ... */
#undef __local___localdep_sigaction_defined
#endif /* !... */
#endif /* !__local___localdep_sigaction_defined */
/* Dependency: sigaddset from signal */
#ifndef __local___localdep_sigaddset_defined
#define __local___localdep_sigaddset_defined 1
#ifdef __CRT_HAVE_sigaddset
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0: Always returns `0' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sigaddset,(struct __sigset_struct *__set, __signo_t __signo),sigaddset,(__set,__signo))
#elif defined(__CRT_HAVE___sigaddset)
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0: Always returns `0' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sigaddset,(struct __sigset_struct *__set, __signo_t __signo),__sigaddset,(__set,__signo))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/signal/sigaddset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0: Always returns `0' */
#define __localdep_sigaddset __LIBC_LOCAL_NAME(sigaddset)
#endif /* !... */
#endif /* !__local___localdep_sigaddset_defined */
/* Dependency: sigemptyset from signal */
#ifndef __local___localdep_sigemptyset_defined
#define __local___localdep_sigemptyset_defined 1
#ifdef __CRT_HAVE_sigemptyset
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigemptyset(3)
 * Clear the given signal set of all contained signals
 * @return: 0: Always returns `0' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sigemptyset,(struct __sigset_struct *__set),sigemptyset,(__set))
#else /* __CRT_HAVE_sigemptyset */
__NAMESPACE_LOCAL_END
#include <libc/local/signal/sigemptyset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigemptyset(3)
 * Clear the given signal set of all contained signals
 * @return: 0: Always returns `0' */
#define __localdep_sigemptyset __LIBC_LOCAL_NAME(sigemptyset)
#endif /* !__CRT_HAVE_sigemptyset */
#endif /* !__local___localdep_sigemptyset_defined */
/* Dependency: sigismember from signal */
#ifndef __local___localdep_sigismember_defined
#define __local___localdep_sigismember_defined 1
#ifdef __CRT_HAVE_sigismember
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: != 0: The given `signo' is apart of `set'
 * @return: == 0: The given `signo' isn't apart of `set' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sigismember,(struct __sigset_struct const *__set, __signo_t __signo),sigismember,(__set,__signo))
#elif defined(__CRT_HAVE___sigismember)
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: != 0: The given `signo' is apart of `set'
 * @return: == 0: The given `signo' isn't apart of `set' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_sigismember,(struct __sigset_struct const *__set, __signo_t __signo),__sigismember,(__set,__signo))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/signal/sigismember.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigismember(3)
 * Check if a given `signo' is apart of the a given signal set
 * @return: != 0: The given `signo' is apart of `set'
 * @return: == 0: The given `signo' isn't apart of `set' */
#define __localdep_sigismember __LIBC_LOCAL_NAME(sigismember)
#endif /* !... */
#endif /* !__local___localdep_sigismember_defined */
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
 * states that this function behaves undefined in such szenarios.
 * However, on KOS, `pthread_sigmask()' is imply an alias for this
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
 * states that this function behaves undefined in such szenarios.
 * However, on KOS, `pthread_sigmask()' is imply an alias for this
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
#include <libc/errno.h>
#include <bits/os/sigaction.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigset(3)
 * Set the handler of `signo' to `disp', or add `signo' to
 * the calling threads's signal mask when `disp == SIG_HOLD'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__LOCAL_LIBC(sigset) __sighandler_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sigset))(__signo_t __signo, __sighandler_t __disp) {
	struct sigaction __act, __oact;
	struct __sigset_struct __set, __oset;
	if __unlikely(__disp == (__sighandler_t)__SIG_ERR)
		goto __err_inval;
	__localdep_sigemptyset(&__set);
	__localdep_sigaddset(&__set, __signo);
	if (__disp == (__sighandler_t)__SIG_HOLD) {
		if __unlikely(__localdep_sigprocmask(__SIG_BLOCK, &__set, &__oset) != 0)
			goto __err;
		if __unlikely(__localdep_sigismember(&__oset, __signo))
			goto __err;
		if __unlikely(__localdep_sigaction(__signo, __NULLPTR, &__oact) != 0)
			goto __err;
		return __oact.sa_handler;
	}
	__act.sa_handler = __disp;
	__localdep_sigemptyset(&__act.sa_mask);
	__act.sa_flags = 0;
	if __unlikely(__localdep_sigaction(__signo, &__act, &__oact) != 0)
		goto __err;
	if __unlikely(__localdep_sigprocmask(__SIG_UNBLOCK, &__set, &__oset) != 0)
		goto __err;
	return __localdep_sigismember(&__oset, __signo)
	       ? (__sighandler_t)__SIG_HOLD
	       : __oact.sa_handler;
__err_inval:
#ifdef __EINVAL
	__libc_seterrno(__EINVAL);
#else /* __EINVAL */
	__libc_seterrno(1);
#endif /* !__EINVAL */
__err:
	return (__sighandler_t)__SIG_ERR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigset_defined
#define __local___localdep_sigset_defined 1
#define __localdep_sigset __LIBC_LOCAL_NAME(sigset)
#endif /* !__local___localdep_sigset_defined */
#else /* __SIG_ERR && __SIG_HOLD && __SIG_BLOCK && (__CRT_HAVE_sigprocmask || __CRT_HAVE_pthread_sigmask) && (__CRT_HAVE_sigaction || __CRT_HAVE___sigaction) */
#undef __local_sigset_defined
#endif /* !__SIG_ERR || !__SIG_HOLD || !__SIG_BLOCK || (!__CRT_HAVE_sigprocmask && !__CRT_HAVE_pthread_sigmask) || (!__CRT_HAVE_sigaction && !__CRT_HAVE___sigaction) */
#endif /* !__local_sigset_defined */
