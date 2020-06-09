/* HASH CRC-32:0xdb1d8e8a */
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
#ifndef _SIGNAL_H
#define _SIGNAL_H 1

#ifdef _CXX_STDONLY_CSIGNAL
#ifdef __CXX_SYSTEM_HEADER
#undef _SIGNAL_H /* Allow the C-header to be re-included to import all std::-symbols into the global namespace. */
#else /* __CXX_SYSTEM_HEADER */
/* Import all symbols into the global namespace when re-including "signal.h" after "csignal" */
#ifndef __sig_atomic_t_defined
#define __sig_atomic_t_defined 1
__NAMESPACE_STD_USING(sig_atomic_t)
#endif /* !__sig_atomic_t_defined */
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
#ifdef __CRT_HAVE_raise
__NAMESPACE_STD_USING(raise)
#endif /* __CRT_HAVE_raise */
#if defined(__CRT_HAVE_sysv_signal) || defined(__CRT_HAVE_signal) || defined(__CRT_HAVE__signal)
__NAMESPACE_STD_USING(signal)
#endif /* __CRT_HAVE_sysv_signal || __CRT_HAVE_signal || __CRT_HAVE__signal */
#undef _CXX_STDONLY_CSIGNAL
#endif /* !__CXX_SYSTEM_HEADER */
#else /* _CXX_STDONLY_CSIGNAL */
#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <bits/signum.h>
#include <bits/sigset.h>

#ifdef __USE_POSIX199309
#include <bits/timespec.h>
#endif /* __USE_POSIX199309 */

#if defined(__USE_POSIX199309) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS)
#include <bits/siginfo.h>
#endif /* __USE_POSIX199309 || __USE_XOPEN_EXTENDED || __USE_KOS */

#ifdef __USE_POSIX
#include <bits/sigaction.h>
#endif /* __USE_POSIX */

#ifdef __USE_MISC
#include <bits/sigcontext.h>
#endif /* __USE_MISC */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#include <bits/sigstack.h>
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <sys/ucontext.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#if defined(__USE_POSIX199506) || defined(__USE_UNIX98)
#include <bits/pthreadtypes.h>
#include <bits/sigthread.h>
#endif /* __USE_POSIX199506 || __USE_UNIX98 */

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __std_sig_atomic_t_defined
#define __std_sig_atomic_t_defined 1
__NAMESPACE_STD_BEGIN
/* An integral type that can be modified atomically, without the
 * possibility of a signal arriving in the middle of the operation.  */
typedef __sig_atomic_t sig_atomic_t;
__NAMESPACE_STD_END
#endif /* !__std_sig_atomic_t_defined */
#ifndef __CXX_SYSTEM_HEADER
#ifndef __sig_atomic_t_defined
#define __sig_atomic_t_defined 1
__NAMESPACE_STD_USING(sig_atomic_t)
#endif /* !__sig_atomic_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifdef __USE_POSIX
#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef __sigset_t sigset_t;
#endif /* !__sigset_t_defined */
#endif /* __USE_POSIX */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */
#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifndef ____sighandler_t_defined
#define ____sighandler_t_defined 1
typedef void (__LIBCCALL *__sighandler_t)(int __signo);
#endif /* !____sighandler_t_defined */

#ifdef __USE_GNU
#ifndef __sighandler_t_defined
#define __sighandler_t_defined 1
typedef __sighandler_t sighandler_t;
#endif /* !__sighandler_t_defined */
#endif /* __USE_GNU */

#ifdef __USE_MISC
#ifndef NSIG
#define NSIG    _NSIG
#endif /* !NSIG */
typedef __sighandler_t sig_t;
#endif /* __USE_MISC */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

__NAMESPACE_STD_BEGIN
#ifdef __CRT_HAVE_raise
/* @param signo: One of `SIG*' */
__CDECLARE(,int,__NOTHROW_NCX,raise,(int __signo),(__signo))
#endif /* __CRT_HAVE_raise */
#ifdef __CRT_HAVE_sysv_signal
/* @param signo: One of `SIG*' */
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,signal,(int __signo, __sighandler_t __handler),sysv_signal,(__signo,__handler))
#elif defined(__CRT_HAVE_signal)
/* @param signo: One of `SIG*' */
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,signal,(int __signo, __sighandler_t __handler),(__signo,__handler))
#elif defined(__CRT_HAVE__signal)
/* @param signo: One of `SIG*' */
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,signal,(int __signo, __sighandler_t __handler),_signal,(__signo,__handler))
#endif /* ... */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
#ifdef __CRT_HAVE_raise
__NAMESPACE_STD_USING(raise)
#endif /* __CRT_HAVE_raise */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __CRT_HAVE_sysv_signal
/* @param signo: One of `SIG*' */
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,__sysv_signal,(int __signo, __sighandler_t __handler),sysv_signal,(__signo,__handler))
#elif defined(__CRT_HAVE___sysv_signal)
/* @param signo: One of `SIG*' */
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,__sysv_signal,(int __signo, __sighandler_t __handler),(__signo,__handler))
#endif /* ... */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_sysv_signal
/* @param signo: One of `SIG*' */
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,sysv_signal,(int __signo, __sighandler_t __handler),(__signo,__handler))
#elif defined(__CRT_HAVE___sysv_signal)
/* @param signo: One of `SIG*' */
__CREDIRECT(,__sighandler_t,__NOTHROW_NCX,sysv_signal,(int __signo, __sighandler_t __handler),__sysv_signal,(__signo,__handler))
#endif /* ... */
#endif /* __USE_GNU */
#ifndef __CXX_SYSTEM_HEADER
#if defined(__CRT_HAVE_sysv_signal) || defined(__CRT_HAVE_signal) || defined(__CRT_HAVE__signal)
__NAMESPACE_STD_USING(signal)
#endif /* __CRT_HAVE_sysv_signal || __CRT_HAVE_signal || __CRT_HAVE__signal */
#endif /* !__CXX_SYSTEM_HEADER */
#ifdef __USE_MISC
#define sigmask(signo) __sigmask(signo)
#ifdef __CRT_HAVE_ssignal
/* @param signo: One of `SIG*' */
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,ssignal,(int __signo, __sighandler_t __handler),(__signo,__handler))
#endif /* __CRT_HAVE_ssignal */
#ifdef __CRT_HAVE_gsignal
/* @param signo: One of `SIG*' */
__CDECLARE(,int,__NOTHROW_NCX,gsignal,(int __signo),(__signo))
#endif /* __CRT_HAVE_gsignal */
#ifdef __CRT_HAVE_sigblock
__CDECLARE(,int,__NOTHROW_NCX,sigblock,(int __mask),(__mask))
#endif /* __CRT_HAVE_sigblock */
#ifdef __CRT_HAVE_sigsetmask
__CDECLARE(,int,__NOTHROW_NCX,sigsetmask,(int __mask),(__mask))
#endif /* __CRT_HAVE_sigsetmask */
#ifdef __CRT_HAVE_siggetmask
__CDECLARE(,int,__NOTHROW_NCX,siggetmask,(void),())
#endif /* __CRT_HAVE_siggetmask */
#undef sys_siglist
#undef _sys_siglist
#if defined(__CRT_HAVE___p_sys_siglist)
#ifndef ____p_sys_siglist_defined
#define ____p_sys_siglist_defined 1
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED __ATTR_RETNONNULL,char const *const *,__NOTHROW_NCX,__p_sys_siglist,(void),())
#endif /* !____p_sys_siglist_defined */
#define _sys_siglist  __p_sys_siglist()
#define sys_siglist   __p_sys_siglist()
#elif defined(__CRT_HAVE_sys_siglist)
#if defined(__CRT_HAVE__sys_siglist) || !defined(__NO_ASMNAME)
__LIBC char const *const _sys_siglist[_NSIG] __ASMNAME("sys_siglist");
#else /* __CRT_HAVE__sys_siglist || !__NO_ASMNAME */
#define _sys_siglist  sys_siglist
#endif /* !__CRT_HAVE__sys_siglist && __NO_ASMNAME */
__LIBC char const *const sys_siglist[_NSIG];
#elif defined(__CRT_HAVE__sys_siglist)
#ifndef __NO_ASMNAME
__LIBC char const *const sys_siglist[_NSIG] __ASMNAME("_sys_siglist");
#else /* !__NO_ASMNAME */
#define sys_siglist     _sys_siglist
#endif /* __NO_ASMNAME */
__LIBC char const *const _sys_siglist[_NSIG];
#endif /* sys_siglist... */
struct sigcontext;
#ifdef __CRT_HAVE_sigreturn
__CDECLARE_VOID(__ATTR_NORETURN,__NOTHROW_NCX,sigreturn,(struct sigcontext const *__scp),(__scp))
#endif /* __CRT_HAVE_sigreturn */
#endif /* __USE_MISC */

#ifdef __USE_XOPEN
#ifdef __CRT_HAVE_bsd_signal
/* @param signo: One of `SIG*' */
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,bsd_signal,(int __signo, __sighandler_t __handler),(__signo,__handler))
#endif /* __CRT_HAVE_bsd_signal */
#ifdef __CRT_HAVE___xpg_sigpause
/* @param signo: One of `SIG*' */
__CREDIRECT(,int,__NOTHROW_NCX,sigpause,(int __signo),__xpg_sigpause,(__signo))
#endif /* __CRT_HAVE___xpg_sigpause */
#endif /* __USE_XOPEN */

#ifdef __USE_POSIX
#ifdef __CRT_HAVE_kill
/* @param signo: One of `SIG*' */
__CDECLARE(,int,__NOTHROW_NCX,kill,(__pid_t __pid, int __signo),(__pid,__signo))
#endif /* __CRT_HAVE_kill */
#ifdef __CRT_HAVE_sigemptyset
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigemptyset,(sigset_t *__set),(__set))
#else /* __CRT_HAVE_sigemptyset */
#include <local/signal/sigemptyset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigemptyset, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigemptyset)(sigset_t *__set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigemptyset))(__set); })
#endif /* !__CRT_HAVE_sigemptyset */
#ifdef __CRT_HAVE_sigfillset
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigfillset,(sigset_t *__set),(__set))
#else /* __CRT_HAVE_sigfillset */
#include <local/signal/sigfillset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigfillset, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigfillset)(sigset_t *__set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigfillset))(__set); })
#endif /* !__CRT_HAVE_sigfillset */
#ifdef __CRT_HAVE_sigaddset
/* @param signo: One of `SIG*' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigaddset,(sigset_t *__set, int __signo),(__set,__signo))
#elif defined(__CRT_HAVE___sigaddset)
/* @param signo: One of `SIG*' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigaddset,(sigset_t *__set, int __signo),__sigaddset,(__set,__signo))
#else /* ... */
#include <local/signal/sigaddset.h>
/* @param signo: One of `SIG*' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigaddset, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigaddset)(sigset_t *__set, int __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigaddset))(__set, __signo); })
#endif /* !... */
#ifdef __CRT_HAVE_sigdelset
/* @param signo: One of `SIG*' */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigdelset,(sigset_t *__set, int __signo),(__set,__signo))
#elif defined(__CRT_HAVE___sigdelset)
/* @param signo: One of `SIG*' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigdelset,(sigset_t *__set, int __signo),__sigdelset,(__set,__signo))
#else /* ... */
#include <local/signal/sigdelset.h>
/* @param signo: One of `SIG*' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigdelset, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigdelset)(sigset_t *__set, int __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigdelset))(__set, __signo); })
#endif /* !... */
#ifdef __CRT_HAVE_sigismember
/* @param signo: One of `SIG*' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigismember,(sigset_t const *__set, int __signo),(__set,__signo))
#elif defined(__CRT_HAVE___sigismember)
/* @param signo: One of `SIG*' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigismember,(sigset_t const *__set, int __signo),__sigismember,(__set,__signo))
#else /* ... */
#include <local/signal/sigismember.h>
/* @param signo: One of `SIG*' */
__NAMESPACE_LOCAL_USING_OR_IMPL(sigismember, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigismember)(sigset_t const *__set, int __signo) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigismember))(__set, __signo); })
#endif /* !... */
#ifdef __CRT_HAVE_sigprocmask
/* @param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK' */
__CDECLARE(,int,__NOTHROW_NCX,sigprocmask,(int __how, sigset_t const *__set, sigset_t *__oset),(__how,__set,__oset))
#endif /* __CRT_HAVE_sigprocmask */
#ifdef __CRT_HAVE_sigsuspend
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigsuspend,(sigset_t const *__set),(__set))
#elif defined(__CRT_HAVE___sigsuspend)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigsuspend,(sigset_t const *__set),__sigsuspend,(__set))
#endif /* ... */
#ifdef __CRT_HAVE_sigaction
/* @param signo: One of `SIG*' */
__CDECLARE(,int,__NOTHROW_NCX,sigaction,(int __signo, struct sigaction const *__act, struct sigaction *__oact),(__signo,__act,__oact))
#elif defined(__CRT_HAVE___sigaction)
/* @param signo: One of `SIG*' */
__CREDIRECT(,int,__NOTHROW_NCX,sigaction,(int __signo, struct sigaction const *__act, struct sigaction *__oact),__sigaction,(__signo,__act,__oact))
#endif /* ... */
#ifdef __CRT_HAVE_sigpending
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigpending,(sigset_t *__restrict __set),(__set))
#endif /* __CRT_HAVE_sigpending */
#ifdef __CRT_HAVE_sigwait
/* @param signo: One of `SIG*' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,sigwait,(sigset_t const *__restrict __set, int *__restrict __signo),(__set,__signo))
#endif /* __CRT_HAVE_sigwait */
#ifdef __USE_GNU
#ifdef __CRT_HAVE_sigisemptyset
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),int,__NOTHROW_NCX,sigisemptyset,(sigset_t const *__restrict __set),(__set))
#else /* __CRT_HAVE_sigisemptyset */
#include <local/signal/sigisemptyset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigisemptyset, __FORCELOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL sigisemptyset)(sigset_t const *__restrict __set) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigisemptyset))(__set); })
#endif /* !__CRT_HAVE_sigisemptyset */
#ifdef __CRT_HAVE_sigandset
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,sigandset,(sigset_t *__set, sigset_t const *__left, sigset_t const *__right),(__set,__left,__right))
#else /* __CRT_HAVE_sigandset */
#include <local/signal/sigandset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigandset, __FORCELOCAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL sigandset)(sigset_t *__set, sigset_t const *__left, sigset_t const *__right) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigandset))(__set, __left, __right); })
#endif /* !__CRT_HAVE_sigandset */
#ifdef __CRT_HAVE_sigorset
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_NCX,sigorset,(sigset_t *__set, sigset_t const *__left, sigset_t const *__right),(__set,__left,__right))
#else /* __CRT_HAVE_sigorset */
#include <local/signal/sigorset.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigorset, __FORCELOCAL __ATTR_NONNULL((1, 2, 3)) int __NOTHROW_NCX(__LIBCCALL sigorset)(sigset_t *__set, sigset_t const *__left, sigset_t const *__right) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigorset))(__set, __left, __right); })
#endif /* !__CRT_HAVE_sigorset */
#endif /* __USE_GNU */
#ifdef __USE_POSIX199309
#ifdef __CRT_HAVE_sigwaitinfo
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigwaitinfo,(sigset_t const *__restrict __set, siginfo_t *__restrict __info),(__set,__info))
#endif /* __CRT_HAVE_sigwaitinfo */
#if defined(__CRT_HAVE_sigtimedwait64) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigtimedwait,(sigset_t const *__restrict __set, siginfo_t *__restrict __info, struct timespec const *__timeout),sigtimedwait64,(__set,__info,__timeout))
#elif defined(__CRT_HAVE_sigtimedwait) && !defined(__USE_TIME_BITS64)
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigtimedwait,(sigset_t const *__restrict __set, siginfo_t *__restrict __info, struct timespec const *__timeout),(__set,__info,__timeout))
#elif defined(__CRT_HAVE_sigtimedwait) || defined(__CRT_HAVE_sigtimedwait64)
#include <local/signal/sigtimedwait.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigtimedwait, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL sigtimedwait)(sigset_t const *__restrict __set, siginfo_t *__restrict __info, struct timespec const *__timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigtimedwait))(__set, __info, __timeout); })
#endif /* ... */
#ifdef __CRT_HAVE_sigqueue
/* @param signo: One of `SIG*' */
__CDECLARE(,int,__NOTHROW_NCX,sigqueue,(__pid_t __pid, int __signo, union sigval const __val),(__pid,__signo,__val))
#endif /* __CRT_HAVE_sigqueue */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_sigtimedwait64
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigtimedwait64,(sigset_t const *__restrict __set, siginfo_t *__restrict __info, struct __timespec64 const *__timeout),(__set,__info,__timeout))
#elif defined(__CRT_HAVE_sigtimedwait) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,sigtimedwait64,(sigset_t const *__restrict __set, siginfo_t *__restrict __info, struct __timespec64 const *__timeout),sigtimedwait,(__set,__info,__timeout))
#elif defined(__CRT_HAVE_sigtimedwait)
#include <local/signal/sigtimedwait64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sigtimedwait64, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL sigtimedwait64)(sigset_t const *__restrict __set, siginfo_t *__restrict __info, struct __timespec64 const *__timeout) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sigtimedwait64))(__set, __info, __timeout); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_POSIX199309 */
#endif /* __USE_POSIX */

#ifdef __USE_KOS
#ifdef __CRT_HAVE_sigqueueinfo
/* @param signo: One of `SIG*' */
__CDECLARE(__ATTR_NONNULL((3)),int,__NOTHROW_NCX,sigqueueinfo,(__pid_t __tgid, int __signo, siginfo_t const *__uinfo),(__tgid,__signo,__uinfo))
#endif /* __CRT_HAVE_sigqueueinfo */
#ifdef __CRT_HAVE_tgsigqueueinfo
/* @param signo: One of `SIG*' */
__CDECLARE(__ATTR_NONNULL((4)),int,__NOTHROW_NCX,tgsigqueueinfo,(__pid_t __tgid, __pid_t __tid, int __signo, siginfo_t const *__uinfo),(__tgid,__tid,__signo,__uinfo))
#endif /* __CRT_HAVE_tgsigqueueinfo */
#endif /* __USE_KOS */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __CRT_HAVE_killpg
/* @param signo: One of `SIG*' */
__CDECLARE(,int,__NOTHROW_NCX,killpg,(__pid_t __pgrp, int __signo),(__pgrp,__signo))
#endif /* __CRT_HAVE_killpg */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_XOPEN2K8
#ifdef __CRT_HAVE_psignal
/* @param signo: One of `SIG*' */
__CDECLARE_VOID(,__NOTHROW_NCX,psignal,(int __signo, char const *__s),(__signo,__s))
#endif /* __CRT_HAVE_psignal */
#ifdef __CRT_HAVE_psiginfo
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,psiginfo,(siginfo_t const *__pinfo, char const *__s),(__pinfo,__s))
#endif /* __CRT_HAVE_psiginfo */
#endif /* __USE_XOPEN2K8 */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
#ifdef __CRT_HAVE_siginterrupt
/* @param signo: One of `SIG*' */
__CDECLARE(,int,__NOTHROW_NCX,siginterrupt,(int __signo, int __interrupt),(__signo,__interrupt))
#endif /* __CRT_HAVE_siginterrupt */
#ifdef __CRT_HAVE_sigstack
__CDECLARE(,int,__NOTHROW_NCX,sigstack,(struct sigstack *__ss, struct sigstack *__oss),(__ss,__oss))
#endif /* __CRT_HAVE_sigstack */
#ifdef __CRT_HAVE_sigaltstack
__CDECLARE(,int,__NOTHROW_NCX,sigaltstack,(struct sigaltstack const *__ss, struct sigaltstack *__oss),(__ss,__oss))
#endif /* __CRT_HAVE_sigaltstack */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

#ifdef __USE_XOPEN_EXTENDED
#ifdef __CRT_HAVE_sighold
/* @param signo: One of `SIG*' */
__CDECLARE(,int,__NOTHROW_NCX,sighold,(int __signo),(__signo))
#endif /* __CRT_HAVE_sighold */
#ifdef __CRT_HAVE_sigrelse
/* @param signo: One of `SIG*' */
__CDECLARE(,int,__NOTHROW_NCX,sigrelse,(int __signo),(__signo))
#endif /* __CRT_HAVE_sigrelse */
#ifdef __CRT_HAVE_sigignore
/* @param signo: One of `SIG*' */
__CDECLARE(,int,__NOTHROW_NCX,sigignore,(int __signo),(__signo))
#endif /* __CRT_HAVE_sigignore */
#ifdef __CRT_HAVE_sigset
/* @param signo: One of `SIG*' */
__CDECLARE(,__sighandler_t,__NOTHROW_NCX,sigset,(int __signo, __sighandler_t __disp),(__signo,__disp))
#endif /* __CRT_HAVE_sigset */
#endif /* __USE_XOPEN_EXTENDED */

#ifdef __CRT_HAVE___libc_current_sigrtmin
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__libc_current_sigrtmin,(void),())
#endif /* __CRT_HAVE___libc_current_sigrtmin */
#ifdef __CRT_HAVE___libc_current_sigrtmax
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__libc_current_sigrtmax,(void),())
#endif /* __CRT_HAVE___libc_current_sigrtmax */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __CXX_SYSTEM_HEADER
#define _CXX_STDONLY_CSIGNAL 1
#undef _SIGNAL_H
#endif /* __CXX_SYSTEM_HEADER */
#endif /* !_CXX_STDONLY_CSIGNAL */
#endif /* !_SIGNAL_H */
