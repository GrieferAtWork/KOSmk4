/* HASH CRC-32:0x4250efff */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_daemon_setup_defined
#define __local_daemon_setup_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_fork) || defined(__CRT_HAVE___fork) || defined(__CRT_HAVE___libc_fork)) && (defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE_exit)) && (defined(__CRT_HAVE_setsid) || defined(__CRT_HAVE___setsid) || defined(__CRT_HAVE___libc_setsid))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__Exit_defined
#define __local___localdep__Exit_defined
#if __has_builtin(__builtin__Exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__Exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,__localdep__Exit,(int __status),_Exit,{ __builtin__Exit(__status); })
#elif __has_builtin(__builtin__exit) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE__exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_NORETURN,void,__THROWING,__localdep__Exit,(int __status),_exit,{ __builtin__exit(__status); })
#elif defined(__CRT_HAVE__Exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),_Exit,(__status))
#elif defined(__CRT_HAVE__exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),_exit,(__status))
#elif defined(__CRT_HAVE_quick_exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),quick_exit,(__status))
#elif defined(__CRT_HAVE_exit)
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep__Exit,(int __status),exit,(__status))
#else /* ... */
#undef __local___localdep__Exit_defined
#endif /* !... */
#endif /* !__local___localdep__Exit_defined */
#ifndef __local___localdep_fork_defined
#define __local___localdep_fork_defined
#if __has_builtin(__builtin_fork) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fork)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),fork,{ return __builtin_fork(); })
#elif defined(__CRT_HAVE_fork)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),fork,())
#elif defined(__CRT_HAVE___fork)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),__fork,())
#elif defined(__CRT_HAVE___libc_fork)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED,__pid_t,__NOTHROW_NCX,__localdep_fork,(void),__libc_fork,())
#else /* ... */
#undef __local___localdep_fork_defined
#endif /* !... */
#endif /* !__local___localdep_fork_defined */
#ifndef __local___localdep_setsid_defined
#define __local___localdep_setsid_defined
#ifdef __CRT_HAVE_setsid
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__pid_t,__NOTHROW_NCX,__localdep_setsid,(void),setsid,())
#elif defined(__CRT_HAVE___setsid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__pid_t,__NOTHROW_NCX,__localdep_setsid,(void),__setsid,())
#elif defined(__CRT_HAVE___libc_setsid)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(,__pid_t,__NOTHROW_NCX,__localdep_setsid,(void),__libc_setsid,())
#else /* ... */
#undef __local___localdep_setsid_defined
#endif /* !... */
#endif /* !__local___localdep_setsid_defined */
#ifndef __local___localdep_sigaction_defined
#define __local___localdep_sigaction_defined
#ifdef __CRT_HAVE_sigaction
__NAMESPACE_LOCAL_END
#include <bits/types.h>
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),sigaction,(__signo,__act,__oact))
#elif defined(__CRT_HAVE___sigaction)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),__sigaction,(__signo,__act,__oact))
#else /* ... */
#undef __local___localdep_sigaction_defined
#endif /* !... */
#endif /* !__local___localdep_sigaction_defined */
#ifndef __local___localdep_sigemptyset_defined
#define __local___localdep_sigemptyset_defined
#ifdef __CRT_HAVE_sigemptyset
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_sigemptyset,(struct __sigset_struct *__set),sigemptyset,(__set))
#else /* __CRT_HAVE_sigemptyset */
__NAMESPACE_LOCAL_END
#include <libc/local/signal/sigemptyset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sigemptyset __LIBC_LOCAL_NAME(sigemptyset)
#endif /* !__CRT_HAVE_sigemptyset */
#endif /* !__local___localdep_sigemptyset_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/sigaction.h>
#include <asm/os/signal.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(daemon_setup) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(daemon_setup))(void) {
	int __result;
#if (defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)) && defined(__SIG_IGN) && defined(__SIGHUP)
	int __has_old_sa;
	struct sigaction __new_sa, __old_sa;
	/* To quote POSIX (on `_Exit(2)'):
	 * """
	 * If the process  is a controlling  process, the  SIGHUP
	 * signal shall be sent to each process in the foreground
	 * process group  of the  controlling terminal  belonging
	 * to the calling process.
	 * """
	 * In other words: if our process is both the controlling
	 * process, as  well as  part of  the foreground  process
	 * group,  meaning that  our child  will also  be of said
	 * group, then it would be sent a SIGHUP which might even
	 * kill it. To prevent this from happening, ignore SIGHUP
	 * while we pass  kill ourselves and  spawn a new  child! */
	(__NAMESPACE_LOCAL_SYM __localdep_sigemptyset)(&__new_sa.sa_mask);
	__new_sa.sa_handler = (__sighandler_t)__SIG_IGN;
	__new_sa.sa_flags   = 0;
	__has_old_sa = (__NAMESPACE_LOCAL_SYM __localdep_sigaction)(__SIGHUP, &__new_sa, &__old_sa);
#endif /* (__CRT_HAVE_sigaction || __CRT_HAVE___sigaction) && __SIG_IGN && __SIGHUP */
	{
		__pid_t __cpid = (__NAMESPACE_LOCAL_SYM __localdep_fork)();
		if __unlikely(__cpid < 0)
			return __cpid;
		if (__cpid != 0)
			(__NAMESPACE_LOCAL_SYM __localdep__Exit)(0); /* The parent process dies. */
	}
	__result = (__NAMESPACE_LOCAL_SYM __localdep_setsid)();
#if (defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction)) && defined(__SIG_IGN) && defined(__SIGHUP)
	if (__has_old_sa == 0)
		(__NAMESPACE_LOCAL_SYM __localdep_sigaction)(__SIGHUP, &__old_sa, __NULLPTR);
#endif /* (__CRT_HAVE_sigaction || __CRT_HAVE___sigaction) && __SIG_IGN && __SIGHUP */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_daemon_setup_defined
#define __local___localdep_daemon_setup_defined
#define __localdep_daemon_setup __LIBC_LOCAL_NAME(daemon_setup)
#endif /* !__local___localdep_daemon_setup_defined */
#else /* (__CRT_HAVE_fork || __CRT_HAVE___fork || __CRT_HAVE___libc_fork) && (__CRT_HAVE__Exit || __CRT_HAVE__exit || __CRT_HAVE_quick_exit || __CRT_HAVE_exit) && (__CRT_HAVE_setsid || __CRT_HAVE___setsid || __CRT_HAVE___libc_setsid) */
#undef __local_daemon_setup_defined
#endif /* (!__CRT_HAVE_fork && !__CRT_HAVE___fork && !__CRT_HAVE___libc_fork) || (!__CRT_HAVE__Exit && !__CRT_HAVE__exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE_exit) || (!__CRT_HAVE_setsid && !__CRT_HAVE___setsid && !__CRT_HAVE___libc_setsid) */
#endif /* !__local_daemon_setup_defined */
