/* HASH CRC-32:0x5995f1f3 */
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
#ifndef __local_sigsetmask_defined
#define __local_sigsetmask_defined 1
#include <__crt.h>
#include <asm/os/signal.h>
#if defined(__SIG_SETMASK) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask))
__NAMESPACE_LOCAL_BEGIN
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
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigsetmask(3)
 * Deprecated method of SIG_SETMASK-ing a given set of signals.
 * Modern code should use `sigprocmask(SIG_SETMASK)' instead.
 * @return: 0: Success */
__LOCAL_LIBC(sigsetmask) __ATTR_DEPRECATED("Using `sigprocmask()\' instead") int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sigsetmask))(int __mask) {
	struct __sigset_struct __sigset;
	__localdep_sigemptyset(&__sigset);
	__sigset.__val[0] = (__UINTPTR_TYPE__)(unsigned int)__mask;
	return __localdep_sigprocmask(__SIG_SETMASK, &__sigset, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigsetmask_defined
#define __local___localdep_sigsetmask_defined 1
#define __localdep_sigsetmask __LIBC_LOCAL_NAME(sigsetmask)
#endif /* !__local___localdep_sigsetmask_defined */
#else /* __SIG_SETMASK && (__CRT_HAVE_sigprocmask || __CRT_HAVE_pthread_sigmask) */
#undef __local_sigsetmask_defined
#endif /* !__SIG_SETMASK || (!__CRT_HAVE_sigprocmask && !__CRT_HAVE_pthread_sigmask) */
#endif /* !__local_sigsetmask_defined */
