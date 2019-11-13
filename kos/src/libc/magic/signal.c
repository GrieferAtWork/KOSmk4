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

%[define_ccompat_header(csignal)]
%[define_replacement(sighandler_t = __sighandler_t)]
%[define_replacement(sigset_t     = struct __sigset_struct)]
%[define_replacement(pid_t        = __pid_t)]
%[define_replacement(timespec32   = __timespec32)]
%[define_replacement(timespec64   = __timespec64)]
%[default_impl_section({.text.crt.sched.signal|.text.crt.dos.sched.signal})]

%(user){
DECL_END
#include <bits/sigaction.h>
DECL_BEGIN

#ifndef __sighandler_t_defined
#define __sighandler_t_defined 1
typedef __sighandler_t sighandler_t;
#endif /* !__sighandler_t_defined */

}

%{
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
}%(c, ccompat){
#ifndef __sig_atomic_t_defined
#define __sig_atomic_t_defined 1
__NAMESPACE_STD_USING(sig_atomic_t)
#endif /* !__sig_atomic_t_defined */
}%{
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

}%(c, ccompat){
#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
}%{
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */
}%(c, ccompat){
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */
}%{

}

%[insert:std]

@@@param signo: One of `SIG*'
[std][dos_variant] raise:(int signo) -> int;

@@@param signo: One of `SIG*'
__sysv_signal:(int signo, $sighandler_t handler) -> $sighandler_t = sysv_signal;

%#ifdef __USE_GNU
@@@param signo: One of `SIG*'
[alias(__sysv_signal)] sysv_signal:(int signo, $sighandler_t handler) -> $sighandler_t;
%#endif /* __USE_GNU */


@@@param signo: One of `SIG*'
[std][preferred_alias(sysv_signal)][alias(_signal)][dos_variant]
signal:(int signo, $sighandler_t handler) -> $sighandler_t;

%#ifdef __USE_MISC
%#define sigmask(signo)    __sigmask(signo)

@@@param signo: One of `SIG*'
ssignal:(int signo, $sighandler_t handler) -> $sighandler_t;

@@@param signo: One of `SIG*'
gsignal:(int signo) -> int;

%#if 1
sigblock:(int mask) -> int;
sigsetmask:(int mask) -> int;
siggetmask:(void) -> int;
%#else
[nouser][ATTR_DEPRECATED("Using `sigprocmask()' instead")] sigblock:(int mask) -> int;
[nouser][ATTR_DEPRECATED("Using `sigprocmask()' instead")] sigsetmask:(int mask) -> int;
[nouser][ATTR_DEPRECATED("Using `sigprocmask()' instead")] siggetmask:(void) -> int;
%#endif

%{
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
}

%struct sigcontext;
[ATTR_NORETURN] sigreturn:(struct sigcontext const *scp);

%#endif /* __USE_MISC */
%
%#ifdef __USE_XOPEN

@@@param signo: One of `SIG*'
bsd_signal:(int signo, $sighandler_t handler) -> $sighandler_t;

@@@param signo: One of `SIG*'
sigpause:(int signo)-> int = __xpg_sigpause?;

%#endif /* __USE_XOPEN */
%
%#ifdef __USE_POSIX

@@@param signo: One of `SIG*'
kill:($pid_t pid, int signo) -> int;

[decl_include(<bits/sigset.h>)]
sigemptyset:([nonnull] sigset_t *set) -> int {
	size_t cnt;
	cnt = sizeof(__sigset_t) / sizeof(__ULONGPTR_TYPE__);
	while (cnt--)
		set->@__val@[cnt] = 0;
	return 0;
}
[decl_include(<bits/sigset.h>)]
sigfillset:([nonnull] sigset_t *set) -> int {
	size_t cnt;
	cnt = sizeof(__sigset_t) / sizeof(__ULONGPTR_TYPE__);
	while (cnt--)
		set->@__val@[cnt] = ~0ul;
	return 0;
}

@@@param signo: One of `SIG*'
[decl_include(<bits/sigset.h>)][alias(__sigaddset)]
sigaddset:([nonnull] sigset_t *set, int signo) -> int {
	__ULONGPTR_TYPE__ mask = @__sigmask@(signo);
	__ULONGPTR_TYPE__ word = @__sigword@(signo);
	set->@__val@[word] |= mask;
	return 0;
}

@@@param signo: One of `SIG*'
[decl_include(<bits/sigset.h>)][alias(__sigdelset)]
sigdelset:([nonnull] sigset_t *set, int signo) -> int {
	__ULONGPTR_TYPE__ mask = @__sigmask@(signo);
	__ULONGPTR_TYPE__ word = @__sigword@(signo);
	set->@__val@[word] &= ~mask;
	return 0;
}

@@@param signo: One of `SIG*'
[decl_include(<bits/sigset.h>)]
[ATTR_WUNUSED][ATTR_PURE][alias(__sigismember)]
sigismember:([nonnull] sigset_t const *set, int signo) -> int {
	__ULONGPTR_TYPE__ mask = @__sigmask@(signo);
	__ULONGPTR_TYPE__ word = @__sigword@(signo);
	return (set->@__val@[word] & mask) != 0;
}

@@@param how: One of `SIG_BLOCK', `SIG_UNBLOCK' or `SIG_SETMASK'
sigprocmask:(int how, sigset_t const *__restrict set, sigset_t *__restrict oset) -> int;

[cp][export_alias(__sigsuspend)]
sigsuspend:([nonnull] sigset_t const *set) -> int;

@@@param signo: One of `SIG*'
[export_alias(__sigaction)]
sigaction:(int signo, struct sigaction const *__restrict act, struct sigaction *__restrict oact) -> int;

sigpending:([nonnull] sigset_t *set) -> int;

@@@param signo: One of `SIG*'
[cp] sigwait:([nonnull] sigset_t const *__restrict set, [nonnull] int *__restrict signo) -> int;

%#ifdef __USE_GNU
[decl_include(<bits/sigset.h>)][ATTR_WUNUSED][ATTR_PURE]
sigisemptyset:([nonnull] sigset_t const *set) -> int {
	size_t i;
	for (i = 0; i < sizeof(sigset_t) / sizeof(__ULONGPTR_TYPE__); ++i)
		if (set->@__val@[i])
			return 0;
	return 1;
}
[decl_include(<bits/sigset.h>)]
sigandset:([nonnull] sigset_t *set,
           [nonnull] sigset_t const *left,
           [nonnull] sigset_t const *right) -> int {
	size_t i;
	for (i = 0; i < sizeof(__sigset_t) / sizeof(__ULONGPTR_TYPE__); ++i)
		set->@__val@[i] = left->@__val@[i] & right->@__val@[i];
	return 0;
}

[decl_include(<bits/sigset.h>)]
sigorset:([nonnull] sigset_t *set,
          [nonnull] sigset_t const *left,
          [nonnull] sigset_t const *right) -> int {
	size_t i;
	for (i = 0; i < sizeof(__sigset_t) / sizeof(__ULONGPTR_TYPE__); ++i)
		set->@__val@[i] = left->@__val@[i] | right->@__val@[i];
	return 0;
}
%#endif /* __USE_GNU */

%#ifdef __USE_POSIX199309
[cp] sigwaitinfo:([nonnull] sigset_t const *__restrict set, [nullable] siginfo_t *__restrict info) -> int;

[cp][ignore]
sigtimedwait32:([nonnull] sigset_t const *__restrict set, [nullable] siginfo_t *__restrict info, [nullable] struct $timespec32 const *timeout) -> int = sigtimedwait?;

[cp][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(sigtimedwait64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(sigtimedwait)]
[requires(defined(__CRT_HAVE_sigtimedwait) || defined(__CRT_HAVE_sigtimedwait64))]
sigtimedwait:([nonnull] sigset_t const *__restrict set,
              [nullable] siginfo_t *__restrict info,
              [nullable] struct timespec const *timeout) -> int {
#ifdef __CRT_HAVE_sigtimedwait64
	struct timespec64 tmv;
	if (!timeout)
		return sigtimedwait64(set, info, NULL);
	tmv.@tv_sec@  = (__time64_t)timeout->@tv_sec@;
	tmv.@tv_nsec@ = timeout->@tv_nsec@;
	return sigtimedwait64(set, info, NULL);
#else /* __CRT_HAVE_sigtimedwait64 */
	struct timespec32 tmv;
	if (!timeout)
		return sigtimedwait32(set, info, NULL);
	tmv.@tv_sec@  = (__time32_t)timeout->@tv_sec@;
	tmv.@tv_nsec@ = timeout->@tv_nsec@;
	return sigtimedwait32(set, info, NULL);
#endif /* !__CRT_HAVE_sigtimedwait64 */
}

@@@param signo: One of `SIG*'
sigqueue:($pid_t pid, int signo, union sigval const val) -> int;

%#ifdef __USE_TIME64

[time64_variant_of(sigtimedwait)]
[cp][noexport][requires(defined(__CRT_HAVE_sigtimedwait))]
sigtimedwait64:([nonnull] sigset_t const *__restrict set,
                [nullable] siginfo_t *__restrict info,
                [nullable] struct $timespec64 const *timeout) -> int {
	struct timespec32 tmv;
	if (!timeout)
		return sigtimedwait32(set, info, NULL);
	tmv.@tv_sec@  = (__time32_t)timeout->@tv_sec@;
	tmv.@tv_nsec@ = timeout->@tv_nsec@;
	return sigtimedwait32(set, info, NULL);
}

%#endif /* __USE_TIME64 */
%#endif /* __USE_POSIX199309 */
%#endif /* __USE_POSIX */

%
%#ifdef __USE_KOS
@@@param signo: One of `SIG*'
sigqueueinfo:($pid_t tgid, int signo, siginfo_t const *uinfo) -> int;

@@@param signo: One of `SIG*'
tgsigqueueinfo:($pid_t tgid, $pid_t tid, int signo, siginfo_t const *uinfo) -> int;
%#endif /* __USE_KOS */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
@@@param signo: One of `SIG*'
killpg:($pid_t pgrp, int signo) -> int;
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#ifdef __USE_XOPEN2K8
@@@param signo: One of `SIG*'
psignal:(int signo, char const *s);

psiginfo:(siginfo_t const *pinfo, char const *s);
%#endif /* __USE_XOPEN2K8 */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
@@@param signo: One of `SIG*'
siginterrupt:(int signo, int interrupt) -> int;

sigstack:(struct sigstack *ss, struct sigstack *oss) -> int;
sigaltstack:(struct sigaltstack const *__restrict ss, struct sigaltstack *__restrict oss) -> int;
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

%
%#ifdef __USE_XOPEN_EXTENDED
@@@param signo: One of `SIG*'
sighold:(int signo) -> int;
@@@param signo: One of `SIG*'
sigrelse:(int signo) -> int;
@@@param signo: One of `SIG*'
sigignore:(int signo) -> int;
@@@param signo: One of `SIG*'
sigset:(int signo, $sighandler_t disp) -> $sighandler_t;
%#endif /* __USE_XOPEN_EXTENDED */
%

[ATTR_CONST] __libc_current_sigrtmin:(void) -> int;
[ATTR_CONST] __libc_current_sigrtmax:(void) -> int;



%{

#endif /* __CC__ */

__SYSDECL_END

}