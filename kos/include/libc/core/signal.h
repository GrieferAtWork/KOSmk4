/* HASH CRC-32:0xb83cdf84 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBC_CORE_SIGNAL_H
#define _LIBC_CORE_SIGNAL_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifndef ____libc_core_raise_defined
#define ____libc_core_raise_defined
#ifdef __CRT_HAVE_raise
#include <bits/types.h>
/* >> raise(3)
 * Raise a signal within the current thread.
 * In  a *-threaded process this is same as:
 *   *=multi:  `pthread_kill(pthread_self(), signo)'
 *   *=single: `kill(getpid(), signo)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
__CREDIRECT(,int,__NOTHROW_NCX,__libc_core_raise,(__signo_t __signo),raise,(__signo))
#elif ((defined(__CRT_HAVE_pthread_kill) || defined(__CRT_HAVE_thr_kill)) && (defined(__CRT_HAVE_pthread_self) || defined(__CRT_HAVE_thrd_current) || defined(__CRT_HAVE_thr_self))) || ((defined(__CRT_HAVE_kill) || defined(__CRT_HAVE___kill) || defined(__CRT_HAVE___libc_kill)) && (defined(__CRT_HAVE_getpid) || defined(__CRT_HAVE__getpid) || defined(__CRT_HAVE___getpid) || defined(__CRT_HAVE___libc_getpid)))
#include <libc/local/signal/raise.h>
/* >> raise(3)
 * Raise a signal within the current thread.
 * In  a *-threaded process this is same as:
 *   *=multi:  `pthread_kill(pthread_self(), signo)'
 *   *=single: `kill(getpid(), signo)'
 * @return: 0:  Success
 * @return: -1: [errno=EINVAL] The given `signo' is invalid */
#define __libc_core_raise __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(raise)
#else /* ... */
#undef ____libc_core_raise_defined
#endif /* !... */
#endif /* !____libc_core_raise_defined */
#ifdef __CRT_HAVE_sigfillset
#include <bits/os/sigset.h>
/* >> sigfillset(3)
 * Add all possible signals (possibly even including undefined signals,
 * though these would be ignored by the kernel) to the given signal set
 * @return: 0: Always returns `0' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__libc_core_sigfillset,(struct __sigset_struct *__set),sigfillset,(__set))
#else /* __CRT_HAVE_sigfillset */
#include <libc/local/signal/sigfillset.h>
/* >> sigfillset(3)
 * Add all possible signals (possibly even including undefined signals,
 * though these would be ignored by the kernel) to the given signal set
 * @return: 0: Always returns `0' */
#define __libc_core_sigfillset __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigfillset)
#endif /* !__CRT_HAVE_sigfillset */
#ifndef ____libc_core_sigprocmask_defined
#define ____libc_core_sigprocmask_defined
#ifdef __CRT_HAVE_sigprocmask
struct __sigset_struct;
#include <features.h>
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
__CREDIRECT(,int,__NOTHROW_NCX,__libc_core_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE___sigprocmask)
struct __sigset_struct;
#include <features.h>
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
__CREDIRECT(,int,__NOTHROW_NCX,__libc_core_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),__sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE___libc_sigprocmask)
struct __sigset_struct;
#include <features.h>
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
__CREDIRECT(,int,__NOTHROW_NCX,__libc_core_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),__libc_sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_pthread_sigmask)
struct __sigset_struct;
#include <features.h>
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
__CREDIRECT(,int,__NOTHROW_NCX,__libc_core_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),pthread_sigmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_thr_sigsetmask)
struct __sigset_struct;
#include <features.h>
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
__CREDIRECT(,int,__NOTHROW_NCX,__libc_core_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),thr_sigsetmask,(__how,__set,__oset))
#else /* ... */
#undef ____libc_core_sigprocmask_defined
#endif /* !... */
#endif /* !____libc_core_sigprocmask_defined */
#if !defined(____libc_core_getsigmaskptr_defined) && defined(__CRT_HAVE_getsigmaskptr)
#define ____libc_core_getsigmaskptr_defined
#include <bits/os/sigset.h>
/* >> getsigmaskptr(3)
 * Return   the   current  signal   mask  pointer.
 * See the documentation of `setsigmaskptr(3)' for
 * what this function is all about.
 * @return: * : A pointer to the calling thread's current signal mask */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED,struct __sigset_struct *,__NOTHROW_NCX,__libc_core_getsigmaskptr,(void),getsigmaskptr,())
#endif /* !____libc_core_getsigmaskptr_defined && __CRT_HAVE_getsigmaskptr */
#if !defined(____libc_core_setsigmaskptr_defined) && defined(__CRT_HAVE_setsigmaskptr)
#define ____libc_core_setsigmaskptr_defined
#include <bits/os/sigset.h>
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
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),struct __sigset_struct *,__NOTHROW_NCX,__libc_core_setsigmaskptr,(struct __sigset_struct *__sigmaskptr),setsigmaskptr,(__sigmaskptr))
#endif /* !____libc_core_setsigmaskptr_defined && __CRT_HAVE_setsigmaskptr */
#ifndef ____libc_core_setsigmaskfullptr_defined
#define ____libc_core_setsigmaskfullptr_defined
#ifdef __CRT_HAVE_setsigmaskfullptr
#include <bits/os/sigset.h>
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
__CREDIRECT(__ATTR_RETNONNULL,struct __sigset_struct *,__NOTHROW_NCX,__libc_core_setsigmaskfullptr,(void),setsigmaskfullptr,())
#elif defined(__CRT_HAVE_setsigmaskptr)
#include <libc/local/signal/setsigmaskfullptr.h>
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
#define __libc_core_setsigmaskfullptr __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(setsigmaskfullptr)
#else /* ... */
#undef ____libc_core_setsigmaskfullptr_defined
#endif /* !... */
#endif /* !____libc_core_setsigmaskfullptr_defined */
#ifdef __CRT_HAVE_sigisemptyset
#include <bits/os/sigset.h>
/* >> sigisemptyset(3)
 * Check if the given signal set is empty
 * @return: != 0: Yes, it is empty
 * @return: == 0: No, at least 1 signal is contained */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,__libc_core_sigisemptyset,(struct __sigset_struct const *__restrict __set),sigisemptyset,(__set))
#else /* __CRT_HAVE_sigisemptyset */
#include <libc/local/signal/sigisemptyset.h>
/* >> sigisemptyset(3)
 * Check if the given signal set is empty
 * @return: != 0: Yes, it is empty
 * @return: == 0: No, at least 1 signal is contained */
#define __libc_core_sigisemptyset __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigisemptyset)
#endif /* !__CRT_HAVE_sigisemptyset */

__SYSDECL_END

#endif /* __CC__ */

#endif /* !_LIBC_CORE_SIGNAL_H */
