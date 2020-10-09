/* HASH CRC-32:0x1fa1cfba */
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
#ifndef __local_sigpause_defined
#define __local_sigpause_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_sigsuspend) || defined(__CRT_HAVE___sigsuspend)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
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
/* Dependency: sigsuspend from signal */
#ifndef __local___localdep_sigsuspend_defined
#define __local___localdep_sigsuspend_defined 1
#ifdef __CRT_HAVE_sigsuspend
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigsuspend(2)
 * Atomically save and set the caller's signal mask to `set', then wait for
 * one of the contained signals to arrive before restoring the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_sigsuspend,(struct __sigset_struct const *__set),sigsuspend,(__set))
#elif defined(__CRT_HAVE___sigsuspend)
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigsuspend(2)
 * Atomically save and set the caller's signal mask to `set', then wait for
 * one of the contained signals to arrive before restoring the old signal mask.
 * @param: set: The set of signals on which to wait
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_sigsuspend,(struct __sigset_struct const *__set),__sigsuspend,(__set))
#else /* ... */
#undef __local___localdep_sigsuspend_defined
#endif /* !... */
#endif /* !__local___localdep_sigsuspend_defined */
/* >> sigpause(3)
 * Atomically save and set the caller's signal mask to consist solely
 * of the signal signal `signo', then wait for that signal to arrive
 * before restoring the old signal mask.
 * @return: -1: [errno=EINTR] The signal handler for `signo' was executed. */
__LOCAL_LIBC(sigpause) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sigpause))(__signo_t __signo) {
	struct __sigset_struct __mask;
	__localdep_sigemptyset(&__mask);
	__localdep_sigaddset(&__mask, __signo);
	return __localdep_sigsuspend(&__mask);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigpause_defined
#define __local___localdep_sigpause_defined 1
#define __localdep_sigpause __LIBC_LOCAL_NAME(sigpause)
#endif /* !__local___localdep_sigpause_defined */
#else /* __CRT_HAVE_sigsuspend || __CRT_HAVE___sigsuspend */
#undef __local_sigpause_defined
#endif /* !__CRT_HAVE_sigsuspend && !__CRT_HAVE___sigsuspend */
#endif /* !__local_sigpause_defined */
